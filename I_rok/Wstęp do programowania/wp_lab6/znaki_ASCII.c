#include <stdio.h>

int main(){
	int i;
	
	//for(i = 0; i <= 127; i++){
	//	a = (char)i;
	//	printf("%c ; %d\n",a, i);
	//}

	for(i=0;i<=255;i++){
		printf("Znak %c w ASCII to %d\n", i,i);
	}
	return 0;
}
