/*hashowanie [S+OL]
   Operacje WSTAW i SZUKAJ.
   Pomiar: wypełnienie tablicy do 80% i wykonanie pewnej ilości
   operacji szukaj ze zliczaniem i wydrukiem ilości
   prób przy szukaniu klucza.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define M 10000 // wielkosc tab
#define A 0.8 // poziom wypelnienia tab
#define MAXD 44 // maks. dlugosc nazwiska

// struktura dane z iloscia i nazwiskiem (name)
typedef struct dane {
        char name[MAXD];
        int ilosc;
} dane;

dane T[M]; // tablica z hashowaniem
int iloscProb = 0;
int iloscSzuk = 0;

void zerowanie(){
        int i;
        for(i=0; i<M; i++) strcpy(T[i].name,"");
}

int hash(char *s, int x){
        int len = strlen(s);
        int i, result = 0;
        for(i = 0; i < len-1; i=i+2) {
                result ^= ((256*s[i])+s[i+1]);
        }
        if(s[i]!=0) {
                result ^= (256*s[i]);
        }
        return (int)((result + x) % M);
}

int HaszhInsert(dane T[], dane x){
        // wstawia element x do tablicy z haszowaniem t

        int j;
        int i = 0; // numer proby
        do {
                j = hash(x.name, i);
                if(j<0){
                  printf("Blad hashowania\nUjemna warosc dla wyrazu ''%s'\n\n", x.name);
                  return -1;
                }
                if(strcmp(T[j].name,"")==0) {
                        T[j] = x;
                        return j;
                }
                i++;
        } while(i<M);

        printf("Brak miejsca!\n");
        return -1;
}

int HaszhSearch(dane T[], char k[]){
  // szuka klucza k w tablicy z hashowaniem
  iloscSzuk++;
  int i = 0;
  int j;
  do{
    iloscProb++;
    j = hash(k,i);
    if(strcmp(T[j].name,k)==0){
      printf("Klucz '%s' znaleziony przy probie nr %d.\n",k,i+1);
      return j; // znaleziony klucz
    }
    i++;
  }while(strcmp(T[j].name,"")!=0 && i<M);
  printf("Klucz '%s' nieznaleziony! Podjeto %d prob\n",k, i+1);
  return -1;
}

int main(){
  int n=0; // ilosc napisow
  int p; // pomocnicza
  dane x;
  zerowanie();

  // otwieranie pliku
  FILE *plik;
  if((plik = fopen("nazwiskaA.txt", "r"))==NULL){
    printf("Nie moge otworzyc pliku\n");
    exit(1);
  }

  //wypelnienie tab do 80%
  while(n<M*A){
    fscanf(plik,"%d",&x.ilosc);
    fscanf(plik,"%s",x.name);
    p = HaszhInsert(T,x);
    //printf("Insert nr %d | %d %s: %d\n",n, x.ilosc,x.name,p);
    n++;

  }

  fclose(plik);

  // printf("Tablica:::WYDRUK\n");
  // for(i = 0; i<M; i++)
  //   printf("%d: %d %s\n",i,T[i].ilosc,T[i].name);

  HaszhSearch(T, "Adamczyk");
  HaszhSearch(T, "Nowak");
  HaszhSearch(T, "Kowalski");
  HaszhSearch(T, "Bobek");
  HaszhSearch(T, "Kubiczek");

  printf("\nIlosc szukan:%d, ilosc prob: %d\n", iloscSzuk, iloscProb);
  printf("wspolczynnik wypelnienia %3.2f\nwspolczynnik wyszukiwan: %3.2f\n",
  A,((float)iloscProb/iloscSzuk));

  return 0;
}
