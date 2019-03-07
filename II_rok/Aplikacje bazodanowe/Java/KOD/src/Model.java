import org.sqlite.SQLiteConfig;

import java.io.File;
import java.sql.*;
import java.util.*;
import javax.swing.*;
import javax.swing.table.DefaultTableModel;


public class Model {
	private final String JDBC_CONNECT = "jdbc:sqlite:Company.db";
	private final String JDBC_CLASS = "org.sqlite.JDBC";

	private Connection connection;
	private Statement statement;
	private ResultSet wynik;

	public Model() {

		File f = new File("Company.db");
		if(!f.exists())
		{
			try {
				connection = getConnection();
				statement = connection.createStatement();
			} catch (SQLException  | NullPointerException e) {
				System.err.println(e.getClass().getName() + ": " + e.getMessage());
				JOptionPane.showMessageDialog(null, "Blad bazy danych : " + e.getMessage());
			}


			createTables();

			insertStanowisko("Pracownik","zwyczajny pracownik",1500,2500,"2015-01-01");
			insertStanowisko("Kierownik","zarządza pracownikami",3000,4000,"2015-01-02");
			insertStanowisko("Dyrektor","zarządza całą firmą",10000,15000, "2015-01-03");

			insertPracownik(1,"Jan","Kowalski","1960-10-12","2000-01-02", 1800);
			insertPracownik(1,"Kamil", "Janiak", "1980-12-11","2005-05-05", 2000);
			insertPracownik(2,"Piotr", "Nowak", "1972-12-10","1999-05-10", 3500);
			insertPracownik(3,"Adam", "Bierka","1958-02-10","1990-08-11", 14000);

			insertProjekt("Wdrozenie_systemu",null,"2011-01-05", "2012-11-10",20000);
			insertProjekt("Implementacja_algorytmu","sortowania","2012-12-12","2013-01-05",30000);
			insertProjekt("Analiza_wydatkow",null,"2013-05-05","2013-05-27",40000);

			insertZadanie(1,3,15,20,null,"2011-02-02","2011-05-05");
			insertZadanie(1,1,10,40,null,"2011-06-02","2011-07-05");
			insertZadanie(2,2,12,10,null,"2012-12-24","2013-01-02");
			insertZadanie(3,1,12,30,null,"2013-05-06","2013-05-10");
			insertZadanie(3,3,15,25,null,"2013-05-08","2011-05-15");

			System.out.println("Dodano przykladowe rekordy");

		} else{
			try {
				connection = getConnection();
				statement = connection.createStatement();
			} catch (SQLException  | NullPointerException e) {
				System.err.println(e.getClass().getName() + ": " + e.getMessage());
				JOptionPane.showMessageDialog(null, "Blad bazy danych : " + e.getMessage());
			}

		}

	}

//	public void restartConnection(){
//		try{
//		closeConnection();
//		connection = getConnection();
//		statement = connection.createStatement();
//	} catch (SQLException  | NullPointerException e) {
//		System.err.println(e.getClass().getName() + ": " + e.getMessage());
//		JOptionPane.showMessageDialog(null, "Blad bazy danych : " + e.getMessage());
//	}
//	}

	private Connection getConnection() {
		try {
			Class.forName(JDBC_CLASS);
			SQLiteConfig config = new SQLiteConfig();
			config.enforceForeignKeys(true);
			Connection c = DriverManager.getConnection(JDBC_CONNECT,config.toProperties());
			System.out.println("Polaczenie z baza nawiazane");
			return c;
		} catch (ClassNotFoundException | SQLException e) {
			System.err.println(e.getClass().getName() + ": " + e.getMessage());
			JOptionPane.showMessageDialog(null, "Blad bazy danych : " + e.getMessage());
		}
		return null;
	}

