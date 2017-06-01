#include <stdio.h>
#include <stdlib.h>

int main(){
	int j, licznik=0, ind=1;
	double u,i,r; //napiecie, natezenie, opor
	FILE *odczyt, *zapis;
	if((odczyt=fopen("odczyty.txt", "r"))==NULL){
		printf("Nie moge otworzyc pliku\n");
		exit(1);
	}

	zapis = fopen("wyniki.txt", "w");
	for(j=0; j<20; j++){
		if(j%2==0){
			fscanf(odczyt, "%lf", &u);
			licznik++;
		} else {
			fscanf(odczyt, "%lf", &i);
			licznik++;
		}

		if(licznik==2){
			fprintf(zapis, "R%d = %lf\n", ind, u/i);
			ind++;
			licznik = 0;
		}
	}
	fclose(odczyt);
	fclose(zapis);
	return 0;
}
