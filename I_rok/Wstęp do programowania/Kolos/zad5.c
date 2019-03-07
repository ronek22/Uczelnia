#include <stdio.h>

void srednia(){
    int n, i;
	float srednia, suma = 0, liczba;

    printf("Ile zmiennych chcesz podac: ");
    scanf("%d", &n);
    
    for(i = 0; i<n; i++){
        printf("Podaj zmienna: ");
        scanf("%f", &liczba);
        while(liczba==0){
            printf("Nie moze byc zerem. Podaj ponownie: ");
            scanf("%f", &liczba); 
        }
        suma+=liczba;
    }

	srednia = suma/(float)n;
    printf("Srednia = %f\n", srednia);
	
}

void suma(){
	int n, i;
	float suma = 0, liczba;
	printf("Ile zmiennych chcesz podac: ");
	scanf("%d", &n);
	
	for(i = 0; i<n; i++){
		printf("Podaj zmienna: ");
		scanf("%f", &liczba);
		while(liczba==0){
			printf("Nie moze byc zerem. Podaj ponownie: ");
			scanf("%f", &liczba); 
		}
		suma+=liczba;
	}

	printf("Suma = %f\n", suma);

}

void iloczyn(){
    int n, i;
	float iloczyn = 1, liczba;
    printf("Ile zmiennych chcesz podac: ");
    scanf("%d", &n);
    
    for(i = 0; i<n; i++){
        printf("Podaj zmienna: ");
        scanf("%f", &liczba);
        while(liczba==0){
            printf("Nie moze byc zerem. Podaj ponownie: ");
            scanf("%f", &liczba); 
        }
        iloczyn*=liczba;
    }

    printf("Iloczyn = %f\n", iloczyn);

}

int main(){

	printf("Menu: \n");
	printf("1. Oblicz srednia.\n2.Oblicz sume\n3.Oblicz iloczyn.\nCo wybierasz: ");

	int wybor;
	scanf("%d", &wybor);

	switch(wybor){
		case 1:
			srednia();
			break;
		case 2:
			suma();
			break;
		case 3:
			iloczyn();
			break;
		default:
			break;
	}


	return 0;
}
