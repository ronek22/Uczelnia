#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#define MAX 18

typedef struct przedmiot {
        int nr_katalogowy;
        char name[MAX];
        float cena;
        struct przedmiot* dalej;
}* lista;

//=======================================================

lista dodaj(int numer, char nazw[MAX], float cen, lista my_list) {
   lista pom;
   pom = (struct przedmiot*) malloc(sizeof(struct przedmiot));
   pom->nr_katalogowy=numer;
   strcpy(pom->name,nazw);
   pom->cena=cen;
   pom->dalej=my_list;
   return pom;
};

//=======================================================

lista  katalog(lista my_list) {
  char nazw[MAX];
  int numer,i;
  float cen;

  FILE* baza = fopen("./lista_przedmiotow","r");
  if (baza == NULL) printf("\n ZLE\n\n");
  for (i=0; i<MAX; i++) {
    fscanf(baza, "%i", &numer);
    fscanf(baza, "%s", nazw);
    fscanf(baza, "%f", &cen);
    my_list=dodaj(numer,nazw,cen,my_list);
  }
  fclose(baza);
  return my_list;
};

//=======================================================

void cena(lista my_list, int nr_kat){
  int found=0;
  while (my_list != NULL){
    if(my_list->nr_katalogowy == nr_kat){
        my_list->cena+=20;
        printf("%i %s %f\n",my_list->nr_katalogowy, my_list->name, my_list->cena);
        found = 1;
    }
    my_list = my_list->dalej;
  }

  if(found==0){
    printf("Nie znaleziono\n");
  }
}


//=======================================================

int main(){
lista my_list=NULL;
my_list=katalog(my_list);

int katalog;
printf("Podaj pierwszy nr_kat: ");
scanf("%i", &katalog);
cena(my_list,katalog);

printf("Podaj drugi nr_kat: ");
scanf("%i", &katalog);
cena(my_list,katalog);

printf("Podaj trzeci nr_kat: ");
scanf("%i", &katalog);
cena(my_list,katalog);

return 0;
}
