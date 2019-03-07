package Projekt2;

import java.util.ArrayList;
import java.util.concurrent.atomic.AtomicInteger;

public class Task {
    private final int number;
    private boolean finished;
    private boolean available;
    private ArrayList<Task> prevTasks;
    private ArrayList<Task> nextTasks;

    public Task(int number){
        this.number = number;
        this.finished = false;
        this.available = true; // w tym momencie jeszcze nie dodajemy zadnych zaleznosci, a wiec jest dostepne
        prevTasks = new ArrayList<>();
        nextTasks = new ArrayList<>();
    }

    void run(){
        if(finished) throw new IllegalArgumentException("Zadanie zostalo juz ukonczone nie mozna dodac do harmonogramu");
        if(!available) throw new IllegalArgumentException("Zadanie nie moze sie wykonac, poniewaz jest zalezne od poprzednich zadan jeszcze nie wykonanych.");
        finished = true;
    }

    void update(){
        available = prevTasks.stream().allMatch(Task::isFinished);
    }

    int getNumber() { return number;}
    boolean isFinished(){ return finished;}
    boolean isAvailable() { return available;}



    public void addPrevTasks(Task prevTask){
        prevTasks.add(prevTask);
    }
    public void addNextTasks(Task nextTask){
        nextTasks.add(nextTask);
    }
    public ArrayList<Task> getPrevTasks() {
        return prevTasks;
    }
    public ArrayList<Task> getNextTasks() {
        return nextTasks;
    }


    @Override
    public String toString(){
        StringBuilder prevList = new StringBuilder();
        StringBuilder nextList = new StringBuilder();
        for(Task task : prevTasks){ prevList.append(task.getNumber()).append(" "); }
        for(Task task : nextTasks){ nextList.append(task.getNumber()).append(" "); }

        String result = String.format("%6d | %-13s | %-13s", number,  prevList.toString(), nextList.toString());
        return result;
    }

}
