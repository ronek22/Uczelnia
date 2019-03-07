#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int heapSize;

void swap(int tab[], int a, int b){
  int temp = tab[a];
  tab[a] = tab[b];
  tab[b] = temp;
}

void Heapify(int A[], int i){
  int l,r,largest;
  l = 2*i;
  r = 2*i+1;
  if(l <= heapSize && A[l]>A[i]){
    largest = l;
  } else largest = i;

  if(r<=heapSize && A[r]>A[largest]){
    largest = r;
  }

  if(largest != i){
    swap(A,i,largest);
    Heapify(A, largest);
  }
}

void BuildHeap(int A[], int length){
  int i;
  heapSize = length;
  for(i = floor(heapSize/2); i>=1; i--){
    Heapify(A,i);
  }
}

void HeapSort(int A[], int length){
  int i;
  BuildHeap(A,length);
  for(i = length; i >= 2; i--){
    swap(A,i,1);
    heapSize--;
    Heapify(A,1);
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
  tab = (int*)malloc((length+1)*sizeof(int));

  for(i=1;i<=length;i++)
    fscanf(plik, "%d", &tab[i]);

  fclose(plik);

  HeapSort(tab,length);

  FILE *zapis;
  if((zapis=fopen("sorted.txt","w"))==NULL) {
    printf("Nie moge otworzyc pliku\n");
    exit(1);
  }

  for(i=1;i<=length;i++){
    fprintf(zapis, "%d\n", tab[i]);
  }
  free(tab);
  fclose(zapis);

  return 0;
}
