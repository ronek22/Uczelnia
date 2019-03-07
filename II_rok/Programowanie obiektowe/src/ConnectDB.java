import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.SQLException;
import java.sql.Statement;


public class ConnectDB {
    public static final String DRIVER = "org.sqlite.JDBC";
    public static final String DB_URL = "jdbc:sqlite:test1.db";
    private static Connection conn;
    private static Statement stmt;

    public static Connection polacz() {
        // dodaj klase JDBC
        try {
            Class.forName(DRIVER);
        } catch (ClassNotFoundException e) {
            System.err.println("Brak sterownika");
            e.printStackTrace();
        }

        // nawiazywanie polaczenia
        try {
            conn = DriverManager.getConnection(DB_URL);
            System.out.println("Połączenie nawiązane!");
        } catch (SQLException ex) {
            System.out.println("Problem z otwarciem polaczenia");
        }
        return conn;
    }

    public static void ExecuteSql(String sql){
        try {
            stmt = conn.createStatement();
            stmt.execute(sql);
        } catch (SQLException ex) {
            System.out.println("Nie mogę wykonać polecenia.");
        }
    }
    // Tworzenie tabeli typ_aktywnosci i wypelnienie jej;
    public static void CreateTabTyp(Statement stmt) {
        try {
            String createTable="CREATE TABLE IF NOT EXISTS typ_aktywnosci(id_typ INTEGER PRIMARY KEY, nazwa VARCHAR(20))";
            stmt.execute(createTable);
        } catch (SQLException e){
            System.out.println("Nie mogę stworzyć tabeli " + e.getMessage());
        }

        try {
            stmt.executeUpdate("DELETE FROM typ_aktywnosci;");
        } catch (SQLException e){
            System.out.println("Nie mogę usunac danych " + e.getMessage());
        }

        try {
            stmt.executeUpdate("INSERT INTO typ_aktywnosci (id_typ,nazwa) VALUES (1,'Biegi');");
            stmt.executeUpdate("INSERT INTO typ_aktywnosci (id_typ,nazwa) VALUES (2,'Kolarstwo');");
            stmt.executeUpdate("INSERT INTO typ_aktywnosci (id_typ,nazwa) VALUES (3,'Spacerowanie');");
            stmt.executeUpdate("INSERT INTO typ_aktywnosci (id_typ,nazwa) VALUES (4,'Plywanie');");
            stmt.executeUpdate("INSERT INTO typ_aktywnosci (id_typ,nazwa) VALUES (5,'Inne');");
        } catch (Exception e) {
            System.out.println("Nie mogę dodać danych " + e.getMessage());
        }

        System.out.println("Tabela typ_aktywnosci z zawartoscia stworzona.");
    }

    public static void CreateTopTen(Statement stmt, String tableName){
        try {
            String createTable="CREATE TABLE IF NOT EXISTS " + tableName
                    +"(id INTEGER PRIMARY KEY AUTOINCREMENT,"
                    +"czas_startu TEXT,"
                    +"dystans REAL,"
                    +"czas_trwania TEXT,"
                    +"avg_tempo TEXT,"
                    +"przewyzszenie INTEGER,"
                    +"avg_tetno INTEGER,"
                    +"max_tetno INTEGER,"
                    +"avg_rytm INTEGER,"
                    +"max_rytm INTEGER)";
            stmt.execute(createTable);
        } catch (SQLException e){
            System.out.println("Nie mogę stworzyć tabeli " + e.getMessage());
        }

        try {
            stmt.executeUpdate("DELETE FROM " + tableName + ";");
            stmt.executeUpdate("DELETE FROM sqlite_sequence WHERE name='"+tableName+"';");
        } catch (SQLException e){
            System.out.println("Nie mogę usunac danych " + e.getMessage());
        }
        System.out.println("Utworzono tabele!");
    }

