#include <stdio.h>
#include <string.h>

int main(){

	int i;
	char znaki[100];
	printf("Wprowadz wyraz malymi literami: ");
	scanf("%99s", znaki);

	for(i=0;i<strlen(znaki);i++){
		znaki[i]=znaki[i]-32;
	}

	for(i=0;i<strlen(znaki);i++){
		printf("%c", znaki[i]);
	}

	printf("\n");
	return 0;
}