	public void createTables() {

		// STANOWISKO
		String sql = "CREATE TABLE IF NOT EXISTS stanowisko (" +
				"id_stanowisko INTEGER PRIMARY KEY AUTOINCREMENT," +
				"nazwa TEXT NOT NULL UNIQUE," +
				"opis TEXT," +
				"dolna INTEGER NOT NULL CHECK (dolna > 0)," +
				"gorna INTEGER CHECK (gorna > 0)," +
				"data_dodania TEXT NOT NULL DEFAULT (DATE('now','localtime')) CHECK (DATE(data_dodania) IS NOT NULL));";

		try {
			statement.executeUpdate(sql);
		} catch (SQLException e) {
			System.err.println(e.getClass().getName() + ": " + e.getMessage());
			JOptionPane.showMessageDialog(null, "Problem z utworzeniem tabeli stanowisko : " + e.getMessage());
		}

		// PRACOWNIK
		sql = "CREATE TABLE IF NOT EXISTS pracownik (" +
				"id_pracownik INTEGER PRIMARY KEY AUTOINCREMENT," +
				"id_stanowisko INTEGER NOT NULL," +
				"imie TEXT NOT NULL," +
				"nazwisko TEXT NOT NULL," +
				"data_urodzenia TEXT NOT NULL CHECK (DATE(data_urodzenia) IS NOT NULL AND data_urodzenia < DATE('now','localtime'))," +
				"data_zatrudnienia TEXT NOT NULL DEFAULT (DATE('now','localtime')) CHECK (DATE(data_zatrudnienia) IS NOT NULL)," +
				"pensja REAL NOT NULL," +
				"UNIQUE(imie,nazwisko),"+
				"FOREIGN KEY(id_stanowisko) REFERENCES stanowisko(id_stanowisko) ON DELETE CASCADE);";

		try {
			statement.executeUpdate(sql);
		} catch (SQLException e) {
			System.err.println(e.getClass().getName() + ": " + e.getMessage());
			JOptionPane.showMessageDialog(null, "Problem z utworzeniem tabeli pracownik : " + e.getMessage());
		}

		// NAGRODA
		sql = "CREATE TABLE IF NOT EXISTS nagroda (" +
				"id_nagroda INTEGER PRIMARY KEY AUTOINCREMENT," +
				"id_pracownik INTEGER NOT NULL," +
				"nazwa TEXT NOT NULL UNIQUE," +
				"opis TEXT," +
				"wartosc REAL NOT NULL," +
				"data_otrzymania TEXT NOT NULL DEFAULT (DATE('now','localtime')) CHECK (DATE(data_otrzymania) IS NOT NULL)," +
				"nagroda_za TEXT," +
				"FOREIGN KEY(id_pracownik) REFERENCES pracownik(id_pracownik) ON DELETE CASCADE ON UPDATE CASCADE);";

		try {
			statement.executeUpdate(sql);
		} catch (SQLException e) {
			System.err.println(e.getClass().getName() + ": " + e.getMessage());
			JOptionPane.showMessageDialog(null, "Problem z utworzeniem tabeli nagroda : " + e.getMessage());
		}

		// PROJEKT
		sql = "CREATE TABLE IF NOT EXISTS projekt (" +
				"id_projekt INTEGER PRIMARY KEY AUTOINCREMENT," +
				"nazwa TEXT NOT NULL UNIQUE,"+
				"opis TEXT," +
				"data_startu TEXT NOT NULL DEFAULT (DATE('now','localtime')) CHECK (DATE(data_startu) IS NOT NULL) ," +
				"data_konca TEXT NOT NULL CHECK (DATE(data_konca) IS NOT NULL),"+
				"budzet REAL DEFAULT 0);";

		try {
			statement.executeUpdate(sql);
		} catch (SQLException e) {
			System.err.println(e.getClass().getName() + ": " + e.getMessage());
			JOptionPane.showMessageDialog(null, "Problem z utworzeniem tabeli projekt : " + e.getMessage());
		}


		// ZADANIA PRACOWNIKOW
		sql = "CREATE TABLE IF NOT EXISTS zadania_pracownikow (" +
				"id_projekt INTEGER NOT NULL REFERENCES projekt(id_projekt) ON DELETE CASCADE," +
				"id_pracownik INTEGER NOT NULL REFERENCES pracownik(id_pracownik) ON DELETE CASCADE," +
				"stawka REAL UNSIGNED NULL," +
				"ilosc_godzin REAL UNSIGNED NULL," +
				"komentarz TEXT,"+
				"data_startu TEXT NOT NULL DEFAULT (DATE('now','localtime')) CHECK (DATE(data_startu) IS NOT NULL)," +
				"data_konca TEXT NOT NULL CHECK (DATE(data_konca) IS NOT NULL),"+
				"PRIMARY KEY(id_projekt,id_pracownik));";

		try {
			statement.executeUpdate(sql);
		} catch (SQLException e) {
			System.err.println(e.getClass().getName() + ": " + e.getMessage());
			JOptionPane.showMessageDialog(null, "Problem z utworzeniem tabeli pracownik : " + e.getMessage());
		}

		// TRIGGER SPRAWDZ PENSJE STANOWISKO
		sql = "CREATE TRIGGER IF NOT EXISTS pensja_pracownika_check "+
				" BEFORE INSERT ON pracownik "+
				"WHEN NEW.pensja < (SELECT dolna FROM stanowisko WHERE id_stanowisko = NEW.id_stanowisko) "+
				"OR NEW.pensja > (SELECT gorna FROM stanowisko WHERE id_stanowisko = NEW.id_stanowisko) "+
				"BEGIN "+
				"SELECT RAISE(FAIL, 'Pensja nie miesci sie w przedziale!'); "+
				"END;";
		try {
			statement.executeUpdate(sql);
		} catch (SQLException e) {
			System.err.println(e.getClass().getName() + ": " + e.getMessage());
			JOptionPane.showMessageDialog(null, "Problem z utworzeniem wyzwalacza dla tabeli pracownik : " + e.getMessage());
		}

		System.out.println("Utworzono tabele");

	}

