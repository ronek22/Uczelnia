/**
 * Algorytmy Numeryczne - Zadanie 4
 * Aproksymacja
 * Autorzy: Jakub Ronkiewicz, Seweryn Rutkowski
 * Informatyka: III rok sp. Tester programista gr. 1
 *
 * Kompilowac za pomoca polecenia:
 * g++ -I sciezka_do_eigena main.cpp -std=c++11 -O3
 */

#include <iostream>
#include <vector>
#include <ctime>
#include <stdio.h>
#include <conio.h>
#include <cstdlib>
#include <Eigen/Dense>
#include <iomanip>
#include <windows.h>
#include <cmath>
#include <map>
#include <set>
#include <fstream>
#include <Eigen/Sparse>

using namespace Eigen;
using namespace std;

typedef SparseMatrix<double> SpMat;  // declares a column-major sparse matrix type of double
typedef Triplet<double> T;


int N = 5;  // N jest rozmiarem planszy, gdzie plansza sk³ada siê z N*2+1 pól (nie jest to sta³a, bêdziemy j¹ prawdopodobnie zwiêkszaæ dla kolejnych ekperymentów)
int size = N*2+1;
int s1 = -N;  // s1 jest polem startowym gracza nr1
int s2 = N;  // s2 jest polem startowym gracza nr2
int l = 5;  // 3 + 2 * (5%4) ; l oznacza liczbê œcian kostki ; œciany maj¹ wartoœci (-2; -1; 0; 1; 2)
int ile_rownan = (2*N)*(2*N)*2;
int ITER = 10; // do jakiego rozmiary planszy dazymy
double epsilon = 1e-10;
int maxIter = 10000000;
int TEST = 10;
double WYNIK;

// ====== MIERZENIE CZASU =========
double PCFreq = 0.0;
__int64 CounterStart = 0;
void StartCounter()
{
        LARGE_INTEGER li;
        if(!QueryPerformanceFrequency(&li))
                cout << "QueryPerformanceFrequency failed!\n";

        PCFreq = double(li.QuadPart)/1000000.0;

        QueryPerformanceCounter(&li);
        CounterStart = li.QuadPart;
}

double GetCounter()
{
        LARGE_INTEGER li;
        QueryPerformanceCounter(&li);
        return double(li.QuadPart-CounterStart)/PCFreq;
}

// ========= GAUSS METHODS ============= 
void GaussPartial(int n, vector<double> x, vector< vector<double> > a, vector<double> b){
        printf("\n%-35s", "GAUSS PARTIAL");
        for(int p = 0; p < n; p++) {
                // find pivot row and swap
                int max = p; // max indeks
                for(int i = p+1; i < n; i++) {
                        if(abs(a[i][p]) > abs(a[max][p]))
                                max = i;
                }

                a[p].swap(a[max]);
                swap(b[p], b[max]);


                // pivot within A and B
                for(int i = p+1; i < n; i++) {
                        double alpha = a[i][p]/a[p][p];
                        b[i] = b[i] - (alpha * b[p]);

                        for(int j = p; j < n; j++) {
                                a[i][j] = a[i][j] - (alpha * a[p][j]);
                        }
                }
        }

        for(int i = n - 1; i >= 0; i--) {
                double sum = 0;
                for(int j = i+1; j < n; j++) {
                        sum += a[i][j] * x[j];
                }
                x[i] = (b[i] - sum)/a[i][i];
        }
        WYNIK = x[0];
}

