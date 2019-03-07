/**
 * Algorytmy Numeryczne - Zadanie 3
 * Grzybobranie
 * Autorzy: Jakub Ronkiewicz, Seweryn Rutkowski
 * Informatyka: III rok sp. Tester programista gr. 1
 *
 * Kompilowac za pomoca polecenia:
 * g++ -I sciezka_do_eigena main.cpp -std=c++11 -03
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
 
 typedef SparseMatrix<double> SpMat; // declares a column-major sparse matrix type of double
 typedef Triplet<double> T;
  
  
 int N = 5; // N jest rozmiarem planszy, gdzie plansza składa się z N*2+1 pól (nie jest to stała, będziemy ją prawdopodobnie zwiększać dla kolejnych ekperymentów)
 int size = N*2+1 ;
 int k = 8; // 3 + 5%6 ; k to liczba grzybów na planszy
 int s1 = -N; // s1 jest polem startowym gracza nr1
 int s2 = N; // s2 jest polem startowym gracza nr2
 int l = 5; // 3 + 2 * (5%4) ; l oznacza liczbę ścian kostki ; ściany mają wartości (-2; -1; 0; 1; 2)
 int ile_rownan = (2*N)*(2*N)*2;
 int MonteTEST = 100;
 double epsilon = 0.00000001;
 int maxIter = 10000;
 int MAX_MX = 100000; // maksymalny rozmiar macierzy
 double WYNIK;
 //typy kostek:
 // - równomierna, gdzie rozkład prawdopodobieństw jest równomierny i wynosi (1/5; 1/5; 1/5; 1/5; 1/5)   // - dowolna, gdzie rozkład prawdopodobieństw jest dowolny i wynosi np. (1/10; 2/10; 3/10; 3/10; 1/10)
  
  //MIERZENIE CZASU
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
  
 void print(vector< vector<double> > A, vector<double> B) {
     int n = A.size();
     for (int i=0; i<n; i++) {
         for (int j=0; j<n; j++) {
             cout << A[i][j] << "\t";
         }
         cout << "| " << B[i] << "\n";      
     }
     cout << endl;
 }
 
 void printFile(vector< vector<double> > A, vector<double> B){
     ofstream myfile;
     myfile.open ("matrix.txt");
 
     int n = A.size();
     for (int i=0; i<n; i++) {
         for (int j=0; j<n; j++) {
             myfile << A[i][j] << "\t";
         }
         myfile << "| " << B[i] << "\n";      
     }
     myfile << endl;
     
     myfile.close();
 }
  
 void printSparseMatrix(vector<double> mtx_val, vector<int> mtx_col, vector<int> mtx_nzl)
 {
     cout<<"Wartości: ";
      for(int i = 0; i<mtx_val.size(); i++)
      {
          cout<<mtx_val[i]<<" ";
     }
     cout<<endl<<"Kolumny: ";
      for(int i = 0; i<mtx_col.size(); i++)
      {
          cout<<mtx_col[i]<<" ";
     }
     cout<<endl<<"Niezerowe w wierszu: ";
      for(int i = 0; i<mtx_nzl.size(); i++)
      {
          cout<<mtx_nzl[i]<<" ";
     }
     cout<<endl;
 } 
  
 void fillMatrix(int n, vector< vector<double> > &a, vector<double> &b){
     int i, j;
     cout<<"\nEnter the right hand side constants : \n";
     for(i=0;i<n;i++) {
         cin>>b[i];
     }
                    
     cout<<"\nEnter the coefficients row wise : \n";
     for(i=0;i<n;i++) {
         for(j=0;j<n;j++) {
             cin>>a[i][j];
         }
     }
 }
  
  //Tworzenie macierzy rzadkiej
 void createSparseMatrix(int n, vector<vector<double> > a, vector<double> b, vector<double> &mtx_val, vector<int> &mtx_col, vector<int> &mtx_nzl)
 {
     for(int i = 0; i<n; i++)
     {
         int howManyInRow = 0;
         for(int j = 0; j < n+1; j++)
         {
             if(a[i][j] != 0)
             {
                 mtx_val.push_back(a[i][j]);
                 mtx_col.push_back(j);	
                 howManyInRow++;			
             }
         }
         if(b[i] != 0)
         {
             mtx_val.push_back(b[i]);
             mtx_col.push_back(n);	
             howManyInRow++;	
         }
         mtx_nzl.push_back(howManyInRow);		
     }
 } 
  
 void GaussPartial(int n, vector<double> x, vector< vector<double> > a, vector<double> b){
     printf("\n%-35s", "GAUSS PARTIAL");
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
 
     WYNIK = x[0];
 
     cout << ": x[0] = " << WYNIK;
 
 }
  
 void GaussPartialSparseMatrix(int n, vector<double> x, vector< vector<double> > a, vector<double> b){
     printf("\n%-35s", "GAUSS PARTIAL FOR SPARSE MATRIX");	
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
             // i wiersz
             // sprawdzenie czy element zerowy jesli tak przejscie do nastepnego wiersza
             if (a[i][p] == 0) continue;
             
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
  
     WYNIK = x[0];
     
     cout << ": x[0] = " << WYNIK;
 
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
                for(int j = 0;j <= i - 1; j++)
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
        cout << ": x[0] = " << WYNIK;
 }
 
 
 void jacobiMethod(int n, vector<double> x, vector< vector<double> > A, vector<double> b)
 {
    printf("\n%-35s", "JACOBI METHOD");
 
       
    vector<double> prevX(n, 0);  
    double rowSum = 0;  
    double subSum = 0;
    int iterations;
    for(iterations = 1; iterations < maxIter; iterations++) //kolejne iteracje
    {
        for(int i = 0; i < n; i++) //kolejne wiersze
        {
            for(int i = 0; i < n; i++)
                prevX[i] = x[i];
            rowSum = 0;
            subSum = 0;
           
            for(int j = 0; j < n; j++)
            {
                if(j!=i)
                {
                    subSum = subSum + (A[i][j] * x[j]);
                }
            }
            rowSum = (b[i] - subSum) / A[i][i];
            x[i] = rowSum;
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
    cout << ": x[0] = " << WYNIK;
 }
  
 double fRand(double fMin, double fMax)
 {
     double f = (double)rand() / RAND_MAX;
     return fMin + f * (fMax - fMin);
 }
  
 int fRand(int max)
 {
    
     int range = max*2;
     int number = rand()%range - max;
     return number;
 }
  
 void fillMushroomArrayWithRandomPositions(int *mushroomsPositions)
 {
     cout<<"Ustalam pozycje grzybow \n";  
     srand( time( NULL ) );
        int arrayPosition = 0;
        bool allMushroomsPlaced = false;
        bool noRedundanceFound = true;
        int iteracje = 0;
        do
        {      
            iteracje++;
            int random = fRand(N);
            noRedundanceFound = true;
            for(int i = 0; i <= arrayPosition; i++)
            {
                if (random == mushroomsPositions[i])
                {
                    noRedundanceFound = false; 
                    i = arrayPosition + 1;     
                }                                  
            }
            if(noRedundanceFound)
            {
           mushroomsPositions[arrayPosition] = random;
                arrayPosition++;
                if(arrayPosition >= k)
                    allMushroomsPlaced = true;
         }              
        } while(!allMushroomsPlaced);
     cout<<"Iteracje: \n"<<iteracje<< "\n";   
 }
  
  void createArrayOfProbs(vector<int> &array) //teraz kostka ma rozkład 15/100, 30/100, 10/100, 30/100, 15/100
 {
     for(int i = 0; i < 15; i++)
     {
         array[i] = -2;
     }
     for(int i = 15; i < 45; i++)
     {
         array[i] = -1;
     }
     for(int i = 45; i < 55; i++)
     {
         array[i] = 0;
     }
     for(int i = 55; i < 85; i++)
     {
         array[i] = 1;
     }
     for(int i = 85; i < 100; i++)
     {
         array[i] = 2;
     }
 }
  
  double monteCarloTest(map<int, bool> mushrooms, bool isEvenProbability)
  {
     int wins = 0;
     int tests = 100000; //liczba testow Monte Carlo
     vector<int> diceArray(100,0);  
     if(isEvenProbability) //kostka rownomierna
     {
         diceArray = {-2, -1, 0, 1, 2};
     }
     else //kostka nierownomierna
     {
         createArrayOfProbs(diceArray);
     }
     int diceMod = diceArray.size();
     int dice;
     for(int i = 0; i < tests; i++)
     {
         map<int,bool> gameFields = mushrooms;
         int pos1 = s1;
         int mushrooms1 = 0; //liczba grzybow zebranych przez gracza 1
         int pos2 = s2;
         int mushrooms2 = 0;
         int player = 1;
         int finishedFirst = 0; //oznacza kto doszedl jako pierwszy na mete (1 - gracz 1, 2 - gracz 2)
    
         while(pos1 != 0 && pos2 != 0)
         {  
             int index = rand()%diceMod; //rzut koscia
             dice = diceArray[index];
             int corrector = 0; //korektor pól, aby nie wyjść poza planszee
             if(player == 1) //ruch gracza 1
             {
                 pos1 += dice;
                 if(pos1 > s2)
                 {
                     corrector = pos1 - s2;
                     pos1 = s1 + corrector-1;
                 }
                 if(pos1 < s1)
                 {
                     corrector = -pos1 + s1;
                     pos1 = s2 - corrector + 1;
                 }
                 if (gameFields[pos1] == true)
                 {
                     mushrooms1++;
                     gameFields[pos1] = false;
                 }
                 if(finishedFirst == 0 && pos1 == 0)
                     finishedFirst = 1;
             }
             else //ruch gracza 2
             {
                 pos2 -= dice;  
                 if(pos2 > s2)
                 {
                     corrector = pos2 - s2;
                     pos2 = s1 + corrector-1;
                 }
                 if(pos2 < s1)
                 {
                     corrector = -pos2 + s1;
                     pos2 = s2 - corrector + 1;
                 }
                 if (gameFields[pos2] == true)
                 {
                     mushrooms2++;
                     gameFields[pos2] = false;
                 }
                 if(finishedFirst == 0 && pos2 == 0)
                     finishedFirst = 2;
             }
             player = (player % 2) + 1;     
         }
        
         if(mushrooms1 > mushrooms2)
         {          
             wins++;
         }
         else if(mushrooms2 > mushrooms1){
             // cout << mushrooms1 << " : " << mushrooms2 << "\tLose\n";
             
         }
         else
         {
             if(finishedFirst == 1)
             {
                 wins++;
                 // cout << "won by finished first: wins = " << wins << endl;
             }
             else
             {
                 // cout << "lost by finished last: wins = " << wins << endl;
             }
         }
     }
     double score = (double)wins/(double)tests;
     // cout << endl << "Prawdopodobienstwo Monte Carlo: "<< score << endl;
     return score;
  }
 
  // functions & structures for generating probability matrix
  struct P{
     int player, x, y, wsp, g1, g2;
     map<int, bool> mushrooms;
 
     P(){};
 
     P(int p, int x_, int y_, int wsp_, int g_1, int g_2, map<int,bool> gameField){
         player = p;
         x = x_;
         y = y_;
         wsp = wsp_;
 
         mushrooms = gameField;
         g1 = g_1;
         g2 = g_2;
     }
 
     void print(){
         string result;
 
         result = "P" + to_string(player) + "(" + to_string(x) + ", " + to_string(y) + ")" + "[" + to_string(g1) + "," + to_string(g2) + "]" + "{";
         for(int i = s1; i<= s2; i++){
             if(mushrooms[i])
                 result += to_string(i) + " ";
         }
         result += "}";
         result += "^" + to_string(wsp);
         
         cout << setw(40) << left << result;
     }
     
 
     string toString(){
         string result;
 
         result = to_string(player) + to_string(x) + to_string(y);
         for(int i = s1; i<= s2; i++){
             if(mushrooms[i])
                 result += to_string(i);
         }
         return result;
     }
 
     int status(){
         if(x == 0){
             if(g1 > g2){
                 return 1; // 1 wygral
             } else if(g1 < g2){
                 return 0; // 2 wygral
             } else {
                 return 1; // takie same 1 wygral
             }
         } 
         else if(y == 0){
             if(g1 > g2){
                 return 1; // 1 wygral
             } else if(g1 < g2){
                 return 0; // 2 wygral
             } else {
                 return 0; // takie same 2 wygral
             }
         }
         else{
             return -1; // gra toczy sie dalej
         }
     }
 };
 
 
  void fillPlansza(vector<int> &p, int n){
     int number = -n;
     for(int i = 0; i < 2*n+1; i++){
         p[i] = number++;
     }
 }
 
 int mod(int a, int b) { return (a % b + b) % b; }
 
 int indexOf(vector<int> p, int n){
     for(int i = 0; i < p.size(); i++){
         if(p[i]==n) return i;
     }
     return -1;
 }
 
 vector< vector<P> > generateProbability(map<int,bool> grzyby, bool wyswietlaj){
 
     bool found;
     int n = N;
     int w = size; 
 
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
     vector< vector<P> > test(MAX_MX, line);
     // wartosci poczatkowe
     int x = -n, y = n, player = 1, wsp=0;
 
 
 
     test[0][0] = P(player, x, y, wsp, 0, 0, grzyby); 
     result = repMap.insert(pair<string, int>(test[0][0].toString(), wsp++));
     repetition.insert(test[0][0].toString());
     x = indexOf(plansza, x);
     y = indexOf(plansza, y);
     map<int, bool> tmpGrzyby;
     player = player%2 + 1;    
 
     for(int i = 1; i < l+1; i++){
         tmpGrzyby = grzyby;
         int tmpX = x, tmpY = y;
         int tmpG1 = 0, tmpG2 = 0;       
 
         // ustawianie odpowiednich parametrow dla dodawanego gracza
         if(player == 2){
             // teraz wykonuje ruch gracz pierwszy, tylko wypisywane sa prawdopodobienstwa dla gracza 2
             tmpX += kostka[i-1];
             tmpX = plansza[mod(tmpX, w)]; // teraz juz mamy odpowiednie pole, a nie indeks pola
             if(tmpGrzyby[tmpX]){ // ustalismy na grzyba
                 tmpG1++;
                 tmpGrzyby[tmpX] = false; // zdejmuje grzyba z planszy dla tej drogi
             }
             // y jest indeksem zamiana na pole
             tmpY = plansza[mod(tmpY, w)];
 
         } else{
             // ruch gracza drugiego
             tmpY += kostka[i-1];
             tmpY = plansza[mod(tmpY, w)]; // teraz juz mamy odpowiednie pole, a nie indeks pola
             if(tmpGrzyby[tmpY]){ // ustalismy na grzyba
                 tmpG2++;
                 tmpGrzyby[tmpY] = false; // zdejmuje grzyba z planszy dla tej drogi
             }
             // x jest indeksem zamiana na pole
             tmpX = plansza[mod(tmpX, w)];
         }
         // dodanie prawdopodobienstwa do rownania
         test[0][i] = P(player, tmpX, tmpY, wsp, tmpG1, tmpG2, tmpGrzyby);
         
         // sprawdzenie czy dodarlismy na mete jesli tak, ustawiamy wspolczynnik na -1, aby wiedziec ze nie rozpisujemy juz tego dalej
         if(tmpX == 0 || tmpY == 0){
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
     int g1, g2;
 
     for(i = 1; i < MAX_MX ; i++){
         // PRZYGOWANIE OBLICZANEGO PRAWDOPODOBIENSTWA ^[P1(x,y)] = P2(x_, y_) + P2(x__, y__) + ...
         // zczytanie wartosci z obliczanego rownania
         x = test[r][c].x;
         y = test[r][c].y;
         player = test[r][c].player;
         tmp_wsp = test[r][c].wsp;
         g1 = test[r][c].g1;
         g2 = test[r][c].g2;
         tmpGrzyby = test[r][c].mushrooms;
         
 
         if(r == i) break;      
         // dzieki temu uzyskujemy wszyskie prawdopodobienstwa nie omijemy zadnego
         c = c%l + 1;
         if (c == 1) r++;
 
 
         // proba wstawienia nowego rownania
         test[i][0] = P(player, x, y, tmp_wsp, g1, g2, tmpGrzyby);
         found = repetition.count(test[i][0].toString()); // sprawdzenie czy juz nie liczylismy tego rownania
 
         if(found == 1 || (test[i][0].x == 0 || test[i][0].y == 0)){
             // albo liczylismy juz te rownanie, albo jest to wygrana lub przegrana i nie ma co liczyc
             i--;
             continue;
         } else {
             repetition.insert(test[i][0].toString());
         }    
     
         x = indexOf(plansza, x);
         y = indexOf(plansza, y);
         player = player%2 + 1;   
 
         for(int j = 1; j < l+1; j++){
             int tmpX = x, tmpY = y;
             int tmpG1 = g1, tmpG2 = g2;
             map<int,bool> newGrzyby = tmpGrzyby; 
             // ustawianie odpowiednich parametrow dla dodawanego gracza
             if(player == 2){
                 // teraz wykonuje ruch gracz pierwszy, tylko wypisywane sa prawdopodobienstwa dla gracza 2
                 tmpX += kostka[j-1];
                 tmpX = plansza[mod(tmpX, w)]; // teraz juz mamy odpowiednie pole, a nie indeks pola
                 if(newGrzyby[tmpX]){ // ustalismy na grzyba
                     tmpG1++;
                     newGrzyby[tmpX] = false; // zdejmuje grzyba z planszy dla tej drogi
                 }
                 // y jest indeksem zamiana na pole
                 tmpY = plansza[mod(tmpY, w)];
 
             } else{
                 // ruch gracza drugiego
                 tmpY += kostka[j-1];
                 tmpY = plansza[mod(tmpY, w)]; // teraz juz mamy odpowiednie pole, a nie indeks pola
                 if(newGrzyby[tmpY]){ // ustalismy na grzyba
                     tmpG2++;
                     newGrzyby[tmpY] = false; // zdejmuje grzyba z planszy dla tej drogi
                 }
                 // x jest indeksem zamiana na pole
                 tmpX = plansza[mod(tmpX, w)];
             }
                 
  
             // wstawiony player
             test[i][j] = P(player, tmpX, tmpY, wsp, tmpG1, tmpG2, newGrzyby);
             
             // sprawdzenie czy dodarlismy na mete jesli tak, ustawiamy wspolczynnik na -1, aby wiedziec ze nie rozpisujemy juz tego dalej
             if(tmpX == 0 || tmpY == 0){
                 test[i][j].wsp = -1;
                 continue;
             }
 
             result = repMap.insert(pair<string, int>(test[i][j].toString(), test[i][j].wsp));
             if(result.second == 0){
                 // trafilismy juz na te prawdopodobienstwo kopiujemy wspolczynnik
                 it = repMap.find(test[i][j].toString());
                 test[i][j].wsp = it->second;
                 continue;
             }
             wsp++;
         }
     }
 
     ile_rownan = i;
     cout << "ILOSC ROWNAN: " << ile_rownan << endl;
 
 //     Wygenerowane
     if(wyswietlaj){
         for(int i = 0; i < ile_rownan; i++){
             cout << i+1 << ": "; 
             for(int j = 0; j < l+1; j++){
                 if( j!= 0 && j!= 1 ) cout << setw(5) << left <<  " + ";
                 test[i][j].print();
                 if(j == 0) cout << setw(5) << left << " = ";
             }
             // getch();
             cout << endl;
         }
     }
 
 
     return test;
  }
 
  void convertToMatrix(vector< vector<P> > test, vector< vector<double> > &matrix, vector<double> &b, vector<double> rozklad){
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
 
  
  
 int main()
 {  
     cout << fixed << setprecision(16);
     IOFormat CommaInitFmt(17, DontAlignCols, " ", " ", "", "", "", "");
     
     ofstream file;
     file.open ("wyniki.csv");
     file << "n,mcr,mcn,gpr,gprt,gpsr,gpsrt,jr,jrt,gsr,gsrt,epr,eprt,esr,esrt,gpn,gpnt,gpsn,gpsnt,jn,jnt,gsn,gsnt,epn,epnt,esn,esnt\n";
     file << fixed << setprecision(16);	
     
     for(N; N < 8; N++){
         printf("\n======   N = %d   ======\n", N);
         file << N << ",";
         // aktualizacja zmiennych globalnych zaleznych od N
         size = N*2+1; s1 = -N; s2 = N;
         
         
         //Grzybobranie-------------------------------------  
         //Ustalanie pozycji grzybów
         int mushrCount; 	
         if(k>=size) //jesli grzybow jest wiecej lub rowno niz pól na planszy to kazde pole ma po 1 grzybie
                mushrCount = size;		   	
         else
             mushrCount = k;
             
         int mushroomsPositions[mushrCount]; //tablica pozycji rozmieszczenia grzybów (trzeba wylosować te pozycje z rozkładem równomiernym, czyli 1/(size)) ; 1 grzyb na 1 pozycję!!!
        
         if(mushrCount != k)
         {
             int place = s1;
             for(int i = 0; i < size; i++)
             {
                 mushroomsPositions[i] = place;
                 place++;
             }
         }
         else
         {
             //wypelnianie tablicy pozycji niemozliwymi pozycjami w celu dalszego jej wypelnienia juz prawdziwymi pozycjami losowymi
             for(int i = 0; i < k; i++)
                 mushroomsPositions[i] = N+1;
            
             //losowanie pozycji grzybow
             fillMushroomArrayWithRandomPositions(mushroomsPositions);
         }
         cout<<"Wylosowane pozycje: \n";
         for(int i = 0; i < mushrCount; i++)
             cout<<mushroomsPositions[i]<<" ";
         
         map<int, bool> gameFields; //zamienimy tablice na mape pol, true jesli grzyb
         for(int i = s1; i<=s2; i++)
         {
             gameFields[i] = false;
         }
         for(int i = 0; i < mushrCount; i++)
         {
             gameFields[mushroomsPositions[i]] = true;
         }
         // KONIEC GRZYBOBRANIA
     
     
         // MONTE CARLO
         double MonteWynik = 0;
        //Metoda Monte Carlo:
         for(int i = 0; i < MonteTEST; i++){
             MonteWynik += monteCarloTest(gameFields, true);   //rowny rozklad na kostce
         }
     
         MonteWynik /= MonteTEST;
         cout << endl << "\nPrawdopodobienstwo Monte Carlo: "<< MonteWynik;
         file << MonteWynik << ",";
         
         MonteWynik = 0;
         for(int i = 0; i < MonteTEST; i++){
             MonteWynik += monteCarloTest(gameFields, false);   //nierowny rozklad na kostce
         }
     
         MonteWynik /= MonteTEST;
         cout << endl << "Prawdopodobienstwo z nierownym rozkladem Monte Carlo: "<< MonteWynik << endl;
         file << MonteWynik << ",";
         
         // KONIEC MONTE CARLO
     
         // GENEROWANIE PRAWDOPODOBIENSTW
         // prawdopodobienstwa kostki
         vector<double> rozklad_rowny(l, (1.0/l));
         vector<double> rozklad = {15.0/100, 30.0/100, 10.0/100, 30.0/100, 15.0/100};
         vector< vector<P> > test = generateProbability(gameFields, false);
         
         //ROZKLAD ROWNY
         cout << "\nROZKLAD ROWNY";
         
         { // scope for equal side
             vector<double> genB(ile_rownan, 0);
             vector<double> line(ile_rownan, 0);
             vector< vector<double> > genA(ile_rownan, line);
             vector<double> genX(ile_rownan, 0);
 
             convertToMatrix(test, genA, genB, rozklad_rowny);
 
             // WYNIKI W ZMIENNEJ GLOBALNEJ WYNIK
             double elapsed;
             StartCounter();
             GaussPartial(ile_rownan, genX, genA, genB);
             elapsed = GetCounter();
             file << WYNIK << "," << elapsed << ",";
             cout << "  Time: " << elapsed;
 
 
             StartCounter();
             GaussPartialSparseMatrix(ile_rownan, genX, genA, genB);
             elapsed = GetCounter();
             file << WYNIK << "," << elapsed << ",";
             cout << "  Time: " << elapsed;
 
 
             StartCounter();
             jacobiMethod(ile_rownan, genX, genA, genB);
             elapsed = GetCounter();
             file << WYNIK << "," << elapsed << ",";
             cout << "  Time: " << elapsed;
 
             StartCounter();
             gaussSeidelMethod(ile_rownan, genX, genA, genB);
             elapsed = GetCounter();
             file << WYNIK << "," << elapsed << ",";
             cout << "  Time: " << elapsed << endl;
 
             //EIGEN
 
             MatrixXd matrixA(ile_rownan, ile_rownan);
             VectorXd vectorB(ile_rownan);
             VectorXd wynik(ile_rownan);
             for (int row = 0; row < ile_rownan; row++) { //zamiana wygenerowanych macierzy na macierze eigenowskie
                     for (int col = 0; col < ile_rownan; col++) {
                             matrixA(row, col) = genA[row][col]; // do eigena
                     }
                     vectorB(row) = genB[row];
                     wynik(row) = 0;
             }
 
             StartCounter();
             wynik = matrixA.partialPivLu().solve(vectorB);
             elapsed = GetCounter();
             printf("%-35s: x[0] = %f  Time: %f\n", "PartialPivLu()", wynik(0), elapsed);
             file << wynik.head(1) << "," << elapsed << ",";
 
 
 
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
             StartCounter();
             wynik = solver.solve(vectorB);
             elapsed = GetCounter();
             printf("%-35s: x[0] = %f  Time: %f\n", "SparseLU()", wynik(0), elapsed);
             file << wynik.head(1) << "," << elapsed << ",";
 
         }
         
         //ROZKLAD NIEROWNY
         cout << "\nROZKLAD NIEROWNY";
         
         { // scope for equal side
             vector<double> genB(ile_rownan, 0);
             vector<double> line(ile_rownan, 0);
             vector< vector<double> > genA(ile_rownan, line);
             vector<double> genX(ile_rownan, 0);
 
             convertToMatrix(test, genA, genB, rozklad);
 
             // WYNIKI W ZMIENNEJ GLOBALNEJ WYNIK
             double elapsed;
             StartCounter();
             GaussPartial(ile_rownan, genX, genA, genB);
             elapsed = GetCounter();
             file << WYNIK << "," << elapsed << ",";
             cout << "  Time: " << elapsed;
 
 
             StartCounter();
             GaussPartialSparseMatrix(ile_rownan, genX, genA, genB);
             elapsed = GetCounter();
             file << WYNIK << "," << elapsed << ",";
             cout << "  Time: " << elapsed;
 
 
             StartCounter();
             jacobiMethod(ile_rownan, genX, genA, genB);
             elapsed = GetCounter();
             file << WYNIK << "," << elapsed << ",";
             cout << "  Time: " << elapsed;
 
             StartCounter();
             gaussSeidelMethod(ile_rownan, genX, genA, genB);
             elapsed = GetCounter();
             file << WYNIK << "," << elapsed << ",";
             cout << "  Time: " << elapsed << endl;
 
             //EIGEN
 
             MatrixXd matrixA(ile_rownan, ile_rownan);
             VectorXd vectorB(ile_rownan);
             VectorXd wynik(ile_rownan);
             for (int row = 0; row < ile_rownan; row++) { //zamiana wygenerowanych macierzy na macierze eigenowskie
                     for (int col = 0; col < ile_rownan; col++) {
                             matrixA(row, col) = genA[row][col]; // do eigena
                     }
                     vectorB(row) = genB[row];
                     wynik(row) = 0;
             }
 
             StartCounter();
             wynik = matrixA.partialPivLu().solve(vectorB);
             elapsed = GetCounter();
             printf("%-35s: x[0] = %f  Time: %f\n", "PartialPivLu()", wynik(0), elapsed);
             file << wynik.head(1) << "," << elapsed << ",";
 
 
 
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
             StartCounter();
             wynik = solver.solve(vectorB);
             elapsed = GetCounter();
             printf("%-35s: x[0] = %f  Time: %f\n", "SparseLU()", wynik(0), elapsed);
             file << wynik.head(1) << "," << elapsed << ",";
 
         }
     }
     file.close();
     
 }