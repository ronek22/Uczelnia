#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(){
	srand(time(NULL));

	int i, liczba, test = 0,suma = 0;
	int tab[10];

	for(i = 0; i<10; i++){
		printf("Podaj liczbe: ");
		scanf("%d", &tab[i]);
	}

	liczba = rand() % 10;
	for(i = 0; i<10; i++){
		if(liczba == tab[i]){
			test = 1;
		}
	}

	if(test==1){
		for(i = 0; i<10; i++){
			suma+=tab[i];
		}
		printf("Suma: %d\n", suma);
	} else {
		printf("Liczby nie ma w tablicy. Nic nie robie.\n");
	}

	return 0;
}
