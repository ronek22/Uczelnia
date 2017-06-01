#include <stdio.h>
#include <stdlib.h>

typedef struct {
	char imie[20];
	char nazwisko[20];
	int wiek;
	double srednia;
} Osoba;

int main(){
	Osoba *Uczniowie;
	int n,i;

	printf("Ile uczniow chcesz wpisac? ");
	scanf("%d", &n);

	Uczniowie = (Osoba*)malloc(n*sizeof(Osoba));

	for(i=0; i<n; i++){
	printf("Podaj imie: ");
	scanf("%s",Uczniowie[i].imie);
	
	printf("Podaj nazwisko: ");
	scanf("%s", Uczniowie[i].nazwisko);

	printf("Ile ma lat? ");
	scanf("%d", &Uczniowie[i].wiek);

	printf("Jaka ma srednia ocen? ");
	scanf("%lf", &Uczniowie[i].srednia); 
	}
	
	for(i=0; i<n;i++){
		printf("\n%d. Osoba: \n", i+1);
		printf("Imie: %s\n", Uczniowie[i].imie);
		printf("Nazwisko: %s\n", Uczniowie[i].nazwisko);
		printf("Wiek: %d\n", Uczniowie[i].wiek);
		printf("Srednia: %lf\n", Uczniowie[i].srednia);
	}

	return 0;
}
