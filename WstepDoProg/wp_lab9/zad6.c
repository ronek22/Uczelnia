#include <stdio.h>
#include <stdlib.h>

int main(){
	int i;
	char zdanie[100];
	FILE *plik;
	if((plik=fopen("6.txt", "r"))==NULL){
		printf("Nie moge otworzyc pliku\n");
		exit(1);
	}

	if(fgets(zdanie, 100, plik)!=NULL) printf("%s", zdanie);


	fclose(plik);
	return 0;
}
