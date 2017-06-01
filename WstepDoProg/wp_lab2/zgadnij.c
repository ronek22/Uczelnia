#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(){

	int guess, los, i;

	srand(time(NULL)); //generacja liczb pseudolosowych
	los = rand()%10; // losowanie liczby z przedzialu od 0 do 9

	printf("Zgadnij liczbe[0..9]: ");
	scanf("%d", &guess);

	while(guess != los){
		printf("Niestety nie trafiles.\nSprobuj jeszcze raz: ");
		scanf("%d", &guess);
	}

	printf("BRAWO zgadles liczbe. To byla %d \n\n", los);

	return 0;
}
