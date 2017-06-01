#include <stdio.h>
#include <string.h>

int main(){
	int i;
	char tab[10];
	printf("Podaj wyraz: ");
	scanf("%9s", tab);

	for(i = 0; i<strlen(tab); i++)
	{	
		if(i%2==0){
			printf("%c", tab[i]);
		}

	}

	printf("\n");

	return 0;
}
