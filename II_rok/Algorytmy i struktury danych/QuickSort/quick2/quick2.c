//Jakub Ronkiewicz, gr 4, QuickSort 
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#define C 10
#define MLD 1000000000.0 //10**9



void copyArray(int desc[], int src[], int length){
  int i;
  for(i=0;i<length;i++){
    desc[i] = src[i];
  }
}
void RandomTab(int tab[], int length){
  int los,i;
  for(i=0;i<length;i++){
    los = rand() % length;
    tab[i] = los;
  }
}

void DecreasingTab(int tab[], int length){
  int i;
  for(i=0; i<length;i++){
    tab[i]=length-i;
  }
}

void wyswietl(int tab[], int length){
  int i;
  for(i=0; i<length; i++){
    printf("%d, ", tab[i]);
  }
  printf("\n");
}

void swap(int tab[], int a, int b){
  int temp = tab[a];
  tab[a] = tab[b];
  tab[b] = temp;
}

int Partition(int A[], int p, int r) { // p-poczatek tablicy, r-koniec
  int x,i,j;
  x = A[r];
  i = p-1;
  for(j=p;j<=r;j++){
    if(A[j] <= x){
      i++;
      swap(A,i,j);
    }
  }
  if(i<r) return i;
  else return i-1;
}

void insertSort(int a[], int length)
{
    int i, j, value;

    for (i = 1; i < length; ++i) {
        value = a[i];
        for (j = i - 1; j >= 0 && a[j] > value; --j)
            a[j + 1] = a[j];
        a[j + 1] = value;
    }
}

void Quicksort(int A[], int p, int r) {
  int q;
  if(p<r){
    q=Partition(A,p,r);
    Quicksort(A,p,q);
    Quicksort(A,q+1,r);
  }
}

void Quicksort2(int A[], int p, int r) {
  if((r-p+1) < C) {
    insertSort(A, r+1);
  }
  int q;
  if(p<r){
    q=Partition(A,p,r);
    Quicksort(A,p,q);
    Quicksort(A,q+1,r);
  }
}

double test(int tab[],int length){
  struct timespec tp0, tp1;
  clock_gettime(CLOCK_PROCESS_CPUTIME_ID,&tp0);
  Quicksort(tab,0,length-1);
  clock_gettime(CLOCK_PROCESS_CPUTIME_ID,&tp1);
  return (tp1.tv_sec+tp1.tv_nsec/MLD)-(tp0.tv_sec+tp0.tv_nsec/MLD);
}

double test2(int tab[],int length){
  struct timespec tp0, tp1;
  clock_gettime(CLOCK_PROCESS_CPUTIME_ID,&tp0);
  Quicksort2(tab,0,length-1);
  clock_gettime(CLOCK_PROCESS_CPUTIME_ID,&tp1);
  return (tp1.tv_sec+tp1.tv_nsec/MLD)-(tp0.tv_sec+tp0.tv_nsec/MLD);
}

int main(){
  double Tn,Tn2;
  int zarodek = time(NULL);
  srand(zarodek);

  //losowe - parzysty numer tablicy
  //niekorzystne - nieparzysty numer tablicy
  int tab1[100],tab2[100],tab3[500];
  int tab4[500],tab5[1000], tab6[1000];
  int tab7[2500], tab8[2500];

  //tab1,tab2 oba wykonaja quicksorta poniewac C = 200
  RandomTab(tab1, 100);
  copyArray(tab2,tab1,100);
  RandomTab(tab3, 500);
  copyArray(tab4,tab3, 500);
  RandomTab(tab5,1000);
  copyArray(tab6,tab5,1000);
  RandomTab(tab7, 2500);
  copyArray(tab8,tab7,2500);

  // printf("Tab1 przed sortowaniem\n");
  // wyswietl(tab1,100);
  // printf("Tab2 przed sortowaniem\n");
  // wyswietl(tab2,100);
  // printf("DANE LOSOWE\n");
  // printf("%15s|%15s|%15s\n","rozmiar tablicy", "QuickSort", "InsertSort(N<3000)");

  Tn = test(tab1,100);
  Tn2 = test2(tab2, 100);
  printf("%15s|%15lf|%15lf\n", "100", Tn, Tn2);

  Tn = test(tab3,500);
  Tn2 = test2(tab4, 500);
  printf("%15s|%15lf|%15lf\n", "500", Tn, Tn2);

  Tn = test(tab5,1000);
  Tn2 = test2(tab6, 1000);
  printf("%15s|%15lf|%15lf\n", "1000", Tn, Tn2);

  Tn = test(tab7, 2500);
  Tn2 = test2(tab8, 2500);
  printf("%15s|%15lf|%15lf\n", "2500", Tn, Tn2);
  //
  // printf("Tab1 po sortowaniu\n");
  // wyswietl(tab1,100);
  // printf("Tab2 po sortowaniu\n");
  // wyswietl(tab2,100);

  return 0;
}
