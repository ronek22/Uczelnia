#include <stdio.h>
#include <limits.h>
#include <float.h>

int main(){

	int Flt2Int = (int)FLT_MAX;
	int Dbl2Int = (int)DBL_MAX;
	double LdblToDbl = (double)LDBL_MAX;

	printf("FLT_MAX: Float to Int: %i\nDBL_MAX: Double to Int = %i\nLDBL_MAX: Long Double to Double = %lf\n",Flt2Int,Dbl2Int,LdblToDbl);

	return 0;
}
