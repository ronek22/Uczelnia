#include <stdio.h>

int dodaj(int x)
{
	return x+=5;
}

int dodaj_wsk(int *x)
{
	return *x+=5;
}

int main(){

	int x = 4;
	int y = dodaj(x);
	printf("Teraz %d ma wartosc\n", x);
	y = dodaj_wsk(&x);
	printf("A teraz %d ma wartosc\n", x); 

	return 0; 
}
