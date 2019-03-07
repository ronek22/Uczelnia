//                                          pmp@inf.ug.edu.pl  2014
// drukowanie drzew cz-cz z wartownikiem wspolnym
// dla wszystkich wezlow:
// drukowanie na ekran tekstowy i przez dot

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define RED 1        /* stala oznaczajaca kolor wezla */
#define BLACK 0      /* stala oznaczajaca kolor wezla */
#define SZER_EKR 80  /* szerokosc ekranu */
#define IL_POZ   6   /* ilosc poziomow drzewa, ktore beda wydrukowane   */
                     /* gwiazdka bedzie sygnalizowac istnienie nizszych */
                     /* poziomow                                        */

/* struktury danych do reprezentowania drzewa */
typedef struct wezel *Wskwezla; /* wskaznik na wezel drzewa  */
typedef struct wezel{
	int klucz;
	Wskwezla left, right, p;
	int kolor;
} Twezla ;  /* typ wezla */

/* drzewa z wartownikami: wezel wskazywany przez "nil" jest wartownikiem
   zastepujacym NULL; dla korzenia pole "p" ma wartosc "nil";
   pole nil->p musi byc ustawione odpowiednio w przy usuwaniu
*/
Wskwezla nil;

void nilInit(void){
/* funkcja inicjujaca nil; musi byc wywolana przed budowaniem drzewa */
  nil= (Wskwezla) malloc(sizeof(Twezla));
  nil->p = NULL;
  nil->kolor = BLACK;
  nil->left = nil->right = NULL;
}

void drukuj(Wskwezla w);
/* funkcja drukujaca drzewo binarne na ekranie (tutaj tylko deklaracja) */
/* funkcja drukuje drzewo o korzeniu "w"                                */

void drukujDot(Wskwezla r);
  // generuje w pliku drzewo1.gv lub drzewo0.gv (naprzemiennie)
  // opis drzewa o korzeniu r do wydrukowania przez program dot
  // zlecenie "dot -Tpdf -O drzewo1.gv" utworzy plik "drzewo1.gv.pdf"

/* ------------  implementacja ------------------------------------- */
char wydruk[IL_POZ+1][SZER_EKR];

void drukujost(Wskwezla w, int l, int p,int poziom){
       int srodek = (l+p)/2;
       if (w==nil)   return;
       wydruk[poziom][srodek]='*';
}

void drukujwew(Wskwezla w, int l, int p,int poziom){
       int srodek = (l+p)/2;
       int i,dl;
       char s[19];
       if (w==nil)    return;
       if (w->kolor==BLACK)
         dl=sprintf(s,"%d",w->klucz);
       else
	 //	        dl=sprintf(s,"\e[31m%+d\e[0m",w->klucz);
       dl=sprintf(s,"%+d",w->klucz);
       for (i=0;i<dl;i++)
         wydruk[poziom][srodek-dl/2+i]=s[i];
       if (++poziom<IL_POZ){
         drukujwew(w->left,l,srodek,poziom) ;
         drukujwew(w->right,srodek+1,p,poziom) ;
       }
       else {
         drukujost(w->left,l,srodek,poziom) ;
         drukujost(w->right,srodek+1,p,poziom) ;
       }
}

void drukuj(Wskwezla w){
  int j,i;
  for (i=0;i<=IL_POZ;i++)
    for (j=0;j<SZER_EKR;j++)
      wydruk[i][j] = ' ';
  drukujwew(w,0,SZER_EKR,0);
  for (i=0;i<=IL_POZ;i++){
      for (j=0;j<SZER_EKR;j++)
        putchar(wydruk[i][j]);
      printf("\n");
  }
}

void drukujKrawedz(FILE *plikwy, int z, Wskwezla syn, int zs){
// wezel r o numerze z jest juz wydrukowany
// teraz drukujemy jego syna "syn" o numerze zs oraz krawedz miedzy nimi
  if (syn == nil){
    fprintf(plikwy,"%d [shape=circle, style=invisible, label=\"",zs);
    fprintf(plikwy,"%d ",0);
    fprintf(plikwy,"\"]\n");
    fprintf(plikwy,"%d -- %d [style=invis];\n ",z,zs);
  } else{
    if (syn->kolor == RED)
      fprintf(plikwy,"%d [shape=circle, color=red, label=\"",zs);
    else
      fprintf(plikwy,"%d [shape=circle, color=black, label=\"",zs);
    fprintf(plikwy,"%d ",syn->klucz);
    fprintf(plikwy,"\"]\n");
    fprintf(plikwy,"%d -- %d ;\n",z,zs);
  }
}

