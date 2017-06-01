#include <stdio.h>



int main(){
	int n;
	float pojKan, ilBz;
	float result;
	int wynik;	

	printf("Podaj ilosc benzyny[l]: ");
	scanf("%f", &ilBz);
	
	printf("Podaj pojemnosc kanistra[l]: ");
	scanf("%f", &pojKan);

	printf("Podaj liczbe kanistrow: ");
	scanf("%d", &n);

	result = (ilBz/pojKan);
	wynik = (int)result + 1;
	printf("Test: %f\n", result);
	printf("int: %d\n", wynik);
	if(wynik <=  n)
	{
		printf("Zmieści się!\n");
	} else printf("Nie zmieści się!\n");
	
	return 0;
}
