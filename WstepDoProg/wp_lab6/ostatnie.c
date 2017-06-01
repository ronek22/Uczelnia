#include <stdio.h>
#include <string.h>



int main(){

	int i,testW,wielka=0,mala=0;
	char znaki[100];
	printf("Wprowadz wyraz literami: ");
	scanf("%99s", znaki);

	for(i=0;i<strlen(znaki);i++){
		testW = (int)znaki[i];
		if(testW >= 65 && testW <= 90){
			wielka++;
		}
		else if(testW >= 97 && testW <= 122){
			mala++;
		}
	}

	if(mala>wielka){
		for(i=0;i<strlen(znaki);i++){
			testW = (int)znaki[i];
			if(testW >= 65 && testW <= 90)
			{
				znaki[i] = znaki[i]+32;
			}
		}
	}
	else
	{
		for(i=0;i<strlen(znaki);i++){
			testW = (int)znaki[i];
			if(testW >= 97 &&  testW <= 122)
			{
				znaki[i] = znaki[i]-32;
			}
		}
	}

	for(i=0;i<strlen(znaki);i++){
		printf("%c", znaki[i]);
	}

	printf("\n");
	return 0;
}
