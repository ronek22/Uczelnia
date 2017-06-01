#include <stdio.h>
#include <stdlib.h>

int main(){
	int i,liczba,suma=0;
	FILE *plik;
	if((plik=fopen("in.txt", "r"))==NULL){
		printf("Nie moge otworzyc pliku\n");
		exit(1);
	}
	

	for(i=0; i<23; i++){
		fscanf(plik, "%d", &liczba);
		suma+=liczba;
	}
	printf("Suma = %d\n", suma);
	fclose(plik);
	return 0;
}