vector<double> GaussPartialVec(int n, vector<double> x, vector< vector<double> > a, vector<double> b){
        for(int p = 0; p < n; p++){
            // find pivot row and swap
            int max = p; // indeks najwiekszego
            for(int i = p+1; i < n; i++){
                if(abs(a[i][p]) > abs(a[max][p]))
                    max = i;
            }
     
            a[p].swap(a[max]);
            swap(b[p], b[max]);
       
     
            // pivot within A and B
            for(int i = p+1; i < n; i++){
                double alpha = a[i][p]/a[p][p];
                b[i] = b[i] - (alpha * b[p]);
     
                for(int j = p; j < n; j++){
                    a[i][j] = a[i][j] - (alpha * a[p][j]);
                }
            }
        }
     
        for(int i = n - 1; i >= 0; i--){
            double sum = 0;
            for(int j = i+1; j < n; j++){
                sum += a[i][j] * x[j];
            }
            x[i] = (b[i] - sum)/a[i][i];
        }
     
        cout << "Wynik gaussa: " << endl;
        for(int i = 0; i < n; i++)
        {
            cout << x[i] << endl;
        }
         return x;
}

void GaussPartialSparseMatrix(int n, vector<double> x, vector< vector<double> > a, vector<double> b){
        printf("\n%-35s", "GAUSS PARTIAL FOR SPARSE MATRIX");
        for(int p = 0; p < n; p++) {
                // find pivot row and swap
                int max = p; // indeks najwiekszego
                for(int i = p+1; i < n; i++) {
                        if(abs(a[i][p]) > abs(a[max][p]))
                                max = i;
                }

                a[p].swap(a[max]);
                swap(b[p], b[max]);


                // pivot within A and B
                for(int i = p+1; i < n; i++) {
                        // i wiersz
                        // sprawdzenie czy element zerowy jesli tak przejscie do nastepnego wiersza
                        if (a[i][p] == 0) continue;

                        double alpha = a[i][p]/a[p][p];
                        b[i] = b[i] - (alpha * b[p]);


                        for(int j = p; j < n; j++) {
                                a[i][j] = a[i][j] - (alpha * a[p][j]);
                        }
                }
        }

        for(int i = n - 1; i >= 0; i--) {
                double sum = 0;
                for(int j = i+1; j < n; j++) {
                        sum += a[i][j] * x[j];
                }
                x[i] = (b[i] - sum)/a[i][i];
        }

        WYNIK = x[0];
}

void gaussSeidelMethod(int n, vector<double> x, vector< vector<double> > A, vector<double> b){
        printf("\n%-35s", "GAUSS-SEIDEL METHOD");
        double rowSum;
        vector<double> prevX(n,0);
        int iterations;
        for(iterations = 1; iterations <= maxIter; iterations++)
        {
                for(int i = 0; i < n; i++)
                        prevX[i] = x[i];

                for(int i = 0; i < n; i++)
                {
                        rowSum = 0;
                        for(int j = 0; j <= i - 1; j++)
                        {
                                rowSum = rowSum + A[i][j]*x[j];
                        }
                        for(int j = i + 1; j < n; j++)
                        {
                                rowSum = rowSum + A[i][j] * prevX[j];
                        }
                        //x[i] = (1/A[i][i])*(b[i] - rowSum );
                        x[i] = (b[i] - rowSum) / A[i][i];
                }

                //sprawdzamy normy w celu okreslenia czy zakonczyc iteracje
                double maxNorm = 0;
                double rowNorm;
                for(int i = 0; i < n; i++)
                {
                        rowNorm = fabs(x[i] - prevX[i]);
                        if(rowNorm > maxNorm)
                        {
                                maxNorm = rowNorm;
                        }
                }
                if(maxNorm < epsilon)
                        break;
        }
        WYNIK = x[0];
}


// =========== HELPERS =============
void fillPlansza(vector<int> &p, int n){
    int number = -n;
    for(int i = 0; i < 2*n+1; i++) {
            p[i] = number++;
    }
}

int mod(int a, int b) {
    return (a % b + b) % b;
}

int indexOf(vector<int> p, int n){
    for(int i = 0; i < p.size(); i++) {
            if(p[i]==n) return i;
    }
    return -1;
}

void fillVector(vector<double> &x, int limit, int start){
        for(int i = start; i <= limit; i++){
                x.push_back(i);
        }
    }

