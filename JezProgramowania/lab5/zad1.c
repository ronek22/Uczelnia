#include <stdio.h>

void dzielenie(int n, int k, int* q, int* r)
{
	*q=n/k;
	*r=n%k;
}


int main(){
	int liczba1,liczba2,iloraz,reszta;
	printf("Podaj pierwsza liczbe: ");
	scanf("%i", &liczba1);
	printf("Podaj druga liczbe: ");
	scanf("%i",&liczba2);

	do{
		if(liczba2 == 0){
			printf("Dzielnik nie moze byc zerem!\nPodaj jescze raz: ");
			scanf("%i",&liczba2);
		}
	}while(liczba2==0);


	dzielenie(liczba1,liczba2,&iloraz,&reszta);
	printf("Iloraz %i/%i wynosi: %i\n",liczba1,liczba2,iloraz);
	printf("Reszta z dzielenia %i/%i wynosi: %i\n",liczba1,liczba2,reszta);



	return 0;
}
