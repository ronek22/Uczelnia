#include <stdio.h>
#include <string.h>

int main(){

	int i,klucz;
	char znaki[100];
	printf("Wprowadz wyraz do zaszyfrowania malymi literami: ");
	scanf("%99s", znaki);
	printf("Podaj klucz: ");
	scanf("%d",&klucz); 

	for(i=0;i<strlen(znaki);i++){
		znaki[i]=znaki[i]+klucz;
	}

	for(i=0;i<strlen(znaki);i++){
		printf("%c", znaki[i]);
	}

	printf("\n");
	return 0;
}
