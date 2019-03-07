import java.io.*;



public class OdczytDanych {

    //zwraca tempo w postaci np. '5:40'
    public static String Pace(double distance, int duration){
        if(distance != 0){
            double totMin = (double)duration/60;
            double pace = totMin/distance;

            int minutes = (int)pace;
            double sec = pace - minutes;
            sec *=60;
            int seconds = (int)sec;
            if(seconds<10){
                return "'"+String.valueOf(minutes)+":0"+String.valueOf(seconds)+"'";
            } else
                return "'"+String.valueOf(minutes)+":"+String.valueOf(seconds)+"'";
        } else
            return "'0:00'";
    }

    public static String Speed(double distance, int duration){
        if(duration != 0){
            double totalH = (double)duration/3600;
            double speed = distance/totalH;
            String speedString = String.format("%.2f", speed);
            return speedString;
        } else
            return "0";
    }

    //Zwraca numer kategorii z tabelii typ_aktywnosci
    public static int Kategorie(String s){
        if(s.equals("Biegi"))
            return 1;
        else if(s.equals("Kolarstwo"))
            return 2;
        else if(s.equals("Spacerowanie"))
            return 3;
        else if(s.equals("Plywanie"))
            return 4;
        else
            return 5;
    }

    public static String Miesiac(String month) {
        String intMonth;
        switch(month) {
            case "sty":
                intMonth = "01";
                break;
            case "lut":
                intMonth = "02";
                break;
            case "mar":
                intMonth = "03";
                break;
            case "kwi":
                intMonth = "04";
                break;
            case "maj":
                intMonth = "05";
                break;
            case "cze":
                intMonth = "06";
                break;
            case "lip":
                intMonth = "07";
                break;
            case "sie":
                intMonth = "08";
                break;
            case "wrz":
                intMonth = "09";
                break;
            case "paz":
                intMonth = "10";
                break;
            case "lis":
                intMonth = "11";
                break;
            case "gru":
                intMonth = "12";
                break;
            default:
                intMonth = "00";
                break;
        }
        return intMonth;

    }

    //zwraca czas z postaci HH:MM:SS do sekund
    public static int timeToSeconds(String time) {
        if(!(time.equals("null"))){
            String[] part = time.split(":");
            return Integer.parseInt(part[0])*3600+Integer.parseInt(part[1])*60+Integer.parseInt(part[2]);
        } else
            return 0;
    }


    public static void ReadWriteSql(BufferedReader read, PrintWriter zapis) throws NumberFormatException, IOException {
        String rekord;
        while ((rekord = read.readLine()) != null) {
            String sql = "INSERT INTO aktywnosci (id_typ,czas_startu,dystans,czas_trwania,avg_tempo,przewyzszenie,avg_tetno,max_tetno,avg_rytm,max_rytm) VALUES (";
            String[] parts = rekord.split("\\|");
            String temp = String.valueOf(Kategorie(parts[0]))+",";
            //dodanie kategorii
            sql+=temp;


            // konwersja daty
            temp="'";
            //usuniecie cudzyslowow;
            parts[1] = parts[1].substring(1, parts[1].length()-1);
            String date[] = parts[1].split("\\s+");
            temp+=date[2]+"-";

            //dodanie miesiaca
            temp+=Miesiac(date[1])+"-";

            //dodanie dnia
            if(Integer.parseInt(date[0])<10){
                temp+="0"+date[0]+" ";
            } else {
                temp+=date[0]+" ";
            }

            //czas, jesli godzina przed 10 trzeba dodac 0 na poczatek
            int hours,minutes,seconds;
            String time[] = date[3].split(":");
            if(Integer.parseInt(time[0])<10){
                temp+="0"+date[3]+"',";
            } else
                temp+=date[3]+"',";
            //dodanie daty do sql
            sql+=temp;
            //dodanie dystansu
            sql+=parts[2]+",";
            //walka z czasem trwania
            int duration; // in seconds
            double distance = Double.parseDouble(parts[2]);
            time = parts[3].split(":");

            // jesli dystans jest wiekszy niz 10km a czas mniejszy niz 10, to wiadomo, ze mamy h a nie mm
            // dlatego, ze nie poruszalem sie z predkoscia 60km/h przez 10km

            // problem ze Spacerowaniem
            // na podstawie danych jesli dystans byl wiekszy niz 4100m
            // to aktywnosc trwala dluzej niz h
            if(parts[0].equals("Spacerowanie") && distance > 4.10){
                hours = Integer.parseInt(time[0]);
                minutes = Integer.parseInt(time[1]);
                seconds = Integer.parseInt(time[2]);
                duration = hours*3600 + minutes*60 + seconds;
            } else if(distance>=10 && Integer.parseInt(time[0])<10){
                hours = Integer.parseInt(time[0]);
                minutes = Integer.parseInt(time[1]);
                seconds = Integer.parseInt(time[2]);
                duration = hours*3600 + minutes*60 + seconds;
            } else {
                minutes = Integer.parseInt(time[0]);
                seconds = Integer.parseInt(time[1]);
                duration = minutes*60+seconds;
            }

            //dodanie czasu w sec
            sql+=String.valueOf(duration)+",";

            //dodanie tempa
            temp = Pace(distance, duration);
            sql+=temp+",";

            //dodanie przewyzszenia
            if(parts[4].equals("--")) // w przypadku aktywnosci bez gps
                sql+="null,";
            else
                sql+=parts[4]+",";

            //dodanie sredniego tetna
            if(parts[5].equals("--"))
                sql+="null,";
            else
                sql+=parts[5]+",";

            //dodanie max tetna
            if(parts[6].equals("--"))
                sql+="null,";
            else
                sql+=parts[6]+",";

            // dodanie sredniej kadencji
            if(parts[7].equals("--"))
                sql+="null,";
            else
                sql+=parts[7]+",";

            //dodanie maksymalnej kadencji
            if(parts[8].equals("--"))
                sql+="null);";
            else
                sql+=parts[8]+");";

            //zapisanie do plikus
            zapis.println(sql);

        }
        System.out.println("Baza danych z pliku odczytana\nInserty znajduję się w pliku insert.sql");
        read.close();
        zapis.close();
    }
}
