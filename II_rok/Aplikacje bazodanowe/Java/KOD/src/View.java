import javax.swing.*;
import javax.swing.table.TableColumn;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.text.DateFormat;
import java.text.ParseException;
import java.text.SimpleDateFormat;


public class View extends JFrame {

    public Model db = new Model();


    public String current; // na ktorej tabeli pracujemy

    //BUTTONY
    public JButton btStanow;
    public JButton btPrac;
    public JButton btProj;
    public JButton btZad;
    public JButton btNag;

    public JButton btAdd;
    public JButton btEdt;
    public JButton btDel;
    public JButton btSea;
    public JTable tabela;


    final static String DATE_FORMAT = "yyyy-MM-dd";
    //Wybrane elementy z listy
    private String selectedStan, selectedPrac, selectedProj, selectedNag;

    private JPanel panelTab;
    private JPanel panelEdit;
    private boolean blad = false;
    private JTextField nazwa = new JTextField();
    private JTextField dolna = new JTextField();
    private JTextField gorna = new JTextField();
    private String nazwa_ = new String();
    private String dolna_ = new String();
    private String gorna_ = new String();

    private JTextField imie = new JTextField();
    private JTextField nazwisko = new JTextField();
    private JTextField dataUr = new JTextField();
    private JTextField dataZatr = new JTextField();
    private JTextField pensja = new JTextField();
    private JTextField komentarz = new JTextField();

    private String stanowisko_ = new String();
    private String imie_ = new String();
    private String nazwisko_ = new String();
    private String dataUr_ = new String();
    private String dataZatr_ = new String();
    private String pensja_ = new String();

    private JTextField opis = new JTextField();
    private JTextField starDate = new JTextField();
    private JTextField endDate = new JTextField();
    private JTextField dataDod = new JTextField();
    private String opis_ = new String();
    private String starDate_ = new String();
    private String endDate_ = new String();


    private JTextField stawka = new JTextField();
    private JTextField ilGodzin = new JTextField();
    private JTextField wartosc = new JTextField();
    private JTextField dataOt = new JTextField();
    private JTextField budzet = new JTextField();
    private JTextField nagrodaZa = new JTextField();
    private String stawka_ = new String();
    private String ilGodzin_ = new String();
    private String budzet_ = new String();
    private String komentarz_ = new String();
    private String wartosc_ = new String();
    private String dataOt_ = new String();
    private String dataDod_ = new String();
    private String nagrodaZa_ = new String();

    private JComboBox comboBoxStan;
    private JComboBox comboBoxPrac = db.comboPrac();
    private JComboBox comboBoxProj = db.comboProj();
    private JComboBox comboBoxZad = db.comboZad();
    private JComboBox comboBoxNag = db.comboNag();
    private String[] dane;

    private int szukaneId, szukaneIdPrac, szukaneIdProj;
    private double dDolna, dGorna, dPensja, dStawka, dIlGodzin,dWartosc,dBudzet;

    private JLabel labelImie = new JLabel();
    private JLabel labelNazw = new JLabel();
    private JLabel przedzialy = new JLabel();

    final static String STAN_TAB = "SELECT * FROM stanowisko";
    final static String PRAC_TAB = "SELECT imie,nazwisko,s.nazwa[stanowisko],data_urodzenia,data_zatrudnienia,pensja FROM pracownik p LEFT JOIN stanowisko s ON p.id_stanowisko=s.id_stanowisko;";
    final static String PROJ_TAB = "SELECT * FROM projekt";
    final static String ZAD_TAB = "SELECT proj.nazwa, p.imie,p.nazwisko,z.stawka,z.ilosc_godzin, (stawka*ilosc_godzin) AS dodatek, z.komentarz,z.data_startu,z.data_konca FROM zadania_pracownikow z LEFT JOIN pracownik p ON p.id_pracownik=z.id_pracownik LEFT JOIN projekt proj ON z.id_projekt=proj.id_projekt;";
    final static String NAG_TAB = "SELECT p.imie,p.nazwisko,n.nazwa,n.opis,n.wartosc,n.data_otrzymania, n.nagroda_za FROM nagroda n JOIN pracownik p ON n.id_pracownik=p.id_pracownik;";

    public View() {
        setTitle("Company Crud");
        setSize(700, 300);

        Container powZawartosci = getContentPane();

        panelTab = new JPanel();
        panelEdit = new JPanel();

        panelEdit.setLayout(new GridLayout(8, 1));
        panelTab.setBackground(Color.DARK_GRAY);

        btStanow = new JButton("Stanowiska");
        btPrac = new JButton("Pracownicy");
        btProj = new JButton("Projekty");
        btZad = new JButton("Zadania");
        btNag = new JButton("Nagrody");

        btAdd = new JButton("Dodaj");
        btEdt = new JButton("Edytuj");
        btDel = new JButton("Usun");
        btSea = new JButton("Szukaj");


        // Maybe better option is gridlayout
        panelEdit.add(btAdd);
        panelEdit.add(Box.createVerticalStrut(20));
        panelEdit.add(btEdt);
        panelEdit.add(Box.createVerticalStrut(20));
        panelEdit.add(btDel);
        panelEdit.add(Box.createVerticalStrut(20));
        panelEdit.add(btSea);
        panelEdit.add(Box.createVerticalStrut(20));

        powZawartosci.add(BorderLayout.WEST, panelEdit);
        tabela = new JTable();

        powZawartosci.add(new JScrollPane(tabela), BorderLayout.CENTER);
        pack();
        panelTab.add(btStanow);
        panelTab.add(btPrac);
        panelTab.add(btProj);
        panelTab.add(btZad);
        panelTab.add(btNag);

        powZawartosci.add(BorderLayout.SOUTH, panelTab);

        btStanow.addActionListener(new ControllerStanowiskoButton());
        btPrac.addActionListener(new ControllerPracownikButton());
        btProj.addActionListener(new ControllerProjektButton());
        btZad.addActionListener(new ControllerZadanieButton());
        btNag.addActionListener(new ControllerNagrodaButton());
        btAdd.addActionListener(new ControllerInsertButton());
        btEdt.addActionListener(new ControllerEditButton());
        btDel.addActionListener(new ControllerDeleteButton());
        btSea.addActionListener(new ControllerSelectButton());
    }

    public void showTable(String query, String current, int removeColumns) {
        tabela.setModel(db.selectTable(query));
        for (int i = 0; i < removeColumns; i++) {
            TableColumn t = tabela.getColumnModel().getColumn(0);
            tabela.getColumnModel().removeColumn(t);
        }
        this.current = current;
        refreshCombo();
    }

    //CONTROLLER

    class ControllerStanowiskoButton implements ActionListener {
        public void actionPerformed(ActionEvent e) {
            showTable(STAN_TAB, "Stan", 1);
        }
    }

    class ControllerPracownikButton implements ActionListener {
        public void actionPerformed(ActionEvent e) {
            showTable(PRAC_TAB, "Prac", 0);
        }
    }

    class ControllerProjektButton implements ActionListener {
        public void actionPerformed(ActionEvent e) {
            showTable(PROJ_TAB, "Proj", 1);
        }
    }

    class ControllerZadanieButton implements ActionListener {
        public void actionPerformed(ActionEvent e) {
            showTable(ZAD_TAB, "Zad", 0);
        }
    }

    class ControllerNagrodaButton implements ActionListener {
        public void actionPerformed(ActionEvent e) {
            showTable(NAG_TAB,"Nag",0);
        }
    }

    class ControllerInsertButton implements ActionListener {
        public void actionPerformed(ActionEvent e) {
//            String name = JOptionPane.showInputDialog(View.this,"Test dodawania rekordu:",null);
            switch (current) {
                case "Stan":
                    AddStanowisko();
                    break;
                case "Prac":
                    AddPracownik();
                    break;
                case "Proj":
                    AddProjekt();
                    break;
                case "Zad":
                    AddZadanie();
                    break;
                case "Nag":
                    AddNagroda();
                    break;
                default:
                    System.out.println("Reszta");
                    break;
            }
        }

        private void AddStanowisko() {

            Object[] message = {
                    "Nazwa:", nazwa,
                    "Opis:",opis,
                    "Minimalna pensja:", dolna,
                    "Maksymalna pensja:", gorna,
                    "Data dodania: ", dataDod
            };

            int option = JOptionPane.showConfirmDialog(null, message, "Dodaj Stanowisko", JOptionPane.OK_CANCEL_OPTION);

            if (option == JOptionPane.OK_OPTION) {

                if (nazwa.getText().equals("") || dolna.getText().equals("") || gorna.getText().equals("")) {
                    JOptionPane.showMessageDialog(null, "Nalezy wypelnic wszystkie pola");
                    AddStanowisko();
                } else {
                    blad = false;

                    try {
                        dDolna = Double.parseDouble(dolna.getText());
                    } catch (NumberFormatException e) {
                        blad = true;
                        dolna = new JTextField();
                        JOptionPane.showMessageDialog(null, "Dolna powinna byc liczba.");

                    }

                    try {
                        dGorna = Double.parseDouble(gorna.getText());
                    } catch (NumberFormatException e) {
                        blad = true;
                        gorna = new JTextField();
                        JOptionPane.showMessageDialog(null, "Gorna powinna byc liczba.");
                    }

                    if (!dataDod.getText().equals("") && !checkData(dataDod.getText())) {
                        JOptionPane.showMessageDialog(null, "Niepoprawny format daty otrzymania [yyyy-MM-dd]");
                        blad = true;
                    }


                    if (!(blad)) {
                        db.insertStanowisko(nazwa.getText(), opis.getText(), dDolna, dGorna,dataDod.getText());
                        nazwa = new JTextField();
                        opis = new JTextField();
                        dolna = new JTextField();
                        gorna = new JTextField();
                        dataDod = new JTextField();
                    } else {
                        AddStanowisko();
                    }

                    //aktualizacja listy rozwijanej po dodaniu stanowisko
                    showTable(STAN_TAB, "Stan", 1);
                }

            } else {
                System.out.println("Dodawanie anulowane");
            }
        }