	public boolean insertStanowisko(String nazwa, String opis, double dolna, double gorna, String data_dod) {
		try {
			if(data_dod.equals("NULL") || data_dod.equals("DEFAULT") || data_dod.equals("")){
				PreparedStatement prep = connection.prepareStatement(
						"insert into stanowisko(nazwa, opis, dolna, gorna) VALUES (?,?,?,?);");
				prep.setString(1, nazwa);
				prep.setString(2, opis);
				prep.setDouble(3, dolna);
				prep.setDouble(4, gorna);
				prep.execute();
			} else {
				PreparedStatement prep = connection.prepareStatement(
						"insert into stanowisko(nazwa, opis, dolna, gorna,data_dodania) VALUES (?,?,?,?,?);");
				prep.setString(1, nazwa);
				prep.setString(2, opis);
				prep.setDouble(3, dolna);
				prep.setDouble(4, gorna);
				prep.setString(5, data_dod);
				prep.execute();
			}

		} catch (SQLException e) {
			System.err.println(e.getClass().getName() + ": " + e.getMessage());
			JOptionPane.showMessageDialog(null, "Problem z dodaniem stanowiska : " + e.getMessage());
			return false;
		}
		return true;
	}


	public boolean insertPracownik(int id_stanowisko, String imie,
								   String nazwisko, String data_urodzenia,
								   String data_zatrudnienia, double pensja){
		try {
			if(data_zatrudnienia.equals("NULL") || data_zatrudnienia.equals("DEFAULT") || data_zatrudnienia.equals("")){
				PreparedStatement prep = connection.prepareStatement(
						"insert into pracownik(id_stanowisko,imie,nazwisko,data_urodzenia,pensja) VALUES (?,?,?,?,?);");
				prep.setInt(1, id_stanowisko);
				prep.setString(2, imie);
				prep.setString(3, nazwisko);
				prep.setString(4, data_urodzenia);
				prep.setDouble(5, pensja);

				prep.execute();
			} else {
				PreparedStatement prep = connection.prepareStatement(
						"insert into pracownik(id_stanowisko,imie,nazwisko,data_urodzenia,data_zatrudnienia,pensja) VALUES (?,?,?,?,?,?);");
				prep.setInt(1, id_stanowisko);
				prep.setString(2, imie);
				prep.setString(3, nazwisko);
				prep.setString(4, data_urodzenia);
				prep.setString(5, data_zatrudnienia);
				prep.setDouble(6, pensja);

				prep.execute();
			}

		} catch (SQLException e) {
			System.err.println(e.getClass().getName() + ": " + e.getMessage());
			JOptionPane.showMessageDialog(null, "Problem z dodaniem pracownika : " + e.getMessage());
			return false;
		}
		return true;
	}

