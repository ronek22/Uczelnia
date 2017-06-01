#include <stdio.h>
#include <string.h>


int main(){

	int i;
	char znaki[100];
	printf("Wprowadz wyraz: ");
	scanf("%99s", znaki);

	int length=strlen(znaki)-1;

	for(i=length;i>=0;i--){
		printf("%c", *(znaki+i));
	}

	printf("\n");
	return 0;
}