        private void AddPracownik() {

//            JComboBox comboBox = db.comboStan();
            Object[] message = {
                    "Stanowisko:", comboBoxStan,
                    "Imie:", imie,
                    "Nazwisko:", nazwisko,
                    "Data urodzenia:", dataUr,
                    "Data zatrudnienia:", dataZatr,
                    "Pensja:", pensja
            };

            String[] options = {"OK", "Cancel"};

            int option = JOptionPane.showOptionDialog(null, message, "Dodaj pracownika",
                    JOptionPane.DEFAULT_OPTION, JOptionPane.PLAIN_MESSAGE, null, options, options[0]);


            if (option == JOptionPane.OK_OPTION) {

                if (String.valueOf(comboBoxStan.getSelectedItem()).equals("") || imie.getText().equals("") || nazwisko.getText().equals("") ||
                        dataUr.getText().equals("") || pensja.getText().equals("")) {
                    JOptionPane.showMessageDialog(null, "Nalezy wypelnic wszystkie pola");
                    AddPracownik();
                } else {
                    blad = false;

                    try {
                        selectedStan = (String) comboBoxStan.getSelectedItem();
                        szukaneId = db.FindidFK("SELECT * FROM stanowisko WHERE nazwa=\"" + selectedStan + "\";", "id_stanowisko");
                    } catch (Exception e) {
                        JOptionPane.showMessageDialog(null, "Nie znaleziono id wybranego stanowiska");
                        blad = true;
                    }

                    if (!checkData(dataUr.getText())) {
                        JOptionPane.showMessageDialog(null, "Niepoprawny format daty urodzenia [yyyy-MM-dd]");
                        blad = true;
                    }

                    if (!checkData(dataZatr.getText()) && !(dataZatr.getText().equals("NULL") || dataZatr.getText().equals("DEFAULT") || dataZatr.getText().equals(""))) {
                        JOptionPane.showMessageDialog(null, "Niepoprawny format daty zatrudnienia [yyyy-MM-dd]");
                        blad = true;
                    }


                    try {
                        dPensja = Double.parseDouble(pensja.getText());
                    } catch (NumberFormatException e) {
                        blad = true;
                        pensja = new JTextField();
                        JOptionPane.showMessageDialog(null, "Pensja powinna byc liczba.");
                    }


                    //::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
                    if (!(blad)) {
                        System.out.println(szukaneId);
                        boolean czysc = db.insertPracownik(szukaneId, imie.getText(), nazwisko.getText(), dataUr.getText(), dataZatr.getText(), dPensja);
                        if (czysc) {
                            imie = new JTextField();
                            nazwisko = new JTextField();
                            dataUr = new JTextField();
                            dataZatr = new JTextField();
                            pensja = new JTextField();
                        } else {
                            AddPracownik();
                            comboBoxStan.getModel().setSelectedItem(selectedStan);
                            comboBoxStan.updateUI();
                        }
                    } else {
                        AddPracownik();
                        comboBoxStan.getModel().setSelectedItem(selectedStan);
                        comboBoxStan.updateUI();
                    }

                    showTable(PRAC_TAB, "Prac", 0);
                }

            } else {
                imie = new JTextField();
                nazwisko = new JTextField();
                dataUr = new JTextField();
                dataZatr = new JTextField();
                pensja = new JTextField();
            }
        }

        private void AddProjekt() {
            Object[] message = {
                    "Nazwa:", nazwa,
                    "Opis:", opis,
                    "Data Startu:", starDate,
                    "Data Końca:", endDate,
                    "Budżet:", budzet,
            };

            int option = JOptionPane.showConfirmDialog(null, message, "Dodaj Projekt", JOptionPane.OK_CANCEL_OPTION);

            if (option == JOptionPane.OK_OPTION) {

                if (nazwa.getText().equals("") || starDate.getText().equals("") || endDate.getText().equals("")) {
                    JOptionPane.showMessageDialog(null, "Nalezy wypelnic wszystkie pola (oprocz opis)");
                    AddProjekt();
                } else {
                    blad = false;

                    if (!checkData(starDate.getText())) {
                        JOptionPane.showMessageDialog(null, "Niepoprawny format daty startu [yyyy-MM-dd]");
                        blad = true;
                    }

                    if (!checkData(endDate.getText())) {
                        JOptionPane.showMessageDialog(null, "Niepoprawny format daty konca [yyyy-MM-dd]");
                        blad = true;
                    }


                    try {
                        if(budzet.getText().equals("")) {
                            dBudzet = 0f;
                        } else
                            dBudzet = Double.parseDouble(budzet.getText());
                    } catch (NumberFormatException e) {
                        blad = true;
                        wartosc = new JTextField();
                        JOptionPane.showMessageDialog(null, "Budżet powinna byc liczba.");
                    }


                    if (!(blad)) {
                        db.insertProjekt(nazwa.getText(), opis.getText(), starDate.getText(), endDate.getText(), dBudzet);
                        nazwa = new JTextField();
                        opis = new JTextField();
                        starDate = new JTextField();
                        endDate = new JTextField();
                        budzet = new JTextField();
                    } else {
                        AddProjekt();
                    }

                    //aktualizacja listy rozwijanej po dodaniu projektu
//                    comboBox = db.comboStan();
                    showTable(PROJ_TAB, "Proj", 1);
                }

            } else {
                System.out.println("Dodawanie anulowane");
            }
        }

        private void AddZadanie() {

//            JComboBox comboBox = db.comboStan();
            Object[] message = {
                    "Projekt:", comboBoxProj,
                    "Pracownik:", comboBoxPrac,
                    "Stawka:", stawka,
                    "Ilosc godzin:", ilGodzin,
                    "Komentarz:",komentarz,
                    "Data Startu:", starDate,
                    "Data Końca:", endDate
            };

            String[] options = {"OK", "Cancel"};

            int option = JOptionPane.showOptionDialog(null, message, "Dodaj zadanie",
                    JOptionPane.DEFAULT_OPTION, JOptionPane.PLAIN_MESSAGE, null, options, options[0]);


            if (option == JOptionPane.OK_OPTION) {

                if (String.valueOf(comboBoxProj.getSelectedItem()).equals("") || String.valueOf(comboBoxPrac.getSelectedItem()).equals("") || stawka.getText().equals("") || ilGodzin.getText().equals("") || starDate.getText().equals("") || endDate.getText().equals("")) {
                    JOptionPane.showMessageDialog(null, "Nalezy wypelnic wszystkie pola");
                    AddZadanie();
                } else {
                    blad = false;

                    try {
                        selectedProj = (String) comboBoxProj.getSelectedItem();
                        szukaneIdProj = db.FindidFK("SELECT * FROM projekt WHERE nazwa=\"" + selectedProj + "\";", "id_projekt");
                    } catch (Exception e) {
                        JOptionPane.showMessageDialog(null, "Nie znaleziono id wybranego projektu");
                        blad = true;
                    }


                    try {
                        selectedPrac = (String) comboBoxPrac.getSelectedItem();
                        String[] pole = selectedPrac.split(" ");
                        szukaneIdPrac = db.FindidFK("SELECT * FROM pracownik WHERE imie=\"" + pole[0] + "\" AND nazwisko=\"" + pole[1] + "\";", "id_pracownik");
                    } catch (Exception e) {
                        JOptionPane.showMessageDialog(null, "Nie znaleziono id wybranego pracownika");
                        blad = true;
                    }

                    if (!checkData(starDate.getText())) {
                        JOptionPane.showMessageDialog(null, "Niepoprawny format daty startu [yyyy-MM-dd]");
                        blad = true;
                    }

                    if (!checkData(endDate.getText())) {
                        JOptionPane.showMessageDialog(null, "Niepoprawny format daty konca [yyyy-MM-dd]");
                        blad = true;
                    }

                    try {
                        dStawka = Double.parseDouble(stawka.getText());
                    } catch (NumberFormatException e) {
                        blad = true;
                        stawka = new JTextField();
                        JOptionPane.showMessageDialog(null, "Stawka powinna byc liczba.");
                    }

                    try {
                        dIlGodzin = Double.parseDouble(ilGodzin.getText());
                    } catch (NumberFormatException e) {
                        blad = true;
                        ilGodzin = new JTextField();
                        JOptionPane.showMessageDialog(null, "Ilosc godzin: powinna byc liczba.");
                    }


                    //::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
                    if (!(blad)) {
                        boolean czysc = db.insertZadanie(szukaneIdProj, szukaneIdPrac, dStawka, dIlGodzin,komentarz.getText(),starDate.getText(),endDate.getText());

                        if (czysc) {
                            stawka = new JTextField();
                            ilGodzin = new JTextField();
                            komentarz = new JTextField();
                            starDate = new JTextField();
                            endDate = new JTextField();
                        } else {
                            AddZadanie();
                            comboBoxProj.getModel().setSelectedItem(selectedProj);
                            comboBoxProj.updateUI();
                            comboBoxPrac.getModel().setSelectedItem(selectedPrac);
                            comboBoxProj.updateUI();
                        }
                    } else {
                        AddZadanie();
                        comboBoxProj.getModel().setSelectedItem(selectedProj);
                        comboBoxProj.updateUI();
                        comboBoxPrac.getModel().setSelectedItem(selectedPrac);
                        comboBoxProj.updateUI();
                    }

                    showTable(ZAD_TAB, "Zad", 0);
                }

            } else {
                imie = new JTextField();
                nazwisko = new JTextField();
                dataUr = new JTextField();
                dataZatr = new JTextField();
                pensja = new JTextField();
                stawka = new JTextField();
                ilGodzin = new JTextField();
                komentarz = new JTextField();
                starDate = new JTextField();
                endDate = new JTextField();
            }
        }

