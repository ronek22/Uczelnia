package Projekt2;

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

    public static void main( String[] args )
    {
        try {
            readFromFile("data3.txt");
        } catch(IOException e){
            System.out.println("Problem z odczytem pliku");
        }

        organizer.LIU();
        organizer.display();
        organizer.makeChart();
    }

    public static void readFromFile(String fileName) throws IOException {
        BufferedReader br = new BufferedReader(new FileReader(fileName));
        String nextLine;
        int taskNo = 1;
        while((nextLine = br.readLine()) != null){
            String[] data = nextLine.split(",");
            int[] node = convertToInt(data[0]);

            if(node.length != 3) throw new IllegalArgumentException("Zla ilosc danych, zadanie musi miec trzy wartosci");
            organizer.addTask(taskNo, node[0], node[1], node[2]);

            if(data.length == 2){
                int[] prevTasks = convertToInt(data[1]);
                for(int task : prevTasks){
                    organizer.connect(task, taskNo);
                }
            }
            taskNo++;
        }
    }

    private static int[] convertToInt(String data){
        return Arrays.stream(data.split(" "))
                .mapToInt(Integer::parseInt).toArray();
    }
}