void printLabel(vector<double> x){
        cout << setw(10) << "METHOD";
        for (auto i: x)
                cout << setw(15) << i;
        cout << endl << "----------------------------------------------------------------------------------------------------------------------------------------------------------------" << endl;
        
}

void printTable(vector<double> fx){
        for (auto i: fx)
                cout << setw(15) << i;
        cout << endl;
}
// ========== GENERATE PROBABILITY EQUATIONS ==============
// structure for generating probability matrix
struct P {
        int player, x, y, wsp;
        P(){
        };
        P(int p, int x_, int y_, int wsp_){
                player = p;
                x = x_;
                y = y_;
                wsp = wsp_;
        }

        void print(){
                string result;

                result = "P" + to_string(player) + "(" + to_string(x) + ", " + to_string(y) + ")^" + to_string(wsp);
                cout << setw(21) << left << result;
        }

        string toString(){
                char buffer[50];
                snprintf(buffer, 50, "%d%d%d", player, x, y);
                return buffer;
        }

        int status(){
                if(x == 0) {
                        return 1; // gracz 1 piewrwszy na mecie wygrana
                } else if(y == 0) {
                        return 0; // przegrana
                } else {
                        return -1; // gra toczy sie dalej
                }
        }
};


vector< vector<P> > generateProbability(bool wyswietlaj){
        bool found;
        int n = N;
        int w = size; //wielkosc planszy

        set<string> repetition; // set do sprawdzania jakie prawdopodobienstwa juz obliczalismy
        // mapa do mapowania odwiedzonych prawdopodobienstw, tak aby przy kolejnym spotkaniu skopiowac wartosci i wspolczynniki
        map<string, int> repMap;
        map<string, int>::iterator it;
        pair<map<string,int>::iterator, bool> result;

        // kostka i plansza
        vector<int> kostka(l, 0);
        kostka[0] = -2; kostka[1] = -1; kostka[2] = 0; kostka[3] = 1; kostka[4] = 2; // l = 5;

        vector<int> plansza(w, 0);
        fillPlansza(plansza, n);

        // Wektory do przechowywania prawdopodobienstw
        vector<P> line(l+1, P());
        vector< vector<P> > test(ile_rownan, line);
        // wartosci poczatkowe
        int x = -n, y = n, player = 1, wsp=0, dod;


        // WYPELENIANIE PIERWSZEGO WIERSZA
        // REPMAP - wspolycznniki, REPETITION - pierwszy wiersz
        test[0][0] = P(player, x, y, wsp); // pierwsze prawdopodobienstwo
        result = repMap.insert(pair<string, int>(test[0][0].toString(), wsp++));
        repetition.insert(test[0][0].toString());
        x = indexOf(plansza, x);
        y = indexOf(plansza, y);
        player = player%2 + 1;

        for(int i = 1; i < l+1; i++) {
                int tmpX = x, tmpY = y;

                // ustawianie odpowiednich parametrow dla dodawanego gracza
                if(player == 2) {
                        // teraz wykonuje ruch gracz pierwszy, tylko wypisywane sa prawdopodobienstwa dla gracza 2
                        tmpX += kostka[i-1];
                        tmpX = plansza[mod(tmpX, w)]; // teraz juz mamy odpowiednie pole, a nie indeks pola
                        // tmpY jest indeksem zamiana na pole
                        tmpY = plansza[mod(tmpY, w)];
                } else{
                        // ruch gracza drugiego
                        tmpY += kostka[i-1];
                        tmpY = plansza[mod(tmpY, w)]; // teraz juz mamy odpowiednie pole, a nie indeks pola
                        // tmpX jest indeksem zamiana na pole
                        tmpX = plansza[mod(tmpX, w)];
                }
                // dodanie obliczonego prawdopodobienstwa do rownania
                test[0][i] = P(player, tmpX, tmpY, wsp);

                // sprawdzenie czy dodarlismy na mete jesli tak, ustawiamy wspolczynnik na -1, aby wiedziec ze nie rozpisujemy juz tego dalej
                if(tmpX == 0 || tmpY == 0) {
                        test[0][i].wsp = -1;
                        wsp--;
                }
                result = repMap.insert(pair<string, int>(test[0][i].toString(), wsp++));
        }
        // KONIEC WYPELNIANIA PIERWSZEGO WIERSZA

        int r = 0; // wiersz
        int c = 1; // kolumna
        int tmp_wsp;
        int i;

        for(i = 1; i < ile_rownan; i++) {
                // PRZYGOWANIE OBLICZANEGO PRAWDOPODOBIENSTWA ^[P1(x,y)] = P2(x_, y_) + P2(x__, y__) + ...
                // zczytanie wartosci z obliczanego rownania
                x = test[r][c].x;
                y = test[r][c].y;
                player = test[r][c].player;
                tmp_wsp = test[r][c].wsp;

                // gdy wiersz, z ktorego pobieramy kolejne prawdopodobienstwo do obliczenia, bedzie tym wierszem, w ktorym jestemy to koniec
                if(r == i) break;
                // dzieki temu uzyskujemy wszyskie prawdopodobienstwa nie omijemy zadnego
                c = c%l + 1;
                if (c == 1) r++;

                // proba wstawienia nowego rownania
                test[i][0] = P(player, x, y, tmp_wsp);
                found = repetition.count(test[i][0].toString()); // sprawdzenie czy juz nie liczylismy tego rownania

                if(found == 1 || (test[i][0].x == 0 || test[i][0].y == 0)) {
                        // albo liczylismy juz te rownanie, albo jest to wygrana lub przegrana i nie ma co liczyc
                        i--;
                        continue;
                } else {
                        repetition.insert(test[i][0].toString());
                }

                x = indexOf(plansza, x);
                y = indexOf(plansza, y);
                player = player%2 + 1;

                for(int j = 1; j < l+1; j++) {
                        int tmpX = x, tmpY = y;
                        // ustawianie odpowiednich parametrow dla dodawanego gracza
                        if(player == 2) {
                                // teraz wykonuje ruch gracz pierwszy, tylko wypisywane sa prawdopodobienstwa dla gracza 2
                                tmpX += kostka[j-1];
                                tmpX = plansza[mod(tmpX, w)]; // teraz juz mamy odpowiednie pole, a nie indeks pola
                                // tmpY jest indeksem zamiana na pole
                                tmpY = plansza[mod(tmpY, w)];

                        } else{
                                // ruch gracza drugiego
                                tmpY += kostka[j-1];
                                tmpY = plansza[mod(tmpY, w)]; // teraz juz mamy odpowiednie pole, a nie indeks pola
                                // tmpX jest indeksem zamiana na pole
                                tmpX = plansza[mod(tmpX, w)];
                        }
                        // wstawiony player
                        test[i][j] = P(player, tmpX, tmpY, wsp);

                        // sprawdzenie czy dodarlismy na mete jesli tak, ustawiamy wspolczynnik na -1, aby wiedziec ze nie rozpisujemy juz tego dalej
                        if(tmpX == 0 || tmpY == 0) {
                                test[i][j].wsp = -1;
                                continue;
                        }

                        result = repMap.insert(pair<string, int>(test[i][j].toString(), test[i][j].wsp));
                        if(result.second == 0) {
                                // trafilismy juz na te prawdopodobienstwo kopiujemy wspolczynnik
                                it = repMap.find(test[i][j].toString());
                                test[i][j].wsp = it->second;
                                continue;
                        }
                        wsp++;
                }
        }

        ile_rownan = i; // ile utworzylismy rownan, potrzebne do zbudowanie macierzy <double>

        // wyswietlanie generacji prawdopodobienstw
        if(wyswietlaj) {
                for(int i = 0; i < ile_rownan; i++) {
                        printf("%d: ", i+1);
                        for(int j = 0; j < l+1; j++) {

                                if( j!= 0 && j!= 1 ) cout << " + ";
                                test[i][j].print();
                                if(j == 0) cout << " = ";
                        }
                        cout << endl;
                }
        }

        return test;
}

