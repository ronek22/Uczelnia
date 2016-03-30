#include <stdio.h>
#include <stdlib.h>

typedef struct {
	char marka[20];
	char model[20];
	int rocznik;
	int przebieg;
	float pojSil;
} Samochod;

int main(){
	FILE *plik;
	Samochod *Baza;
	int n,i;

	printf("Ile samochodow chcesz dodac? ");
	scanf("%d", &n);

	Baza = (Samochod*)malloc(n*sizeof(Samochod));

    if((plik=fopen("samochody.txt", "a"))==NULL) {
        printf("Nie moge otworzyc pliku do zapisu!\n");
        exit(1);
    }

	for(i=0; i<n; i++){
	printf("Podaj marke: ");
	scanf("%s", Baza[i].marka);

	printf("Podaj model: ");
	scanf("%s", Baza[i].model);

	printf("Rocznik? ");
	scanf("%d", &Baza[i].rocznik);

	printf("Jaki ma przebieg? ");
	scanf("%d", &Baza[i].przebieg);

    printf("Jaki ma pojemnosc silnika? ");
    scanf("%f", &Baza[i].pojSil);



    fprintf(plik,"\n%d. Samochod: \n", i+1);
    fprintf(plik,"Marka: %s\n", Baza[i].marka);
    fprintf(plik,"Model: %s\n", Baza[i].model);
    fprintf(plik,"Rocznik: %d\n", Baza[i].rocznik);
    fprintf(plik,"Przebieg: %d\n", Baza[i].przebieg);
    fprintf(plik,"Pojemnosc silnika: %.2f\n", Baza[i].pojSil);
	}

	fclose(plik);
	free(Baza);


	return 0;
}
