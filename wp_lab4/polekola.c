#include <stdio.h>

int main()
{
	float r,d,s; //r - promien strefy; d - odleglosc miedzy srodkami sfer
	printf("Podaj promien sfery(r): ");
	scanf("%f",&r);
	printf("Podaj odleglosc miedzy srodkami sfer(d): ");
	scanf("%f",&d);

	s = 3.141592654 * (r * r - (0.25) * d * d);

	printf("Pole tego kola wynosi: %.2f\n", s);

	return 0;
}
