#include <stdio.h>
#include <stdlib.h>

//struktury do drzewa
typedef struct wezel *Wsk; //wksaznik na wezel BST

typedef struct wezel{
  int key;
  Wsk lewy,prawy,ojciec;
} Wezel;

//innorder succesor
// zwraca mniejszy element wezla,
//chyba ze nie istnieje to zwraca ten wezel
Wsk minimum(Wsk x){
  while(x->lewy != NULL){
    printf("min: %d;",x->key);
    x=x->lewy;
  }
  return x;
}

Wsk usunPom(Wsk *korzen, Wsk z){ // z-usuwany wezel, zostanie wyszukany
  Wsk x,y; //wezly pomocnicze
  if(z->lewy == NULL || z->prawy == NULL)
    y = z; // zapamietanie znalezionego wezla przynajmniej bez jednego z synow w y
  else // wezel ma obydwu synow
    y = minimum(z->prawy); // usuwamy z co najw. jedynm synem


  if(y->lewy != NULL ) x=y->lewy;
  else                 x=y->prawy; // x - jedyny syn y badz NULL

  x->ojciec = y->ojciec;
  if(y->ojciec == NULL)
    *korzen = x;
  else
    if(y == y->ojciec->lewy)
      y->ojciec->lewy = x; // y byl lewym synem
    else
      y->ojciec->prawy = x; // y byl prawym synem

  if(y!=z) z->key = y->key; // z mial dwoch synow
  y->ojciec = x; //x wszedl w miejsce usunietego y

  return y;
}

void WSTAW(Wsk *korzen, int wartosc){
  Wsk x,y;
  Wsk z = (Wsk) malloc (sizeof(Wezel));
  z->key=wartosc;z->lewy=NULL;z->prawy=NULL;

  //jesli drzewo jest puste
  if(*korzen==NULL){
    *korzen = z;
    (*korzen)->ojciec=NULL;
  } else {
      x=*korzen;
      while(x!=NULL){
        y=x;
        if(y->key > wartosc) //jesli wartosc jest mniejsza od akutlanego klucza to idz na lewo
          x=y->lewy;
        else
          x=y->prawy;
      }
      z->ojciec=y;
      if(y->key > wartosc) y->lewy = z;
      else y->prawy = z;
  }
}
//typ funkcji wskaznikowy, aby wykorzystac przy usuwaniu
Wsk SZUKAJ(Wsk korzen,int wartosc){
  if(korzen==NULL || wartosc == korzen->key){
    if(korzen!=NULL) printf("\nZnaleziono klucz: %d\n", wartosc);
    else printf("\nNie znaleziono klucza: %d\n", wartosc);
    return korzen;
  }
  if(wartosc < korzen->key)
    SZUKAJ(korzen->lewy,wartosc);
  else
    SZUKAJ(korzen->prawy,wartosc);

  return NULL;
}

void USUN(Wsk *korzen,int wartosc){
  Wsk w;
  if ((w=SZUKAJ(*korzen,wartosc))!= NULL) usunPom(korzen,w);
}

void DRUKUJ(Wsk korzen){
  if(korzen!=NULL){
    DRUKUJ(korzen->lewy);
    printf("%d ", korzen->key);
    DRUKUJ(korzen->prawy);
  }
}

int main(){
  //int i;
  Wsk korzen = NULL;
  WSTAW(&korzen,3);
  WSTAW(&korzen,4);
  WSTAW(&korzen,12);
  WSTAW(&korzen,5);
  DRUKUJ(korzen);

  USUN(&korzen,5);

  DRUKUJ(korzen);


  printf("\n\n");
  return 0;
}
