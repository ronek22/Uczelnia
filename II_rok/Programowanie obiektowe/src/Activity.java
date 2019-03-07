// Jakub Ronkiewicz, 2016-11-13
/* Stworzony program wczytuje do bazy danych
 Dane moich treningów z pliku activ.txt
 Dane zostały wyeksportowane z serwisu Garmin Connect do pliku .csv
 Następnie skonwertowane do pliku .txt
 Celem programu jest analiza treningu, tzn. podsumowania roczne, miesieczne, tygodniowe,
 możliwośc zobaczenia najszybszych i najdluzszych aktywnosci
 */
import java.sql.*;
import java.text.ParseException;
import java.text.SimpleDateFormat;
import java.util.*;
import java.util.Date;
import java.io.*;


public class Activity {

    private static Connection conn = null;
    private static Statement stmt = null;
    
    // zmienne do menu
    private BufferedReader br;
    private int selectedOption;

    public Activity() {
        showMainMenu();
        br = new BufferedReader(new InputStreamReader(System.in));

        try {
            try{
            	selectedOption = Integer.parseInt(br.readLine());
            } catch (NumberFormatException e){
            	System.out.println("Musisz wybrać numer!");
            	new Activity();
            }
            switch(selectedOption) {
                case 1:
                    showSubMenuOptions(1);
                    break;
                case 2:
                    showSubMenuOptions(2);
                    break;
                case 3:
                    showSubMenuOptions(3);
                    break;
                case 4:
                    showSubMenuOptions(4);
                    break;
                case 5:
                    quitProgram();
                    break;
                default:
                	System.out.println("Nie ma takiej opcji!");
                	new Activity();
                	break;
            }
        } catch (IOException | SQLException ioe) {
            System.out.println("IO error trying to read your input." + ioe);
            System.exit(1);
        }



    }

    public void showMainMenu() {
        System.out.println("");
        System.out.println("Menu główne");
        System.out.println("------------------------------------------");
        System.out.println("1. Odczyt danych & Tworzenie tabeli & dodanie bazy z pliku");
        System.out.println("2. Dodawanie nowych rekordów");
        System.out.println("3. Przetwarzanie danych");
        System.out.println("4. Wyświetlanie przetworzonych informacji");
        System.out.println("5. Wyjście z programu");
        System.out.println("------------------------------------------");
        System.out.println("");
        System.out.println("");
    }

    public void kategorie(){
        System.out.println("------------------------------------------");
        System.out.println("1. Biegi");
        System.out.println("2. Kolarstwo");
        System.out.println("3. Spacerowanie");
        System.out.println("4. Pływanie");
    }

