package Projekt2;

import com.sun.istack.internal.NotNull;
import guru.nidi.graphviz.engine.Format;
import guru.nidi.graphviz.engine.Graphviz;
import guru.nidi.graphviz.model.MutableGraph;
import guru.nidi.graphviz.parse.Parser;
import javafx.scene.chart.Chart;
import org.jfree.chart.*;
import org.jfree.chart.axis.*;
import org.jfree.chart.labels.*;
import org.jfree.chart.plot.CategoryPlot;
import org.jfree.chart.plot.PlotOrientation;
import org.jfree.chart.plot.XYPlot;
import org.jfree.chart.renderer.category.BarRenderer;
import org.jfree.chart.renderer.category.CategoryItemRenderer;
import org.jfree.chart.renderer.category.StackedBarRenderer;
import org.jfree.chart.renderer.category.StandardBarPainter;
import org.jfree.chart.renderer.xy.StandardXYBarPainter;
import org.jfree.chart.renderer.xy.XYBarPainter;
import org.jfree.chart.renderer.xy.XYBarRenderer;
import org.jfree.chart.renderer.xy.XYItemRenderer;
import org.jfree.data.Range;
import org.jfree.data.category.CategoryDataset;
import org.jfree.data.category.DefaultCategoryDataset;
import org.jfree.data.category.IntervalCategoryDataset;
import org.jfree.data.gantt.TaskSeries;
import org.jfree.data.gantt.TaskSeriesCollection;
import org.jfree.data.xy.IntervalXYDataset;
import org.jfree.data.xy.XYDataset;
import org.jfree.data.xy.XYSeries;
import org.jfree.data.xy.XYSeriesCollection;
import org.jfree.ui.RectangleEdge;
import org.jfree.ui.TextAnchor;

import java.awt.*;
import java.awt.geom.RectangularShape;
import java.io.File;
import java.io.IOException;
import java.text.NumberFormat;
import java.text.SimpleDateFormat;
import java.util.*;
import java.util.List;
import java.util.concurrent.atomic.AtomicInteger;

public class TaskOrganizer {
    private List<Task> tasks;
    private List<ArrayList<Integer>> schedule;
    private int machineNo;

    private static TaskOrganizer ourInstance = new TaskOrganizer();
    public static TaskOrganizer getInstance() {
        return ourInstance;
    }
    private TaskOrganizer() {
        tasks = new ArrayList<>();
        schedule = new ArrayList<>();
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

    void addTask(int number){
        tasks.add(new Task(number));
    }
    private Task getTaskNo(int number){
        return tasks.stream()
                .filter(p -> p.getNumber() == number)
                .findFirst().orElse(null);
    }
    void connect(int prevNo, int nextNo){
        if(prevNo >= nextNo) throw new IllegalArgumentException("Pierwszy zadanie musi byc wczesniejesz niz drugie");

        Task prev = getTaskNo(prevNo);
        Task next = getTaskNo(nextNo);

        if(prev == null || next == null) throw new IllegalArgumentException("Jednego z zadan nie ma na liscie");

        prev.addNextTasks(next);
        next.addPrevTasks(prev);
    }
    private void addToSchedule(Task added, int machine){
        if(added != null){
            added.run();
            schedule.get(machine).add(added.getNumber());
        }

    }
    private boolean isAllFinished(){
        return tasks.stream().allMatch(Task::isFinished);
    }

    void HU(){
        while(!isAllFinished()){
            for(int i = 0; i < machineNo; i++){
                Task available = tasks.stream()
                        .filter(p -> !p.isFinished() && p.isAvailable())
                        .min(Comparator.comparingInt(Task::getNumber)).orElse(null);
                addToSchedule(available, i);
            }
            tasks.forEach(Task::update); // update available tasks;
        }

    }
    void display(){
        int mNo = 1;
        for(List<Integer> machine : schedule){
            System.out.print("M" + mNo++ + "\t| ");
            for(int task : machine){
                System.out.print(task + " | ");
            }
            System.out.println();

        }
    }

    public void saveGraph() {
        String graphFileContent = graphCreator();
        try {
            MutableGraph g = Parser.read(graphFileContent);
            Graphviz.fromGraph(g).render(Format.PNG).toFile(new File("example/graph.png"));
        } catch(IOException e){
            System.out.println("Wystapil problem z drukowaniem wykresu.");
        }



    }

    private String graphCreator()
    {
        StringBuilder resultBuilder = new StringBuilder();
        resultBuilder.append("digraph G {\n");
        for (Task task : tasks) {
            if(!task.getPrevTasks().isEmpty()) {
                for (Task prevTask : task.getPrevTasks())
                    resultBuilder.append("  Z").append(prevTask.getNumber()).append("->Z").append(task.getNumber()).append(";\n");
            } else {
                resultBuilder.append("  Z").append(task.getNumber()).append(";\n");
            }
        }
        resultBuilder.append(" }");
        return resultBuilder.toString();
    }


//     MAKE CHART
    public void makeChart() {
        StackedBarRenderer.setDefaultShadowsVisible(false);
        StackedBarRenderer.setDefaultBarPainter(new StandardBarPainter());
        CategoryPlot plot = new CategoryPlot();

        plot.setRangeAxisLocation(AxisLocation.BOTTOM_OR_RIGHT);
        plot.setOrientation(PlotOrientation.HORIZONTAL);

        CategoryDataset dataset = createDataset();


        CategoryAxis catAxis = new CategoryAxis();
        NumberAxis numberAxis = new NumberAxis();
        numberAxis.setVerticalTickLabels(true);
        numberAxis.setTickUnit(new NumberTickUnit(1));

        // set up the renderer
        StackedBarRenderer rend = new StackedBarRenderer();

        rend.setBaseItemLabelGenerator(    new StandardCategoryItemLabelGenerator(
                "{0}", NumberFormat.getInstance()));
        rend.setBaseItemLabelsVisible(true);

        // set up the plot
        plot.setDataset(dataset);
        plot.setDomainAxis(catAxis);
        plot.setRangeAxis(numberAxis);
        plot.setRenderer(rend);


        // create the chart and add it
        ChartFactory.setChartTheme(StandardChartTheme.createLegacyTheme());

        JFreeChart chart = new JFreeChart("", JFreeChart.DEFAULT_TITLE_FONT, plot, false);
        ChartPanel chartPanel = new ChartPanel(chart);
        chartPanel.setPreferredSize(new Dimension(600, 450));
        File scheduleChart = new File( "harmonogram.png" );

        try {
            ChartUtilities.saveChartAsPNG(scheduleChart, chart, 500, 200);
        } catch(IOException e){
            System.out.println("Problem z zapisaniem grafu");
        }

    }


    private CategoryDataset createDataset() {
        DefaultCategoryDataset dataset = new DefaultCategoryDataset();
        String machineString;
        int machineNumber = 1;

        for(List<Integer> machine : schedule){
            machineString = "M"+machineNumber++;
            for(int task : machine){
                dataset.addValue(1, "Z"+task, machineString);
            }
        }
        return dataset;
    }




}
