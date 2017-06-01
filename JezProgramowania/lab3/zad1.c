#include <stdio.h>
#include <limits.h>
#include <float.h>

int main(){

	printf("\n");
	printf("%-15s%-10s%-40s%-40s%-30s%-30s\n\n", "typ","bajty","dolna wartosc","gorna wartosc","ziarno","precyzja");
	printf("%-15s%-10i%-40i%-40i\n","short",(int) sizeof(short), SHRT_MIN,SHRT_MAX);
	printf("%-15s%-10i%-40i%-40i\n","int",(int) sizeof(int),INT_MIN,INT_MAX);
	printf("%-15s%-10i%-40li%-40li\n","long",(int) sizeof(long),LONG_MIN,LONG_MAX);
	printf("%-15s%-10i%-40lli%-40lli\n","long long",(int) sizeof(long long),LLONG_MIN,LLONG_MAX);
	printf("%-15s%-10i%-40e%-40.2e%-30e%-30i\n","float",(int) sizeof(float),FLT_MIN,FLT_MAX,FLT_EPSILON,FLT_DIG);
	printf("%-15s%-10i%-40le%-40.2le%-30le%-30i\n","double",(int) sizeof(double),DBL_MIN,DBL_MAX,DBL_EPSILON,DBL_DIG);
	printf("%-15s%-10i%-40Le%-40.2Le%-30Le%-30i\n","long double",(int) sizeof(long double),LDBL_MIN,LDBL_MAX,LDBL_EPSILON,LDBL_DIG);


	return 0;
}
