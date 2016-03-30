#include <stdio.h>

int main()
{
	int ilosc, r, a, b,k;
	int i = 0;
	printf("Ile dzielen chcesz sprawdzic: ");
	scanf("%d", &ilosc);
	
	int dziel[ilosc*2];
	int wynik[ilosc];

	for(i = 0; i<ilosc; i++)
	{
		k = 0;
		printf("A: ");
		scanf("%d", &dziel[i]);
		printf("/ \n B: ");
		scanf("%d", &dziel[i+1]);
		
		do		
		{
			wynik[i] = dziel[i] - k * dziel[i+1];
			k++;
		}while(wynik[i]>0);

		if(wynik[i]<0)
		{
			k--;

			wynik[i] = dziel[i] - (k-1) * dziel[i+1];
		}
		printf("Reszta[%d] = %d\n", i, wynik[i]); 

		
	}


	return 0;
}
