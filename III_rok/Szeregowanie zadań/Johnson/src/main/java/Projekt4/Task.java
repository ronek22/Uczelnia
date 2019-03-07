package Projekt4;

import java.util.ArrayList;
import java.util.List;

class Task {
    private final int number;
    private List<Integer> times;
    private int t1, t2;

    Task(int number, List<Integer> times){
        this.number = number;
        this.times = times;
        calcModifiedTimes();
    }

    int getTime(int machine){
        return times.get(machine);
    }

    public List<Integer> getTimes() {
        return times;
    }

    public int getT1() {
        return t1;
    }

    public int getT2() {
        return t2;
    }

    boolean isSetN1(){
        return t1 < t2;
    }

    boolean isSetN2(){
        return t1 >= t2;
    }

    private void calcModifiedTimes(){
        t1 = times.get(0) + times.get(1);
        t2 = times.get(1) + times.get(2);
    }

    int getNumber() { return number;}



//    @Override
//    public String toString(){
//        StringBuilder prevList = new StringBuilder();
//        StringBuilder nextList = new StringBuilder();
//        for(Task task : prevTasks){ prevList.append(task.getNumber()).append(" "); }
//        for(Task task : nextTasks){ nextList.append(task.getNumber()).append(" "); }
//
//        String result = String.format("%6d | %-13s | %-13s", number,  prevList.toString(), nextList.toString());
//        return result;
//    }

}
