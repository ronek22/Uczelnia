#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 256


typedef struct wezel {
  char slowo[MAX];
  struct wezel * next;
}* lista;

// dolacza slowo na poczatek listy
lista WSTAW(char s[MAX], lista lis){
  lista nowy;
  nowy = malloc(sizeof(struct wezel));
  strcpy(nowy->slowo, s);
  nowy->next = lis;
  return nowy;
}

// zwraca wezel w kt�rym jest element s, jesli taki istnieje
lista SZUKAJ(char *s, lista lis){
	lista pom = lis;
	while(pom != NULL){
		if(strcmp(pom->slowo, s) == 0){ //istnieje
      printf("Slowo '%s' znalezione.\n", s);
			return pom;
		} else {
			pom = pom->next;
		}
	}
  printf("Slowa nie znaleziono.\n");
	return NULL;

}

//usuwa element znajdujacy sie na liscie l, o ile na niej jest
lista USUN(char *s,lista lis){
	// pom - wskazuje poprzedni element
	lista tmp, pom;
	tmp = SZUKAJ(s, lis);

	if(tmp == NULL){
		printf("Nie ma takiego elementu\n");
    return lis;
	} else {
		// element na poczatku listy
		if (tmp == lis) {
			lis = lis->next;
			// oczyszczanie pamieci
			free(tmp);
		} else {
			pom = lis;
			while((strcmp(pom->next->slowo, tmp->slowo)) != 0) // pom - szukanie poprzednika el. usu
				pom = pom->next; // poprzednik
			// element nie jest ostatni
			if(tmp->next!=NULL){
				pom->next = tmp->next;
			} else {
				pom->next = NULL;
			}
			free(tmp);
		}

	}
  printf("Element usunieto\n");
	return lis;
}

//kasuje wszystkie elementy z listy l
lista KASUJ(lista lis){
	while(lis != NULL){
		free(lis);
		lis = lis->next;
	}
  printf("Lista wyczyszczona.\n");
	return lis;
}


// funkcja liczaca powtorzenia danego wyrazu
int REP(lista lis, char *s){
	int count=0;
	while(lis!=NULL){
		if(strcmp(lis->slowo,s)==0) // przeszukanie calej listy w poszukiwaniu powtorzne
			count++;
		lis = lis->next;
	}
	return count;
}

lista BEZPOWTORZEN(lista lis){
	lista norep = NULL;
	while(lis != NULL){
		if(REP(norep,lis->slowo)==0)
			norep=WSTAW(lis->slowo, norep);
		lis = lis->next;
	}
	return norep;
}

lista SCAL(lista lis1, lista lis2){
	lista scalona = NULL;
	lista A = lis1;
	lista B = lis2;
	int rep=0;

  //sprawdzenie czy rozlaczne
	while(lis1 != NULL){
		if(REP(lis2,lis1->slowo)!=0)
			rep++;
		lis1 = lis1->next;
	}

	if(rep!=0){
		printf("Listy zawieraja wspolne elementy. Nie sa rozlaczne!\n");
    printf("Liczba powtarzajcych sie elementow: %d\n", rep);
		return NULL;
	}

	while(A!=NULL){
		scalona = WSTAW(A->slowo,scalona);
		A=A->next;
	}

	while(B!=NULL){
		scalona=WSTAW(B->slowo,scalona);
		B=B->next;
	}

	return scalona;
}

void DRUKUJ(lista lis){
  if(lis == NULL) printf("Lista jest pusta!");
  while(lis!=NULL){
    printf("%s, ", lis->slowo);
    lis = lis->next;
  }
  printf("\n");
}



int main(){

  lista ani = NULL;
  ani = WSTAW("kot", ani);ani = WSTAW("pies", ani);
  ani = WSTAW("mysz", ani);ani = WSTAW("szczur", ani);

  lista car = NULL;
  car = WSTAW("ferrari", car);car = WSTAW("porsche", car);

  printf("\n------------------------------------------------\n");
  printf("Lista zwierzat: "); DRUKUJ(ani);
  printf("Lista samochodów: "); DRUKUJ(car);
  printf("------------------------------------------------\n");
  printf("SZUKAJ('kot', ani): ");SZUKAJ("kot",ani);
  printf("SZUKAJ('ferrari', ani): ");SZUKAJ("ferrari",ani);
  printf("SZUKAJ('porsche', car): ");SZUKAJ("porsche",car);
  printf("------------------------------------------------\n");
  printf("USUN('szczur', ani): "); ani=USUN("szczur", ani);
  printf("Lista zwierzat: "); DRUKUJ(ani);
  printf("\nUSUN('mercedes', car): "); car=USUN("mercedes",car);
  printf("Lista samochodów: "); DRUKUJ(car);
  printf("\nKASUJ(ani): "); ani = KASUJ(ani);printf("DRUKUJ(ani): "); DRUKUJ(ani);
  printf("------------------------------------------------\n");
  car=WSTAW("ford",car);car=WSTAW("ferrari",car);car=WSTAW("ford",car);
  printf("Lista samochodów: ");DRUKUJ(car);
  lista bezpowt=NULL;bezpowt=BEZPOWTORZEN(car);
  printf("Lista samochodów bez powtórzeń: "); DRUKUJ(bezpowt);
  printf("------------------------------------------------\n");
  lista part1=NULL;
  part1=WSTAW("1",part1);part1=WSTAW("2",part1);part1=WSTAW("3",part1);
  lista part2=NULL;
  part2=WSTAW("3",part2);part2=WSTAW("4",part2);part2=WSTAW("5",part2);part2=WSTAW("6",part2);
  lista scalona = NULL;

  printf("part1: "); DRUKUJ(part1);
  printf("part2: "); DRUKUJ(part2);

  scalona = SCAL(part1, part2);
  printf("USUN('3',part2): ");part2=USUN("3",part2);

  printf("part1: "); DRUKUJ(part1);
  printf("part2: "); DRUKUJ(part2);

  scalona = SCAL(part1, part2);
  printf("SCALONA: "); DRUKUJ(scalona);

  printf("------------------------------------------------\n\n");

  return 0;
}
