#include <stdio.h>
#include <math.h>
#include <limits.h>
#include <float.h>


int main(){

	short Sa = SHRT_MAX;
	int Ia = SHRT_MAX;
	Ia+=1;


	int Ib = INT_MIN;
	long Lb = INT_MIN;

	Lb-=1;

	printf("Short--> %i != %i\n", Sa-1, Ia); 
	printf("Int--> %li != %i\n", Lb,Ib-1);

	float Fc = FLT_MAX;
	long double Dc = FLT_MAX;
	Dc*=2;

	printf("%f\t!=\t%Lf\n", Fc*2,Dc);

	return 0;
}
