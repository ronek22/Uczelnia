/*=====================================================
 * Funkcja
 *   Boolean form0(drzewo* drz)
 * wczytuje formule logiczna i produkuje drzewo tej formuly.
 *
 * Formula na wejsciu musi byc zgodna z gramatyka:
 *
 *   form0  ::=  form1 { '=' form1 }*
 *   form1  ::=  form2  |  form2 '>' form1
 *   form2  ::=  form3 { 'V' form3 }*
 *   form3  ::=  form4 { '&' form4 }*
 *   form4  ::=  form5 | '~' form4
 *   form5  ::=  zm | st | '(' from0 ')'
 *
 * np.:  (p&q > r) = (p > (q > r)) .
 *
 * Zmienne logiczne: pojedyncze male litery.
 * Stale logiczne: znaki '0' i '1'.
 *
 * Operatory wg pierwszenstw wykonywania (od najsilniejszego do
 * najslabszego):
 *   ~  (negacja),
 *   &  (koniunkcja -- wiaze do lewej),
 *   V  (alternatywa -- wiaze do lewej),
 *   >  (implikacja -- wiaze do prawej),
 *   =  (rownowaznosc -- wiaze do lewej).
 * Oczywiscie mozna zmienic kolejnosc wykonywania przez zastosowanie
 * nawiasow.
 *
 * Ponizej nadane sa poczatkowe wartosci zmiennym.  Oczywiscie mozna
 * je poprawic zaleznie od wlasnych potrzeb.
 *
 *
 * Program nalezy kompilowac komenda
 *   gcc -Wall glowny.c funkcje.c -std=gnu99
 * i wywolywac komenda
 *   ./a.out
 *
 *=====================================================
*/

#include "funkcje.h"

int main(int argnum, char* arg[]) {
  drzewo drz;
  char tab[26] =
    { /* a= */ '0',  /* b= */ '0',  /* c= */ '0',  /* d= */ '0',
      /* e= */ '0',  /* f= */ '0',  /* g= */ '0',  /* h= */ '0',
      /* i= */ '0',  /* j= */ '0',  /* k= */ '0',  /* l= */ '0',
      /* m= */ '0',  /* n= */ '0',  /* o= */ '0',  /* p= */ '0',
      /* q= */ '0',  /* r= */ '0',  /* s= */ '0',  /* t= */ '0',
      /* u= */ '0',  /* v= */ '0',  /* w= */ '0',  /* x= */ '0',
      /* y= */ '0',  /* z= */ '0'
    };
  if (argnum==1)  poziom=0;
  else  poziom=2;

  nowy_lex();
  if (form0(&drz)) {
    printf("\n  wartosc: %c\n\n", wylicz(drz, tab));
  }
  else blad("nie formula");
  if (lex != EOF && lex != '\n')  blad("smieci na koncu");

  return 0;
}
