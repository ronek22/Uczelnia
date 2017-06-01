#include <stdio.h>

int main(){
	int a[10];
	int N=10,i;
	for (i=0; i<N; a[i++]=i);
	for(i=0;i<N;i++){
		printf("a[%d] = %d\n", i, a[i]);
} 


	return 0;
}