    public void showSubMenuOptions(int mainMenuChoice) throws IOException, SQLException {
        br = new BufferedReader(new InputStreamReader(System.in));

        switch(mainMenuChoice) {
            case 1:
                Scanner scan = new Scanner(System.in);
                System.out.println("Jesteś pewny, ta operacje usunie dotychczasowa baze danych i zastąpi ją podstawowa do dnia 2016-11-05");

                while(true){
                    System.out.println("Tak = wciśnij [Y], Nie - wciśnij [N]");
                    String choice = scan.nextLine();

                    if(choice.equalsIgnoreCase("y")){
                        BufferedReader odczyt = new BufferedReader(new FileReader("activ.txt"));
                        PrintWriter zapis = new PrintWriter("insert.sql");
                        OdczytDanych.ReadWriteSql(odczyt, zapis); 	//Odczyt danych z pliku i zapis do insert.sql
                        ConnectDB.CreateTabTyp(stmt); 	// tw. tabeli typ_aktywnosci i dodanie rekordow
                        ConnectDB.CreateTabAkt(stmt);	// tw. tabeli aktywnosci i dodanie bazy do dnia 2016-11-05
                        System.out.println("Utworzono tabele i dodano dane");
                        break;
                    } else if(choice.equalsIgnoreCase("n"))
                        break;
                    else
                        System.out.println("Błąd!");
                }

                System.out.println("Wracam do menu głównego.");
                new Activity();
                break;
            case 2:

                String typ,czas_startu,avg_tempo,temp;
                int czas_trwania, przewyzszenie, avg_tetno, max_tetno, avg_rytm, max_rytm;
                double dystans;
                System.out.println("Dodawanie rekordów");
                System.out.println("W przypadku wciśnięcia enter bez wprowadzenia danych ustawiana jest wartość null");
                Scanner input = new Scanner(System.in);

                System.out.println("Podaj typ aktywności:");
                System.out.println("Biegi,Kolarstwo,Spacerowanie,Plywanie");
                typ = InputNullS(input);

                System.out.println("Podaj czas startu w formacie YYYY-MM-DD HH:MM");
                do {
                    czas_startu = InputNullS(input);
                }while(!CheckCzasStartu(czas_startu));

                System.out.println("Podaj dystans");
                dystans = InputNullD(input);

                System.out.println("Podaj czas trwania w postaci HH:MM:SS");
                temp = InputNullS(input);
                while(!temp.matches("(?:[0-9]\\d|2[0123]):(?:[012345]\\d):(?:[012345]\\d)")){
                    System.out.println("Format sie nie zgadza! Wprowadę jeszcze raz");
                    temp = InputNullS(input);
                }
                czas_trwania = OdczytDanych.timeToSeconds(temp);

                avg_tempo = OdczytDanych.Pace(dystans, czas_trwania);
                avg_tempo = avg_tempo.substring(1, avg_tempo.length()-1); //usuniecie apostrofow

                System.out.println("Podaj przewyższenie w [m].");
                przewyzszenie = InputNullI(input);

                System.out.println("Podaj średnie tętno.");
                avg_tetno = InputNullI(input);

                System.out.println("Podaj maksymalne tętno.");
                max_tetno = InputNullI(input);

                System.out.println("Podaj średni rytm.");
                avg_rytm = InputNullI(input);

                System.out.println("Podaj maksymalny rytm.");
                max_rytm = InputNullI(input);


                ConnectDB.DodajRekord(conn, typ, czas_startu, dystans, czas_trwania, avg_tempo, przewyzszenie, avg_tetno, max_tetno, avg_rytm, max_rytm);
                System.out.println("Wracam do menu głównego.");
                new Activity();
                break;
            case 3:
                //Generowanie wynikow
                System.out.println("");
                System.out.println("Generowanie wyników do bazy");
                System.out.println("------------------------------------------");
                System.out.println("1. Powrót do menu głównego.");
                System.out.println("2. Podsumowanie roczne");
                System.out.println("3. Podsumowanie miesięczne");
                System.out.println("4. Podsumowanie tygodniowe");
                System.out.println("5. Najszybsze 10 aktywności");
                System.out.println("6. Najdłuższe 10 aktywności");
                System.out.println("------------------------------------------");
                System.out.println("");
                try{
                	selectedOption = Integer.parseInt(br.readLine());
                } catch (NumberFormatException e){
                	System.out.println("Musisz wybrać numer!\nWracam do menu głównego");
                	new Activity();
                }
                
                SubMenuGen(selectedOption);
                System.out.println("Wciśnij enter, aby wrócić do menu głównego");
                br.readLine();
                new Activity();
                break;
            case 4:
                // Wyswietlanie wynikow
                System.out.println("Wyświetlanie wyników");
                System.out.println("------------------------------------------");
                System.out.println("1. Powrót do menu głównego.");
                System.out.println("2. Podsumowanie roczne");
                System.out.println("3. Podsumowanie miesięczne");
                System.out.println("4. Podsumowanie tygodniowe");
                System.out.println("5. Najszybsze 10 aktywności");
                System.out.println("6. Najdłuższe 10 aktywności");
                System.out.println("------------------------------------------");
                System.out.println("");

                try{
                	selectedOption = Integer.parseInt(br.readLine());
                } catch (NumberFormatException e){
                	System.out.println("Musisz wybraś numer!\nWracam do menu głównego");
                	new Activity();
                }
                SubMenuShow(selectedOption);
                System.out.println("Wracam do menu głównego.");
                new Activity();
                break;
            case 5:
                quitProgram();
                break;
            default:
                System.out.println("Nie ma takiego wyboru, wracam do menu głównego");
                new Activity();
                break;
        }


    }

    public void SubMenuGen(int subMenuChoice) throws SQLException {
    	try{
            switch(subMenuChoice){
            case 1:
                new Activity();
                break;
            case 2:
                Obliczenia.CreateSummary(conn ,stmt, "%Y", "podsumowanie_rok");
                break;
            case 3:
                Obliczenia.CreateSummary(conn, stmt, "%Y-%m", "podsumowanie_miesiac");
                break;
            case 4:
                Obliczenia.CreateSummary(conn, stmt, "%Y-%W", "podsumowanie_tydzien");
                break;
            case 5:
                Obliczenia.CreateTenFastest(conn,stmt,"NajszybszeBiegi","Biegi", "((czas_trwania/60.0)/dystans) ASC LIMIT 10");
                Obliczenia.CreateTenFastest(conn,stmt,"NajszybszeKolarstwo","Kolarstwo", "((czas_trwania/60.0)/dystans) ASC LIMIT 10");
                break;
            case 6:
                Obliczenia.CreateTenFastest(conn,stmt,"NajdluzszeBiegi","Biegi", "dystans DESC LIMIT 10");
                Obliczenia.CreateTenFastest(conn,stmt,"NajdluzszeKolarstwo","Kolarstwo", "dystans DESC LIMIT 10");
                break;
            default:
                System.out.println("Nie ma takiego wyboru, wracam do menu głównego");
                new Activity();
                break;
        } 
        }catch (SQLException e){
        	System.out.println("Czy utworzyles tabele i baze danych?");
        	System.out.println("Przetworzenie nie udane.\n Wracam do menu głównego." );
        	new Activity();
        }
    }

 