void convertToMatrix(vector< vector<P> > test, vector< vector<double> > &matrix, vector<double> &b, vector<double> rozklad){
            // Przenoszenie prawdopodobienstw do macierzy
            int stan;
            for(int i = 0; i < ile_rownan; i++) {
                    for(int j = 0; j < l + 1; j++) {
                            stan = test[i][j].status();
                            if(i == test[i][j].wsp) { // jesli wspolczynnik taki sam wierszy to przekatna i 1
                                    matrix[i][test[i][j].wsp] = 1;
                            } else if(stan == -1) {
                                    matrix[i][test[i][j].wsp] = -rozklad[j-1]; // gramy dalej
                            } else if(stan == 1) {
                                    b[i] += rozklad[j-1]; // zwyciestwo dodajemy do wektora b
                            }
                    }
            }
}


// =========== APROXIMATION ===============
double checkWielomian(int stopien, vector<double> a, double x)
{
   double wynik = 0;
   for(int i = 0; i < stopien + 1; i++)
   {
       wynik = wynik + a[i] * pow(x,i);
   }
   return wynik;
}

void ASD(vector<double> x, vector<double> fx, int stopien, int liczba_wezlow, ofstream &file) //dla wielomianow stopmnia m > 1
{
   cout << endl << "APROKSYMACJA SREDNIOKWADRATOWA DYSKRETNA DLA WIELOMIANÓW STOPNIA M > 1: " << endl;
   vector<double> s(2*stopien+1, 0); //tablica z wartosciami s ukladu rownan
   vector<double> t(stopien+1, 0); //tablica z wartosciami t ukladu rownan
       
   //wypelniamy tablice s i t by stworzyc uklad rownan
   for(int i = 0; i <= 2*stopien; i++ ) //sumujemy do s-ów
   {
       for(int j = 0; j < liczba_wezlow; j++)
       {
           s[i] = s[i] + pow(x[j], i);
       }
       cout << "s[" << i << "] = " << s[i] << endl;		
   }
   for(int i = 0; i <= stopien; i++) //sumujemy do t
   {
       for(int j = 0; j < liczba_wezlow; j++)
       {
           t[i] = t[i] + fx[j]*pow(x[j], i);
       }
       cout << "T[" << i << "] = " << t[i] << endl;
   }
   
   //rozwiazuje uklad rownan gaussem
   vector<double> matr_x(stopien+1, 0);	
   vector<double> matr_b = t;
   vector< vector<double> > matr_a(stopien+1, matr_x);
   int row = 0;
   for(int i = 0; i < stopien+1; i++)
   {
       for(int j = 0; j < stopien+1; j++)
       {
           matr_a[i][j] = s[j+row];	
       }
       row++;
   }
   matr_x = GaussPartialVec(stopien+1, matr_x, matr_a, matr_b);
   cout << "Wielomian aproksymacyjny: F(x) = ";
   for(int i = stopien; i >= 0; i--)
   {
       cout << matr_x[i];
       file << matr_x[i] << " ";
       if(i != 0)
       {
            
           cout << "x^" << i << " + ";
       }
       else
       {
           cout << endl;
       }
   }
   
   //sprawdzenie
   double wynik = 0;
   double blad = 0;
   for(int i = 0; i < liczba_wezlow; i++)
   {
       wynik = checkWielomian(stopien, matr_x, x[i]);
       blad = blad + pow(fx[i] - wynik, 2);
       cout << "Wynik dla F( " << x[i] << ") = " << wynik << endl;
   }
   //blad aproksymacji
   blad = sqrt(blad);
   cout << "Blad aproksymacji wynosi: " << blad << endl;

   wynik = checkWielomian(stopien, matr_x, 17000);
      wynik = wynik/1000000; // wynik w sekundach
   //    wynik = wynik/60; // wynik w minutach
      cout << "Wynik dla F(100 000) = " << wynik << endl;
    file << "\n";
   
}