        private void AddNagroda() {
            Object[] message = {
                    "Pracownik:", comboBoxPrac,
                    "Nazwa:", nazwa,
                    "Opis:", opis,
                    "Wartość:",wartosc,
                    "Data otrzymania:", dataOt,
                    "Nagroda za: ",nagrodaZa
            };

            String[] options = {"OK", "Cancel"};

            int option = JOptionPane.showOptionDialog(null, message, "Przyznaj nagrodę",
                    JOptionPane.DEFAULT_OPTION, JOptionPane.PLAIN_MESSAGE, null, options, options[0]);


            if (option == JOptionPane.OK_OPTION) {

                if (String.valueOf(comboBoxPrac.getSelectedItem()).equals("") || nazwa.getText().equals("") || wartosc.getText().equals("")) {
                    JOptionPane.showMessageDialog(null, "Nalezy wypelnic wszystkie pola");
                    AddZadanie();
                } else {
                    blad = false;

                    try {
                        selectedPrac = (String) comboBoxPrac.getSelectedItem();
                        String[] pole = selectedPrac.split(" ");
                        szukaneIdPrac = db.FindidFK("SELECT * FROM pracownik WHERE imie=\"" + pole[0] + "\" AND nazwisko=\"" + pole[1] + "\";", "id_pracownik");
                    } catch (Exception e) {
                        JOptionPane.showMessageDialog(null, "Nie znaleziono id wybranego pracownika");
                        blad = true;
                    }


                    try {
                        dWartosc = Double.parseDouble(wartosc.getText());
                    } catch (NumberFormatException e) {
                        blad = true;
                        wartosc = new JTextField();
                        JOptionPane.showMessageDialog(null, "Wartosc powinna byc liczba.");
                    }

                    if (!dataOt.getText().equals("") && !checkData(dataOt.getText())) {
                        JOptionPane.showMessageDialog(null, "Niepoprawny format daty otrzymania [yyyy-MM-dd]");
                        blad = true;
                    }


                    //::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
                    if (!(blad)) {
                        boolean czysc = db.insertNagroda(szukaneIdPrac,nazwa.getText(),opis.getText(),dWartosc,dataOt.getText(),nagrodaZa.getText());

                        if (czysc) {
                            nazwa = new JTextField();
                            opis = new JTextField();
                            wartosc = new JTextField();
                            dataOt = new JTextField();
                            nagrodaZa = new JTextField();
                        } else {
                            AddNagroda();
                            comboBoxPrac.getModel().setSelectedItem(selectedPrac);
                            comboBoxPrac.updateUI();
                        }
                    } else {
                        AddNagroda();
                        comboBoxPrac.getModel().setSelectedItem(selectedPrac);
                        comboBoxPrac.updateUI();
                    }

                    showTable(NAG_TAB, "Nag", 0);
                }

            } else {
                nazwa = new JTextField();
                opis = new JTextField();
                wartosc = new JTextField();
                dataOt = new JTextField();
                nagrodaZa = new JTextField();
            }
        }

    }

    class ControllerDeleteButton implements ActionListener {
        public void actionPerformed(ActionEvent e) {
            switch (current) {
                case "Stan":
                    DelStanowisko();
                    break;
                case "Prac":
                    DelPracownik();
                    break;
                case "Proj":
                    DelProjekt();
                    break;
                case "Zad":
                    DelZadanie();
                    break;
                case "Nag":
                    DelNagroda();
                    break;
                default:
                    System.out.println("Reszta");
                    break;
            }
        }

        public void DelStanowisko() {
            Object[] message = {
                    "Wybierz, który element chcesz usunąć",
                    "Stanowisko:", comboBoxStan,
            };

            String[] options = {"OK", "Cancel"};

            int option = JOptionPane.showOptionDialog(null, message, "Usuń stanowisko",
                    JOptionPane.DEFAULT_OPTION, JOptionPane.PLAIN_MESSAGE, null, options, options[0]);

            if (option == JOptionPane.OK_OPTION) {
                //nazwa usuwanego stanowiska
                selectedStan = (String) comboBoxStan.getSelectedItem();
                int confirm = JOptionPane.showConfirmDialog(null, "Jesteś pewny, że chcesz usunąć to stanowisko? Spowoduje to usuniecie pracownikow na tym stanowisku", "Jesteś pewny?", JOptionPane.OK_CANCEL_OPTION);
                if (confirm == JOptionPane.OK_OPTION) {
                    db.ExecuteSQLStatement("DELETE FROM stanowisko WHERE nazwa=\"" + selectedStan + "\";");
                    showTable(STAN_TAB, "Stan", 1);
                }
            } else {
            }
        }

        public void DelPracownik() {
            Object[] message = {
                    "Wybierz, który element chcesz usunąć",
                    "Pracownik:", comboBoxPrac,
            };

            String[] options = {"OK", "Cancel"};

            int option = JOptionPane.showOptionDialog(null, message, "Usuń pracownika",
                    JOptionPane.DEFAULT_OPTION, JOptionPane.PLAIN_MESSAGE, null, options, options[0]);

            if (option == JOptionPane.OK_OPTION) {
                //usuwany pracownik
                selectedPrac = (String) comboBoxPrac.getSelectedItem();
                String[] data = selectedPrac.split(" ");
                int confirm = JOptionPane.showConfirmDialog(null, "Jesteś pewny, że chcesz zwolnić:" + data[0] + " " + data[1] + ", pracującego na stanowisku: " + data[2] + "?", "Jesteś pewny?", JOptionPane.OK_CANCEL_OPTION);

                if (confirm == JOptionPane.OK_OPTION) {
                    db.ExecuteSQLStatement("DELETE FROM pracownik WHERE imie=\"" + data[0] + "\" AND nazwisko=\"" + data[1] + "\";");
                    showTable(PRAC_TAB, "Prac", 0);
                }
            } else {
            }
        }

        public void DelProjekt() {
            Object[] message = {
                    "Wybierz, który element chcesz usunąć",
                    "Projekt:", comboBoxProj,
            };

            String[] options = {"OK", "Cancel"};

            int option = JOptionPane.showOptionDialog(null, message, "Usuń projekt",
                    JOptionPane.DEFAULT_OPTION, JOptionPane.PLAIN_MESSAGE, null, options, options[0]);

            if (option == JOptionPane.OK_OPTION) {
                //usuwany pracownik
                selectedProj = (String) comboBoxProj.getSelectedItem();
                int confirm = JOptionPane.showConfirmDialog(null, "Jesteś pewny, że chcesz usunąć projekt:" + selectedProj + "? Usunie to rowniez przydzielenie tego projektu do pracowników", "Jesteś pewny?", JOptionPane.OK_CANCEL_OPTION);

                if (confirm == JOptionPane.OK_OPTION) {
                    db.ExecuteSQLStatement("DELETE FROM projekt WHERE nazwa=\"" + selectedProj + "\";");
                    showTable(PROJ_TAB, "Proj", 1);
                }
            } else {
            }
        }

        public void DelZadanie() {
            Object[] message = {
                    "Wybierz, który element chcesz usunąć",
                    "Projekt:", comboBoxZad,
            };

            String[] options = {"OK", "Cancel"};

            int option = JOptionPane.showOptionDialog(null, message, "Usuń przydzielone zadanie pracowikowi",
                    JOptionPane.DEFAULT_OPTION, JOptionPane.PLAIN_MESSAGE, null, options, options[0]);

            if (option == JOptionPane.OK_OPTION) {
                //usuwany pracownik
                selectedProj = (String) comboBoxZad.getSelectedItem();
                String[] dane = selectedProj.split(" ");
                int confirm = JOptionPane.showConfirmDialog(null, "Jesteś pewny, że chcesz usunąć przydzielony projekt:" + dane[0] + ", pracownikowi: " + dane[1] + " " + dane[2] + "?", "Jesteś pewny?", JOptionPane.OK_CANCEL_OPTION);

                int idPrac = db.FindidFK("SELECT * FROM pracownik WHERE imie=\"" + dane[1] + "\" AND nazwisko=\"" + dane[2] + "\";", "id_pracownik");
                int idProj = db.FindidFK("SELECT * FROM projekt WHERE nazwa=\"" + dane[0] + "\";", "id_projekt");


                if (confirm == JOptionPane.OK_OPTION) {
                    db.ExecuteSQLStatement("DELETE FROM zadania_pracownikow WHERE id_pracownik=\"" + idPrac + "\" AND id_projekt=\"" + idProj + "\";");
                    showTable(ZAD_TAB, "Zad", 0);
                }
            } else {
            }
        }

        public void DelNagroda() {
            Object[] message = {
                    "Wybierz, który element chcesz usunąć",
                    "Nagroda:", comboBoxNag,
            };

            String[] options = {"OK", "Cancel"};

            int option = JOptionPane.showOptionDialog(null, message, "Usuń nagrodę",
                    JOptionPane.DEFAULT_OPTION, JOptionPane.PLAIN_MESSAGE, null, options, options[0]);

            if (option == JOptionPane.OK_OPTION) {
                //usuwana nagroda
                selectedNag = (String) comboBoxNag.getSelectedItem();
                dane = selectedNag.split(" ");
                int confirm = JOptionPane.showConfirmDialog(null, "Jesteś pewny, że chcesz usunąć nagrode:" + dane[0] + ", pracownika: "+ dane[1] + " "+ dane[2] + " ?", "Jesteś pewny?", JOptionPane.OK_CANCEL_OPTION);

                if (confirm == JOptionPane.OK_OPTION) {
                    db.ExecuteSQLStatement("DELETE FROM nagroda WHERE nazwa=\"" + dane[0] + "\";");
                    showTable(NAG_TAB, "Nag", 0);
                }
            } else {
            }
        }


    }

    class ControllerSelectButton implements ActionListener {
        public void actionPerformed(ActionEvent e) {
            switch (current) {
                case "Stan":
                    FindStanowisko();
                    break;
                case "Prac":
                    FindPracownik();
                    break;
                case "Proj":
                    FindProjekt();
                    break;
                case "Zad":
                    FindZadanie();
                    break;
                case "Nag":
                    FindNagroda();
                    break;
                default:
                    System.out.println("Reszta");
                    break;
            }
        }

        public void FindStanowisko() {
            Object[] message = {
                    "Nazwa:", nazwa,
                    "Opis:", opis,
                    "Minimalna pensja:", dolna,
                    "Maksymalna pensja:", gorna,
                    "Data Dodania: ", dataDod
            };

            int option = JOptionPane.showConfirmDialog(null, message, "Szukaj Stanowisko", JOptionPane.OK_CANCEL_OPTION);

            if (option == JOptionPane.OK_OPTION) {

                if (nazwa.getText().equals("") && opis.getText().equals("") && dolna.getText().equals("") && gorna.getText().equals("") && dataDod.getText().equals("")) {
                    JOptionPane.showMessageDialog(null, "Nalezy wypelnic przynajmniej jedno pole");
                    FindStanowisko();
                } else {
                    showTable("SELECT nazwa,opis, dolna, gorna, data_dodania FROM stanowisko WHERE nazwa LIKE '%" + nazwa.getText() + "%' AND dolna LIKE '%" + dolna.getText() + "%' AND opis LIKE '%" + opis.getText()+ "%' AND gorna LIKE '%" + gorna.getText() + "%' AND data_dodania LIKE '%" + dataDod.getText() + "%';", current, 0);
                    nazwa = new JTextField();
                    opis = new JTextField();
                    dolna = new JTextField();
                    gorna = new JTextField();
                    dataDod = new JTextField();
                }
            } else {
                System.out.println("Wyszukiwanie anulowane");
            }
        }

