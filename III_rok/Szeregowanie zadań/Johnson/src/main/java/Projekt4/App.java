package Projekt4;

import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;
import java.util.stream.Collectors;

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
            readFromFile("data.txt");
        } catch(IOException e){
            System.out.println("Problem z odczytem pliku");
        }

//        organizer.saveGraph();
        organizer.Johnson();
        organizer.display();
    }

    private static void readFromFile(String fileName) throws IOException {
        String nextLine;
        BufferedReader br = new BufferedReader(new FileReader(fileName));

        organizer.setMachineNumber(Integer.valueOf(br.readLine()));

        while((nextLine = br.readLine()) != null){
            String[] data = nextLine.split(",");
            int taskNo = Integer.valueOf(data[0]);
            List<Integer> times = Arrays.stream(data[1].split(" "))
                    .map(Integer::parseInt)
                    .collect(Collectors.toList());

            organizer.addTask(taskNo, times);
        }
    }
}
