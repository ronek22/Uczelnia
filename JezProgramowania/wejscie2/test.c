#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<ctype.h>

#define MAX 15

typedef struct przedmiot {
        int numer_katalogowy;
        char nazwa[MAX];
        float cena;
        struct przedmiot* next;
}* lista;

//=======================================================

lista dodaj(int numer, char nazw[MAX], float cen, lista moja_lista) {
   lista pom;
   pom = (struct przedmiot*) malloc(sizeof(struct przedmiot));
   pom->numer_katalogowy=numer;
   strcpy(pom->nazwa,nazw);
   pom->cena=cen;
   pom->next=moja_lista;
   return pom;
};

//=======================================================

lista  katalog(lista moja_lista) {
  char nazw[MAX];
  int numer,i;
  float cen;

  FILE* baza = fopen("lista_przedmiotow","r");
  if (baza == NULL) printf("\n ZLE\n\n");
  for (i=0; i<5; i++) {
    fscanf(baza, "%i", &numer);
    fscanf(baza, "%s", nazw);
    fscanf(baza, "%f", &cen);
    moja_lista=dodaj(numer,nazw,cen,moja_lista);
  }
  fclose(baza);
  return moja_lista;
};

//=======================================================

lista max (lista lis) {
lista wynik=lis;
lista pom = NULL;

float max = wynik->cena;
wynik = wynik->next;

while (wynik != NULL){
    if(wynik->cena>max){
      max = wynik->cena;
      pom = wynik;
    }
    wynik = wynik->next;
}
return pom;
}


//=======================================================

int main(){
lista moja_lista=NULL;
moja_lista=katalog(moja_lista);

lista maks = max(moja_lista);
printf("\n%s\n",maks->nazwa);

return 0;
}