    public void SubMenuShow(int subMenuChoice){

        String tableName = null;
        switch(subMenuChoice){
            case 1:
                new Activity();
                break;
            case 2:
                kategorie();
                tableName = "podsumowanie_rok";
                break;
            case 3:
                kategorie();
                tableName = "podsumowanie_miesiac";
                break;
            case 4:
                kategorie();
                tableName = "podsumowanie_tydzien";
                break;
            case 5:
                System.out.println("------------------------------------------");
                System.out.println("1. Biegi");
                System.out.println("2. Kolarstwo");
                try {
                    try{
                    	selectedOption = Integer.parseInt(br.readLine());
                    } catch (NumberFormatException e){
                    	System.out.println("Musisz wybrać numer!\nWracam do menu głównego");
                    	new Activity();
                    }
                    switch(selectedOption) {
                        case 1:
                            Obliczenia.ShowTenFastest(stmt,"NajszybszeBiegi");
                            System.out.println("Wracam do menu głównego.");
                            new Activity();
                            break;
                        case 2:
                            Obliczenia.ShowTenFastest(stmt,"NajszybszeKolarstwo");
                            System.out.println("Wracam do menu głównego.");
                            new Activity();
                            break;
                        default:
                            System.out.println("Nie ma takiego wyboru, wracam do menu głównego");
                            new Activity();
                            break;
                    }
                } catch (IOException  | SQLException ex) {
                	System.out.println("Czy na pewno wygenerowałeś wyniki?");
                	System.out.println("Wracam do menu.");
                    new Activity();
                }

                break;
            case 6:
                System.out.println("------------------------------------------");
                System.out.println("1. Biegi");
                System.out.println("2. Kolarstwo");
                try {
                    try{
                    	selectedOption = Integer.parseInt(br.readLine());
                    } catch (NumberFormatException e){
                    	System.out.println("Musisz wybrać numer!\nWracam do menu głównego");
                    	new Activity();
                    }
                    switch(selectedOption) {
                        case 1:
                            Obliczenia.ShowTenFastest(stmt,"NajdluzszeBiegi");
                            System.out.println("Wracam do menu głównego.");
                            new Activity();
                            break;
                        case 2:
                            Obliczenia.ShowTenFastest(stmt,"NajdluzszeKolarstwo");
                            System.out.println("Wracam do menu głównego.");
                            new Activity();
                            break;
                        default:
                            System.out.println("Nie ma takiego wyboru, wracam do menu głównego");
                            new Activity();
                            break;
                    }
                } catch (IOException  | SQLException ex) {
                	System.out.println("Czy na pewno wygenerowałeś wyniki?");
                	System.out.println("Wracam do menu.");
                    new Activity();
                }

                break;
            default:
                System.out.println("Nie ma takiego wyboru, wracam do menu głównego");
                new Activity();
                break;
        }



        try {
            try{
            	selectedOption = Integer.parseInt(br.readLine());
            } catch (NumberFormatException e){
            	System.out.println("Musisz wybrać numer!\nWracam do menu głównego");
            	new Activity();
            }
            switch(selectedOption) {
                case 1:
                    Obliczenia.ShowSummary(stmt,"Biegi",tableName);
                    break;
                case 2:
                    Obliczenia.ShowSummary(stmt,"Kolarstwo", tableName);
                    break;
                case 3:
                    Obliczenia.ShowSummary(stmt,"Spacerowanie",tableName);
                    break;
                case 4:
                    Obliczenia.ShowSummary(stmt,"Plywanie", tableName);
                    break;
                default:
                    System.out.println("Nie ma takiego wyboru, wracam do menu głównego");
                    new Activity();
                    break;
            }
        } catch (IOException  | SQLException ex) {
        	System.out.println("Czy na pewno wygenerowałeś wyniki?");
        	System.out.println("Wracam do menu.");
            new Activity();
        }


    }


    public void quitProgram() {
        System.out.println("Zamykam program."); System.exit(1);
    }

    public static boolean CheckCzasStartu(String value) {
        Date date = null;
        try {
            SimpleDateFormat sdf = new SimpleDateFormat("yyyy-MM-dd HH:mm");
            date = sdf.parse(value);
            if (!value.equals(sdf.format(date))) {
                date = null;
            }
        } catch (ParseException ex) {
            System.out.println("Format sie nie zgadza! Wprowadź jeszcze raz");
            return false;
        }
        return date != null;
    }

    public String InputNullS(Scanner sc){
        System.out.println("Podaj dane zatwierdzając enterem.");
        String s = sc.nextLine();
        if(s.equals(""))
            return "null";
        else
            return s;
    }

    public int InputNullI(Scanner sc){
        System.out.println("Podaj dane zatwierdzając enterem.");
        String s = sc.nextLine();
        if(s.equals(""))
            return 0;
        else
            return Integer.parseInt(s);
    }

    public double InputNullD(Scanner sc){
        System.out.println("Podaj dane zatwierdzając enterem.");
        String s = sc.nextLine();
        if(s.equals(""))
            return 0;
        else
            return Double.parseDouble(s);
    }

    public static void main(String[] args) throws SQLException, NumberFormatException, IOException{

        System.out.println("Nawiązywanie połączenia z baza w trakcie uruchamiania");
        // połączenie z baza przed wyświetleniem menu
        conn = ConnectDB.polacz();
        stmt = conn.createStatement();

        //Menu
        new Activity();

    }
}