int rekDrukujDot(Wskwezla r, int z, FILE *plikwy){
  // drukuje drzewo o korzeniu r
  // z  - numer wezla r
  // zwraca najwiekszy numer wezla w poddrzewie, ktorego jest korzeniem
  // zakladamy, ze korzen r jest juz wydrukowany
  int nz;
  if (r == nil) return z;
  else{
    drukujKrawedz(plikwy,z,r->left,z+1);
    nz=rekDrukujDot(r->left,z+1,plikwy);
    drukujKrawedz(plikwy,z,r->right,nz+1);
    nz=rekDrukujDot(r->right,nz+1,plikwy);
    return nz;
  }
}

void drukujDot(Wskwezla r){
  // generuje w pliku drzewo1.gv lub drzewo0.gv (naprzemiennie)
  // opis drzewa o korzeniu r do wydrukowania przez program dot
  // zlecenie "dot -Tpdf -O drzewo1.gv" utworzy plik "drzewo1.gv.pdf"
  static int gdzie=0;
  FILE *plikwy;
  if (gdzie) {
    plikwy=fopen("drzewo1.gv","w");
    gdzie=0;
  }else{
    plikwy=fopen("drzewo0.gv","w");
    gdzie=1;
  }
  fprintf(plikwy, "graph drzewo{\n");
  fprintf(plikwy, "size = \"2,20\"");
  if (r!=nil){
    if (r->kolor == RED)
      fprintf(plikwy,"%d [shape=circle, color=red, label=\"",0);
    else
      fprintf(plikwy,"%d [shape=circle, color=black, label=\"",0);
    fprintf(plikwy,"%d ",r->klucz);
    fprintf(plikwy,"\"]\n");
    rekDrukujDot(r,0,plikwy);
  }
  fprintf(plikwy, "}\n");
  fclose(plikwy);
  printf("wydrukowane drzewo%d.gv\n",(gdzie+1)%2);
}

/* ------------- miejsce na inne funkcje -------------------- */


void lewaRotacja(Wskwezla *k,Wskwezla x){
	Wskwezla y = x->right;
	x->right = y->left;
	if(y->left != nil){
		y->left->p = x;
	}
	y->p = x->p;
	if(x->p  == nil){
        (*k) = y;
	} else if(x == x->p->left){
        x->p->left = y;
	} else{
        x->p->right = y;
	}
	y->left = x;
	x->p = y;
}

void prawaRotacja(Wskwezla *k,Wskwezla x){
	Wskwezla y = x->left;
	x->left = y->right;
	if(y->right != nil){
		y->right->p = x;
	}
	y->p = x->p;
	if(x->p == nil){
        (*k)=y;
	} else if(x == x->p->right){
        x->p->right = y;
	} else {
	    x->p->left = y;
	}
	y->right = x;
	x->p = y;
}

Wskwezla Insert(Wskwezla *k, int key){
	Wskwezla z = malloc(sizeof(Twezla));
	z->p = nil;
	z->klucz = key;
	z->left = nil;
	z->right = nil;

	Wskwezla y = nil;
	Wskwezla x = *k;
	while( x!=nil){
		y = x;
		if(z->klucz < x->klucz){ // wstawiany element jest mniejszy od danego wezla, idz na lewo
			x=x->left;
		} else {
			x=x->right;  // wstawiany wezel jest wiekszy, idz na prawo
		}
	} // chodz dopoki nie trafisz na lisc
	z->p = y; // rodzic wstawianego elementu to y
	if(y == nil){ // jesli y jest pusty, to znaczy ze wstawiany element bedzie korzeniem
	    *k=z;
	} else if(z->klucz < y->klucz){ // wstawiany element jest mniejszy niz znaleziony rodzic, idzie na lewo
		y->left = z;
	} else {
		y->right = z;
	}
	return z;
}


