#include <stdio.h>
#include <stdlib.h>

typedef struct {
	char imie[20];
	char nazwisko[20];
	int wiek;
	double srednia;
} Osoba;

int main(){
	Osoba Jan;

	printf("Podaj imie: ");
	scanf("%s",Jan.imie);
	
	printf("Podaj nazwisko: ");
	scanf("%s", Jan.nazwisko);

	printf("Ile ma lat? ");
	scanf("%d", &Jan.wiek);

	printf("Jaka ma srednia ocen? ");
	scanf("%lf", &Jan.srednia); 

	printf("Imie: %s\n", Jan.imie);
	printf("Nazwisko: %s\n", Jan.nazwisko);
	printf("Wiek: %d\n", Jan.wiek);
	printf("Srednia ocen: %lf\n", Jan.srednia);

	return 0;
}
