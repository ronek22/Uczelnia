#include <stdio.h>
#include <string.h>

int main(){

	int i,test,length;
	char wyraz1[100], wyraz2[100], wynik[100];
	printf("Wprowadz wyraz pierwszy: ");
	scanf("%99s", wyraz1);
	printf("Wprowadz wyraz drugi: ");
	scanf("%99s", wyraz2);

	//dlugosc nowego wyrazu
	if(strlen(wyraz1)<strlen(wyraz2)){
		length = strlen(wyraz1)*2;
	} else{
		length = strlen(wyraz2)*2;
	}

	int j=0,k=0;
	for(i = 0; i<length;i++){
		if(i%2==0)
		{
			wynik[i] = wyraz1[j];
			j++; 
		}
		else
		{
			wynik[i] = wyraz2[k];
			k++;
		}
	}

	for(i=0; i<length; i++){
		printf("%c", wynik[i]);
	}




	printf("\n");
	return 0;
}