void regresjaLiniowa(vector<double> x, vector<double> fx, int liczba_wezlow, ofstream &file) //dla wielomianow stopnia m = 1
{
   cout << endl << "REGRESJA LINIOWA DLA WIELOMIANÓW STOPNIA M = 1: " << endl;
   
   double sum_pow_x = 0;
   double sum_x = 0;
   double sum_fx = 0;
   double sum_xfx = 0;
   for(int i = 0; i < liczba_wezlow; i++)
   {
       sum_pow_x = sum_pow_x + pow(x[i], 2);
       sum_x = sum_x + x[i];
       sum_fx = sum_fx + fx[i];
       sum_xfx = sum_xfx + x[i]*fx[i];
   }
   double a0 = (sum_pow_x * sum_fx - sum_x * sum_xfx) / (liczba_wezlow * sum_pow_x - pow(sum_x, 2));
   double a1 = (liczba_wezlow * sum_xfx - sum_x * sum_fx) / (liczba_wezlow * sum_pow_x - pow(sum_x, 2));
   cout << "a0 = " << a0 << " , a1 = " << a1 << endl;
   file << a1 << " " << a0;
   cout << "Wielomian aproksymacyjny: F(x) = " << a1 << "x + " << a0 << endl;
   
   //sprawdzenie
   vector<double> matr_x;
   matr_x.push_back(a0);
   matr_x.push_back(a1);
   double wynik = 0;
   double blad = 0;
   for(int i = 0; i < liczba_wezlow; i++)
   {
       wynik = checkWielomian(1, matr_x, x[i]);
       blad = blad + pow(fx[i] - wynik, 2);
       cout << "Wynik dla F( " << x[i] << ") = " << wynik << endl;
   }
   //blad aproksymacji
   blad = sqrt(blad);
   cout << "Blad aproksymacji wynosi: " << blad << endl;

   wynik = checkWielomian(1, matr_x, 100000);
   wynik = wynik/1000000; // wynik w sekundach
//    wynik = wynik/60; // wynik w minutach
   cout << "Wynik dla F(100 000) = " << wynik << endl;
   file << "\n";
   
   
}

