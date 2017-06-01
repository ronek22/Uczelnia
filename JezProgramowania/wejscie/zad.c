#include <stdio.h>
#include <stdlib.h>

typedef struct{
	char tytul_gry[30];
	float cena;
	int id;
} gra;

void obnizka(int id, int procent, gra tab[]){
	int i;
	for(i = 0; i<3; i++){
		if(tab[i].id==id){
			float odjac = 0.01*procent*tab[i].cena;
			tab[i].cena = tab[i].cena-odjac;
		}
	}

}



int main(){
	int i,id_gry,procent;
	gra *tab;
	tab = (gra*)malloc(3*sizeof(gra));

	for(i=0;i<3;i++){
		printf("Podaj tytul gry: ");
		scanf("%s",tab[i].tytul_gry);
		printf("Podaj cene gry: ");
		scanf("%f",&tab[i].cena);
		tab[i].id=(i+1);
	}

	printf("Podaj id gry, ktorej cene chcesz obnizyc: ");
	scanf("%i", &id_gry);
	printf("Podaj procent: ");
	scanf("%i", &procent);


	obnizka(id_gry,procent,tab);

	free(tab);

	return 0;
}
