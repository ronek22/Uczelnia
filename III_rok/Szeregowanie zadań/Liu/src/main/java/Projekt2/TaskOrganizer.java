package Projekt2;

import com.sun.istack.internal.NotNull;
import javafx.scene.chart.Chart;
import org.jfree.chart.ChartFactory;
import org.jfree.chart.ChartUtilities;
import org.jfree.chart.JFreeChart;
import org.jfree.chart.StandardChartTheme;
import org.jfree.chart.axis.NumberAxis;
import org.jfree.chart.axis.NumberTickUnit;
import org.jfree.chart.labels.StandardXYItemLabelGenerator;
import org.jfree.chart.plot.PlotOrientation;
import org.jfree.chart.plot.XYPlot;
import org.jfree.chart.renderer.category.BarRenderer;
import org.jfree.chart.renderer.category.StandardBarPainter;
import org.jfree.chart.renderer.xy.StandardXYBarPainter;
import org.jfree.chart.renderer.xy.XYBarPainter;
import org.jfree.chart.renderer.xy.XYBarRenderer;
import org.jfree.chart.renderer.xy.XYItemRenderer;
import org.jfree.data.category.IntervalCategoryDataset;
import org.jfree.data.gantt.TaskSeries;
import org.jfree.data.gantt.TaskSeriesCollection;
import org.jfree.data.xy.IntervalXYDataset;
import org.jfree.data.xy.XYDataset;
import org.jfree.data.xy.XYSeries;
import org.jfree.data.xy.XYSeriesCollection;
import org.jfree.ui.RectangleEdge;

import java.awt.*;
import java.awt.geom.RectangularShape;
import java.io.File;
import java.io.IOException;
import java.util.ArrayList;
import java.util.Collections;
import java.util.Comparator;
import java.util.NoSuchElementException;
import java.util.concurrent.atomic.AtomicInteger;

public class TaskOrganizer {
    private ArrayList<Task> tasks;
    private ArrayList<Integer> schedule;
    private AtomicInteger time;
    private int lMAX;


    private static TaskOrganizer ourInstance = new TaskOrganizer();

    public static TaskOrganizer getInstance() {
        return ourInstance;
    }

    private TaskOrganizer() {
        tasks = new ArrayList<>();
        schedule = new ArrayList<>();
        time = new AtomicInteger(0);
    }

    void addTask(int number, int duration, int startTime, int deadline){
        tasks.add(new Task(number, duration, startTime, deadline));
    }

    private Task getTaskNo(int number){
        return tasks.stream()
                .filter(p -> p.getNumber() == number)
                .findFirst().orElse(null);
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

    private void traverse(Task task, ArrayList<Integer> deadlines) {
        if(!deadlines.contains(task.getDeadline()))
            deadlines.add(task.getDeadline());
        if(!task.getNextTasks().isEmpty()){
            for(Task nextTask : task.getNextTasks()){
                traverse(nextTask, deadlines);
            }
        }
    }

    private void newDeadlines(){
        ArrayList<Integer> deadlines = new ArrayList<>();
        ArrayList<Integer> finalDeadlines = new ArrayList<>();
        for(Task task : tasks){
            traverse(task, deadlines);
            finalDeadlines.add(Collections.min(deadlines));
            deadlines.clear();
        }

        for(Task task : tasks){
            task.setDeadline(finalDeadlines.get(task.getNumber() - 1));
        }
    }

    private void addToSchedule(@NotNull Task added){
        added.run(time);
        schedule.add(added.getNumber());
    }

    private boolean isAllFinished(){
        for(Task task : tasks){
            if(!task.isFinished())
                return false;
        }
        return true;
    }

    void LIU(){
        newDeadlines();
        while(!isAllFinished()){
            try{
                Task early = tasks.stream()
                        .filter(p -> p.getStartTime() <= time.get() && !p.isFinished())
                        .min(Comparator.comparingInt(Task::getDeadline))
                        .get();
                if(checkIfPrevTasksIsFinished(early))
                    addToSchedule(early);
                else
                    schedule.add(0);
            } catch(NoSuchElementException e){
                System.out.println("Zadanie musi poczekac");
                schedule.add(0);
            } finally {
                time.getAndAdd(1);
            }

        }
        setLMAX();
    }

    boolean checkIfPrevTasksIsFinished(Task task){
        for(Task prevTask : task.getPrevTasks()){
            if(!prevTask.isFinished())
                return false;
        }
        return true;
    }

    private void setLMAX(){
        lMAX = tasks.stream()
                .max(Comparator.comparingInt(Task::getLateness))
                .get().getLateness();
    }

    public void display(){
        System.out.print("| ");
        for(int task : schedule)
            System.out.print(task + " | ");

        System.out.println();

        for(Task task : tasks)
            System.out.println("L(Z" + task.getNumber() + ") = " + task.getLateness());

        System.out.println("LMAX = " + lMAX);
        System.out.println("TIME = " + time.get());
    }

     //MAKE CHART
    public void makeChart() {
        XYBarRenderer.setDefaultShadowsVisible(false);
        ChartFactory.setChartTheme(StandardChartTheme.createLegacyTheme());
        JFreeChart chart = ChartFactory.createXYBarChart(
                null,
                "Czas",
                false,
                "",
                createDataset(),
                PlotOrientation.VERTICAL,
                true, true, false
        );


        XYPlot plot = (XYPlot) chart.getPlot();

        plot.setBackgroundPaint( Color.lightGray );
        plot.setDomainGridlinePaint( Color.white );
        plot.setRangeGridlinePaint( Color.white );
        plot.setRangeGridlinesVisible(false);
        plot.setDomainCrosshairVisible( true );
        plot.setRangeCrosshairVisible( false );


        NumberAxis range = (NumberAxis) plot.getRangeAxis();
        range.setVisible(false);
        range.setRange(0.0, 1);
        range.setTickUnit(new NumberTickUnit(1));

        int width = 640;   /* Width of the image */
        int height = 300;  /* Height of the image */
        File XYChart = new File( "harmonogram.png" );

        try {
            ChartUtilities.saveChartAsPNG(XYChart, chart, 500, 100);
        } catch(IOException e){
            System.out.println("Problem z zapisaniem grafu");
        }
    }

    public IntervalXYDataset createDataset(){
        ArrayList<XYSeries> series = new ArrayList<>();
        for(Task task : tasks){
            series.add(new XYSeries(task.abbrev()));
            XYSeries temp = series.get(series.size() - 1);
            for(int i = 0; i<schedule.size(); i++){
                if(schedule.get(i) == task.getNumber()) temp.add(i+0.5, 1);
            }
        }

        XYSeriesCollection dataset = new XYSeriesCollection();
        for(XYSeries serie : series){
            dataset.addSeries(serie);
        }
        return dataset;

    }


    void reset(){
        tasks = new ArrayList<>();
        schedule = new ArrayList<>();
        time.getAndSet(0);
    }
}
