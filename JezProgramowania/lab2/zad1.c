#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void decToBin(int n){

	if(n>0){
		decToBin(n/2);
		printf("%i",n%2);
	}
}

int main(){

	int tbin;
	int i;
	char wers[100];
	FILE *fp;
	if((fp=fopen("test.txt","r"))==NULL) {
		printf("Nie moge otworzyc pliku\n");
		exit(1);
	}

	while(fgets(wers,100,fp)!=NULL){
		int n = strlen(wers)-1;
		for(i=0;i<n;i++){
			tbin = (int) wers[i];
			decToBin(tbin);
		}
		printf("\n");
	}

	fclose(fp);
	

	return 0;
}
