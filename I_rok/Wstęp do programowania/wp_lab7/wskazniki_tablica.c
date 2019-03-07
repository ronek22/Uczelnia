#include <stdio.h>

int main(){

	int tab[10],i;
	
	for(i = 0; i<10; i++)
	{
	printf("Adres %d komorki tablicy: %p\n", i, (tab+i));
	}
	return 0;
}
