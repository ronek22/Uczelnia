#include <stdio.h>
#include <stdlib.h>

int main(){
	int i,liczby[20];
	FILE *odczyt, *zapis;
	if((odczyt=fopen("in.txt", "r"))==NULL){
		printf("Nie moge otworzyc pliku\n");
		exit(1);
	}
	
	zapis = fopen("out.txt", "w");
	
	for(i=0; i<20; i++){
		fscanf(odczyt, "%d", &liczby[i]);
		fprintf(zapis, "%d\n", liczby[i]);
	}
	fclose(odczyt);
	fclose(zapis);
	return 0;
}
