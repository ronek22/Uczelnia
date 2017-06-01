#include <stdio.h>

int main(){

	int n = 7 << (2&7);
	printf("%i\n", 5&3);
	printf("%i\n", 5|3);
	printf("%i\n", 7<<2&7);
	printf("%i\n", n);
	printf("%i\n", ((-1)<<8)>>16);
	printf("%i\n", 13^9);

	return 0;
}
