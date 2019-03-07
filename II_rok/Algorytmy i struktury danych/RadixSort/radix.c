#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define ALFA 256 // mozliwe znaki char 0-255

void drukuj(char **A, int n, int j){
  int i;
  printf("\nPosortowane do pozycji: %d\n", j);
  for(i = 0; i<n; i++){
    printf("%c | %s\n",*(A[i]+j),A[i]);
  }
}

void czytaj(char **A, int ilosc, int *maks){
  char slowo[ALFA];
  int i, len;
  for(i=0;i<ilosc;i++){
    scanf("%s", slowo);
    len = strlen(slowo);
    if(len>*maks) *maks = len;
    A[i] = (char*) malloc(sizeof(char)*ALFA);
    strcpy(A[i], slowo);
  }
}

void counting_sort(char **A, char **B, int n, int h){
  // h - która, litera wyrazu, n - ilosc wyrazow
  int C[ALFA]; // pomocnicza tablica licznik znakow
  int i, j;

  for(i=0;i<ALFA; i++) C[i] = 0; // zerowanie tablicy licznikow

  for(j=0; j<n;j++){
    if((A[j][h] >= 65) && (A[j][h]<=90)){
      A[j][h] += 32; // to lower case
    }
    C[A[j][h]]++; // liczenie wystapien poszczegolnych liter
  }

  for(i=1;i<ALFA;i++) C[i] += C[i-1]; // sumowanie licznikow

  for(j=n-1; j>=0;j--){
    // umieszczanie w tablicy b od a-z;
    B[C[A[j][h]]-1] = A[j];
    C[A[j][h]]--;
  }
}

void radix_sort(char **A, int n, int d){
  // d - dlugosc stringow
  // n - ilosc wyrazow
  int i, j;
  char *B[n];

  for(i=d-1;i>=0;i--){
    counting_sort(A,B,n,i);

    for(j=0;j<n;j++) A[j] = B[j]; // porzadkowanie wyrazow po kazdej literze
    drukuj(A, n,i);
  }
}

int main (){
  int i,n,length=0;
  printf("Ile slow chcesz podac, maksymalnie 1000\n>> ");
  scanf("%d", &n);

  char **A = (char**) malloc(n*sizeof(char*));

  printf("Podaj wyrazy zatwierdzajac enterem\n");
  czytaj(A, n, &length);


  radix_sort(A,n,length);

  printf("Sortowanie ukonczone\n");
  for(i = 0; i<n; i++) printf("%s\n", A[i]);


  return 0;
}