	public boolean insertNagroda(int id_pracownik,String nazwa, String opis, double wartosc, String data_otrzymania, String nag_za) {

		try {
			if(data_otrzymania.equals("NULL") || data_otrzymania.equals("DEFAULT") || data_otrzymania.equals("")){
				PreparedStatement prep = connection.prepareStatement(
						"insert into nagroda(id_pracownik,nazwa,opis,wartosc,nagroda_za) VALUES (?,?,?,?,?);");
				prep.setInt(1, id_pracownik);
				prep.setString(2, nazwa);
				prep.setString(3, opis);
				prep.setDouble(4, wartosc);
				prep.setString(5,nag_za);

				prep.execute();
			} else {
				PreparedStatement prep = connection.prepareStatement(
						"insert into nagroda(id_pracownik,nazwa,opis,wartosc,data_otrzymania,nagroda_za) VALUES (?,?,?,?,?,?);");
				prep.setInt(1, id_pracownik);
				prep.setString(2, nazwa);
				prep.setString(3, opis);
				prep.setDouble(4, wartosc);
				prep.setString(5, data_otrzymania);
				prep.setString(6,nag_za);

				prep.execute();
			}

		} catch (SQLException e) {
			System.err.println(e.getClass().getName() + ": " + e.getMessage());
			JOptionPane.showMessageDialog(null, "Problem z dodaniem nagrody : " + e.getMessage());
			return false;
		}
		return true;
	}

	public boolean insertProjekt(String nazwa,String opis, String data_startu,
								 String data_konca, double budzet){
		try {
			PreparedStatement prep = connection.prepareStatement(
					"insert into projekt(nazwa, opis, data_startu, data_konca,budzet) VALUES (?,?,?,?,?);");
			prep.setString(1,nazwa);
			prep.setString(2,opis);
			prep.setString(3,data_startu);
			prep.setString(4,data_konca);
			prep.setDouble(5,budzet);
			prep.execute();
		} catch (SQLException e) {
			System.err.println(e.getClass().getName() + ": " + e.getMessage());
			JOptionPane.showMessageDialog(null, "Problem z dodaniem projektu : " + e.getMessage());
			return false;
		}
		return true;
	}

	public boolean insertZadanie(int id_projekt, int id_pracownik, double stawka, double ilosc_godzin, String komentarz,String data_startu,
								 String data_konca){
		try {
			PreparedStatement prep = connection.prepareStatement(
					"insert into zadania_pracownikow(id_projekt,id_pracownik,stawka,ilosc_godzin,komentarz,data_startu,data_konca) VALUES (?,?,?,?,?,?,?);");
			prep.setInt(1, id_projekt);
			prep.setInt(2,id_pracownik);
			prep.setDouble(3, stawka);
			prep.setDouble(4, ilosc_godzin);
			prep.setString(5,komentarz);
			prep.setString(6,data_startu);
			prep.setString(7,data_konca);
			prep.execute();
		} catch (SQLException e) {
			System.err.println(e.getClass().getName() + ": " + e.getMessage());
			JOptionPane.showMessageDialog(null, "Problem z dodaniem zadanie : " + e.getMessage());
			return false;
		}
		return true;
	}

