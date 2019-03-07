package Projekt2;

import java.util.ArrayList;
import java.util.concurrent.atomic.AtomicInteger;

public class Task {
    // p - duration, r - startTime, d - deadline
    private final int number, r;
    private int p , d, finishTime;
    private boolean finished;
    private int lateness;
    private ArrayList<Task> prevTasks;
    private ArrayList<Task> nextTasks;

    public Task(int number, int duration, int startTime, int deadline){
        this.number = number;
        this.p = duration;
        this.r = startTime;
        this.d = deadline;
        this.finished = false;
        prevTasks = new ArrayList<>();
        nextTasks = new ArrayList<>();
    }

    void run(AtomicInteger time){
        if(p == 0) throw new IllegalArgumentException("Zadanie zostalo juz ukonczone nie mozna dodac do harmonogramu");
        if(--p == 0){
            finished = true;
            finishTime = time.get() + 1;
            calcLateness();
        }
    }

    int getNumber() { return number;}
    int getDeadline() {return d;}
    void setDeadline(int deadline) {this.d = deadline;}
    int getStartTime() { return r;}
    private void calcLateness() {
        this.lateness = finishTime - d;
    }
    int getLateness() { return lateness;}
    boolean isFinished(){ return finished;}

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
        return number + ": Start: " + r + ", Deadline: " + d + ", Duration:" + p;
    }

    public String abbrev(){ return "Z" + number;}


}