    public static void CreateTabSummary(Statement stmt, String tableName){
        try {
            String createTable="CREATE TABLE IF NOT EXISTS " + tableName +" (przedzial_czasu CHAR(8) NOT NULL, id_typ INTEGER NOT NULL,"
                    +"dystans REAL, laczny_czas INTEGER, avg_tempo TEXT, przewyzszenie INTEGER,"
                    +"tetno INTEGER, rytm INTEGER,"
                    +"PRIMARY KEY ( przedzial_czasu, id_typ))";
            stmt.execute(createTable);
        } catch (SQLException e){
            System.out.println("Nie mogę stworzyć tabeli " + e.getMessage());
        }

        try {
            stmt.executeUpdate("DELETE FROM " + tableName + ";");
            stmt.executeUpdate("DELETE FROM sqlite_sequence WHERE name='"+tableName+"';");
        } catch (SQLException e){
            System.out.println("Nie mogę usunac danych " + e.getMessage());
        }

        System.out.println("Utworzono tabele!");
    }

    // Tworzenie tabeli aktywnosci i dodawanie insertow
    public static void CreateTabAkt(Statement stmt) throws IOException, SQLException {
        try {
            String createTable="CREATE TABLE IF NOT EXISTS aktywnosci"
                    +"(id_aktywnosci INTEGER PRIMARY KEY AUTOINCREMENT,"
                    +"id_typ INTEGER,"
                    +"czas_startu TEXT UNIQUE,"
                    +"dystans REAL,"
                    +"czas_trwania INTEGER,"
                    +"avg_tempo TEXT,"
                    +"przewyzszenie INTEGER,"
                    +"avg_tetno INTEGER,"
                    +"max_tetno INTEGER,"
                    +"avg_rytm INTEGER,"
                    +"max_rytm INTEGER,"
                    +"FOREIGN KEY(id_typ) REFERENCES typ_aktywnosci(id_typ))";;
            stmt.execute(createTable);
        } catch (SQLException e){
            System.out.println("Nie mogę stworzyć tabeli " + e.getMessage());
        }

        try {
            stmt.executeUpdate("DELETE FROM aktywnosci;");
            stmt.executeUpdate("DELETE FROM sqlite_sequence WHERE name='aktywnosci';");
        } catch (SQLException e){
            System.out.println("Nie mogę usunac danych " + e.getMessage());
        }

        BufferedReader odczyt = new BufferedReader(new FileReader("insert.sql"));
        String rekord;
        try{
            while ((rekord = odczyt.readLine()) != null){
                stmt.executeUpdate(rekord);
            }
        } catch (SQLException e) {
            System.err.println("Blad przy dodawaniu aktywnosci");
            e.printStackTrace();
        }
        odczyt.close();
        System.out.println("Tabela aktywnosci z zawartoscia stworzona.");
    }

    public static void SetIntOrNull(PreparedStatement p, int kolumna, int wartosc) throws SQLException{
        if (wartosc != 0) {
            p.setInt(kolumna, wartosc);
        } else {
            p.setNull(kolumna, java.sql.Types.INTEGER);
        }
    }

    public static void DodajRekord
            (Connection conn, String typ, String czas_startu, double dystans, int czas_trwania, String avg_tempo, int przewyzszenie, int avg_tetno, int max_tetno, int avg_rytm, int max_rytm ) throws SQLException {
        PreparedStatement insert = conn.prepareStatement
                ("INSERT INTO aktywnosci (id_typ,czas_startu,dystans,czas_trwania,avg_tempo,przewyzszenie,avg_tetno,max_tetno,avg_rytm,max_rytm) VALUES (?,?,?,?,?,?,?,?,?,?)");
        insert.setInt(1, OdczytDanych.Kategorie(typ));
        insert.setString(2, czas_startu);
        insert.setDouble(3, dystans);
        insert.setInt(4, czas_trwania);
        insert.setString(5, avg_tempo);
        SetIntOrNull(insert,6, przewyzszenie);
        SetIntOrNull(insert,7, avg_tetno);
        SetIntOrNull(insert,8, max_tetno);
        SetIntOrNull(insert,9, avg_rytm);
        SetIntOrNull(insert,10, max_rytm);

        insert.executeUpdate();
    }
}
