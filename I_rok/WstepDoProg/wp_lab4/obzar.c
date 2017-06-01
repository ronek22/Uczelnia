#include <stdio.h>
#include <math.h>

int main()
{
	int i,obzart, pudCiast;
	float ilePudCiast;
	printf("Podaj ile obzartuchow bierze udzial: ");
	scanf("%d", &obzart);
	printf("Ile ciastek w jednym pudelku: ");
	scanf("%d", &pudCiast);

	int czas[obzart];
	int ileCiast[obzart];

	for(i = 0; i<obzart; i++)
	{
		printf("Podaj czas obzart[%d] w sek.: ", i+1);
		scanf("%d", &czas[i]);
		ileCiast[i] = 86400/czas[i];
	}

	ilePudCiast = 0;

	for(i = 0; i<obzart; i++)
	{
		ilePudCiast += ileCiast[i];
		printf("Ciast: %d, Razem: %.1f\n", ileCiast[i], ilePudCiast);
	}

	ilePudCiast = ilePudCiast/pudCiast;

	printf("Pudelka = %.1f \n\n", ceil(ilePudCiast));

	return 0;
}
