/*
Algorytmy Numeryczne - Zadanie 1
Funkcja sinus
Autor: Jakub Ronkiewicz, 238155
Informatyka: III rok sp. Tester programista gr. 1
*/

#include <stdio.h>
#include <math.h>
#include <stdlib.h>


 double power(double x, int y){
    double temp;
    if( y == 0)
       return 1;
    temp = power(x, y/2);
    if (y%2 == 0)
        return temp*temp;
    else{
        if(y > 0)
            return x*temp*temp;
        else
            return (temp*temp)/x;
        }
}

double blad_bezwzgledny(double x, double x_z){
    // x - wartosc dokladna, x_z - wartosc zmierzona
    double blad = fabs(x_z - x);
    return blad;
}

double blad_wzgledny(double x, double x_z){
    double blad = blad_bezwzgledny(x, x_z)/fabs(x);
    return blad;
}

// works correctly untill n < 21
unsigned long long factorial(int n){
    unsigned long long result = 1;
    for (int i = 2; i <= n; i++)
    {
        result *= i;
    }
    return result;
}

double deg2rad(double deg){
    double radian;
    radian = deg * (M_PI/180);
    return radian;
}

double mySin(double x, int n){
    // max n = 10, because 2*10+1 = 21, for that value factorial doesn't work
    double result = 0;
    double change = 0;
    for(int i = 0; i < n; i++){
        change = (1.0 /factorial(2*i+1))*power(x,2*i+1);
        if (i%2 != 0) change = -change;
        result += change;
    }
    return result;
}

double mySinReverse(double x, int n){
    // max n = 10, because 2*10+1 = 21, for that value factorial doesn't work
    double result = 0;
    double change = 0;
    for(int i = n - 1; i >= 0; i--){
        change = (1.0 /factorial(2*i+1))*power(x,(2*i+1));
        if (i%2 != 0) change = -change;
        result += change;
    }
    return result;
}



double mySinTerms(double x, int n){
    double term = x;
    double result = x;
    double x_sq = x * x;
    int i;
    for(i = 0; i < n-1; i++){
        term = term * (-x_sq/((2*i+2)*(2*i+3)));
        result += term;
    }
    return result;
}

// double mySinTermsRev(double x, int n){
//     // n max = 9, ilosc wyrazow 10
//     n--;
//     double result = power(x,(2*n+1))/factorial(2*n+1);
//     if ((n%2) != 0) result = -result;
//     printf("MYSIN: %d: %.10lf\n", n, result);
//     double term = result;
//     double x_sq = x*x;
//     int i;
//     for(i = n-1; i >= 0; --i){
//         term = term * ((2*i+2)*(2*i+3)/-x_sq);
//         printf("MYSIN: %d: %.10lf\n", i, term);
//         result += term;
//     }
//     return result;
// }

double mySinTermsRev(double x, int n){
    int el_id = 1;
    double elements[n];
    double term = x;
    elements[0] = x;
    double result = 0;
    double x_sq = x * x;
    int i;
    for(i = 0; i < n-1; i++){
        term = term * (-x_sq/((2*i+2)*(2*i+3)));
        elements[el_id++] = term;
    }

    for(i = n-1; i>=0; i--){
        result += elements[i];
    }
    return result;
}


void test(double x, double deg, FILE *results, FILE *errors_bb, FILE *errors_bw,  int n){
    int i;
    // RESULTS
    double sin_lib = sin(x);
    double sin_szereg = mySin(x, n);
    double sin_szereg_rev = mySinReverse(x, n);
    double sin_term = mySinTerms(x, n);
    double sin_term_rev = mySinTermsRev(x, n);
    printf("%.20lf\n%.20lf\n%.20lf\n%.20lf\n%.20lf\n",sin_lib, sin_szereg, sin_szereg_rev, sin_term, sin_term_rev);


    // ERRORS
    // bb - blad bezwzgledny, bw - blad wzgledny
    double bb_sin_szereg = blad_bezwzgledny(sin_lib, sin_szereg);
    double bb_sin_szereg_rev = blad_bezwzgledny(sin_lib, sin_szereg_rev);
    double bb_sin_term = blad_bezwzgledny(sin_lib, sin_term);
    double bb_sin_term_rev = blad_bezwzgledny(sin_lib, sin_term_rev);

    double bw_sin_szereg = bb_sin_szereg/fabs(sin_lib);
    double bw_sin_szereg_rev = bb_sin_szereg_rev/fabs(sin_lib);
    double bw_sin_term = bb_sin_term/fabs(sin_lib);
    double bw_sin_term_rev = bb_sin_term_rev/fabs(sin_lib);


    printf("%32s %e\n","Blad bezwzgledny mySin:", bb_sin_szereg);
    printf("%32s %e\n","Blad bezwzgledny mySinReverse:", bb_sin_szereg_rev);
    printf("%32s %e\n","Blad bezwzgledny mySinTerms:", bb_sin_term);
    printf("%32s %e\n","Blad bezwzgledny mySinTermsRev:", bb_sin_term_rev);


    printf("%32s %e\n","Blad wzgledny mySin:", bw_sin_szereg);
    printf("%32s %e\n","Blad wzgledny mySinReverse:", bw_sin_szereg_rev);
    printf("%32s %e\n","Blad wzgledny mySinTerms:", bw_sin_term);
    printf("%32s %e\n","Blad wzgledny mySinTermsRev:", bw_sin_term_rev);

    printf("--------------------------------\n");

    // DO PLIKU
    fprintf(results, "%.2lf,%.20lf,%.20lf,%.20lf,%.20lf,%.20lf\n",deg, sin_lib, sin_szereg, sin_szereg_rev, sin_term,sin_term_rev);
    fprintf(errors_bb, "%.2lf,%.20lf,%.20lf,%.20lf,%.20lf\n",deg, bb_sin_szereg, bb_sin_szereg_rev, bb_sin_term, bb_sin_term_rev);
    fprintf(errors_bw, "%.2lf,%.20lf,%.20lf,%.20lf,%.20lf\n",deg, bw_sin_szereg, bw_sin_szereg_rev, bw_sin_term, bw_sin_term_rev);
}


int main(){
    FILE *results;
    FILE *errors_bb;
    FILE *errors_bw;
    errors_bb = fopen("bledy_bezwzgledne.csv", "w");
    errors_bw = fopen("bledy_wzgledne.csv", "w");
    results = fopen("wyniki.csv", "w");

    double i;
    double rad;

    fprintf(results, "%s,%s,%s,%s,%s,%s\n","x", "sin", "mysin", "mysinrev", "mysinterms", "mysintermsrev");
    fprintf(errors_bb, "%s,%s,%s,%s,%s\n", "x","mysin", "mysinrev", "mysinterms", "mysintermsrev");
    fprintf(errors_bw, "%s,%s,%s,%s,%s\n", "x","mysin", "mysinrev", "mysinterms","mysintermsrev");


    for(i = 1.0; i<180; i += 1){
        printf("STOPIEN: %.2lf\n", i);
        rad = deg2rad(i);
        test(rad, i, results, errors_bb, errors_bw, 10);
    }

    fclose(results);
    fclose(errors_bb);
    fclose(errors_bw);

    return 0;
}
