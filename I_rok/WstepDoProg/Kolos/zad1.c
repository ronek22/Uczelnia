#include <stdio.h>

int main(){
	int n; //liczba kafelkow
	float bokK; //dlugosc boku
	float powK; // powierzchnia kafelka 
	float powS; // powierchnia sciany

	printf("Podaj dlugosc boku kafelka[m]: ");
	scanf("%f", &bokK);

	printf("Podaj liczbe kafelkow: ");
	scanf("%d", &n);

	printf("Powierzchnia sciany: ");
	scanf("%f", &powS);

	powK = (bokK*bokK)*n;

	if(powK==powS){
		printf("Powierzchnia %d kafelkow o boku %.3f jest rowna scianie o powierzchni %.3f\n\n",n, bokK, powS);
	}else{
		printf("Powierzchnie nie sa rowne\n");
	}
	
	
	return 0;
}
