#include <stdio.h>
#include <stdlib.h>

int main(){
	int i,liczby[20];
	FILE *plik;
	if((plik=fopen("in.txt", "r"))==NULL){
		printf("Nie moge otworzyc pliku\n");
		exit(1);
	}
	

	for(i=0; i<20; i++){
		fscanf(plik, "%d", &liczby[i]);
		printf("%d => %d\n", i, liczby[i]);
	}
	fclose(plik);
	return 0;
}
