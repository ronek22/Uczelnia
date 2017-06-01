#include <stdio.h>

int powRek(int a, int n);
int trojkatProst(int a, int b, int c);

int main(){
	int wynik,a,b,c;
	printf("Wprowadz trzy boki trojkata, zatwierdzajac kolejno enterem.\n>>");
	scanf("%d",&a);
	scanf("%d",&b);
	scanf("%d",&c);

	wynik = trojkatProst(a,b,c);
	if(wynik == 1)
	{
		printf("Ten trojkat jest prostokatny.\n");
	}else printf("Niestety nie jest prostokatny.\n");

	return 0;
}

int trojkatProst(int a, int b, int c)
{
	a = powRek(a, 2);
	b = powRek(b, 2);
	c = powRek(c, 2);

	if(a+b==c || c+a==b || b+c==a){
		return 1;
	}else return -1;
}


int powRek(int a, int n)
{
	if(n<=0) return 1;
	return a*powRek(a,n-1);
}
