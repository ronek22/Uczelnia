package Projekt1;

import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;
import java.util.Arrays;


/**
 * Hello world!
 *
 */
public class App
{
    static TaskOrganizer organizer = TaskOrganizer.getInstance();

    public static void main(String[] args) throws IOException{
        try {
            readFromFile("data.txt");
        } catch(IOException e){
            System.out.println("Problem z odczytem pliku");
            e.printStackTrace();
            System.exit(-1);
        }

        if(!organizer.isCyclic()){
            organizer.calcTimes();
            organizer.display();
            organizer.CPM();
            organizer.saveGraph();
        }
    }




    public static void readFromFile(String fileName) throws IOException {
        BufferedReader br = new BufferedReader(new FileReader(fileName));
        String nextLine;
        while((nextLine = br.readLine()) != null){
            String[] data = nextLine.split(",");
            int[] node = convertToInt(data[0]);

            if(node.length != 2) throw new IllegalArgumentException("Zla ilosc danych, nalezy podac numer zadania i czas");
            organizer.addTask(node[0], node[1]);

            if(data.length == 2){
                int[] prevTasks = convertToInt(data[1]);
                for(int taskNo : prevTasks){
                    organizer.connect(taskNo, node[0]);
                }
            }
        }
    }

    private static int[] convertToInt(String data){
        return Arrays.stream(data.split(" "))
                .mapToInt(Integer::parseInt).toArray();
    }

}
