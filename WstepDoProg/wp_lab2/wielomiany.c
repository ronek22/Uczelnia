#include <stdio.h>
#include <math.h>

int main(){

float a, b, c, x1, x2;

printf("Wprowadz wsp. a: ");
scanf("%f", &a);
printf("Wprowadz wsp. b: ");
scanf("%f", &b);
printf("Wprowadz wsp. c: ");
scanf("%f", &c);

float delta = b * b - 4 * a * c;
float pierw = sqrt(delta);

if(delta < 0){
	printf("Brak rozwiazan.\n");
} else if(delta == 0) {
	x1 = -b/a;
	printf("Pierwiastkiem tego wielomianu kwadratowego jest: %f \n", x1);
} else {
	x1 = (-b + pierw)/(2 * a);
	x2 = (-b - pierw)/(2 * a);
	printf("Pierwiastkami tego wielomianu sa: x1 = %f, x2 = %f \n", x1, x2);
}


return 0;
}
