package Projekt4;

import guru.nidi.graphviz.engine.Format;
import guru.nidi.graphviz.engine.Graphviz;
import guru.nidi.graphviz.model.MutableGraph;
import guru.nidi.graphviz.parse.Parser;

import java.io.File;
import java.io.IOException;
import java.util.*;
import java.util.stream.Collectors;

public class TaskOrganizer {
    private List<Task> tasks;
    private List<ArrayList<Integer>> schedule;
    private int machineNo;
    private List<Integer> orderList;

    private static TaskOrganizer ourInstance = new TaskOrganizer();
    public static TaskOrganizer getInstance() {
        return ourInstance;
    }
    private TaskOrganizer() {
        tasks = new ArrayList<>();
        schedule = new ArrayList<>();
        orderList = new ArrayList<>();
    }

    void setMachineNumber(int machine){
        this.machineNo = machine;
        prepareScheduleTable();
    }

    private void prepareScheduleTable(){
        for(int i = 0; i < machineNo; i++){
            schedule.add(new ArrayList<>());
        }
    }

    void addTask(int number, List<Integer> times) {
        if(times.size() != machineNo) throw new IllegalArgumentException("Quantity of times must be equal to quantity of machines");
        tasks.add(new Task(number, times));
    }

    private Task getTaskNo(int number){
        return tasks.stream()
                .filter(p -> p.getNumber() == number)
                .findFirst().orElse(null);
    }


    private void addToSchedule(Task added, int machine){
        List<Integer> machineSchedule = schedule.get(machine);
        for(int i = 0; i < added.getTime(machine); i++)
            machineSchedule.add(added.getNumber());

    }


    private void addToSchedule(Task added, int machine, int start){
        int howMany = start + 1 - schedule.get(machine).size();
        List<Integer> machineSchedule = schedule.get(machine);
        for(int i = 0; i < howMany; i++)
            machineSchedule.add(0);
        for(int i = 0; i < added.getTime(machine); i++)
            machineSchedule.add(added.getNumber());

    }


    void Johnson() {
        prepareOrder();

        // fill machines begins from 0 to machineNo
        for (int i = 0; i < machineNo; i++) {
            for (int task : orderList) {
                if(i == 0) {
                    addToSchedule(getTaskNo(task), i);
                } else {
                    addToSchedule(getTaskNo(task), i, schedule.get(i-1).lastIndexOf(task));
                }
            }
        }
    }

    private void prepareOrder(){
        List<Integer> n1 = tasks.stream()
                .filter(Task::isSetN1)
                .sorted(Comparator.comparingInt(Task::getT1))
                .map(Task::getNumber)
                .collect(Collectors.toList());

        List<Integer> n2 = tasks.stream()
                .filter(Task::isSetN2)
                .sorted(Comparator.comparingInt(Task::getT2).reversed())
                .map(Task::getNumber)
                .collect(Collectors.toList());

        orderList.addAll(n1);
        orderList.addAll(n2);

        // DISPLAY FOR DEBUG
        System.out.println("ORDER: ");
        for(int x : orderList)
            System.out.print("Z" + x + " ");
        System.out.println();

    }


    void display(){
        int mNo = 1;
        System.out.println();
        for(List<Integer> machine : schedule){
            System.out.print("M" + mNo++ + "\t| ");
            for(int task : machine){
                if(task == 0)
                    System.out.print("  | ");
                else
                    System.out.print(task + " | ");
            }
            System.out.println();

        }
        System.out.println("\nTIME: " + schedule.get(machineNo-1).size());
    }

//    public void saveGraph() {
//        String graphFileContent = graphCreator();
//        try {
//            MutableGraph g = Parser.read(graphFileContent);
//            Graphviz.fromGraph(g).render(Format.PNG).toFile(new File("example/graph.png"));
//        } catch(IOException e){
//            System.out.println("Wystapil problem z drukowaniem wykresu.");
//        }
//
//
//
//    }

//    private String graphCreator()
//    {
//        StringBuilder resultBuilder = new StringBuilder();
//        resultBuilder.append("digraph G {\n");
//        for (Task task : tasks) {
//            if(!task.getPrevTasks().isEmpty()) {
//                for (Task prevTask : task.getPrevTasks())
//                    resultBuilder.append("  Z").append(prevTask.getNumber()).append("->Z").append(task.getNumber()).append(";\n");
//            } else {
//                resultBuilder.append("  Z").append(task.getNumber()).append(";\n");
//            }
//        }
//        resultBuilder.append(" }");
//        return resultBuilder.toString();
//    }


//     MAKE CHART
//    public void makeChart() {
//        XYBarRenderer.setDefaultShadowsVisible(false);
//        ChartFactory.setChartTheme(StandardChartTheme.createLegacyTheme());
//        JFreeChart chart = ChartFactory.createXYBarChart(
//                null,
//                "Czas",
//                false,
//                "",
//                createDataset(),
//                PlotOrientation.VERTICAL,
//                true, true, false
//        );
//
//
//        XYPlot plot = (XYPlot) chart.getPlot();
//
//        plot.setBackgroundPaint( Color.lightGray );
//        plot.setDomainGridlinePaint( Color.white );
//        plot.setRangeGridlinePaint( Color.white );
//        plot.setRangeGridlinesVisible(false);
//        plot.setDomainCrosshairVisible( true );
//        plot.setRangeCrosshairVisible( false );
//
//
//        NumberAxis range = (NumberAxis) plot.getRangeAxis();
//        range.setVisible(false);
//        range.setRange(0.0, 1);
//        range.setTickUnit(new NumberTickUnit(1));
//
//        int width = 640;   /* Width of the image */
//        int height = 300;  /* Height of the image */
//        File XYChart = new File( "harmonogram.png" );
//
//        try {
//            ChartUtilities.saveChartAsPNG(XYChart, chart, 500, 100);
//        } catch(IOException e){
//            System.out.println("Problem z zapisaniem grafu");
//        }
//    }
//
//    public IntervalXYDataset createDataset(){
//        ArrayList<XYSeries> series = new ArrayList<>();
//        for(Task task : tasks){
//            series.add(new XYSeries(task.abbrev()));
//            XYSeries temp = series.get(series.size() - 1);
//            for(int i = 0; i<schedule.size(); i++){
//                if(schedule.get(i) == task.getNumber()) temp.add(i+0.5, 1);
//            }
//        }
//
//        XYSeriesCollection dataset = new XYSeriesCollection();
//        for(XYSeries serie : series){
//            dataset.addSeries(serie);
//        }
//        return dataset;
//
//    }



}
