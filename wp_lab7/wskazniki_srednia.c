#include <stdio.h>

int main(){
	int tab[5],i;
	double srednia=0;

	for(i=0;i<5;i++)
	{
		printf("Wprowadz liczbe nr %d: ",i+1);
		scanf("%d",(tab+i));
		srednia+=*(tab+i);
	}

	srednia/=5;
	printf("Srednia = %f\n",srednia);

	return 0;
}
