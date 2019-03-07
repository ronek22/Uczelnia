#include <stdio.h>
#include <stdlib.h>

typedef struct {
	char imie[20];
	char nazwisko[20];
	int wiek;
	double srednia;
} Osoba;

int main(){
	FILE *plik;
	Osoba *Uczniowie;
	int n,i;

	printf("Ile uczniow chcesz wpisac? ");
	scanf("%d", &n);

	Uczniowie = (Osoba*)malloc(n*sizeof(Osoba));

    if((plik=fopen("wynik.txt", "w"))==NULL) {
        printf("Nie moge otworzyc pliku do zapisu!\n");
        exit(1);
    }

	for(i=0; i<n; i++){
	printf("Podaj imie: ");
	scanf("%s",Uczniowie[i].imie);

	printf("Podaj nazwisko: ");
	scanf("%s", Uczniowie[i].nazwisko);

	printf("Ile ma lat? ");
	scanf("%d", &Uczniowie[i].wiek);

	printf("Jaka ma srednia ocen? ");
	scanf("%lf", &Uczniowie[i].srednia);

    fprintf(plik,"\n%d. Osoba: \n", i+1);
    fprintf(plik,"Imie: %s\n", Uczniowie[i].imie);
    fprintf(plik,"Nazwisko: %s\n", Uczniowie[i].nazwisko);
    fprintf(plik,"Wiek: %d\n", Uczniowie[i].wiek);
    fprintf(plik,"Srednia: %.2lf\n", Uczniowie[i].srednia);
	}

	fclose(plik);
	free(Uczniowie);


	return 0;
}
