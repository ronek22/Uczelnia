#include <stdio.h>

int main(){
	int i,suma = 0;

	srand(time(NULL));
	int wymiar = rand()%20 + 1;
	int tab[wymiar];

	for(i=0; i<wymiar; i++)
	{
		tab[i] = rand()%10;
		suma+=tab[i];
		printf("%d\n", tab[i]);
	}

	printf("\nSuma: %d\n", suma);


	return 0;
}
