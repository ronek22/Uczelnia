#include <stdio.h>

int main(){

	float x = 1.0;
	double y= 1.0;
	long double z = 1.0;

	while(1.0+x > 1.0){
		printf("x = %f\n", x);
		x = x/2.0;
	}

	printf("Ziarno float = %fe\n",x);


	return 0;
}
