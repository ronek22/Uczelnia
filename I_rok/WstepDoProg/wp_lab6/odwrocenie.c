#include <stdio.h>
#include <string.h>

int main(){

	int i;
	char znaki[100], odwrocone[100];
	printf("Wprowadz wyraz: ");
	scanf("%99s", znaki);
	int length=strlen(znaki)-1;

	for(i=0;i<=length;i++){
		odwrocone[i]=znaki[length-i];
	}

	for(i=0;i<strlen(odwrocone);i++){
		printf("%c", odwrocone[i]);
	}

	printf("\n");
	return 0;
}
