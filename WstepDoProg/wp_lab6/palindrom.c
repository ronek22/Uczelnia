#include <stdio.h>
#include <string.h>

int main(){

	int i,test;
	char znaki[100];
	printf("Wprowadz wyraz: ");
	scanf("%99s", znaki);
	int length=strlen(znaki)-1;

	for(i=0;i<=length;i++){
		if(znaki[i]==znaki[length-i]){
			test = 1;
		}
		else
		{
			test = 0;
			break;
		}

	}

	printf("Czy jest palindromem?\n");

	if(test == 1)
	{
		printf("TAK");
	}
	else
	{
		printf("NIE");
	}


	printf("\n");
	return 0;
}
