#include <stdio.h>

int main(){
	srand(time(NULL));
	int i,j;
	int lotto[6];
	lotto[0] = rand()%49 + 1;

	for(i = 1; i<6; i++){
		lotto[i] = rand() % 49 + 1;
		j = 0;
		for(j = 0; j<i; j++){
			while(lotto[i] == lotto[j]){
				lotto[i] = rand()%49 + 1;
				j = 0;
			}
		} 
	}

	for(i = 0; i < 6; i++){
		printf("%d \t", lotto[i]);
	}
	printf("\n");
	return 0;
}
