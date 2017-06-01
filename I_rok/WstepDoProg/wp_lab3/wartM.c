#include <stdio.h>

int main(){

	int tab[6];
	int i,maks,minim;;
	
	printf("Podaj liczbe nr 1: ");
	scanf("%d", &tab[0]);
	
	maks = tab[0];
	minim = tab[0];

	for(i = 1; i<6; i++){
		printf("Podaj liczbe nr %d: ", i+1);
		scanf("%d", &tab[i]);

		if(tab[i]>maks){
			maks = tab[i];
		}else if(tab[i] < minim) minim = tab[i];
	}

	printf("Liczba najwieksza: %d, Liczba najmniejsza: %d \n", maks, minim);



	return 0;
}
