#include <stdio.h>

int main(){

	int tab[10];
	int i, suma;

	for(i = 0; i<10; i++){
		printf("Podaj liczbe nr %d: ", i+1);
		scanf("%d", &tab[i]);

		suma = suma + tab[i];
	}

	printf("Suma dla podanych liczb wynosi: %d \n\n", suma);

	return 0;
}