	public boolean updateStanowisko(String stara_nazwa, String nazwa,String opis, double dolna, double gorna, String data_dod) {
		try {
			PreparedStatement prep = connection.prepareStatement(
					"UPDATE stanowisko SET nazwa=?, opis=?, dolna=?, gorna=?, data_dodania=? WHERE nazwa=?;");
			prep.setString(1, nazwa);
			prep.setString(2, opis);
			prep.setDouble(3, dolna);
			prep.setDouble(4, gorna);
			prep.setString(5,data_dod);
			prep.setString(6,stara_nazwa);
			prep.executeUpdate();
		} catch (SQLException e) {
			System.err.println(e.getClass().getName() + ": " + e.getMessage());
			JOptionPane.showMessageDialog(null, "Problem z edytowaniem stanowiska : " + e.getMessage());
			return false;
		}
		return true;
	}

	public boolean updatePracownik(String old_imie, String old_nazwisko, int id_stanowisko, String imie,
								   String nazwisko, String data_urodzenia,
								   String data_zatrudnienia, double pensja){
		try {
			PreparedStatement prep = connection.prepareStatement(
					"UPDATE pracownik SET id_stanowisko=?, imie=?, nazwisko=?, data_urodzenia=?, data_zatrudnienia=?,pensja=? WHERE imie=? AND nazwisko=?;");
			prep.setInt(1, id_stanowisko);
			prep.setString(2, imie);
			prep.setString(3, nazwisko);
			prep.setString(4, data_urodzenia);
			prep.setString(5, data_zatrudnienia);
			prep.setDouble(6, pensja);
			prep.setString(7,old_imie);
			prep.setString(8,old_nazwisko);
			prep.executeUpdate();
		} catch (SQLException e) {
			System.err.println(e.getClass().getName() + ": " + e.getMessage());
			JOptionPane.showMessageDialog(null, "Problem z edytowaniem stanowiska : " + e.getMessage());
			return false;
		}
		return true;
	}

	public boolean updatePracownik(String old_imie, String old_nazwisko, double pensja){
		try {
			PreparedStatement prep = connection.prepareStatement(
					"UPDATE pracownik SET pensja=? WHERE imie=? AND nazwisko=?;");
			prep.setDouble(1, pensja);
			prep.setString(2,old_imie);
			prep.setString(3,old_nazwisko);
			prep.executeUpdate();
		} catch (SQLException e) {
			System.err.println(e.getClass().getName() + ": " + e.getMessage());
			JOptionPane.showMessageDialog(null, "Problem z edytowaniem stanowiska : " + e.getMessage());
			return false;
		}
		return true;
	}

	public boolean updateNagroda(String old_nazwa,String nazwa,String opis, double wartosc, String data_otrzymania, String nag_za){
		try {
			PreparedStatement prep = connection.prepareStatement(
					"UPDATE nagroda SET nazwa=?, opis=?, wartosc=?, data_otrzymania=?, nagroda_za=? WHERE nazwa=?;");
			prep.setString(1, nazwa);
			prep.setString(2, opis);
			prep.setDouble(3, wartosc);
			prep.setString(4, data_otrzymania);
			prep.setString(5,nag_za);
			prep.setString(6, old_nazwa);

			prep.executeUpdate();
		} catch (SQLException e) {
			System.err.println(e.getClass().getName() + ": " + e.getMessage());
			JOptionPane.showMessageDialog(null, "Problem z edytowaniem nagrody : " + e.getMessage());
			return false;
		}
		return true;
	}

	public boolean updateProjekt(String old_nazwa, String nazwa,String opis, String data_startu,
								 String data_konca, double budzet){
		try {
			PreparedStatement prep = connection.prepareStatement(
					"UPDATE projekt SET nazwa=?, opis=?, data_startu=?, data_konca=?, budzet=? WHERE nazwa=?;");
			prep.setString(1, nazwa);
			prep.setString(2, opis);
			prep.setString(3, data_startu);
			prep.setString(4,data_konca);
			prep.setDouble(5, budzet);
			prep.setString(6, old_nazwa);
			prep.executeUpdate();
		} catch (SQLException e) {
			System.err.println(e.getClass().getName() + ": " + e.getMessage());
			JOptionPane.showMessageDialog(null, "Problem z edytowaniem projektu : " + e.getMessage());
			return false;
		}
		return true;
	}

