#include <stdio.h>

int main(){

float celsj;
float fahr;
float temp;

printf("Wprowadz temperature w celsjuszach: ");
scanf("%f",&celsj); 

temp = 32 + (1.8)*celsj;
printf("Temperatura w skali Fahrenheita: %.2f F \n", temp);

return 0;
}
