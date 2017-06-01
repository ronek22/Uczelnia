#include <stdio.h>


int sprawdz(int n){
	if(n >= 0 && n <= 10){
		return 1;
	} else{
		return 0;
	}
}

int silniaIt(int n){
	int wynik = 1;
	int i;
	if(n <= 1) return 1;
	for(i = 2; i<=n; i++){
		wynik = wynik*i;
	}
	return wynik;
}

int silniaRek(int n){
	if(n <= 1) return 1;
	return n * silniaRek(n-1); 
}


int main(){

	int liczba,wybor,silnia;
	printf("Wybierz w jaki sposob chcesz policzyc silnie: ");
	printf("\n1.Iteracyjnie\n2.Rekurencyjnie\n>>");
	scanf("%d", &wybor);
	printf("\nPodaj dla jakiej liczby, chcesz policzyc silnie: ");
	scanf("%d", &liczba);
	if(sprawdz(liczba) == 0){
		printf("Liczba nie jest z zakresu\n");
		return 0;
	}


	switch(wybor)
	{
		case 1:
			silnia = silniaIt(liczba);
			printf("\nSilnia z %d = %d\n", liczba, silnia);
			break;
		case 2:
			silnia = silniaRek(liczba);
			printf("\nSilnia z %d = %d\n", liczba, silnia);
	}

	return 0;
}
