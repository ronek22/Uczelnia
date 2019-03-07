#include <stdio.h>

int main(){
	int tab[5],i,suma=0;

	for(i=0;i<5;i++)
	{
		printf("Wprowadz liczbe nr %d: ",i+1);
		scanf("%d",(tab+i));
		suma+=*(tab+i);
	}
	printf("Suma = %d\n",suma);

	return 0;
}
