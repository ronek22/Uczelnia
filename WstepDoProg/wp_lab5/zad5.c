#include <stdio.h>

int powIt(int a, int n);
int powRek(int a, int n);

int main(){
	int a, n, potega, wybor;

	printf("Podaj jaka liczba do jakiej potegi: \n");
	scanf("%d", &a);
	scanf("%d", &n);

	printf("W jaki sposob chcesz obliczyc potege.\n1.Iteracyjnie\n2.Rekurencyjnie\n>> ");
	scanf("%d", &wybor);

	switch(wybor)
	{
		case 1:
			potega = powIt(a,n);
			printf("\n%d^%d = %d\n", a, n, potega);
			break;
		case 2:
			potega = powRek(a,n);
			printf("\n%d^%d = %d\n", a, n, potega);
	}
	return 0;
}

int powIt(int a, int n){
	int i;
	int wynik = a;
	for(i = 1; i<n; i++){
		wynik = wynik*a;
	}
	return wynik;
}

int powRek(int a, int n){
	if(n<=0) return 1;
	return a*powRek(a,n-1);
}
