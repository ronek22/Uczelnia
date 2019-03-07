#include <stdio.h>
#include <stdlib.h>

int f(int n){
	if(n==0)
		return 2;
	if(n==1 || n ==2)
		return 0;
	
	return 2*f(n-1)+f(n-2)-f(n-3);
		
}

int main() {
	int n,wynik;
	
	printf("Podaj n: ");
	scanf("%d", &n);
	
	wynik=f(n);
	
	printf("Wynik: %d\n", wynik);
	
	
	return 0;
}
