#include <stdio.h>
#include <stdlib.h>

int main(){
	int *x;
	int n, i;

	printf("Ile liczb calkowitych chcesz wpisac? ");
	scanf("%d", &n);


	x = (int*) malloc(n*sizeof(n));
	for(i = 0; i<n; i++){
		printf("Podaj liczbe: ");
		scanf("%d", (x+i));
	}

	for(i = 0; i<n; i++){
		printf("%d\n", *(x+i));
	}
	free(x);



	return 0;
}
