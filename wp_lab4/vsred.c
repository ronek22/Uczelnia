#include <stdio.h>

int main()
{
	int v1,v2,vSr;
	
	printf("Podaj predkosc pociagu z A do B: ");
	scanf("%d", &v1);
	printf("Podaj predkosc pociagu z B do A: ");
	scanf("%d", &v2);
	
	vSr = (2 * v1 * v2)/(v1 + v2);
	printf("Predkosc srednia wynosi: %d\n", vSr);
	return 0;
}
