import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;
import java.util.Arrays;
import java.util.stream.Stream;

/**
 * Algorytmy Numeryczne - Zadanie 2
 * Macierze
 * Autor: Jakub Ronkiewicz, 238155
 * Informatyka: III rok sp. Tester programista gr. 1
 * Kompilowac za pomoca polecenia
 * javac Main.java
 */

public class Main {

    public static void main(String[] args) throws IOException {
        //DEKLARACJA MACIERZY I WEKTOROW
        Matrix<Fraction> frA = new Matrix<>(1, new Fraction[]{new Fraction(2)});
        Matrix<Fraction> frB = new Matrix<>(1, new Fraction[]{new Fraction(2)});
        Matrix<Fraction> frC = new Matrix<>(1, new Fraction[]{new Fraction(2)});
        Fraction[] fr_vX = new Fraction[0];
        Fraction[] fr_vB = new Fraction[0];

        Matrix<Float> flA = new Matrix<>(1, new Float[]{1f});
        Matrix<Float> flB = new Matrix<>(1, new Float[]{1f});
        Matrix<Float> flC = new Matrix<>(1, new Float[]{1f});
        Float[] fl_vX = new Float[0];
        Float[] fl_vB = new Float[0];

        Matrix<Double> dA = new Matrix<>(1, new Double[]{1d});
        Matrix<Double> dB = new Matrix<>(1, new Double[]{1d});
        Matrix<Double> dC = new Matrix<>(1, new Double[]{1d});
        Double[] d_vX = new Double[0];
        Double[] d_vB = new Double[0];

        // OTWIERAMY PLIKI DO ODCZYTU
        BufferedReader wBr = new BufferedReader((new FileReader("wynikicpp.txt")));
        BufferedReader dBr = new BufferedReader((new FileReader("danecpp.txt")));
        // OTWIERAMY PLIK DO ZAPISU
        BufferedWriter bW = new BufferedWriter((new FileWriter("bledy.csv")));


        bW.write("n,fr1B,fr1T,d1B,d1T,fl1B,fl1T,e1T,fr2B,fr2T,d2B,d2T,fl2B,fl2T,e2T,fr3B,fr3T,d3B,d3T,fl3B,fl3T,e3T,e5B,e5T,fr4B,fr4T,d4B,d4T,fl4B,fl4T,fr5B,fr5T,d5B,d5T,fl5B,fl5T,fr6B,fr6T,d6B,d6T,fl6B,fl6T,e6T\n");
        String lineD, lineW;
        int number = 0;
        int size = Integer.valueOf(dBr.readLine()); //omit first line
        wBr.readLine(); // omijam pierwsza linie z pliku zapisami, aby rowna szla z danymi
        while(((lineD = dBr.readLine()) != null)){
            String[] fracs = lineD.split(" "); // ze stringa oddzielam ulamki spacja i zpaisuje do tablicy
            switch(number){
                case 0:
                    //Wczytanie macierzy A
                    //Stworzenie tablicy z ulamkami, ktore wypelnia macierz
                    Fraction[] values = new Fraction[fracs.length];
                    for(int i = 0; i < fracs.length; i++)
                        values[i] = new Fraction(fracs[i]);

                    frA = new Matrix<>(size, values); // macierz z ulamkami utworzona
                    // tablica z floatami uzyskana poprzez przekonwertowania ulamkow na floata
                    Float[] floatVal = frA.val2Float(values);
                    // tablica z double uzyskana poprzez przekonwertowania ulamkow na double
                    Double[] doubleVal = frA.val2Double(values);

                    flA = new Matrix<>(size, floatVal); // macierz z floatami
                    dA = new Matrix<>(size,doubleVal); // macierz z double

                    number++;
                    break;
                case 1:
                    // Wczytanie macierzy B
                    values = new Fraction[fracs.length];
                    for(int i = 0; i < fracs.length; i++)
                        values[i] = new Fraction(fracs[i]);

                    frB = new Matrix<>(size, values);
                    floatVal = frA.val2Float(values);
                    doubleVal = frA.val2Double(values);

                    flB = new Matrix<>(size, floatVal);
                    dB = new Matrix<>(size,doubleVal);
                    number++;
                    break;
                case 2:
                    // Wczytanie macierzy C
                    values = new Fraction[fracs.length];
                    for(int i = 0; i < fracs.length; i++)
                        values[i] = new Fraction(fracs[i]);

                    frC = new Matrix<>(size, values);
                    floatVal = frA.val2Float(values);
                    doubleVal = frA.val2Double(values);

                    flC = new Matrix<>(size, floatVal);
                    dC = new Matrix<>(size,doubleVal);
                    number++;
                    break;
                case 3:
                    // Wczytanie wektora X
                    fr_vX = new Fraction[fracs.length];
                    fl_vX = new Float[fracs.length];
                    d_vX = new Double[fracs.length];

                    for(int i = 0; i < fracs.length; i++) {
                        fr_vX[i] = new Fraction(fracs[i]);
                        fl_vX[i] = fr_vX[i].toFloat();
                        d_vX[i] = fr_vX[i].toDouble();
                    }

                    number++;
                    break;
                case 4:
                    // Wczytanie wektora B
                    fr_vB = new Fraction[fracs.length];
                    fl_vB = new Float[fracs.length];
                    d_vB = new Double[fracs.length];

                    for(int i = 0; i < fracs.length; i++) {
                        fr_vB[i] = new Fraction(fracs[i]);
                        fl_vB[i] = fr_vB[i].toFloat();
                        d_vB[i] = fr_vB[i].toDouble();
                    }

                    number++;
                    break;
                case 5:
                    // OBLICZENIA
                    bW.write(size+",");

                    // POBRANIE WYNIKOW Z EIGENA
                    lineW = wBr.readLine();
                    String[] temp_wynik = lineW.split("\\|");
                    double czas_eig = Double.valueOf(temp_wynik[1]);
                    Double[] wynik_eig = Arrays.stream(temp_wynik[0].split(" "))
                            .map(Double::valueOf)
                            .toArray(Double[]::new);

                    // A*X =================================================================================================================
                    // ULAMEK
                    double tStart = System.nanoTime();
                    Fraction[] temp = frA.mulMatrix(fr_vX);
                    double tEnd = System.nanoTime();
                    double blad = liczBlad(temp, wynik_eig);
                    double tRes = (tEnd - tStart)/1e9; // time in nanoseconds
                    bW.write(blad + "," + tRes + ",");


                    // DOUBLE
                    tStart = System.nanoTime();
                    Double[] dTemp = dA.mulMatrix(d_vX);
                    tEnd = System.nanoTime();
                    tRes = (tEnd - tStart)/1e9; // time in nanoseconds
                    blad = liczBlad(dTemp, wynik_eig);
                    bW.write(blad + "," + tRes + ",");


                    // FLOAT
                    tStart = System.nanoTime();
                    Float[] fTemp = flA.mulMatrix(fl_vX);
                    tEnd = System.nanoTime();
                    tRes = (tEnd - tStart)/1e9; // time in nanoseconds
                    blad = liczBlad(fTemp, wynik_eig);
                    bW.write(blad + "," + tRes + "," + czas_eig + ",");

                    // =================================================================================================================


                    // POBRANIE WYNIKOW Z EIGENA
                    lineW = wBr.readLine();
                    temp_wynik = lineW.split("\\|");
                    czas_eig = Double.valueOf(temp_wynik[1]);
                    wynik_eig = Arrays.stream(temp_wynik[0].split(" "))
                            .map(Double::valueOf)
                            .toArray(Double[]::new);


                    // (A+B+C)*x =======================================================================================================

                    // ULAMKI
                    tStart = System.nanoTime();
                    temp = (Fraction[])(frA.addMatrix(frB.getMatrix()).addMatrix(frC.getMatrix())).mulMatrix(fr_vX);
                    tEnd = System.nanoTime();
                    tRes = (tEnd - tStart)/1e9; // time in nanoseconds
                    blad = liczBlad(temp, wynik_eig);
                    bW.write(blad + "," + tRes + ",");

                    // DOUBLE
                    tStart = System.nanoTime();
                    dTemp = (Double[])(dA.addMatrix(dB.getMatrix()).addMatrix(dC.getMatrix())).mulMatrix(d_vX);
                    tEnd = System.nanoTime();
                    tRes = (tEnd - tStart)/1e9; // time in nanoseconds
                    blad = liczBlad(dTemp, wynik_eig);
                    bW.write(blad + "," + tRes + ",");

                    // FLOAT
                    tStart = System.nanoTime();
                    fTemp = (Float[])(flA.addMatrix(flB.getMatrix()).addMatrix(flC.getMatrix())).mulMatrix(fl_vX);
                    tEnd = System.nanoTime();
                    tRes = (tEnd - tStart)/1e9; // time in nanoseconds
                    blad = liczBlad(fTemp, wynik_eig);
                    bW.write(blad + "," + tRes + "," + czas_eig + ",");


                    // =================================================================================================================

                    // POBRANIE WYNIKOW Z EIGENA
                    lineW = wBr.readLine();
                    temp_wynik = lineW.split("\\|");
                    czas_eig = Double.valueOf(temp_wynik[1]);
                    wynik_eig = Arrays.stream(temp_wynik[0].split(" "))
                            .map(Double::valueOf)
                            .toArray(Double[]::new);

                    // A*(B*C) =========================================================================================================

                    // A× (B × C) = (A × B) × C (łączność mnożenia);
                    // ULAMEK
                    tStart = System.nanoTime();
                    temp = (Fraction[])(frA.mulMatrix(frB.getMatrix()).mulMatrix(frC.getMatrix())).get1D();
                    tEnd = System.nanoTime();
                    tRes = (tEnd - tStart)/1e9; // time in nanoseconds
                    blad = liczBlad(temp, wynik_eig);
                    bW.write(blad + "," + tRes + ",");

                    // DOUBLE
                    tStart = System.nanoTime();
                    dTemp = (Double[])(dA.mulMatrix(dB.getMatrix()).mulMatrix(dC.getMatrix())).get1D();
                    tEnd = System.nanoTime();
                    tRes = (tEnd - tStart)/1e9; // time in nanoseconds
                    blad = liczBlad(dTemp, wynik_eig);
                    bW.write(blad + "," + tRes + ",");

                    // FLOAT
                    tStart = System.nanoTime();
                    fTemp = (Float[])(flA.mulMatrix(flB.getMatrix()).mulMatrix(flC.getMatrix())).get1D();
                    tEnd = System.nanoTime();
                    tRes = (tEnd - tStart)/1e9; // time in nanoseconds
                    blad = liczBlad(fTemp, wynik_eig);
                    bW.write(blad + "," + tRes + "," + czas_eig + ",");


                    // =================================================================================================================

                    // POBRANIE WYNIKOW Z EIGENA PARTIALPIVLU
                    lineW = wBr.readLine();
                    temp_wynik = lineW.split("\\|");
                    Double czas_part = Double.valueOf(temp_wynik[1]);
                    Double[] wynik_part = Arrays.stream(temp_wynik[0].split(" "))
                            .map(Double::valueOf)
                            .toArray(Double[]::new);

                    lineW = wBr.readLine();
                    temp_wynik = lineW.split("\\|");
                    czas_eig = Double.valueOf(temp_wynik[1]);
                    wynik_eig = Arrays.stream(temp_wynik[0].split(" "))
                            .map(Double::valueOf)
                            .toArray(Double[]::new);

                    // Porownanie PARTIALA z FULLEM ====================================================================================

                    blad = liczBlad(wynik_part, wynik_eig);
                    bW.write(blad + "," + czas_part + ",");
                    // =================================================================================================================

                    // POROWNUJE WSZYSTKIE FUNKCJE Z FULL PIVOTEM

                    // GAUSS PODSTAWOWY ================================================================================================
                    // ULAMEK
                    tStart = System.nanoTime();
                    temp = frA.solve(fr_vB);
                    tEnd = System.nanoTime();
                    tRes = (tEnd - tStart)/1e9; // time in nanoseconds
                    blad = liczBlad(temp, wynik_eig);
                    bW.write(blad + "," + tRes + ",");

                    // DOUBLE
                    tStart = System.nanoTime();
                    dTemp = dA.solve(d_vB);
                    tEnd = System.nanoTime();
                    tRes = (tEnd - tStart)/1e9; // time in nanoseconds
                    blad = liczBlad(dTemp, wynik_eig);
                    bW.write(blad + "," + tRes + ",");

                    // FLOAT
                    tStart = System.nanoTime();
                    fTemp = flA.solve(fl_vB);
                    tEnd = System.nanoTime();
                    tRes = (tEnd - tStart)/1e9; // time in nanoseconds
                    blad = liczBlad(fTemp, wynik_eig);
                    bW.write(blad + "," + tRes + ",");
                    // =================================================================================================================

                    // GAUSS PARTIAL ================================================================================================
                    // ULAMEK
                    tStart = System.nanoTime();
                    temp = frA.solvePartial(fr_vB);
                    tEnd = System.nanoTime();
                    tRes = (tEnd - tStart)/1e9; // time in nanoseconds
                    blad = liczBlad(temp, wynik_eig);
                    bW.write(blad + "," + tRes + ",");

                    // DOUBLE
                    tStart = System.nanoTime();
                    dTemp = dA.solvePartial(d_vB);
                    tEnd = System.nanoTime();
                    tRes = (tEnd - tStart)/1e9; // time in nanoseconds
                    blad = liczBlad(dTemp, wynik_eig);
                    bW.write(blad + "," + tRes + ",");

                    // FLOAT
                    tStart = System.nanoTime();
                    fTemp = flA.solvePartial(fl_vB);
                    tEnd = System.nanoTime();
                    tRes = (tEnd - tStart)/1e9; // time in nanoseconds
                    blad = liczBlad(fTemp, wynik_eig);
                    bW.write(blad + "," + tRes + ",");
                    // =================================================================================================================

                    // GAUSS FULLPIVOT =================================================================================================
                    // ULAMEK
                    tStart = System.nanoTime();
                    temp = frA.solveFull(fr_vB);
                    tEnd = System.nanoTime();
                    tRes = (tEnd - tStart)/1e9; // time in nanoseconds
                    blad = liczBlad(temp, wynik_eig);
                    bW.write(blad + "," + tRes + ",");

                    // DOUBLE
                    tStart = System.nanoTime();
                    dTemp = dA.solveFull(d_vB);
                    tEnd = System.nanoTime();
                    tRes = (tEnd - tStart)/1e9; // time in nanoseconds
                    blad = liczBlad(dTemp, wynik_eig);
                    bW.write(blad + "," + tRes + ",");

                    // FLOAT
                    tStart = System.nanoTime();
                    fTemp = flA.solveFull(fl_vB);
                    tEnd = System.nanoTime();
                    tRes = (tEnd - tStart)/1e9; // time in nanoseconds
                    blad = liczBlad(fTemp, wynik_eig);
                    bW.write(blad + "," + tRes + "," + czas_eig + "\n");
                    // =================================================================================================================

                    // PRZYGOTOWANIE DO WCZYTANIA NASTEPNEJ LINII
                    lineW = wBr.readLine();
                    size = Integer.valueOf(fracs[0]);
                    number = 0;
                    System.out.println("MACIERZ UKONCZONA: " + size);
                    break;
            }
        }
        bW.close();

    }

    static double liczBlad(Fraction[] frac, Double[] wynik){
        // zwraca srednia z bledow
        double result = 0;
        for(int i = 0; i < wynik.length; i++){
            result += Math.abs((wynik[i] - frac[i].toDouble())/wynik[i]);
        }
        return result/wynik.length;
    }

    static double liczBlad(Double[] frac, Double[] wynik){
        double result = 0;
        for(int i = 0; i < wynik.length; i++){
            result += Math.abs((wynik[i] - frac[i])/wynik[i]);
        }
        return result/wynik.length;
    }

    static double liczBlad(Float[] frac, Double[] wynik){
        double result = 0;
        for(int i = 0; i < wynik.length; i++){
            result += Math.abs((wynik[i] - frac[i])/wynik[i]);
        }
        return result/wynik.length;
    }


    static void printArr(Fraction[] arr){
        for(int i = 0; i < arr.length; i++){
            System.out.println(arr[i]);
        }
        System.out.println();
    }

    static void printArr(Double[] arr){
        for(int i = 0; i < arr.length; i++){
            System.out.println(arr[i]);
        }
        System.out.println();
    }
}
