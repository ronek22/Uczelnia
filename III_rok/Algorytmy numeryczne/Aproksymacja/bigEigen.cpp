/**
 * Algorytmy Numeryczne - Zadanie 4
 * Aproksymacja - big eigen
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


int N = 112;  // N jest rozmiarem planszy, gdzie plansza sk³ada siê z N*2+1 pól (nie jest to sta³a, bêdziemy j¹ prawdopodobnie zwiêkszaæ dla kolejnych ekperymentów)
int size = N*2+1;
int s1 = -N;  // s1 jest polem startowym gracza nr1
int s2 = N;  // s2 jest polem startowym gracza nr2
int l = 5;  // 3 + 2 * (5%4) ; l oznacza liczbê œcian kostki ; œciany maj¹ wartoœci (-2; -1; 0; 1; 2)
int ile_rownan = (2*N)*(2*N)*2;
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

int main()
{
        cout << fixed << setprecision(16);
        IOFormat CommaInitFmt(17, DontAlignCols, " ", " ", "", "", "", "");

        ofstream file;
        file.open ("big.txt");
        file << "n,ile,lu\n";
        file << fixed << setprecision(16);


        printf("\n======   N = %d   ======\n", N);
        cout << ile_rownan << endl;
        file << N << "," << ile_rownan << ",";
        
        // GENEROWANIE PRAWDOPODOBIENSTW
        vector<double> rozklad(l, (1.0/l));
        vector< vector<P> > test = generateProbability(false);
        

        double elapsed;
        // ========= EIGEN ==============
        
        VectorXd vectorB(ile_rownan);
        VectorXd wynik(ile_rownan);
        for(int row = 0; row < ile_rownan; row++){
                vectorB(row) = 0;
                wynik(row) = 0;
        }
        
		int stan;
        vector<T> coefficients;    // list of non-zeros coefficients
        SpMat A(ile_rownan,ile_rownan);
        coefficients.reserve(ile_rownan * 6);
        for(int i = 0; i < ile_rownan; i++)
        {
        	//rows
        	for(int j = 0; j < l + 1; j++) {
                stan = test[i][j].status();
                if(i == test[i][j].wsp) { // jesli wspolczynnik taki sam wierszy to przekatna i 1
                        coefficients.push_back(T(i,test[i][j].wsp,1));
                } else if(stan == -1) {
                        coefficients.push_back(T(i,test[i][j].wsp,-rozklad[j-1]));
                } else if(stan == 1) {
                        vectorB(i) = rozklad[j-1];
                }
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
        StartCounter();
        wynik = solver.solve(vectorB);
        elapsed = GetCounter();
		printf("%-35s: x[0] = %f  Time: %f\n", "SparseLU()", wynik(0), elapsed);
        file << elapsed << endl;
        file.close();
}
