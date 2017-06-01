#include <stdio.h>

int main(){
	int i, parzyste = 0, przez5 = 0, przez7 = 0;
	int tab[16];

	for(i=0; i<16; i++){
		printf("Podaj liczbe: ");
		scanf("%d", &tab[i]);
	}

	for(i=0; i<16; i++){
		if(tab[i]%2 == 0){
			parzyste++;
		} 
		if(tab[i]%5==0){
			przez5++;
		}
		if(tab[i]%7==0){
			przez7++;
		}
	}

	printf("Parzystych:\t%d\nPodzielnych przez 5:\t%d\nPodzielnych przez 7:\t%d\n", parzyste, przez5, przez7);

	return 0;
}
