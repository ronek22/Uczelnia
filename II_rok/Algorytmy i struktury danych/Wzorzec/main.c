#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#define PLIK "wzorzec-tekst.txt"
#define MLD 1000000000.0

void zlicz_znaki(char* nazwa_pliku, int *patSize, int *tekSize);
void wczytaj_dane(char* nazwa_pliku, char P[], char T[]);
void Naiwny(char *P,char *T);
int* PrefixFunction(char *P);
void KMP(char *P, char *T);
void RK(char *P, char *T,int d, int q);



int main(){

        struct timespec tp0, tp1;
        int sizeP,sizeT,i;

        zlicz_znaki(PLIK,&sizeP,&sizeT);
        char P[sizeP],T[sizeT];
        wczytaj_dane(PLIK,P,T);


        // NAIWNY
        printf("NAIWNY: \n");
        clock_gettime(CLOCK_PROCESS_CPUTIME_ID,&tp0);
        Naiwny(P,T);
        clock_gettime(CLOCK_PROCESS_CPUTIME_ID,&tp1);
        printf("CZAS WYKONYWANIA: %lf\n\n",tp1.tv_sec+tp1.tv_nsec/MLD)-(tp0.tv_sec+tp0.tv_nsec/MLD);

        // KMP
        printf("KMP: \n");
        clock_gettime(CLOCK_PROCESS_CPUTIME_ID,&tp0);
        KMP(P,T);
        clock_gettime(CLOCK_PROCESS_CPUTIME_ID,&tp1);
        printf("CZAS WYKONYWANIA: %lf\n\n",tp1.tv_sec+tp1.tv_nsec/MLD)-(tp0.tv_sec+tp0.tv_nsec/MLD);

        // RK
        printf("RK: \n");
        clock_gettime(CLOCK_PROCESS_CPUTIME_ID,&tp0);
        RK(P,T,128,27077);
        clock_gettime(CLOCK_PROCESS_CPUTIME_ID,&tp1);
        printf("CZAS WYKONYWANIA: %lf\n\n",tp1.tv_sec+tp1.tv_nsec/MLD)-(tp0.tv_sec+tp0.tv_nsec/MLD);

        return 0;
}

void zlicz_znaki(char* nazwa_pliku, int *patSize, int *tekSize){
        int znak;
        char napis[1024];
        int ile = 0;
        FILE *plik = fopen(nazwa_pliku,"r");

        fscanf(plik,"%s",napis); //pierwsza linia wczytana
        fscanf(plik,"%s",napis); //wzorzec w napisie
        *patSize = strlen(napis);
        fscanf(plik,"%s",napis); //"tekst" w napisie

        /* zliczamy ile jest znaków w pliku, pomijając spacje */
        znak = getc(plik);
        ile++;
        while (znak != EOF) {
                if(znak == ' ' || znak == '\0' || znak == '\n') {
                        znak = getc(plik);
                } else {
                        znak = getc(plik);
                        ile++;
                }
        }
        ile--;
        fclose(plik);
        *tekSize=ile;
}
void wczytaj_dane(char* nazwa_pliku, char P[], char T[]){
        int i;
        char napis[1024];


        FILE *plik;
        if((plik=fopen(nazwa_pliku,"r"))==NULL) {
                printf("Nie moge otworzyc pliku\n");
                exit(1);
        }

        fscanf(plik,"%s",napis); //pierwsza linia wczytana
        fscanf(plik,"%s",napis); //wzorzec w napisie
        strcpy(P,napis); // wzorzec do tablicy
        fscanf(plik,"%s",napis); //"tekst" w napisie
        fscanf(plik,"%s",napis); // pierwsza linia tekstu w napisie
        strcpy(T,napis);

        while(fscanf(plik, "%s", napis)!=EOF) {
                strcat(T,napis);
        }



        // while(ile){
        //  if(znak == ' ' || znak == '\0' || znak == '\n'){
        //                       znak = getc(plik);
        //               } else {
        //                       tablica_znakow[pozycja] = znak;
        //    znak = getc(plik);
        //    ile--;
        //    pozycja++;
        //               }
        // }
        fclose(plik);
}
void Naiwny(char *P,char *T){
        int m = strlen(P);
        int n = strlen(T);
        int s,i;
        for(s = 0; s <= n - m; s++) {
                i = 0;
                while(i<m) if(P[i]==T[s+i]) i++; else break;
                if(i==m) printf("Wzorzec wystepuje od pozycji %d\n", s+1);
        }
}
int* PrefixFunction(char *P){
        int m = strlen(P);
        int i=1;
        int *pi = (int*) malloc(sizeof (int)*m);
        pi[0] = 0;
        int len = 0; // length
        while(i < m) {
                if(P[i] == P[len]) {
                        len++;
                        pi[i] = len;
                        i++;
                } else { // (P[i]!=P[len])
                        if(len!=0) {
                                len = pi[len-1];
                        } else {
                                pi[i] = 0;
                                i++;
                        }
                }
        }
        return pi;
}
void KMP(char *P, char *T){
        int m = strlen(P);
        int n = strlen(T);
        int *pi;
        pi = PrefixFunction(P);

        int i = 0; // indeks dla tekstu
        int j = 0; // indeks dla patternu
        while(i < n) {
                if(P[j] == T[i]) {
                        j++; i++;
                }

                if(j == m) { // jesli caly wzorzec znalazl sie w tekscie
                        printf("Wzorzec wystepuje od pozycji %d\n", i-j+1);
                        j = pi[j-1];
                } else if(i < n && P[j] != T[i]) {
                        if (j!=0)
                                j = pi[j-1];
                        else
                                i++;
                } // jesli jeszcze nie przeslismy calego tekstu
        }
        free(pi);
}
void RK(char *P, char *T,int d, int q){
        int m = strlen(P);
        int n = strlen(T);
        int i, j;
        int p = 0; // wartosc kodujaca dla wzorca
        int t = 0; // wartosc kodujaca dla tekstu
        int h = 1;

        for (i = 0; i < m-1; i++) h = (h*d)%q; // wyliczy h = (d do potęgi m-1) modulo q

        for (i = 0; i < m; i++) {
                p = (d*p + P[i])%q;
                t = (d*t + T[i])%q;
        }

        for (i = 0; i <= n - m; i++)
        {
                // Jeśli kodowania pasuje, sprawdzaj po kolei
                if ( p == t )
                {
                        // porownywanie m znakow w petli
                        for (j = 0; j < m; j++)
                        {
                                if (T[i+j] != P[j])
                                        break;
                        }

                        //przeszlo caly wzorzec, wiec znaleziono
                        if (j == m)
                                printf("Wzorzec wystepuje od pozycji %d\n", i+1);
                }

                // tekst sie skonczyl?
                if ( i < n-m )
                {
                        t = (d*(t - T[i]*h) + T[i+m])%q;

                        // mozemy dostac ujemny wynik, wtedy zamieniamy na dodatni
                        if (t < 0)
                                t = (t + q);
                }
        }

}
