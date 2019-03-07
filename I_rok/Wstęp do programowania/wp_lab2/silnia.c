#include <stdio.h>

int main() {

int n, i;
int silnia = 1;

do {
	printf("Wprowadz n!: ");
	scanf("%d", &n);
}while(n < 0 || n > 30);

for(i = 2; i <= n; i++){
	silnia = silnia * i;
}

printf("Wartosc silni wynosi: %d", silnia);

return 0;
}
