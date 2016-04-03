#include "funkcje.h"

/***************************************************/

Boolean  blad (char s[]) {
  printf ("\n  BLAD:  %s\n\n", s); exit(1);
  return FALSE;
}

void  we (char nazwa[]) {
  if (poziom > 0) {
    poziom++;
    for (int i=0; i<poziom; i++)  printf("  ");
    printf ("WEJSCIE DO %s\n", nazwa);
  }
}

void  wy (char nazwa[]) {
  if (poziom > 0) {
    for (int i=0; i<poziom; i++)  printf("  ");
    printf ("WYJSCIE Z %s\n", nazwa);
    poziom--;
  }
}

/***************************************************/

void  nowy_lex(void) {
  we("nowy_lex");
  do {
    lex = getchar();
  }  while (lex!=EOF && lex!='\n' && isspace(lex));
  if (poziom > 0)  printf("(%c)\n", lex);
  wy("nowy_lex");
}


Boolean  term(char ch) {
  we("term");
  if (lex == ch) {
    nowy_lex(); wy("term"); return TRUE;
  }
  else { wy("term"); return FALSE; }
}


Boolean  stala(drzewo* drz) {
  we("stala");
  if (term('0')) {
    *drz = (drzewo)malloc(sizeof(wezel));
    (*drz)->tp = ss;  (*drz)->st = '0';
    wy("stala");
    return TRUE;
  }
  else
    if (term('1')) {
      *drz = (drzewo)malloc(sizeof(wezel));
      (*drz)->tp = ss;  (*drz)->st = '1';
      wy("stala");
      return TRUE;
    }
    else { wy("stala"); return FALSE; }
}


Boolean  zmienna(drzewo* drz) {
  we("zmienna");
  if ('a'<=lex && lex<='z') {
    *drz = (drzewo)malloc(sizeof(wezel));
    (*drz)->tp = zz;  (*drz)->zm = lex;  nowy_lex();
    wy("zmienna");
    return  TRUE;
  }
  else { wy("zmienna"); return FALSE; }
}

/***************************************************/

Boolean  form0 (drzewo* drz) {
  drzewo drz1, drz2;
  we("form0");
  if (form1(drz)) {
    while (term('=')) {
      if (form1(&drz1)) {
	drz2 = (drzewo)malloc(sizeof(wezel));
	drz2->tp = dd;
	drz2->sp = wttw;
	drz2->lewy = *drz;
	drz2->prawy = drz1;
	*drz = drz2;
      }
      else blad("form0 = ???");
    }
    wy("form0"); return TRUE;
  }
  else {
    wy("form0"); return FALSE;
  }
}


Boolean  form1 (drzewo* drz) {
  drzewo drz1, drz2;
  we("form1");
  if (form2(drz)) {
    if (term('>')) {
      if (form1(&drz1)) {
	drz2 = (drzewo)malloc(sizeof(wezel));
	drz2->tp = dd;
	drz2->sp = jesli;
	drz2->lewy = *drz;
	drz2->prawy = drz1;
	*drz = drz2;
        return TRUE;
      }
      else  return blad("form2 > ???");
    }
    else  { wy("form1"); return TRUE; }
  }
  else  { wy("form1"); return FALSE; }
}


Boolean  form2 (drzewo* drz) {
  drzewo drz1, drz2;
  we("form2");
  if (form3(drz)) {
    while (term('V')) {
      if (form3(&drz1)) {
	drz2 = (drzewo)malloc(sizeof(wezel));
	drz2->tp = dd;
	drz2->sp = lub;
	drz2->lewy = *drz;
	drz2->prawy = drz1;
	*drz = drz2;
      }
      else  return blad("form3 | ???");
    }
     wy("form2"); return TRUE;
  }
  else  { wy("form2"); return FALSE; }
}


Boolean  form3 (drzewo* drz) {
  drzewo drz1, drz2;
  we("form3");
  if (form4(drz)) {
    while (term('&')) {
      if (form4(&drz1)) {
	drz2 = (drzewo)malloc(sizeof(wezel));
	drz2->tp = dd;
	drz2->sp = ii;
	drz2->lewy = *drz;
	drz2->prawy = drz1;
	*drz = drz2;
      }
      else  return blad("form4 & ???");
    }
    wy("form3"); return TRUE;
  }
  else  { wy("form3"); return FALSE; }
}


Boolean  form4 (drzewo* drz) {
  drzewo drz1;
  we("form4");
  if (term('~')) {
    if (form4(&drz1)) {
      *drz = (drzewo)malloc(sizeof(wezel));
      (*drz)->tp = dd;
      (*drz)->sp = nie;
      (*drz)->prawy = drz1;
      wy("form4");  return TRUE;
    }
    else  return blad("~ ???");
  }
  else
    if (form5(drz))  { wy("form4"); return TRUE; }
    else  { wy("form4"); return FALSE; }
}


Boolean  form5 (drzewo* drz) {
  we("form5");
  if (term('(')) {
    if (form0(drz)) {
      if (term(')'))  { wy("form5"); return TRUE; }
      else  return blad("( form0 ???");
    }
    else  return blad("( ???");
  }
  else
    if (stala(drz))  { wy("form5"); return TRUE; }
    else
      if (zmienna(drz))  { wy("form5"); return TRUE; }
      else  { wy("form5"); return FALSE; }
}

/***************************************************/
//tp - typ(zz(zmienna),ss(stala),dd(spojnik))
//sp - spojnik(nie=0, ii=1, lub=2, jesli=3, wttw=4)

char  wylicz(drzewo drz, char tab[26]) {
  if(drz->tp==zz)
  {
    return tab[drz->zm-97];
  }
  else if(drz->tp==ss)
  {
    return drz->st;
  }
  else if(drz->tp==dd && drz->sp==nie)
  {
    if(wylicz(drz->prawy,tab)=='0') return '1';
    else return '0';
  }
  else if(drz->tp==dd && drz->sp==ii)
  {
    if((wylicz(drz->lewy,tab)=='1') && (wylicz(drz->prawy,tab)=='1')) return '1';
    else return '0';
  }
  else if(drz->tp==dd && drz->sp==lub){
    if((wylicz(drz->lewy,tab)=='0') && (wylicz(drz->prawy,tab)=='0')) return '0';
    else return '1';
  }
  else if(drz->tp==dd && drz->sp==jesli){
    if((wylicz(drz->lewy,tab)=='1') && (wylicz(drz->prawy,tab)=='0')) return '0';
    else return '1';
  }
  else if(drz->tp==dd && drz->sp==wttw){
    if(((wylicz(drz->lewy,tab)=='0') && (wylicz(drz->prawy,tab)=='0')) || ((wylicz(drz->lewy,tab)=='1') && (wylicz(drz->prawy,tab)=='1'))) return '1';
    else return '0';
  }
  else return '2';

  return '\n';
}

/***************************************************/