        public void FindPracownik() {
            Object[] message = {
                    "Stanowisko:", comboBoxStan,
                    "Imie:", imie,
                    "Nazwisko:", nazwisko,
                    "Data urodzenia:", dataUr,
                    "Data zatrudnienia:", dataZatr,
                    "Pensja:", pensja
            };

            String[] options = {"OK", "Cancel"};

            int option = JOptionPane.showOptionDialog(null, message, "Szukaj pracownika",
                    JOptionPane.DEFAULT_OPTION, JOptionPane.PLAIN_MESSAGE, null, options, options[0]);


            if (option == JOptionPane.OK_OPTION) {
                String stanowisko = (String) comboBoxStan.getSelectedItem();
                if (String.valueOf(comboBoxStan.getSelectedItem()).equals("") && imie.getText().equals("") && nazwisko.getText().equals("") &&
                        dataUr.getText().equals("") && dataZatr.getText().equals("") && pensja.getText().equals("")) {
                    JOptionPane.showMessageDialog(null, "Nalezy wypelnic przynajmniej jedno pole");
                    FindPracownik();
                } else {
                    showTable("SELECT imie,nazwisko,s.nazwa[stanowisko],data_urodzenia,data_zatrudnienia,pensja FROM pracownik p LEFT JOIN stanowisko s ON p.id_stanowisko=s.id_stanowisko WHERE stanowisko LIKE '%" + stanowisko + "%' AND imie LIKE '%" + imie.getText() + "%' AND nazwisko LIKE '%" + nazwisko.getText() + "%' AND data_urodzenia LIKE '%" + dataUr.getText() + "%' AND data_zatrudnienia LIKE '%" + dataZatr.getText() + "%' AND pensja LIKE '%" + pensja.getText() + "%';", current, 0);
                    imie = new JTextField();
                    nazwisko = new JTextField();
                    dataUr = new JTextField();
                    dataZatr = new JTextField();
                    pensja = new JTextField();
                }
            }
        }//FindPracownik

        public void FindProjekt() {
            Object[] message = {
                    "Nazwa:", nazwa,
                    "Opis:", opis,
                    "Data Startu:", starDate,
                    "Data Końca:", endDate,
                    "Budżet:",budzet
            };

            int option = JOptionPane.showConfirmDialog(null, message, "Szukaj Projekt", JOptionPane.OK_CANCEL_OPTION);

            if (option == JOptionPane.OK_OPTION) {

                if (nazwa.getText().equals("") && opis.getText().equals("") && starDate.getText().equals("") && endDate.getText().equals("") && budzet.getText().equals("")) {
                    JOptionPane.showMessageDialog(null, "Nalezy wypelnic przynajmniej jedno pole");
                    FindProjekt();
                } else {
                    showTable("SELECT nazwa, opis, data_startu, data_konca, budzet FROM projekt WHERE nazwa LIKE '%" + nazwa.getText() + "%' AND opis LIKE '%" + opis.getText() + "%' AND data_startu LIKE '%" + starDate.getText() + "%' AND data_konca LIKE '%" + endDate.getText() + "%' AND budzet LIKE '%" + budzet.getText() + "%';", current, 0);
                    nazwa = new JTextField();
                    opis = new JTextField();
                    starDate = new JTextField();
                    endDate = new JTextField();
                    budzet = new JTextField();
                }
            } else {
                System.out.println("Wyszukiwanie anulowane");
            }
        }

        public void FindZadanie() {
            Object[] message = {
                    "Projekt:", comboBoxProj,
                    "Pracownik:", comboBoxPrac,
                    "Stawka:", stawka,
                    "Ilosc godzin:", ilGodzin,
                    "Data Startu:", starDate,
                    "Data Końca:", endDate
            };


            String[] options = {"OK", "Cancel"};

            int option = JOptionPane.showOptionDialog(null, message, "Szukaj zadanie",
                    JOptionPane.DEFAULT_OPTION, JOptionPane.PLAIN_MESSAGE, null, options, options[0]);


            if (option == JOptionPane.OK_OPTION) {

                String Proj = (String) comboBoxProj.getSelectedItem();
                String Prac = (String) comboBoxPrac.getSelectedItem();
                String[]pracT = new String[3];

                if(Prac.equals("")){
                    pracT[0] = "";
                    pracT[1] = "";
                } else{
                    pracT = Prac.split(" ");
                }

                if (String.valueOf(comboBoxProj.getSelectedItem()).equals("") && String.valueOf(comboBoxPrac.getSelectedItem()).equals("") && stawka.getText().equals("") && ilGodzin.getText().equals("")) {
                    JOptionPane.showMessageDialog(null, "Nalezy wypelnic przynajmniej jedno pole");
                    FindZadanie();
                } else {
                    showTable("SELECT proj.nazwa, p.imie,p.nazwisko,stawka,ilosc_godzin,(stawka*ilosc_godzin)[dodatek], komentarz, z.data_startu, z.data_konca FROM zadania_pracownikow z JOIN pracownik p ON p.id_pracownik=z.id_pracownik JOIN projekt proj ON z.id_projekt=proj.id_projekt WHERE nazwa LIKE '%"+Proj+"%' AND imie LIKE '%"+pracT[0]+"%' AND nazwisko LIKE '%"+pracT[1]+"%' AND stawka LIKE '%"+stawka.getText()+"%' AND ilosc_godzin LIKE '%"+ilGodzin.getText()+"%';", current, 0);
                    stawka = new JTextField();
                    ilGodzin = new JTextField();
                    starDate = new JTextField();
                    endDate = new JTextField();
                }
            }

        }//SelectButton

        public void FindNagroda(){
            Object[] message = {
                    "Pracownik:", comboBoxPrac,
                    "Nazwa:", nazwa,
                    "Opis:", opis,
                    "Wartość:",wartosc,
                    "Data otrzymania:", dataOt,
                    "Nagroda za:",nagrodaZa
            };

            String[] options = {"OK", "Cancel"};

            int option = JOptionPane.showOptionDialog(null, message, "Szukaj nagrody",
                    JOptionPane.DEFAULT_OPTION, JOptionPane.PLAIN_MESSAGE, null, options, options[0]);

            if (option == JOptionPane.OK_OPTION) {
                String pracownik = (String) comboBoxPrac.getSelectedItem();
                String[]pracT = new String[3];

                if(pracownik.equals("")){
                    pracT[0] = "";
                    pracT[1] = "";
                } else{
                    pracT = pracownik.split(" ");
                }

                dane = pracownik.split(" "); //0-nazwa, 1-imie, 2-nazwisko
                if (String.valueOf(comboBoxPrac.getSelectedItem()).equals("") && nazwa.getText().equals("") && opis.getText().equals("") && starDate.getText().equals("") && endDate.getText().equals("") &&
                        wartosc.getText().equals("") && dataOt.getText().equals("") && nagrodaZa.getText().equals("")) {
                    JOptionPane.showMessageDialog(null, "Nalezy wypelnic przynajmniej jedno pole");
                    FindNagroda();
                } else {
                    showTable("SELECT p.imie,p.nazwisko,n.nazwa,n.opis,n.wartosc,n.data_otrzymania, n.nagroda_za FROM nagroda n JOIN pracownik p ON n.id_pracownik=p.id_pracownik WHERE imie LIKE '%" +pracT[0]+ "%' AND nazwisko LIKE '%" +pracT[1]+ "%' AND nazwa LIKE '%" + nazwa.getText() + "%' AND opis LIKE '%" + opis.getText() + "%' AND wartosc LIKE '%" + wartosc.getText() + "%' AND nagroda_za LIKE '%" + nagrodaZa.getText() + "%' AND data_otrzymania LIKE '%" + dataOt.getText() + "%';",current, 0);
                    nazwa = new JTextField();
                    opis = new JTextField();
                    wartosc = new JTextField();
                    dataOt = new JTextField();
                    nagrodaZa = new JTextField();
                }
            }
        }

    }

    class ControllerEditButton implements ActionListener {
        public void actionPerformed(ActionEvent e) {
            switch (current) {
                case "Stan":
                    EditStanowisko();
                    break;
                case "Prac":
                    EditPracownik();
                    break;
                case "Proj":
                    EditProjekt();
                    break;
                case "Zad":
                    EditZadanie();
                    break;
                case "Nag":
                    EditNagroda();
                    break;
                default:
                    System.out.println("Reszta");
                    break;
            }
        }


        public void EditStanowisko() {
            ResultSet result;


            Object[] message = {
                    "Wybierz, który element chcesz edytować",
                    "Stanowisko:", comboBoxStan,
            };

            Object[] message2 = {
                    "Nazwa:", nazwa,
                    "Opis:", opis,
                    "Minimalna pensja:", dolna,
                    "Maksymalna pensja:", gorna,
                    "Data dodania:", dataDod
            };


            String[] options = {"OK", "Cancel"};

            int option = JOptionPane.showOptionDialog(null, message, "Edytuj stanowisko",
                    JOptionPane.DEFAULT_OPTION, JOptionPane.PLAIN_MESSAGE, null, options, options[0]);

            if (option == JOptionPane.OK_OPTION) {
                //nazwa usuwanego stanowiska
                selectedStan = (String) comboBoxStan.getSelectedItem();

                try {
                    result = db.ExecuteSQLQuery("SELECT * FROM stanowisko WHERE nazwa=\"" + selectedStan + "\";");

                    // pobranie wartosci
                    nazwa_ = result.getString("nazwa");
                    opis_ = result.getString("opis");
                    dolna_ = result.getString("dolna");
                    gorna_ = result.getString("gorna");
                    dataDod_ = result.getString("data_dodania");
                    result.close();
                } catch (SQLException e) {
                    System.err.println(e.getClass().getName() + ": " + e.getMessage());
                    JOptionPane.showMessageDialog(null, "Problem z edytowaniem stanowiska : " + e.getMessage());
                }

                nazwa.setText(nazwa_);
                opis.setText(opis_);
                dolna.setText(dolna_);
                gorna.setText(gorna_);
                dataDod.setText(dataDod_);

                //otwarcie nowego okna
                int insertOpen = JOptionPane.showConfirmDialog(null, message2, "Edytuj Stanowisko", JOptionPane.OK_CANCEL_OPTION);

                if (insertOpen == JOptionPane.OK_OPTION) {

                    if (nazwa.getText().equals("") || dolna.getText().equals("") || gorna.getText().equals("") || dataDod.getText().equals("")) {
                        JOptionPane.showMessageDialog(null, "Nalezy wypelnic wszystkie pola");
                        EditStanPom();
                    } else {
                        blad = false;

                        try {
                            dDolna = Double.parseDouble(dolna.getText());
                        } catch (NumberFormatException e) {
                            blad = true;
                            dolna = new JTextField();
                            JOptionPane.showMessageDialog(null, "Dolna powinna byc liczba.");

                        }

                        try {
                            dGorna = Double.parseDouble(gorna.getText());
                        } catch (NumberFormatException e) {
                            blad = true;
                            gorna = new JTextField();
                            JOptionPane.showMessageDialog(null, "Gorna powinna byc liczba.");
                        }

                        if (!dataDod.getText().equals("") && !checkData(dataDod.getText())) {
                            JOptionPane.showMessageDialog(null, "Niepoprawny format daty otrzymania [yyyy-MM-dd]");
                            blad = true;
                        }



                        if (!(blad)) {
                            // System.out.println("Update zaraz bedzie, wprowadzane wartosci: old_name:" + nazwa_ + ", new_n:" + nazwa.getText() + " dolna:" + dDolna + " gorna: " + dGorna);
                            db.updateStanowisko(nazwa_, nazwa.getText(),opis.getText(), dDolna, dGorna, dataDod.getText());

                            /*
                            :::::::::::::::::::::::::::::::::::::::::::::::
                            SPRAWDZANIE CZY PENSJE NIE WYCHODZA POZA ZAKRES
                            :::::::::::::::::::::::::::::::::::::::::::::::
                             */
                            StanFkCheck();
                            /*
                            :::::::::::::::::::::::::::::::::::::::::::::::
                                    END OF SPRAWDZANIE
                            :::::::::::::::::::::::::::::::::::::::::::::::
                            */


                            // resetowanie wartosci textfieldow
                            nazwa = new JTextField();
                            opis = new JTextField();
                            dolna = new JTextField();
                            gorna = new JTextField();
                            dataDod = new JTextField();
//                            result = db.ExecuteSQLQuery(SELECT * FROM pracownik )
                            //Edytowanie pracownika po ewewntualnej zmianie wynagrodzenia;

                        } else {
                            nazwa.setText(nazwa_);
                            opis.setText(opis_);
                            dolna.setText(dolna_);
                            gorna.setText(gorna_);
                            dataDod.setText(dataDod_);
                            EditStanPom();
                        }

                    }

                    //aktualizacja listy rozwijanej po edytowaniu stanowisko
                    showTable(STAN_TAB, "Stan", 1);
                } else {
                    nazwa = new JTextField();
                    opis = new JTextField();
                    dolna = new JTextField();
                    gorna = new JTextField();
                    dataDod = new JTextField();
                    System.out.println("Anulowano edycje na 2 poziomie");
                }

            } else {
                System.out.println("Edytowanie anulowane");
            }


        }

