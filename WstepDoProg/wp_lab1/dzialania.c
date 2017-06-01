#include <stdio.h>

int main(void){

int a;
int b;
printf("Podaj zmienna a: ");
scanf("%d", &a);
printf("Podaj zmienna b: ");
scanf("%d", &b);

int suma = a + b;
int roznica = a - b;
int iloczyn = a * b;
int iloraz = a/b;
int modulo = a%b;

printf("Suma: %d\nRoznica: %d\nIloczyn: %d\nIloraz: %d\nModulo: %d\n", suma, roznica, iloczyn, iloraz, modulo);


return 0;
}
