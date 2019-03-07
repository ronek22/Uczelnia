package Projekt1;



import guru.nidi.graphviz.attribute.Color;
import guru.nidi.graphviz.attribute.Shape;
import guru.nidi.graphviz.attribute.Style;
import guru.nidi.graphviz.engine.Format;
import guru.nidi.graphviz.engine.Graphviz;
import guru.nidi.graphviz.model.Graph;
import guru.nidi.graphviz.model.Label;
import guru.nidi.graphviz.model.MutableGraph;
import guru.nidi.graphviz.model.Node;
import guru.nidi.graphviz.model.Factory.*;
import guru.nidi.graphviz.parse.*;

import java.io.File;
import java.io.IOException;
import java.io.PrintWriter;
import java.util.*;

import static guru.nidi.graphviz.model.Factory.*;

public class TaskOrganizer {

    private ArrayList<Task> tasks;
    private ArrayList<Task> criticalPath;
    private int criticalPathTime;

    private static TaskOrganizer ourInstance = new TaskOrganizer();
    public static TaskOrganizer getInstance() {
        return ourInstance;
    }
    private TaskOrganizer() {
        tasks = new ArrayList<>();
        criticalPath = new ArrayList<>();
    }

    public void addTask(int number, int duration){
        tasks.add(new Task(number, duration));
    }

    public void connect(int prevNo, int nextNo){
        if(prevNo >= nextNo) throw new IllegalArgumentException("Pierwszy zadanie musi byc wczesniejesz niz drugie");
        Task prev = getTaskNo(prevNo);
        Task next = getTaskNo(nextNo);

        if(prev == null || next == null){
            throw new IllegalArgumentException("Jednego z zadan nie ma na liscie");
        }

        prev.addNextTasks(next);
        next.addPrevTasks(prev);
    }

    public Task getTaskNo(int number){
        for(Task task : tasks)
            if(task.getNumber() == number) return task;

        return null;
    }

    public void calcTimes(){
        for(Task task : tasks){
            // Jesli zadanie nie jest od niczego zalezne to startuje w chwili 0
            if(task.getPrevTasks().isEmpty()){
                task.setStartTime(0);
                task.setFinishTime(task.getDuration());
            } else {
                int maxFinishTime = task.getPrevTasks().stream()
                        .max(Comparator.comparingInt(Task::getFinishTime))
                        .get().getFinishTime();

                task.setStartTime(maxFinishTime);
                task.setFinishTime(task.getStartTime() + task.getDuration());
            }
        }
    }

    private void makeCriticalPath(ArrayList<Task> path){
        // rekurencyjnie, bierzemy od konca po kolei taski z najwiekszym czasem zakonczenia
        Task lastTask = path.stream()
                .max(Comparator.comparingInt(Task::getFinishTime))
                .get();

        criticalPath.add(lastTask);
        if(!lastTask.getPrevTasks().isEmpty())
            makeCriticalPath(lastTask.getPrevTasks());
    }

    public void CPM(){
        makeCriticalPath(tasks);
        criticalPathTime = criticalPath.get(0).getFinishTime();
        Collections.reverse(criticalPath);

        System.out.print("KRYTYCZNA SCIEZKA: ");

        for(Task task : criticalPath)
            System.out.print("Z" + task.getNumber() + " ");

        System.out.println("\nCZAS KRYTYCZNEJ SCIEZKI: " + criticalPathTime);
    }



    public ArrayList<Task> getAllTasks(){ return tasks;}
    public ArrayList<Task> getCriticalPath(){ return criticalPath;}

    public void display(){
        System.out.printf("%6s | %6s | %6s | %6s | %-13s | %-13s\n", "ZAD", "CZAS", "START", "END", "POPRZEDNICY", "NASTEPNICY");
        for(Task task : tasks){
            System.out.println(task);
        }

        System.out.println("================================================================");
    }


    public void saveGraph() throws IOException {

        String begin = "digraph G {\n";
        String body;
        String end = " }";

        body = graphCreator(tasks, "");
        String graphFileContent = begin + body + end;

        MutableGraph g = Parser.read(graphFileContent);
        Graphviz.fromGraph(g).width(700).render(Format.PNG).toFile(new File("example/graph.png"));


    }

    private String graphCreator(ArrayList<Task> tasksToGraph, String result)
    {
        for (Task task : tasksToGraph) {
            if(!task.getPrevTasks().isEmpty()) {
                for (Task prevTask : task.getPrevTasks())
                    result = result + "  Z" + prevTask.getNumber() + "_" + prevTask.getDuration() + "->Z" + task.getNumber() + "_" + task.getDuration() + ";\n";
            } else {
                result = result + "  Z" + task.getNumber() + "_" + task.getDuration() + ";\n";
            }
        }
        return result;
    }

    public boolean isCyclic(){
        boolean[] visited = new boolean[tasks.size()];
        Arrays.fill(visited, false);
        Set<Integer> recStack = new HashSet<>();
        for(int i = 1; i < tasks.size() - 1; i++){
            if(helper(i, visited, recStack))
                return true;
        }
        return false;
    }

    private boolean helper(int v, boolean[]visited, Set<Integer> recStack){
        if(!visited[v])
        {
            //mark the vertex v to be visited
            visited[v] = true;
            //add v in the recursion stack
            recStack.add(v);
            //for all adjacent vertices
            for(Task task : tasks.get(0).getPrevTasks())
            {
                int i = task.getNumber();
                //if the adjacent node is not visited yet
                if(!visited[i])
                {
                    if(helper(i, visited, recStack))
                        return true;
                }
                //if the node is already present on the recursion stack
                //then there is cycle add return true
                else if(recStack.contains(i))
                    return true;
            }
        }
        //remove the node from the recursion stack
        recStack.remove(v);
        return false;
    }


    public void clear(){
        tasks = new ArrayList<>();
        criticalPath = new ArrayList<>();
    }
}