int main()
{
        cout << fixed << setprecision(16);
        IOFormat CommaInitFmt(17, DontAlignCols, " ", " ", "", "", "", "");

        ofstream file;
        file.open ("czasy.csv");
        file << "n,ile,build,gauss,gauss_opt,seidel,lu\n";
        file << fixed << setprecision(16);

		int WEZLY = ITER - N + 1;

        vector<double> x; 
        vector<double> fxGauss, fxGaussSparse, fxSeidel, fxLU;

        for(N; N <= ITER; N++) {
                printf("\n======   N = %d   ======\n", N);
                // aktualizacja zmiennych globalnych zaleznych od N
                size = N*2+1; s1 = -N; s2 = N; ile_rownan = (2*N)*(2*N)*2;
                file << N << "," << ile_rownan << ",";
                


                // GENEROWANIE PRAWDOPODOBIENSTW
                vector<double> rozklad_rowny(l, (1.0/l));
                vector< vector<P> > test = generateProbability(false);
                x.push_back(ile_rownan);
                

                { // scope for free memory after end of the block
                    double elapsed;
                    StartCounter();                    
                    vector<double> genB(ile_rownan, 0);
                    vector<double> line(ile_rownan, 0);
                    vector< vector<double> > genA(ile_rownan, line);
                    vector<double> genX(ile_rownan, 0);
                    // convert from P structure and bouild double matrix
                    convertToMatrix(test, genA, genB, rozklad_rowny);
                    elapsed = GetCounter();
                    file << elapsed << ",";
    
                    // 1 method
                    for(int i = 0; i < TEST; i++){
                    	StartCounter();
                    	GaussPartial(ile_rownan, genX, genA, genB);
                		elapsed += GetCounter();
					}

					elapsed = elapsed/TEST;
                    fxGauss.push_back(elapsed);
                    file << elapsed << ",";                    
                    cout << "x[0]: " << WYNIK <<"  Time: " << elapsed;
    
                    // 2 method
                    for(int i = 0; i < TEST; i++){
                    	StartCounter();
                    	GaussPartialSparseMatrix(ile_rownan, genX, genA, genB);
                		elapsed += GetCounter();
					}

					elapsed = elapsed/TEST;
                    fxGaussSparse.push_back(elapsed);
                    file << elapsed << ",";
                    cout << "x[0]: " << WYNIK << "  Time: " << elapsed;
    
                    // 4 method
                    for(int i = 0; i < TEST; i++){
                    	StartCounter();
                    	gaussSeidelMethod(ile_rownan, genX, genA, genB);
                		elapsed += GetCounter();
					}

					elapsed = elapsed/TEST;
                    fxSeidel.push_back(elapsed);
                    file << elapsed << ",";
                    cout << "x[0]: " << WYNIK << "  Time: " << elapsed << endl;
    
                    // ========= EIGEN ==============
                    
                    VectorXd vectorB(ile_rownan);
                    VectorXd wynik(ile_rownan);
                    for(int row = 0; row < ile_rownan; row++){
                            vectorB(row) = genB[row];
                            wynik(row) = 0;
                    }
        
                    vector<T> coefficients;    // list of non-zeros coefficients
                    SpMat A(ile_rownan,ile_rownan);
                    coefficients.reserve(ile_rownan * ile_rownan);
                    for(int i = 0; i < ile_rownan; i++)
                    {
                            for(int j = 0; j < ile_rownan; j++)
                            {
                                    coefficients.push_back(T(i,j,genA[i][j]));
                            }
                    }
                    A.setFromTriplets(coefficients.begin(), coefficients.end());
                    SparseLU<SparseMatrix<double, ColMajor>, COLAMDOrdering<int> > solver;
                    // Compute the ordering permutation vector from the structural pattern of A
                    solver.analyzePattern(A);
                    // Compute the numerical factorization
                    solver.factorize(A);
                    //Use the factors to solve the linear system
                    // 3 method
                    for(int i = 0; i < TEST; i++){
                    	StartCounter();
                    	wynik = solver.solve(vectorB);
                		elapsed += GetCounter();
					}

					elapsed = elapsed/TEST;
                    fxLU.push_back(elapsed);
                    printf("%-35s: Time: %f\n", "SparseLU()",elapsed);
                    file << elapsed << endl;
                }
                
        }
        file.close();
        /* PRINT TABLES */
        cout << fixed << setprecision(2);
        cout << endl;
        printLabel(x); 
        cout << setw(10) << "GAUSS";
        printTable(fxGauss);
        cout << setw(10) << "G.SPARSE";
        printTable(fxGaussSparse); 
        cout << setw(10) << "LU";
        printTable(fxLU);      
        cout << setw(10) << "SEIDEL";  
        printTable(fxSeidel);
        cout << endl;

        // ========== APROKSYMACJA ==================
        
        ofstream file2;
        file2.open("wielomiany.txt"); // kolejnosc gauss, sparse, lu, seidel
        file2 << fixed << setprecision(16);
        
        ASD(x, fxGauss, 3, WEZLY, file2); // 1. WIELOMIAN 3-go stopnia dla metody Gaussa
        ASD(x, fxGaussSparse, 2, WEZLY, file2); // 2. WIELOMIAN 2-go stopnia dla metody Gaussa z drobna optymalizacja
        regresjaLiniowa(x, fxLU, WEZLY, file2);  // 3. WIELOMIAN 1-go stopnia dla metody LU z wykorzystaniem specjalizowanych struktur danych z biblioteki EIGEN3
        ASD(x, fxSeidel, 2, WEZLY, file2);  // 4. WIELOMIAN 2-go stopnia dla metody Iteracyjnej Gaussa-Seidela
        
        
}
