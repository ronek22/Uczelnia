#include <stdio.h>

int main(){
	int y = 11;
	int * wsk_y = &y;

	printf("Wartosc zmiennej(tradycjnie)  = %d\n", y);
	printf("Wartosc zmiennej(wskazniki) = %d\n", *wsk_y);
	printf("Adres komorki pamieci = %p\n", wsk_y);

	return 0;
}
