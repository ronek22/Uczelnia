#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct {
  char nazwa[20];
  float cena;
  char kolor[16];
} przedmiot;


  char miejsce[20];
  char nazwa_wlasna[40];
  char trunek[16];
  int odleglosc;
  int ile_przed;


void  czytanie(char *arg) {
        int i;
        FILE* baza = fopen(arg, "r");
        if (baza == NULL) printf("\n ZLE\n\n");

        fscanf(baza, "%s", miejsce);
        fscanf(baza, "%s", nazwa_wlasna);
        fscanf(baza, "%s", trunek);
        fscanf(baza, "%d", &odleglosc);
        fscanf(baza, "%d", &ile_przed);
        przedmiot pd[ile_przed];

        for (i=0; i<ile_przed; i++) {
                fscanf(baza, "%s", pd[i].nazwa);
                fscanf(baza, "%f", &pd[i].cena);
                fscanf(baza, "%s", pd[i].kolor);
        }
        fclose(baza);
}


int main (int arg_num, char* arg[]) {

  int i;
  if (arg_num == 2) {
    czytanie(arg[1]);// wywołanie funkcji czytanie
  }
  else
  printf("\n Poprawne wywolanie: './wczytaj nazwa_pliku'\n\n");

  return 0;
}
