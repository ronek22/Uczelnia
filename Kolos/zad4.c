#include <stdio.h>
#include <string.h>

int main(){
	int i;
	char wyraz[20];
	printf("Podaj wyraz: ");
	scanf("%19s", wyraz);

	for(i = 0; i<strlen(wyraz);i++)
	{
		if(i%3==0){
			printf("%c", wyraz[i]);
		}
	} 

	printf("\n");	

	return 0;
}