        public void StanFkCheck(){
            ResultSet rs;

            Object[] message3 = {
                    labelImie,
                    labelNazw,
                    przedzialy,
                    "Pensja:", pensja
            };

            Object[] options = {"OK"};
            try{
                String sql_mess;
                int ilosc = 0;
                double paramDolna,paramGorna;
                rs = db.ExecuteSQLQuery("SELECT imie,nazwisko,s.nazwa[stanowisko],data_urodzenia,data_zatrudnienia,pensja,s.dolna,s.gorna FROM pracownik p LEFT JOIN stanowisko s ON p.id_stanowisko=s.id_stanowisko "+
                        "WHERE (pensja < s.dolna OR pensja > s.gorna) AND s.nazwa='"+nazwa.getText()+"';");
                while(rs.next()){
                    if(!blad){
                        sql_mess="Musisz zmienić pensje pracownika, ponieważ po zmianie nie miesci sie w widelkach <"+dDolna+", "+dGorna+">.";
                        JOptionPane.showMessageDialog(null,sql_mess,"Informacja", JOptionPane.INFORMATION_MESSAGE);
                    }
                    //Ustawienie wartosci dla edytowanie podanego elementu
                    labelImie.setText(rs.getString("imie"));
                    labelNazw.setText(rs.getString("nazwisko"));
                    przedzialy.setText("< "+rs.getString("dolna")+", "+rs.getString("gorna")+" >");
                    pensja.setText(rs.getString("pensja"));
                    paramDolna = Integer.parseInt(rs.getString("dolna"));
                    paramGorna = Integer.parseInt(rs.getString("gorna"));

                    int MustEdit = JOptionPane.showOptionDialog(null,message3,"Popraw pensje",
                            JOptionPane.DEFAULT_OPTION, JOptionPane.PLAIN_MESSAGE, null, options, options[0]);

                    if (MustEdit == JOptionPane.OK_OPTION){

                        blad = false;
                        try {
                            dPensja = Double.parseDouble(pensja.getText());
                        } catch (NumberFormatException e) {
                            blad = true;
                            pensja = new JTextField();
                            JOptionPane.showMessageDialog(null, "Pensja powinna byc liczba.");
                        }

                        if(dPensja < paramDolna || dPensja > paramGorna){
                            blad = true;
                            pensja = new JTextField();
                            JOptionPane.showMessageDialog(null, "Pensja nie miesci sie w przedzialach");
                        }

                        if (!(blad)) {
                            db.updatePracownik(labelImie.getText(),labelNazw.getText(),dPensja);
                            // System.out.println("UPDATE pracownik SET pensja="+dPensja+" WHERE imie='"+labelImie.getText()+"' AND nazwisko='"+labelNazw.getText()+"';");
                            //db.ExecuteSQLStatement("UPDATE pracownik SET pensja="+dPensja+" WHERE imie="+labelImie.getText()+" AND nazwisko="+labelNazw.getText()+";");
                        } else {
                            rs.close();
                            StanFkCheck();
                        }
                    } else {
                        System.out.println("Nie mozna nie edytowac!");
                    }

                }
                rs.close();
            } catch (SQLException e){
                System.out.println("Blad SQL");
            }
        }

        public void EditStanPom() {
            Object[] message2 = {
                    "Nazwa:", nazwa,
                    "Opis:",opis,
                    "Minimalna pensja:", dolna,
                    "Maksymalna pensja:", gorna,
                    "Data dodania:",dataDod
            };

            nazwa.setText(nazwa_);
            dolna.setText(dolna_);
            gorna.setText(gorna_);
            dataDod.setText(dataDod_);

            int insertOpen = JOptionPane.showConfirmDialog(null, message2, "Edytuj Stanowisko", JOptionPane.OK_CANCEL_OPTION);

            if (insertOpen == JOptionPane.OK_OPTION) {

                if (nazwa.getText().equals("") || dolna.getText().equals("") || gorna.getText().equals("") || dataDod.getText().equals("")) {
                    JOptionPane.showMessageDialog(null, "Nalezy wypelnic wszystkie pola");
                    EditStanPom();
                } else {
                    blad = false;

                    try {
                        dDolna = Double.parseDouble(dolna.getText());
                    } catch (NumberFormatException e) {
                        blad = true;
                        dolna = new JTextField();
                        JOptionPane.showMessageDialog(null, "Dolna powinna byc liczba.");

                    }

                    try {
                        dGorna = Double.parseDouble(gorna.getText());
                    } catch (NumberFormatException e) {
                        blad = true;
                        gorna = new JTextField();
                        JOptionPane.showMessageDialog(null, "Gorna powinna byc liczba.");
                    }

                    if (!dataDod.getText().equals("") && !checkData(dataDod.getText())) {
                        JOptionPane.showMessageDialog(null, "Niepoprawny format daty otrzymania [yyyy-MM-dd]");
                        blad = true;
                    }


                    if (!(blad)) {
                        db.updateStanowisko(nazwa_, nazwa.getText(), opis.getText(),dDolna, dGorna,dataDod.getText());
                        nazwa = new JTextField();
                        opis = new JTextField();
                        dolna = new JTextField();
                        gorna = new JTextField();
                        dataDod = new JTextField();
                    } else {
                        nazwa.setText(nazwa_);
                        opis.setText(opis_);
                        dolna.setText(dolna_);
                        gorna.setText(gorna_);
                        dataDod.setText(dataDod_);
                        EditStanPom();
                    }

                    //aktualizacja listy rozwijanej po dodaniu stanowisko
                    showTable(STAN_TAB, "Stan", 1);
                }

            } else {
                System.out.println("Dodawanie anulowane");
            }
        }

