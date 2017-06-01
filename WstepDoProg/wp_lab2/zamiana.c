#include <stdio.h>

int main(){

float celsj;
float fahr;
float tempF;
float tempC;
int wybor;

printf("1. Zamiana z C na F.\n2. Zamiana z F na C.\n >>");
scanf("%d", &wybor);


switch(wybor) {
	case 1:
		printf("Wprowadz temp. w celsjuszach: ");
		scanf("%f",&celsj); 
		tempF = 32 + (1.8)*celsj;
		printf("Temperatura w skali Fahrenheita: %.2f F \n", tempF);
		break;
	case 2: 
		printf("Wprowadz temp. w fahrenheitach: ");
		scanf("%f",&fahr); 
		tempC = (fahr - 32)/(1.8);
		printf("Temperatura w skali Celsjusza: %.2f C \n", tempC);
		break;
}

return 0;
}
