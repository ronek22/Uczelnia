#include <stdio.h>

int main() {

	int i,j;
	int wiersz,kolumna;
	
	printf("Jak duza bedzie macierz: [wiersze][kolumny]: ");
	scanf("%d", &wiersz);
	scanf("%d", &kolumna);

	int macierz[wiersz][kolumna];

	for(i = 0; i<wiersz; i++)
	{
		for(j = 0; j<kolumna; j++)
		{
			printf("Podaj liczbe dla [%d][%d]: ", i, j);
			scanf("%d", &macierz[i][j]);
		}
	}

	for(i = 0; i<kolumna; i++)
	{
		for(j = 0; j<wiersz; j++)
		{
			printf("%2d", macierz[j][i]);
		}
		printf("\n");
	}

	return 0;
}