	public boolean updateZadanie(int o_idProj, int o_idPrac, int id_projekt, int id_pracownik, double stawka, double ilosc_godzin, String komentarz,String data_startu,
								 String data_konca){
		try {
			PreparedStatement prep = connection.prepareStatement(
					"UPDATE zadania_pracownikow SET id_projekt=?, id_pracownik=?, stawka=?, ilosc_godzin=?, komentarz=?, data_startu=?, data_konca=? WHERE id_projekt=? AND id_pracownik=?;");
			prep.setInt(1, id_projekt);
			prep.setInt(2,id_pracownik);
			prep.setDouble(3, stawka);
			prep.setDouble(4, ilosc_godzin);
			prep.setString(5, komentarz);
			prep.setString(6,data_startu);
			prep.setString(7,data_konca);
			prep.setInt(8,o_idProj);
			prep.setInt(9,o_idPrac);
			prep.executeUpdate();
		} catch (SQLException e) {
			System.err.println(e.getClass().getName() + ": " + e.getMessage());
			JOptionPane.showMessageDialog(null, "Problem z edytowaniem zadania : " + e.getMessage());
			return false;
		}
		return true;
	}



	public JComboBox comboStan(){
		JComboBox jb = new JComboBox();
		try{
			wynik = statement.executeQuery("SELECT nazwa FROM stanowisko;");
			jb.addItem("");
			while(wynik.next()){
				jb.addItem(wynik.getString("nazwa"));
			}

			return jb;
		} catch (SQLException e) {
			System.err.println(e.getClass().getName() + ": " + e.getMessage());
			JOptionPane.showMessageDialog(null, "Problem z zaladowaniem danych do listy : " + e.getMessage());
			return null;
		}

	}

	public JComboBox comboProj(){
		JComboBox jb = new JComboBox();
		try{
			wynik = statement.executeQuery("SELECT nazwa FROM projekt;");
			jb.addItem("");
			while(wynik.next()){
				jb.addItem(wynik.getString("nazwa"));
			}

			return jb;
		} catch (SQLException e) {
			System.err.println(e.getClass().getName() + ": " + e.getMessage());
			JOptionPane.showMessageDialog(null, "Problem z zaladowaniem danych do listy : " + e.getMessage());
			return null;
		}

	}

	public JComboBox comboPrac(){
		JComboBox jb = new JComboBox();
		jb.addItem("");
		String imie, nazwisko, stanowisko, prac;
		try{
			wynik = statement.executeQuery("SELECT imie,nazwisko,s.nazwa[stanowisko],data_urodzenia,data_zatrudnienia,pensja FROM pracownik p LEFT JOIN stanowisko s ON p.id_stanowisko=s.id_stanowisko;");
			while(wynik.next()){
				imie = wynik.getString("imie");
				nazwisko = wynik.getString("nazwisko");
				stanowisko = wynik.getString("stanowisko");
				prac=imie+" "+nazwisko+" "+stanowisko;
				jb.addItem(prac);
			}

			return jb;
		} catch (SQLException e) {
			System.err.println(e.getClass().getName() + ": " + e.getMessage());
			JOptionPane.showMessageDialog(null, "Problem z zaladowaniem danych do listy : " + e.getMessage());
			return null;
		}
	}

	public JComboBox comboZad() {
		JComboBox jb = new JComboBox();
		jb.addItem("");
		String proj, imie, nazwisko, stanowisko, list;
		try {
			wynik = statement.executeQuery("SELECT proj.nazwa, p.imie,p.nazwisko,s.nazwa[stanowisko],stawka,ilosc_godzin, (stawka*ilosc_godzin) AS dodatek FROM zadania_pracownikow z LEFT JOIN pracownik p ON p.id_pracownik=z.id_pracownik LEFT JOIN projekt proj ON z.id_projekt=proj.id_projekt LEFT JOIN stanowisko s ON s.id_stanowisko=p.id_stanowisko;");
			while (wynik.next()) {
				proj = wynik.getString("nazwa");
				imie = wynik.getString("imie");
				nazwisko = wynik.getString("nazwisko");
				stanowisko = wynik.getString("stanowisko");
				list = proj + " " + imie + " " + nazwisko + " " + stanowisko;
				jb.addItem(list);
			}

			return jb;
		} catch (SQLException e) {
			System.err.println(e.getClass().getName() + ": " + e.getMessage());
			JOptionPane.showMessageDialog(null, "Problem z zaladowaniem danych do listy : " + e.getMessage());
			return null;
		}
	}

