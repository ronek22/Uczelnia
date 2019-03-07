package Projekt1;

import java.util.ArrayList;
import java.util.List;

public class Task {
    // given
    private int number;
    private int duration;
    private ArrayList<Task> prevTasks;
    private ArrayList<Task> nextTasks;

    // calculated
    private int startTime;
    private int finishTime;

    public Task(int number, int duration){
        this.number = number;
        this.duration = duration;
        prevTasks = new ArrayList<>();
        nextTasks = new ArrayList<>();

    }

    public int getNumber() {
        return number;
    }
    public int getDuration() {
        return duration;
    }
    public int getStartTime() {
        return startTime;
    }
    public void setStartTime(int startTime) {
        this.startTime = startTime;
    }
    public int getFinishTime() {
        return finishTime;
    }
    public void setFinishTime(int finishTime) {
        this.finishTime = finishTime;
    }

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


        String result = String.format("%6d | %6d | %6d | %6d | %-13s | %-13s", number, duration, startTime, finishTime,  prevList.toString(), nextList.toString());
        return result;
    }

    public String toStringNo(){
        return "Z" + number + " ( " + duration + " )";
    }

}

