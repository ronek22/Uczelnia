//Jakub Ronkiewicz, gr 4, HeapSort Rekurencyjnie
/*przed wykonaniem program nalezy utworzyc plik "unsorted.txt"
Liczby zapisane są w kolejnych wierszach pliku
*/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>


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

void Quicksort(int A[], int p, int r) {
  int q;
  if(p<r){
    q=Partition(A,p,r);
    Quicksort(A,p,q);
    Quicksort(A,q+1,r);
  }
}

int main(){
  int i, length=0;
  int *tab;
  FILE *plik;
  if((plik=fopen("unsorted.txt","r"))==NULL) {
		printf("Nie moge otworzyc pliku\n");
		exit(1);
	}

  while(fscanf(plik, "%d", &i)!=EOF) length++;
  rewind(plik);
  tab = (int*)malloc((length)*sizeof(int));

  for(i=0;i<length;i++)
    fscanf(plik, "%d", &tab[i]);

  fclose(plik);

  Quicksort(tab,0,length-1);

  FILE *zapis;
  if((zapis=fopen("sorted.txt","w"))==NULL) {
    printf("Nie moge otworzyc pliku\n");
    exit(1);
  }

  for(i=0;i<length;i++){
    fprintf(zapis, "%d\n", tab[i]);
  }
  free(tab);
  fclose(zapis);

  return 0;
}
