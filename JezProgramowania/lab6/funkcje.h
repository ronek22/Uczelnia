#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>

typedef enum {FALSE=0, TRUE=1} Boolean;

typedef enum {zz=0, ss=1, dd=2} typ;
typedef enum {nie=0, ii=1, lub=2, jesli=3, wttw=4} spojnik;

typedef  struct wz {
  typ tp;
  char zm;
  char st;
  spojnik sp;  struct wz* lewy;  struct wz* prawy;
}  wezel;
typedef wezel* drzewo;

/***************************************************/

Boolean  blad (char s[]);
    // sygnalizacja b��du:
    // drukuje napis  s  a nast�pnie przerywa wykonanie programu

int poziom;
    //do odpluskwiania

void  we (char nazwa[]);
    // sygnalizacja wejscia do funkcji (do odpluskiwania)

void  wy (char nazwa[]);
    // sygnalizacja wyjscia z funkcji (do odpluskiwania)

/***************************************************/

char lex;

void  nowy_lex(void);
    // wczytanie kolejnego znaku

Boolean  term(char ch);
    // sprawdzenie, czy na wejsciu jest znak  ch

Boolean  stala(drzewo* drz);
    // drzewo dla stalej  0  lub  1

Boolean  zmienna(drzewo* drz);
    // drzewo dla zmiennej

/***************************************************/

Boolean  form0 (drzewo* drz);  // form0  ::=  form1 { = form1 }*
Boolean  form1 (drzewo* drz);  // form1  ::=  form2  |  form2 > form1
Boolean  form2 (drzewo* drz);  // form2  ::=  form3 { V form3 }*
Boolean  form3 (drzewo* drz);  // form3  ::=  form4 { & form4 }*
Boolean  form4 (drzewo* drz);  // form4  ::=  form5 | ~ form4
Boolean  form5 (drzewo* drz);  // form5  ::=  zm | st | ( from0 )

/***************************************************/

char  wylicz(drzewo drz, char tab[26]);
    // wyliczenie warto�ci drzewa

/***************************************************/