        public void EditPracownik() {
            ResultSet result;
            Object[] message = {
                    "Wybierz, który element chcesz usunąć",
                    "Pracownik:", comboBoxPrac,
            };

            Object[] message2 = {
                    "Stanowisko:", comboBoxStan,
                    "Imie:", imie,
                    "Nazwisko:", nazwisko,
                    "Data urodzenia:", dataUr,
                    "Data zatrudnienia:", dataZatr,
                    "Pensja:", pensja
            };

            String[] options = {"OK", "Cancel"};

            int option = JOptionPane.showOptionDialog(null, message, "Edytuj pracownika",
                    JOptionPane.DEFAULT_OPTION, JOptionPane.PLAIN_MESSAGE, null, options, options[0]);

            if (option == JOptionPane.OK_OPTION) {
                //edytowany pracownik
                selectedPrac = (String) comboBoxPrac.getSelectedItem();
                String[] data = selectedPrac.split(" ");

                try {
                    result = db.ExecuteSQLQuery("SELECT * FROM pracownik WHERE imie=\"" + data[0] + "\" AND nazwisko=\"" + data[1] + "\";");

                    // pobranie wartosci
                    stanowisko_ = data[2];
                    imie_ = result.getString("imie");
                    nazwisko_ = result.getString("nazwisko");
                    dataUr_ = result.getString("data_urodzenia");
                    dataZatr_ = result.getString("data_zatrudnienia");
                    pensja_ = result.getString("pensja");
                    result.close();

                    result = db.ExecuteSQLQuery("SELECT * FROM stanowisko WHERE nazwa=\""+stanowisko_+"\";");
                    dDolna = Double.parseDouble(result.getString("dolna"));
                    dGorna = Double.parseDouble(result.getString("gorna"));
                    result.close();
                } catch (SQLException e) {
                    System.err.println(e.getClass().getName() + ": " + e.getMessage());
                    JOptionPane.showMessageDialog(null, "Problem z edytowaniem pracownika : " + e.getMessage());
                }

                //domyslne wartosci do dodawania
                comboBoxStan.setSelectedItem(stanowisko_);
                imie.setText(imie_);
                nazwisko.setText(nazwisko_);
                dataUr.setText(dataUr_);
                dataZatr.setText(dataZatr_);
                pensja.setText(pensja_);

                String checkChange = String.valueOf(comboBoxStan.getSelectedItem());

                //otwarcie nowego okna
                int insertOpen = JOptionPane.showOptionDialog(null, message2, "Edytuj pracownika",
                        JOptionPane.DEFAULT_OPTION, JOptionPane.PLAIN_MESSAGE, null, options, options[0]);

                if (insertOpen == JOptionPane.OK_OPTION) {
                    if (String.valueOf(comboBoxStan.getSelectedItem()).equals("") || imie.getText().equals("") || nazwisko.getText().equals("") ||
                            dataUr.getText().equals("") || pensja.getText().equals("")) {
                        JOptionPane.showMessageDialog(null, "Nalezy wypelnic wszystkie pola");
//                        AddPracownik();
                    } else {
                        blad = false;
                        try {
                            selectedStan = (String) comboBoxStan.getSelectedItem();
                            szukaneId = db.FindidFK("SELECT * FROM stanowisko WHERE nazwa=\"" + selectedStan + "\";", "id_stanowisko");
                        } catch (Exception e) {
                            JOptionPane.showMessageDialog(null, "Nie znaleziono id wybranego stanowiska");
                            blad = true;
                        }

                        if((String.valueOf(comboBoxStan.getSelectedItem()).equals(checkChange)) == false){
                            // System.out.println("Zawod zmieniony na "+ String.valueOf(comboBoxStan.getSelectedItem()));
                            try{
                                result = db.ExecuteSQLQuery("SELECT * FROM stanowisko WHERE nazwa=\""+selectedStan+"\";");
                                dDolna = Double.parseDouble(result.getString("dolna"));
                                dGorna = Double.parseDouble(result.getString("gorna"));
                                result.close();
                            } catch(SQLException e){
                                System.out.println("Blad SQL");
                            }
                        }

                        if (!checkData(dataUr.getText())) {
                            JOptionPane.showMessageDialog(null, "Niepoprawny format daty urodzenia [yyyy-MM-dd]");
                            blad = true;
                        }

                        if (!checkData(dataZatr.getText()) && !(dataZatr.getText().equals("NULL") || dataZatr.getText().equals("DEFAULT") || dataZatr.getText().equals(""))) {
                            JOptionPane.showMessageDialog(null, "Niepoprawny format daty zatrudnienia [yyyy-MM-dd]");
                            blad = true;
                        }

                        try {
                            dPensja = Double.parseDouble(pensja.getText());
                        } catch (NumberFormatException e) {
                            blad = true;
                            pensja = new JTextField();
                            JOptionPane.showMessageDialog(null, "Pensja powinna byc liczba.");
                        }

                        if(dPensja < dDolna || dPensja > dGorna || blad == true){
                            blad = true;
                            pensja = new JTextField();
                            JOptionPane.showMessageDialog(null, "Pensja nie miesci sie w przedzialach <" + dDolna + ", " + dGorna + "> ");
                        }


                        //::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
                        if (!(blad)) {
                            boolean czysc = db.updatePracownik(imie_, nazwisko_, szukaneId, imie.getText(), nazwisko.getText(), dataUr.getText(), dataZatr.getText(), dPensja);
                            if (czysc) {
                                imie = new JTextField();
                                nazwisko = new JTextField();
                                dataUr = new JTextField();
                                dataZatr = new JTextField();
                                pensja = new JTextField();
                            } else {
                                EditPracownikPom();
                                comboBoxStan.getModel().setSelectedItem(selectedStan);
                                comboBoxStan.updateUI();
                            }
                        } else {
                            EditPracownikPom();
                            comboBoxStan.getModel().setSelectedItem(selectedStan);
                            comboBoxStan.updateUI();
                        }

                        showTable(PRAC_TAB, "Prac", 0);
                    }


                }//koniec wewnetrznego ifa
                else {
                    imie = new JTextField();
                    nazwisko = new JTextField();
                    dataUr = new JTextField();
                    dataZatr = new JTextField();
                    pensja = new JTextField();
                }//jesli sie nie edytuje


            } //koniec zwenetrzengo if'a
            else {
                System.out.println("Edytowanie anulowane");
            }
        }//koniec funkcji

        public void EditPracownikPom() {
            Object[] message2 = {
                    "Stanowisko:", comboBoxStan,
                    "Imie:", imie,
                    "Nazwisko:", nazwisko,
                    "Data urodzenia:", dataUr,
                    "Data zatrudnienia:", dataZatr,
                    "Pensja:", pensja
            };

            String[] options = {"OK", "Cancel"};

            comboBoxStan.setSelectedItem(stanowisko_);
            imie.setText(imie_);
            nazwisko.setText(nazwisko_);
            dataUr.setText(dataUr_);
            dataZatr.setText(dataZatr_);
            pensja.setText(pensja_);

            int insertOpen = JOptionPane.showOptionDialog(null, message2, "Edytuj pracownika",
                    JOptionPane.DEFAULT_OPTION, JOptionPane.PLAIN_MESSAGE, null, options, options[0]);

            if (insertOpen == JOptionPane.OK_OPTION) {
                if (String.valueOf(comboBoxStan.getSelectedItem()).equals("") || imie.getText().equals("") || nazwisko.getText().equals("") ||
                        dataUr.getText().equals("") || pensja.getText().equals("")) {
                    JOptionPane.showMessageDialog(null, "Nalezy wypelnic wszystkie pola");
                    EditPracownikPom();
                } else {
                    blad = false;
                    try {
                        selectedStan = (String) comboBoxStan.getSelectedItem();
                        szukaneId = db.FindidFK("SELECT * FROM stanowisko WHERE nazwa=\"" + selectedStan + "\";", "id_stanowisko");
                    } catch (Exception e) {
                        JOptionPane.showMessageDialog(null, "Nie znaleziono id wybranego stanowiska");
                        blad = true;
                    }

                    if (!checkData(dataUr.getText())) {
                        JOptionPane.showMessageDialog(null, "Niepoprawny format daty urodzenia [yyyy-MM-dd]");
                        blad = true;
                    }

                    if (!checkData(dataZatr.getText()) && !(dataZatr.getText().equals("NULL") || dataZatr.getText().equals("DEFAULT") || dataZatr.getText().equals(""))) {
                        JOptionPane.showMessageDialog(null, "Niepoprawny format daty zatrudnienia [yyyy-MM-dd]");
                        blad = true;
                    }


                    try {
                        dPensja = Double.parseDouble(pensja.getText());
                    } catch (NumberFormatException e) {
                        blad = true;
                        pensja = new JTextField();
                        JOptionPane.showMessageDialog(null, "Pensja powinna byc liczba.");
                    }


                    //::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
                    if (!(blad)) {
                        boolean czysc = db.updatePracownik(imie_, nazwisko_, szukaneId, imie.getText(), nazwisko.getText(), dataUr.getText(), dataZatr.getText(), dPensja);
                        if (czysc) {
                            imie = new JTextField();
                            nazwisko = new JTextField();
                            dataUr = new JTextField();
                            dataZatr = new JTextField();
                            pensja = new JTextField();
                        } else {
                            EditPracownikPom();
                            comboBoxStan.getModel().setSelectedItem(selectedStan);
                            comboBoxStan.updateUI();
                        }
                    } else {
                        EditPracownikPom();
                        comboBoxStan.getModel().setSelectedItem(selectedStan);
                        comboBoxStan.updateUI();
                    }

                    showTable(PRAC_TAB, "Prac", 0);
                }


            }//koniec wewnetrznego ifa
            else {
                imie = new JTextField();
                nazwisko = new JTextField();
                dataUr = new JTextField();
                dataZatr = new JTextField();
                pensja = new JTextField();
            }//jesli sie nie edytuje


        }

        public void EditProjekt() {
            ResultSet result;


            Object[] message = {
                    "Wybierz, który element chcesz edytować",
                    "Projekt:", comboBoxProj,
            };

            Object[] message2 = {
                    "Nazwa:", nazwa,
                    "Opis:", opis,
                    "Data Startu:", starDate,
                    "Data Końca:", endDate,
                    "Budżet:", budzet,
            };


            String[] options = {"OK", "Cancel"};

            int option = JOptionPane.showOptionDialog(null, message, "Edytuj projekt",
                    JOptionPane.DEFAULT_OPTION, JOptionPane.PLAIN_MESSAGE, null, options, options[0]);

            if (option == JOptionPane.OK_OPTION) {
                //nazwa usuwanego stanowiska
                selectedStan = (String) comboBoxProj.getSelectedItem();

                try {
                    result = db.ExecuteSQLQuery("SELECT * FROM projekt WHERE nazwa=\""+selectedStan+"\";");

                    // pobranie wartosci
                    nazwa_ = result.getString("nazwa");
                    opis_ = result.getString("opis");
                    starDate_ = result.getString("data_startu");
                    endDate_ = result.getString("data_konca");
                    budzet_ = result.getString("budzet");
                    result.close();
                } catch (SQLException e) {
                    System.err.println(e.getClass().getName() + ": " + e.getMessage());
                    JOptionPane.showMessageDialog(null, "Problem z edytowaniem stanowiska : " + e.getMessage());
                }

                nazwa.setText(nazwa_);
                opis.setText(opis_);
                starDate.setText(starDate_);
                endDate.setText(endDate_);
                budzet.setText(budzet_);

                //otwarcie nowego okna
                int insertOpen = JOptionPane.showConfirmDialog(null, message2, "Edytuj Projekt", JOptionPane.OK_CANCEL_OPTION);

                if (insertOpen == JOptionPane.OK_OPTION) {

                    if (nazwa.getText().equals("") || starDate.getText().equals("") || endDate.getText().equals("")) {
                        JOptionPane.showMessageDialog(null, "Nalezy wypelnic wszystkie pola (oprocz opis)");
                        EditProjektPom();
                    } else {
                        blad = false;

                        if (!checkData(starDate.getText())) {
                            JOptionPane.showMessageDialog(null, "Niepoprawny format daty startu [yyyy-MM-dd]");
                            blad = true;
                        }

                        if (!checkData(endDate.getText())) {
                            JOptionPane.showMessageDialog(null, "Niepoprawny format daty konca [yyyy-MM-dd]");
                            blad = true;
                        }

                        try {
                            dBudzet = Double.parseDouble(budzet.getText());
                        } catch (NumberFormatException e) {
                            blad = true;
                            wartosc = new JTextField();
                            JOptionPane.showMessageDialog(null, "Budżet powinna byc liczba.");
                        }


                        if (!(blad)) {
                            db.updateProjekt(nazwa_,nazwa.getText(), opis.getText(), starDate.getText(), endDate.getText(),dBudzet);
                            nazwa = new JTextField();
                            opis = new JTextField();
                            starDate = new JTextField();
                            endDate = new JTextField();
                            budzet = new JTextField();
                        } else {
                            EditProjektPom();
                        }


                        showTable(PROJ_TAB, "Proj", 1);
                    }

                } else {
                    nazwa = new JTextField();
                    opis = new JTextField();
                    starDate = new JTextField();
                    endDate = new JTextField();
                    budzet = new JTextField();
                    System.out.println("Edytowanie anulowane");
                }

            } else {
                System.out.println("Edytowanie anulowane");
            }


        }

