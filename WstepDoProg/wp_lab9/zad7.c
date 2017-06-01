#include <stdio.h>
#include <stdlib.h>

int main(){
	int i;
	char zdanie[100];
	FILE *plik,*zapis;
	if((plik=fopen("6.txt", "r"))==NULL){
		printf("Nie moge otworzyc pliku\n");
		exit(1);
	}

	zapis =fopen("out6.txt", "w");



	if(fgets(zdanie, 100, plik)!=NULL) {
		fprintf(zapis,"%s", zdanie);
		
	}
	fclose(plik);
	return 0;
}
