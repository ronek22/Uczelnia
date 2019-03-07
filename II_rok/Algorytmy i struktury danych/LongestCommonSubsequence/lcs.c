#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char x[100], y[100], b[100][100];
int c[100][100],m,n;

void LCS(){
	int i,j;

	//zerowanie pierwszej kolumny i pierwszego wiersza
	for(i=0; i<=m;i++) c[i][0] = 0;
	for(j=1; j<=n;j++) c[0][j] = 0;

	for(i=1;i<=m;i++){
		for(j=1;j<=n;j++){
			if(x[i-1]==y[j-1]){ // napisy indeksuje od 0, wiec musze odjac 1
				c[i][j] = c[i-1][j-1]+1;
				b[i][j] = '\\';
			} else if(c[i-1][j] >= c[i][j-1]){
				c[i][j] = c[i-1][j];
				b[i][j] = '|';
			} else{
				c[i][j] = c[i][j-1];
				b[i][j] = '-';
			}
		}
	}
}

void print(int i, int j){
	if(i==0 || j==0){
		return;
	}
	if(b[i][j]=='\\'){
		print(i-1,j-1);
		printf("%c",x[i-1]);
	} else if(b[i][j]=='|'){
		print(i-1,j);
	} else{
		print(i,j-1);
	}
}

void drukujTab(){
	int i,j;

	printf("TABELKA\n------------\n");
	printf("\t\t");
	for(i=0;i<n;i++)	printf("%2c\t", y[i]);
	printf("\n");

	for(i=0;i<=m;i++){
		if(i==0) printf("\t");
		if(i!=0) printf("%c\t",x[i-1]);

		for(j=0;j<=n;j++){
			printf("%c%d\t", b[i][j],c[i][j]);
		}
		printf("\n");
	}
	printf("\n");
}


int main(){

	printf("Podaj dwa ciagi, po spacji:\n");
	scanf("%s %s",x,y);

	m = strlen(x);
	n = strlen(y);

	LCS();
	drukujTab();

	printf("Najdluzszy wspolny podciag: ");
	print(m,n);
	printf("\n");

	return 0;
}
