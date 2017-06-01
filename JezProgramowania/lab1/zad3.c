#include <stdio.h>

int main(){

	int i=0;
	int x=3,y,z,e,f;
	int a[3];
	int b[3];

	a[i++]=0;
	a[++i]=0;
	for(i=0;i<3;i++){
		printf("a[%d]=%d\n", i, a[i]);
	} 

	y=(x+=2);
	printf("y=%d\n",y);

	x=3;
	e=x%3;
	printf("(x mod 3) = %d\n",e);

    x=3;
    f = x%4;
    printf("(x mod 4) = %d\n",f);


	x=3;
	z=(x%=3)+(x%=4);
	printf("z=%d\n",z);
	return 0;

}
