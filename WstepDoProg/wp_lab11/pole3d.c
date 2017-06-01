#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int a, b, c, h, hFig,l;
float r;

void polGraPra4(){
  printf("Podaj bok podstawy: ");
  scanf("%d", &a);
  printf("Podaj wysokosc: ");
  scanf("%d", &hFig);

  printf("Pole graniastoslupa prawidlowego czworokatnego wynosi = %d\n", a*a*hFig);
}
void polGraPra3(){
  printf("Podaj bok podstawy: ");
  scanf("%d", &a);
  printf("Podaj wysokosc boku podstawy: ");
  scanf("%d", &h);
  printf("Podaj wysokosc graniastoslupa: ");
  scanf("%d", &hFig);
  printf("Pole graniastoslupa prawidlowego czworokatnego wynosi = %d\n", ((a*h)/2)*hFig);
}
void polGraPra6(){
  printf("Podaj bok podstawy: ");
  scanf("%d", &a);
  printf("Podaj wysokosc: ");
  scanf("%d", &hFig);
  float pierw = sqrt(3);
  float wynik = (3*a*a*pierw)/2*hFig;
  printf("Pole graniastoslupa prawidlowego szesciokatnego wynosi = %f\n", wynik);
}

void polOstrPra4(){
  printf("Podaj bok podstawy: ");
  scanf("%d", &a);
  printf("Podaj wysokosc: ");
  scanf("%d", &hFig);
  int wys;

  wys = (a/2)*(a/2)+hFig*hFig;
  wys = sqrt(wys);

  printf("Pole ostroslupa prawidlowego czworokatnego wynosi = %d\n", a*a+(2*a*wys));
}

void polOstrPra3(){
  int hbFig;
  printf("Podaj bok podstawy: ");
  scanf("%d", &a);

  printf("Podaj wysokosc boku figury: ");
  scanf("%d", &hbFig);

  float pole = (a*a*sqrt(3))/4;

  printf("Pole ostroslupa prawidlowego czworokatnego wynosi = %f\n", pole+0.5*a*hbFig*3);
}
void polOstrPra6(){
  int hbFig;
  printf("Podaj bok podstawy: ");
  scanf("%d", &a);

  printf("Podaj wysokosc boku figury: ");
  scanf("%d", &hbFig);

  float pole = 6*(a*a*sqrt(3))/4;

  printf("Pole ostroslupa prawidlowego czworokatnego wynosi = %f\n", pole+0.5*a*hbFig*6);
}

void polWalca(){
  printf("Podaj promien podstawy: ");
  scanf("%f", &r);
  printf("Podaj wysokosc: ");
  scanf("%d", &hFig);

  printf("Pole walca wynosi = %f\n", 2*3.14*r*r+2*3.14*r*hFig);
}


void polStozka(){
  printf("Podaj promien podstawy: ");
  scanf("%f", &r);
  printf("Podaj tworzaca: ");
  scanf("%d", &l);
  printf("Podaj wysokosc: ");
  scanf("%d", &hFig);

  printf("Pole walca wynosi = %f\n", 2*3.14*r*r+2*3.14*r*l);
}

void polKuli(){
  printf("Podaj promien kuli: ");
  scanf("%f", &r);

  printf("Pole graniastoslupa prawidlowego szesciokatnego wynosi = %f\n",4*3.14*r*r);
}