        public void EditProjektPom(){
            Object[] message2 = {
                    "Nazwa:", nazwa,
                    "Opis:", opis,
                    "Data Startu:", starDate,
                    "Data Końca:", endDate,
                    "Budżet:", budzet,
            };

            nazwa.setText(nazwa_);
            opis.setText(opis_);
            starDate.setText(starDate_);
            endDate.setText(endDate_);
            budzet.setText(budzet_);

            //otwarcie nowego okna
            int insertOpen = JOptionPane.showConfirmDialog(null, message2, "Edytuj Projekt", JOptionPane.OK_CANCEL_OPTION);

            if (insertOpen == JOptionPane.OK_OPTION) {

                if (nazwa.getText().equals("") || starDate.getText().equals("") || endDate.getText().equals("")) {
                    JOptionPane.showMessageDialog(null, "Nalezy wypelnic wszystkie pola (oprocz opis)");
                    EditProjektPom();
                } else {
                    blad = false;

                    if (!checkData(starDate.getText())) {
                        JOptionPane.showMessageDialog(null, "Niepoprawny format daty startu [yyyy-MM-dd]");
                        blad = true;
                    }

                    if (!checkData(endDate.getText())) {
                        JOptionPane.showMessageDialog(null, "Niepoprawny format daty konca [yyyy-MM-dd]");
                        blad = true;
                    }

                    try {
                        dBudzet = Double.parseDouble(budzet.getText());
                    } catch (NumberFormatException e) {
                        blad = true;
                        wartosc = new JTextField();
                        JOptionPane.showMessageDialog(null, "Budżet powinna byc liczba.");
                    }


                    if (!(blad)) {
                        db.updateProjekt(nazwa_,nazwa.getText(), opis.getText(), starDate.getText(), endDate.getText(),dBudzet);
                        nazwa = new JTextField();
                        opis = new JTextField();
                        starDate = new JTextField();
                        endDate = new JTextField();
                        budzet = new JTextField();
                    } else {
                        EditPracownikPom();
                    }


                    showTable(PROJ_TAB, "Proj", 1);
                }

            } else {
                nazwa = new JTextField();
                opis = new JTextField();
                starDate = new JTextField();
                endDate = new JTextField();
                budzet = new JTextField();
                System.out.println("Dodawanie anulowane");
            }
        }

        public void EditZadanie(){
            ResultSet result;
            Object[] message = {
                    "Wybierz, który element chcesz edytowac",
                    "Projekt:", comboBoxZad,
            };

            Object[] message2 = {
                    "Projekt:", comboBoxProj,
                    "Pracownik:", comboBoxPrac,
                    "Stawka:", stawka,
                    "Ilosc godzin:", ilGodzin,
                    "Komentarz:",komentarz,
                    "Data Startu:", starDate,
                    "Data Końca:", endDate
            };

            String[] options = {"OK", "Cancel"};

            int option = JOptionPane.showOptionDialog(null, message, "Edytuj zadanie",
                    JOptionPane.DEFAULT_OPTION, JOptionPane.PLAIN_MESSAGE, null, options, options[0]);

            if (option == JOptionPane.OK_OPTION) {
                //usuwany pracownik
                selectedProj = (String) comboBoxZad.getSelectedItem();
                dane = selectedProj.split(" "); //0-projekt, 1-imie, 2-nazwisko, 3-stanowisko, what i need project imie naziwsko stanowisko
                int idPrac = db.FindidFK("SELECT * FROM pracownik WHERE imie=\"" + dane[1] + "\" AND nazwisko=\"" + dane[2] + "\";", "id_pracownik");
                int idProj = db.FindidFK("SELECT * FROM projekt WHERE nazwa=\"" + dane[0] + "\";", "id_projekt");

                try {
                    result = db.ExecuteSQLQuery("SELECT * FROM zadania_pracownikow WHERE id_pracownik=\""+idPrac+"\" AND id_projekt=\"" + idProj + "\";");

                    // pobranie wartosci
                    komentarz_ = result.getString("komentarz");
                    stawka_ = result.getString("stawka");
                    ilGodzin_ = result.getString("ilosc_godzin");
                    starDate_ = result.getString("data_startu");
                    endDate_ = result.getString("data_konca");
                    result.close();
                } catch (SQLException e) {
                    System.err.println(e.getClass().getName() + ": " + e.getMessage());
                    JOptionPane.showMessageDialog(null, "Problem z edytowaniem stanowiska : " + e.getMessage());
                }

                //zaldaowanie wartosci
                comboBoxProj.setSelectedItem(dane[0]);
                comboBoxPrac.setSelectedItem(dane[1]+" "+dane[2]+" "+dane[3]);
                stawka.setText(stawka_);
                ilGodzin.setText(ilGodzin_);
                komentarz.setText(komentarz_);
                starDate.setText(starDate_);
                endDate.setText(endDate_);

                int insertOpen = JOptionPane.showOptionDialog(null, message2, "Edytuj zadanie",
                        JOptionPane.DEFAULT_OPTION, JOptionPane.PLAIN_MESSAGE, null, options, options[0]);
                if (insertOpen == JOptionPane.OK_OPTION) {

                    if (String.valueOf(comboBoxProj.getSelectedItem()).equals("") || String.valueOf(comboBoxPrac.getSelectedItem()).equals("") || stawka.getText().equals("") || ilGodzin.getText().equals("") || starDate.getText().equals("") || endDate.getText().equals("")) {
                        JOptionPane.showMessageDialog(null, "Nalezy wypelnic wszystkie pola");
                        EditZadaniePom();
                    } else {
                        blad = false;

                        try {
                            selectedProj = (String) comboBoxProj.getSelectedItem();
                            szukaneIdProj = db.FindidFK("SELECT * FROM projekt WHERE nazwa=\"" + selectedProj + "\";", "id_projekt");
                        } catch (Exception e) {
                            JOptionPane.showMessageDialog(null, "Nie znaleziono id wybranego projektu");
                            blad = true;
                        }


                        try {
                            selectedPrac = (String) comboBoxPrac.getSelectedItem();
                            String[] pole = selectedPrac.split(" ");
                            szukaneIdPrac = db.FindidFK("SELECT * FROM pracownik WHERE imie=\"" + pole[0] + "\" AND nazwisko=\"" + pole[1] + "\";", "id_pracownik");
                        } catch (Exception e) {
                            JOptionPane.showMessageDialog(null, "Nie znaleziono id wybranego pracownika");
                            blad = true;
                        }


                        try {
                            dStawka = Double.parseDouble(stawka.getText());
                        } catch (NumberFormatException e) {
                            blad = true;
                            stawka = new JTextField();
                            JOptionPane.showMessageDialog(null, "Stawka powinna byc liczba.");
                        }

                        try {
                            dIlGodzin = Double.parseDouble(ilGodzin.getText());
                        } catch (NumberFormatException e) {
                            blad = true;
                            ilGodzin = new JTextField();
                            JOptionPane.showMessageDialog(null, "Ilosc godzin: powinna byc liczba.");
                        }

                        if (!checkData(starDate.getText())) {
                            JOptionPane.showMessageDialog(null, "Niepoprawny format daty startu [yyyy-MM-dd]");
                            blad = true;
                        }

                        if (!checkData(endDate.getText())) {
                            JOptionPane.showMessageDialog(null, "Niepoprawny format daty konca [yyyy-MM-dd]");
                            blad = true;
                        }


                        //::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
                        if (!(blad)) {
                            boolean czysc = db.updateZadanie(idProj,idPrac,szukaneIdProj, szukaneIdPrac, dStawka, dIlGodzin,komentarz.getText(),starDate.getText(),endDate.getText());

                            if (czysc) {
                                stawka = new JTextField();
                                ilGodzin = new JTextField();
                                komentarz = new JTextField();
                                starDate = new JTextField();
                                endDate = new JTextField();
                            } else {
                                EditZadaniePom();
                            }
                        } else {
                            EditZadaniePom();
                        }

                        showTable(ZAD_TAB, "Zad", 0);
                    }

                } else {
                    imie = new JTextField();
                    nazwisko = new JTextField();
                    dataUr = new JTextField();
                    dataZatr = new JTextField();
                    pensja = new JTextField();
                    stawka = new JTextField();
                    ilGodzin = new JTextField();
                    komentarz = new JTextField();
                    starDate = new JTextField();
                    endDate = new JTextField();
                }



            } else {
            }
        }