int cRED(Wskwezla T){
  static int cz;

  //inorder, jesli trafie na czerwony zwiekszam licznik
	if(T != nil){
		cRED(T->left);
		if(T->kolor == RED) cz++;
		cRED(T->right);
	}
  return cz;
}

int WysokoscM(Wskwezla T){
	int wys1; // liczenie lewego poddrzewa
	int wys2; // liczenie prawego poddrzewa

	if(T != nil){
		wys1 = WysokoscM(T->left);
		wys2 = WysokoscM(T->right);
		if(wys1 > wys2){
            return wys1 + 1; // dodajemy korzen
		} else {
            return wys2 + 1; // dodajemy korzen
		}
    }
    else
    {
    return -1;
	}
}

int WysokoscL(Wskwezla T){
    int wys1;
    int wys2;

    if(T == nil){
        return -1;
    }

    if(T->left == nil){ // jesli lewym synem jest lisc to z prawej moze byc tylko brat bez synow
        return WysokoscL(T->right) + 1;
    }

    if(T->right == nil){
        return WysokoscL(T->left) + 1;
    }

    wys1 = WysokoscL(T->right);
    wys2 = WysokoscL(T->left);

    if(wys1 > wys2){
        return wys2 + 1;
    } else {
        return wys1 + 1;
    }

}

void RBinsert(Wskwezla *k,int key){
	Wskwezla x = Insert(k,key);
	x->kolor = RED; // wstawiany element musi byc czerwony
	while(x !=(*k) && x->p->kolor == RED){ // wykonuj dopoki rodzic wstawionego elementu jest czerwony lub wstawiony element zostanie korzeniem
		if(x->p==x->p->p->left){ // spr. czy ojciec jest prawym lub lewym synem dziadka -> ojciec x jest lewym synem dziadka
			Wskwezla y = x->p->p->right; // y-> brat ojca
			if(y->kolor == RED){ // PRZYPADEK 1, BRAT OJCA x CZERWONY
				x->p->kolor = BLACK;
				y->kolor = BLACK;
				x->p->p->kolor = RED;
				x = x->p->p;
			} else { // brat ojca x jest czarny
				if(x == x->p->right){ // PRZYPADEK 2, ojciec i syn tworza zakret
					x = x->p; // syn wchodzi na miejsce ojca
					lewaRotacja(k, x); // rotacja w lewo po synie
				}
        //PRZYPADEK 3
				x->p->kolor = BLACK;
				x->p->p->kolor = RED;
				prawaRotacja(k, x->p->p); // rotacja w prawo po, dziadku
			}
		} else { // OJCIEC jest PRAWYM synem dziadka, lustrzane odbicie
			Wskwezla y = x->p->p->left;
			if(y->kolor == RED){
				x->p->kolor = BLACK;
				y->kolor = BLACK;
				x->p->p->kolor = RED;
				x = x->p->p;
			} else {
				if(x == x->p->left){
					x = x->p;
					prawaRotacja(k, x);
				}
				x->p->kolor = BLACK;
				x->p->p->kolor = RED;
				lewaRotacja(k, x->p->p);
			}
		}
	}
	(*k)->kolor = BLACK; // korzen zawsze musi byc czarny

}

void dodajDrukuj(Wskwezla *k, int key){
  RBinsert(k,key);
  drukuj(*k);
  drukujDot(*k);
  getchar();
}

/* ----------------- program testujacy -----------------------*/

int main(){

    nilInit();
    int cz, i,x,n;
    Wskwezla korzen=nil;

    // dodajDrukuj(&korzen,5);
    // dodajDrukuj(&korzen,3);
    // dodajDrukuj(&korzen,8);
    // dodajDrukuj(&korzen,6);
    // dodajDrukuj(&korzen,9);

    dodajDrukuj(&korzen,38);
    dodajDrukuj(&korzen,31);
    dodajDrukuj(&korzen,22);
    dodajDrukuj(&korzen,8);
    dodajDrukuj(&korzen,20);
    dodajDrukuj(&korzen,5);
    dodajDrukuj(&korzen,10);
    dodajDrukuj(&korzen,9);

    cz = cRED(korzen);
    printf("czerwone: %i \n", cz);
    printf("Hmax: %i \n", WysokoscM(korzen));
    printf("Hmin: %i \n", WysokoscL(korzen));
    return 0;
}
