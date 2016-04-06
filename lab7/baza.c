#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_DL_IM 11
#define MAX_DL_NA 17
#define DUZO 10000

typedef struct {
        char imie[MAX_DL_IM];
        char nazwisko[MAX_DL_NA];
        int pensja;
} osoba;

osoba tabl[DUZO];

void swap(osoba arr[],int i, int j){
        osoba temp = arr[i];
        arr[i]=arr[j];
        arr[j]=temp;
}

int czytanie(char *arg){
        char znak;
        int wiersz;
        FILE* baza =
                fopen(arg, "r");
        if (baza == NULL) return 0;
        else{
                while((znak = getc(baza)) != EOF)
                {
                        if(znak == '\n')
                                ++wiersz;
                }
                fclose(baza);
                return wiersz;
        }
}

void  utworz_spis(char *arg, int ile) {
        int i;
        FILE* baza = fopen(arg, "r");
        if (baza == NULL) printf("\n ZLE\n\n");
        for (i=0; i<ile; i++) {
                fscanf(baza, "%s", tabl[i].imie);
                fscanf(baza, "%s", tabl[i].nazwisko);
                fscanf(baza, "%i", &tabl[i].pensja);
        }
        fclose(baza);
}

void  sortowanie(int ile) {
        int i,j;

        for(i=0; i<ile-1; i++) {
                for(j=0; j<ile-1-i; j++) {
                        if(strcmp(tabl[j].nazwisko,tabl[j+1].nazwisko)>0) {
                                swap(tabl, j,j+1);
                        }else if(strcmp(tabl[j].nazwisko,tabl[j+1].nazwisko)==0) {
                                if(strcmp(tabl[j].imie,tabl[j+1].imie)>0) {
                                        swap(tabl, j, j+1);
                                }
                        }
                }
        }
}

void pisanie(char *arg, int ile){
        int i;
        FILE* zapis = fopen(arg, "w");
        for(i=0; i<ile; i++) {
                fprintf(zapis,"%s %s %i\n",tabl[i].imie,tabl[i].nazwisko,tabl[i].pensja);
        }
        fclose(zapis);
}



int main (int arg_num, char* arg[]) {

        if (arg_num == 3) {
                int ile = czytanie(arg[1]);
                printf("ILE: %d\n",ile);
                if (ile > 0) {
                        utworz_spis(arg[1],ile);
                        sortowanie(ile);
                        pisanie(arg[2], ile);
                }
        }
        else
                printf("\n Poprawne wywolanie: './porzadkuj dane wynik'\n\n");
        return 0;
}
