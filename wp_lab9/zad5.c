#include <stdio.h>
#include <stdlib.h>

int main(){
	srand(time(NULL));
	int tab[20],i;
	FILE *zapis;
	zapis = fopen("lotto.txt", "w");
	

	for(i = 0;i<20;i++){
		tab[i]=rand()%50 + 1;
		fprintf(zapis, "%d\t", tab[i]);
	}

	fclose(zapis);
	return 0;
}
