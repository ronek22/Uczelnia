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
            readFromFile("data.txt");
        } catch(IOException e){
            System.out.println("Problem z odczytem pliku");
        }

        organizer.saveGraph();
        organizer.HU();
        organizer.makeChart();
        organizer.display();
    }

    private static void readFromFile(String fileName) throws IOException {
        String nextLine;
        BufferedReader br = new BufferedReader(new FileReader(fileName));

        organizer.setMachineNumber(Integer.valueOf(br.readLine()));

        while((nextLine = br.readLine()) != null){
            String[] data = nextLine.split(",");
            int taskNo = Integer.valueOf(data[0]);

            organizer.addTask(taskNo);

            if(data.length == 2)
                Arrays.stream(data[1].split(" ")).mapToInt(Integer::parseInt)
                        .forEach(task -> organizer.connect(task, taskNo));
        }
    }
}
