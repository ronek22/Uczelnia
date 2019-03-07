import java.sql.Connection;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.sql.Statement;

public class Obliczenia {

    public static void ShowSummary(Statement stmt, String typ, String tableName) throws SQLException{
        String sql = "SELECT przedzial_czasu, nazwa, dystans, laczny_czas, avg_tempo, przewyzszenie, tetno, rytm FROM "+tableName+" INNER JOIN typ_aktywnosci ON "+tableName+".id_typ=typ_aktywnosci.id_typ WHERE nazwa='"+typ+"';";
        ResultSet rs = stmt.executeQuery(sql);
        String label = (typ.equals("Kolarstwo")) ? "Speed" : "Tempo";
        System.out.println("-------------------------------------------------------------------------------------");
        System.out.printf("%10s|%15s|%10s|%14s|%7s|%7s|%5s|%5s",
                "Data", "Typ", "Dystans", "Czas Trwania", label, "W górę", "Tętno", "Rytm");
        System.out.println("\n-------------------------------------------------------------------------------------");

        while(rs.next()){
            int duration = rs.getInt("laczny_czas"); // do obliczenia czasu w postaci HH:MM:SS
            double distance = rs.getDouble(3);
            String czas = String.format("%d:%02d:%02d", duration / 3600, (duration % 3600) / 60, (duration % 60));


            System.out.printf("%10s|%15s|%10s|%14s|%7s|%7s|%5s|%5s\n",
                    rs.getString(1), rs.getString(2), rs.getString(3), czas, (typ.equals("Kolarstwo")) ? OdczytDanych.Speed(distance,duration) : rs.getString(5), rs.getString(6),rs.getString(7),rs.getString(8));
        }
        System.out.println("-------------------------------------------------------------------------------------");
    }

    public static void CreateSummary(Connection conn, Statement stmt,String dateFormat, String tableName) throws SQLException {
        ConnectDB.CreateTabSummary(stmt, tableName);
        String query = "SELECT strftime('" + dateFormat +"',czas_startu) AS przedzial_czasu, id_typ, Round(Sum(dystans),1) AS dystans, Sum(czas_trwania) AS laczny_czas, Sum(przewyzszenie) AS przewyzszenie, CAST(AVG(avg_tetno) as INTEGER) AS tetno, CAST(AVG(avg_rytm) as INTEGER) AS rytm FROM aktywnosci Group By strftime('" + dateFormat +"',czas_startu), id_typ ORDER BY przedzial_czasu, id_typ";
        ResultSet rs = stmt.executeQuery(query);
        String c = ","; //comma shortcut
        Statement stIns = conn.createStatement();

        while(rs.next()){
            double distance = rs.getDouble("dystans");
            int duration = rs.getInt("laczny_czas");
            String pace = OdczytDanych.Pace(distance, duration);
            String insert = "INSERT INTO " + tableName + " (przedzial_czasu, id_typ, dystans, avg_tempo, laczny_czas, przewyzszenie, tetno, rytm) VALUES (";
            insert+="'"+rs.getString(1)+"'"+c+rs.getString(2)+c+rs.getString(3)+c+pace+c+rs.getString(4)+c+rs.getString(5)+c+rs.getString(6)+c+rs.getString(7)+")";
            stIns.executeUpdate(insert);
        }
        System.out.println("Dodano rekordy");
    }

    public static void CreateTenFastest(Connection conn, Statement stmt, String tableName, String typ, String order) throws SQLException {
        ConnectDB.CreateTopTen(stmt, tableName);
        String query = "SELECT * FROM aktywnosci WHERE id_typ="+OdczytDanych.Kategorie(typ)+" ORDER BY "+order;
        ResultSet rs = stmt.executeQuery(query);
        String c=",";
        Statement stIns = conn.createStatement();

        while(rs.next()){
            int duration = rs.getInt("czas_trwania"); // do obliczenia czasu w postaci HH:MM:SS
            String czas = String.format("%s:%02d:%02d", ((duration / 3600)<10) ? "0"+String.valueOf(duration / 3600) : String.valueOf(duration / 3600), (duration % 3600) / 60, (duration % 60));
            String insert = "INSERT INTO " + tableName + " (czas_startu,dystans,czas_trwania,avg_tempo,przewyzszenie,avg_tetno,max_tetno,avg_rytm,max_rytm) VALUES (";
            insert+="'"+rs.getString(3)+"',"+rs.getString(4)+",'"+czas+"','"+rs.getString(6)+"',"+rs.getString(7)+c+rs.getString(8)+c+rs.getString(9)+c+rs.getString(10)+c+rs.getString(11)+")";
            stIns.executeUpdate(insert);
        }
        System.out.println("Utworzono ranking top10 dla kategorii: " + typ);
    }

    public static void ShowTenFastest(Statement stmt, String tableName) throws SQLException{
        String sql = "SELECT * FROM "+tableName;
        ResultSet rs = stmt.executeQuery(sql);
        String label = (tableName.contains("Kolarstwo")) ? "Speed" : "Tempo";
        System.out.println("------------------------------------------------------------------------------------------------------------");
        System.out.printf("%18s|%10s|%14s|%9s|%9s|%9s|%9s|%9s|%9s",
                "Data", "Dystans", "Czas Trwania", label, "W górę", "AvgTętno", "MaxTętno", "AvgRytm","MaxRytm");
        System.out.println("\n------------------------------------------------------------------------------------------------------------");

        while(rs.next()){
            double distance = rs.getDouble(3);
            String temp = rs.getString(4);
            int czas = OdczytDanych.timeToSeconds(temp);
            System.out.printf("%18s|%10s|%14s|%9s|%9s|%9s|%9s|%9s|%9s\n",
                    rs.getString(2), rs.getString(3), rs.getString(4), (tableName.contains("Kolarstwo")) ? OdczytDanych.Speed(distance,czas) : rs.getString(5), rs.getString(6),rs.getString(7),rs.getString(8), rs.getString(9), rs.getString(10));
        }
        System.out.println("------------------------------------------------------------------------------------------------------------");
    }
}

