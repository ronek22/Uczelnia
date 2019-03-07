#include<stdio.h>

/*
	Adj(u) 		to zbiór wierzchołków, do których jest krawędź z wierzchołka u
	u.kolor 	to kolor wierzchołka: BIAŁY lub SZARY
	u.pi 		to taki wierzchołek v, że dotarliśmy do u krawędzią(v,u).
		Takie krawędzie tworzą drzewo (lub las drzew) spinające przeszukiwany graf.
		Korzeń (korzenie) tego drzewa (lasu) to te wierzchołki u dla których u.pi == NIL
*/

int n;
int time;

struct wsk{
        char kolor;
        int pi;
        int d;
        int f;
}* wezel;

void DFS2(int i, struct wsk u[], int matrix[][n]){	//matrix - graf
	// przeszukujemy graf w głąb rozpoczynając od wierzchołka startowego u
	// wierzchołki już odwiedzone mają kolor SZARY

        u[i].kolor = 's'; //szary
        time++;
        u[i].d=time;
        printf("%-4d",i+1);
        int j = 0;
        for(j = 0; j < n; j++){				//dla każdego v należącego do Adj(u)
                if(matrix[i][j] == 1){
                        if(u[j].kolor == 'b'){		//if v.kolor==BIAŁY
                                u[j].pi = i;		//v.pi=u
                                DFS2(j,u,matrix);
                        }
                }
        }
        u[i].kolor='c';
        time++;
        u[i].f=time;
}

void DFS1(struct wsk u[], int matrix[][n]){ //matrix - graf
        time = 0;
        int i = 0;

        // zerowanie
        for(i = 0; i < n; i++){			//dla każdego wierzchołka u
                u[i].kolor = 'b';			//u.kolor=BIAŁY
                u[i].pi = -1;			//u.pi=NIL
        }


        for(i = 0; i < n; i++){			//dla każdego wierzchołka u
                if(u[i].kolor == 'b'){		//if u.kolor==BIAŁY
                        DFS2(i, u, matrix);
                }
        }
}

int main(){

        FILE* plik = fopen("graf4.txt", "r");
        n = 0;
        fscanf(plik, "%i", &n);
        printf("##########################\n#\tGRAFY\t\t #\n##########################\n");
        printf("\nIlosc wezlow: %i\n", n);

        int matrix[n][n];
        int i = 0, j = 0;

        printf("\nMacierz sasiedztwa:\n");

        for(i = 0; i < n; i++){
                for(j = 0; j < n; j++){
                        fscanf(plik, "%i", &matrix[i][j]);
                        printf("%i ", matrix[i][j]);
                } printf("\n");
        }

        fclose(plik);
        printf("\n");

        struct wsk tab[n];

        printf("Porzadek DFS:\n");
        DFS1(tab, matrix);

        printf("\n\nKrawedz, czas odw. i czas przetw.:\n");
        for(i = 0; i < n; i++){
                printf("%-2i", i+1);
                printf(" -  %2i Odw: %i Prz: %i\n", tab[i].pi+1 != 0 ? tab[i].pi+1 : -1,tab[i].d,tab[i].f);
        }

        return 0;
}