	public JComboBox comboNag(){
		JComboBox jb = new JComboBox();
		String nazwa,imie,nazwisko,stanowisko, str;
		try{
			wynik = statement.executeQuery("SELECT n.nazwa, p.imie,p.nazwisko, s.nazwa[stanowisko] FROM nagroda n JOIN pracownik p ON n.id_pracownik=p.id_pracownik JOIN stanowisko s ON s.id_stanowisko=p.id_stanowisko;");
			jb.addItem("");
			while(wynik.next()){
				nazwa = wynik.getString("nazwa");
				imie = wynik.getString("imie");
				nazwisko = wynik.getString("nazwisko");
				stanowisko = wynik.getString("stanowisko");
				str = nazwa + " " + imie + " " + nazwisko + " " + stanowisko;
				jb.addItem(str);
			}

			return jb;
		} catch (SQLException e) {
			System.err.println(e.getClass().getName() + ": " + e.getMessage());
			JOptionPane.showMessageDialog(null, "Problem z zaladowaniem danych do listy : " + e.getMessage());
			return null;
		}

	}

	public DefaultTableModel selectTable(String sql){
		try{
			wynik = statement.executeQuery(sql);
			ResultSetMetaData meta = wynik.getMetaData();
			int iloscKolumn = meta.getColumnCount();
            Vector columnNames = new Vector();

            // get the column names
            for(int column = 0; column < iloscKolumn; column++){
                columnNames.addElement(meta.getColumnLabel(column+1));
            }

            // get all rows
            Vector rows = new Vector();
			while(wynik.next()){
                Vector newRow = new Vector();
				//Object [] rekord = new Object[iloscKolumn];
				for(int i = 1; i <= iloscKolumn; i++){
					newRow.addElement(wynik.getObject(i));
				}
				rows.addElement(newRow);
			}

			return new DefaultTableModel(rows,columnNames);
		} catch (SQLException e) {
			System.err.println(e.getClass().getName() + ": " + e.getMessage());
			JOptionPane.showMessageDialog(null, "Problem z zaladowaniem danych do tabeli : " + e.getMessage());
            return null;
		}
	}

	public int FindidFK(String sql, String column){
		int id;
		try {
			wynik = statement.executeQuery(sql);
			id = wynik.getInt(column);
			return id;
		} catch (SQLException ex) {
			System.out.println("The following error has occured: " + ex.getMessage());
			return -1;
		}
	}

	public void ExecuteSQLStatement(String sql_stmt) {
		try {
			statement = connection.createStatement();

			statement.executeUpdate(sql_stmt);
		} catch (SQLException ex) {
			System.out.println("The following error has occured: " + ex.getMessage());
		}
	}

	public ResultSet ExecuteSQLQuery(String sql){
		try {
			statement = connection.createStatement();
			return statement.executeQuery(sql);
		}catch(SQLException e){
			System.err.println(e.getClass().getName() + ": " + e.getMessage());
			JOptionPane.showMessageDialog(null, "Problem z wykokonaniem zapytania : " + e.getMessage());
			return null;
		}
	}


	public void closeConnection() {
		try {
			connection.close();
			System.out.println("Polaczenie zamkniete");
		} catch(SQLException e){
			System.err.println(e.getClass().getName() + ": " + e.getMessage());
			JOptionPane.showMessageDialog(null, "Problem z zamknieciem polaczenia : " + e.getMessage());
		}
	}


}
