#include <stdio.h>

int main(){

int a, b, wybor, wynik;

printf("Wprowadz pierwsza liczbe: ");
scanf("%d", &a);
printf("Wprowadz druga liczbe: ");
scanf("%d", &b);


printf("1. Dodawanie\n2.Odejmowanie\n3.Mnozenie\n4.Dzielenie modulo\nCo wybierasz: ");
scanf("%d", &wybor);

switch(wybor) {
	case 1:
		wynik = a + b;
		printf("a + b = %d \n", wynik);
		break;
	case 2: 
		wynik = a - b;
		printf("a - b = %d \n", wynik);
		break;
	case 3: 
		wynik = a * b;
		printf("a * b = %d \n", wynik);
		break;
	case 4:
		wynik = a % b;
		printf("Wynik modulo = %d \n", wynik);
		break;
}



return 0;
}
