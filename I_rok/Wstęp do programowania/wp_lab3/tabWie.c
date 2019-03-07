#include <stdio.h>

int main(){

	srand(time(NULL));
	int tab[5][5];
	int i, j;

	for(i = 0; i<5; i++){
		for(j = 0; j<5; j++){
			tab[i][j] = rand() % 10;
			printf("%2d", tab[i][j]);
		}
		printf("\n");
	}

	


	return 0;
}