        public void EditZadaniePom(){


            comboBoxProj.setSelectedItem(dane[0]);
            comboBoxPrac.setSelectedItem(dane[1]+" "+dane[2]+" "+dane[3]);
            stawka.setText(stawka_);
            ilGodzin.setText(ilGodzin_);
            starDate.setText(starDate_);
            endDate.setText(endDate_);

            int idPrac = db.FindidFK("SELECT * FROM pracownik WHERE imie=\"" + dane[1] + "\" AND nazwisko=\"" + dane[2] + "\";", "id_pracownik");
            int idProj = db.FindidFK("SELECT * FROM projekt WHERE nazwa=\"" + dane[0] + "\";", "id_projekt");

            Object[] message2 = {
                    "Projekt:", comboBoxProj,
                    "Pracownik:", comboBoxPrac,
                    "Stawka:", stawka,
                    "Ilosc godzin:", ilGodzin,
                    "Komentarz:",komentarz,
                    "Data Startu:", starDate,
                    "Data Końca:", endDate
            };
            String[] options = {"OK", "Cancel"};

            int insertOpen = JOptionPane.showOptionDialog(null, message2, "Edytuj zadanie",
                    JOptionPane.DEFAULT_OPTION, JOptionPane.PLAIN_MESSAGE, null, options, options[0]);
            if (insertOpen == JOptionPane.OK_OPTION) {

                if (String.valueOf(comboBoxProj.getSelectedItem()).equals("") || String.valueOf(comboBoxPrac.getSelectedItem()).equals("") || stawka.getText().equals("") || ilGodzin.getText().equals("")  || starDate.getText().equals("") || endDate.getText().equals("")) {
                    JOptionPane.showMessageDialog(null, "Nalezy wypelnic wszystkie pola");
                    EditZadaniePom();
                } else {
                    blad = false;

                    try {
                        selectedProj = (String) comboBoxProj.getSelectedItem();
                        szukaneIdProj = db.FindidFK("SELECT * FROM projekt WHERE nazwa=\"" + selectedProj + "\";", "id_projekt");
                    } catch (Exception e) {
                        JOptionPane.showMessageDialog(null, "Nie znaleziono id wybranego projektu");
                        blad = true;
                    }


                    try {
                        selectedPrac = (String) comboBoxPrac.getSelectedItem();
                        String[] pole = selectedPrac.split(" ");
                        szukaneIdPrac = db.FindidFK("SELECT * FROM pracownik WHERE imie=\"" + pole[0] + "\" AND nazwisko=\"" + pole[1] + "\";", "id_pracownik");
                    } catch (Exception e) {
                        JOptionPane.showMessageDialog(null, "Nie znaleziono id wybranego pracownika");
                        blad = true;
                    }


                    try {
                        dStawka = Double.parseDouble(stawka.getText());
                    } catch (NumberFormatException e) {
                        blad = true;
                        stawka = new JTextField();
                        JOptionPane.showMessageDialog(null, "Stawka powinna byc liczba.");
                    }

                    try {
                        dIlGodzin = Double.parseDouble(ilGodzin.getText());
                    } catch (NumberFormatException e) {
                        blad = true;
                        ilGodzin = new JTextField();
                        JOptionPane.showMessageDialog(null, "Ilosc godzin: powinna byc liczba.");
                    }

                    if (!checkData(starDate.getText())) {
                        JOptionPane.showMessageDialog(null, "Niepoprawny format daty startu [yyyy-MM-dd]");
                        blad = true;
                    }

                    if (!checkData(endDate.getText())) {
                        JOptionPane.showMessageDialog(null, "Niepoprawny format daty konca [yyyy-MM-dd]");
                        blad = true;
                    }


                    //::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
                    if (!(blad)) {
                        boolean czysc = db.updateZadanie(idProj,idPrac,szukaneIdProj, szukaneIdPrac, dStawka, dIlGodzin,komentarz.getText(), starDate.getText(),endDate.getText());

                        if (czysc) {
                            stawka = new JTextField();
                            ilGodzin = new JTextField();
                            komentarz = new JTextField();
                            starDate = new JTextField();
                            endDate = new JTextField();
                        } else {
                            EditZadaniePom();
                        }
                    } else {
                        EditZadaniePom();
                    }

                    showTable(ZAD_TAB, "Zad", 0);
                }

            } else {
                stawka = new JTextField();
                ilGodzin = new JTextField();
                komentarz = new JTextField();
                starDate = new JTextField();
                endDate = new JTextField();
                imie = new JTextField();
                nazwisko = new JTextField();
                dataUr = new JTextField();
                dataZatr = new JTextField();
                pensja = new JTextField();
            }
        }

        public void EditNagroda(){
            ResultSet result;
            Object[] message = {
                    "Wybierz, który element chcesz edytowac",
                    "Projekt:", comboBoxNag,
            };

            Object[] message2 = {
                    "Pracownik:", comboBoxPrac,
                    "Nazwa:", nazwa,
                    "Opis:", opis,
                    "Wartość:",wartosc,
                    "Data otrzymania:",dataOt,
                    "Nagroda za:",nagrodaZa
            };

            String[] options = {"OK", "Cancel"};

            int option = JOptionPane.showOptionDialog(null, message, "Edytuj nagrode",
                    JOptionPane.DEFAULT_OPTION, JOptionPane.PLAIN_MESSAGE, null, options, options[0]);

            if (option == JOptionPane.OK_OPTION) {
                //usuwany pracownik
                selectedNag = (String) comboBoxNag.getSelectedItem();
                dane = selectedNag.split(" "); //0-nazwa, 1-imie, 2-nazwisko, 3-stanowisko, what i need project imie naziwsko stanowisko
                int idPrac = db.FindidFK("SELECT * FROM pracownik WHERE imie=\"" + dane[1] + "\" AND nazwisko=\"" + dane[2] + "\";", "id_pracownik");

                try {
                    result = db.ExecuteSQLQuery("SELECT * FROM nagroda WHERE nazwa=\""+dane[0]+"\";");

                    // pobranie wartosci
                    nazwa_ = result.getString("nazwa");
                    opis_ = result.getString("opis");
                    wartosc_ = result.getString("wartosc");
                    dataOt_ = result.getString("data_otrzymania");
                    nagrodaZa_ = result.getString("nagroda_za");
                    result.close();
                } catch (SQLException e) {
                    System.err.println(e.getClass().getName() + ": " + e.getMessage());
                    JOptionPane.showMessageDialog(null, "Problem z edytowaniem stanowiska : " + e.getMessage());
                }

                //zaldaowanie wartosci
                comboBoxPrac.setSelectedItem(dane[1]+" "+dane[2]+" "+dane[3]);
                nazwa.setText(nazwa_);
                opis.setText(opis_);
                wartosc.setText(wartosc_);
                dataOt.setText(dataOt_);
                nagrodaZa.setText(nagrodaZa_);

                int insertOpen = JOptionPane.showOptionDialog(null, message2, "Edytuj nagrode",
                        JOptionPane.DEFAULT_OPTION, JOptionPane.PLAIN_MESSAGE, null, options, options[0]);
                if (insertOpen == JOptionPane.OK_OPTION) {

                    if (String.valueOf(comboBoxPrac.getSelectedItem()).equals("") || nazwa.getText().equals("") || wartosc.getText().equals("")) {
                        JOptionPane.showMessageDialog(null, "Nalezy wypelnic wszystkie pola");
                        EditZadaniePom();
                    } else {
                        blad = false;

                        try {
                            selectedPrac = (String) comboBoxPrac.getSelectedItem();
                            String[] pole = selectedPrac.split(" ");
                            szukaneIdPrac = db.FindidFK("SELECT * FROM pracownik WHERE imie=\"" + pole[0] + "\" AND nazwisko=\"" + pole[1] + "\";", "id_pracownik");
                        } catch (Exception e) {
                            JOptionPane.showMessageDialog(null, "Nie znaleziono id wybranego pracownika");
                            blad = true;
                        }


                        try {
                            dWartosc = Double.parseDouble(wartosc.getText());
                        } catch (NumberFormatException e) {
                            blad = true;
                            stawka = new JTextField();
                            JOptionPane.showMessageDialog(null, "Wartość powinna byc liczba.");
                        }



                        //::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
                        if (!(blad)) {
                            boolean czysc = db.updateNagroda(nazwa_,nazwa.getText(),opis.getText(),dWartosc,dataOt.getText(),nagrodaZa.getText());

                            if (czysc) {
                                nazwa = new JTextField();
                                opis = new JTextField();
                                wartosc = new JTextField();
                                dataOt = new JTextField();
                                nagrodaZa = new JTextField();
                            } else {
                                EditNagrodaPom();
                            }
                        } else {
                            EditNagrodaPom();
                        }

                        showTable(NAG_TAB, "Nag", 0);
                    }

                } else {
                    nazwa = new JTextField();
                    opis = new JTextField();
                    wartosc = new JTextField();
                    dataOt = new JTextField();
                    nagrodaZa = new JTextField();
                }



            } else {
            }
        }

        public void EditNagrodaPom(){

            comboBoxPrac.setSelectedItem(dane[1]+" "+dane[2]+" "+dane[3]);
            nazwa.setText(nazwa_);
            opis.setText(opis_);
            wartosc.setText(wartosc_);
            dataOt.setText(dataOt_);
            nagrodaZa.setText(nagrodaZa_);

            int idPrac = db.FindidFK("SELECT * FROM pracownik WHERE imie=\"" + dane[1] + "\" AND nazwisko=\"" + dane[2] + "\";", "id_pracownik");


            Object[] message2 = {
                    "Pracownik:", comboBoxPrac,
                    "Nazwa:", nazwa,
                    "Opis:", opis,
                    "Wartość:",wartosc,
                    "Data otrzymania:",dataOt,
                    "Nagroda za:",nagrodaZa
            };

            String[] options = {"OK", "Cancel"};


            int insertOpen = JOptionPane.showOptionDialog(null, message2, "Edytuj nagrode",
                    JOptionPane.DEFAULT_OPTION, JOptionPane.PLAIN_MESSAGE, null, options, options[0]);
            if (insertOpen == JOptionPane.OK_OPTION) {

                if (String.valueOf(comboBoxPrac.getSelectedItem()).equals("") || nazwa.getText().equals("") || wartosc.getText().equals("")) {
                    JOptionPane.showMessageDialog(null, "Nalezy wypelnic wszystkie pola");
                    EditZadaniePom();
                } else {
                    blad = false;

                    try {
                        selectedPrac = (String) comboBoxPrac.getSelectedItem();
                        String[] pole = selectedPrac.split(" ");
                        szukaneIdPrac = db.FindidFK("SELECT * FROM pracownik WHERE imie=\"" + pole[0] + "\" AND nazwisko=\"" + pole[1] + "\";", "id_pracownik");
                    } catch (Exception e) {
                        JOptionPane.showMessageDialog(null, "Nie znaleziono id wybranego pracownika");
                        blad = true;
                    }


                    try {
                        dWartosc = Double.parseDouble(wartosc.getText());
                    } catch (NumberFormatException e) {
                        blad = true;
                        stawka = new JTextField();
                        JOptionPane.showMessageDialog(null, "Wartość powinna byc liczba.");
                    }



                    //::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
                    if (!(blad)) {
                        boolean czysc = db.updateNagroda(nazwa_,nazwa.getText(),opis.getText(),dWartosc,dataOt.getText(),nagrodaZa.getText());

                        if (czysc) {
                            nazwa = new JTextField();
                            opis = new JTextField();
                            wartosc = new JTextField();
                            dataOt = new JTextField();
                            nagrodaZa = new JTextField();
                        } else {
                            EditNagrodaPom();
                        }
                    } else {
                        EditNagrodaPom();
                    }

                    showTable(NAG_TAB, "Nag", 0);
                }

            } else {
                nazwa = new JTextField();
                opis = new JTextField();
                wartosc = new JTextField();
                dataOt = new JTextField();
                nagrodaZa = new JTextField();
            }





        }

    }

    public boolean checkData(String date) {
        try {
            DateFormat df = new SimpleDateFormat(DATE_FORMAT);
            df.setLenient(false);
            df.parse(date);
            return true;
        } catch (ParseException e) {
            return false;
        }
    }//checkData

    public void refreshCombo() {
        comboBoxProj = db.comboProj();
        comboBoxPrac = db.comboPrac();
        comboBoxStan = db.comboStan();
        comboBoxZad = db.comboZad();
        comboBoxNag = db.comboNag();
    }
}

