/*
   Liczba badania kolizji
   w przypadku łancuchowej metody,
   ktora eliminiuje te kolizje, dzieki listom

   :::::Rozmiary tablic::::::::
   Korzys | Niekorzystne
   1873   | 1024
   3761   | 1536
   7607   | 2048
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define M 3761

int T[M];


int hash(char *s){
        int len = strlen(s);
        int i, result = 0;
        for(i = 0; i < len-1; i=i+2) {
                result ^= ((256*s[i])+s[i+1]);
        }
        if(s[i]!=0) {
                result ^= (256*s[i]);
        }
        return (int)(result % M);
}

void wczytaj(){
        int i, indeks;
        char napis[100];

        // zerowanie tablicy T
        for(i=0; i<M; i++) T[i]=0;

        FILE *plik;
        if((plik=fopen("3700.txt", "r"))==NULL) {
                printf("Nie moge otworzyc pliku\n");
                exit(1);
        }

        while(fscanf(plik, "%s", napis)!=EOF) {
                indeks = hash(napis);
                T[indeks]++;
        }

        fclose(plik);
}

void wypisz(){
        int i,zera=0,maks=0;
        float avg = 0;

        for(i=0; i<M; i++) {
                if(T[i]==0) {
                        zera++;
                } else if(T[i]>maks) {
                        maks = T[i];
                }

                avg+=T[i];
        }

        int bezZer=M-zera;
        printf("Zerowe pozycje: %d\nMaksymalna wartosc: %d\nSrednia wartosc: %.2lf\n",zera,maks,avg/bezZer);
}

int main(){
        wczytaj();
        wypisz();
        return 0;
}
