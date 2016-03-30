#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int a, b, c, h, hFig,l;
float r;

void objGraPra4(){
  printf("Podaj bok podstawy: ");
  scanf("%d", &a);
  printf("Podaj wysokosc: ");
  scanf("%d", &hFig);

  printf("Objetosc graniastoslupa prawidlowego czworokatnego wynosi = %d\n", a*a*hFig);
}
void objGraPra3(){
  printf("Podaj bok podstawy: ");
  scanf("%d", &a);
  printf("Podaj wysokosc graniastoslupa: ");
  scanf("%d", &hFig);

  float pole = (a*a*sqrt(3))/4;

  printf("Objetosc graniastoslupa prawidlowego czworokatnego wynosi = %f\n", pole*hFig);
}
void objGraPra6(){
  printf("Podaj bok podstawy: ");
  scanf("%d", &a);
  printf("Podaj wysokosc graniastoslupa: ");
  scanf("%d", &hFig);

  float pole = 6*(a*a*sqrt(3))/4;

  printf("Objetosc graniastoslupa prawidlowego czworokatnego wynosi = %f\n", pole*hFig);
}

void objOstrPra4(){
  printf("Podaj bok podstawy: ");
  scanf("%d", &a);
  printf("Podaj wysokosc: ");
  scanf("%d", &hFig);

  printf("Objetosc ostroslupa prawidlowego czworokatnego wynosi = %d\n", ((a*h)/2*hFig)/3);
}

void objOstrPra3(){
  printf("Podaj bok podstawy: ");
  scanf("%d", &a);
  printf("Podaj wysokosc graniastoslupa: ");
  scanf("%d", &hFig);

  float pole = (a*a*sqrt(3))/4;

  printf("Objetosc graniastoslupa prawidlowego czworokatnego wynosi = %f\n", (pole*hFig)/3);
}
void objOstrPra6(){
  printf("Podaj bok podstawy: ");
  scanf("%d", &a);
  printf("Podaj wysokosc graniastoslupa: ");
  scanf("%d", &hFig);

  float pole = 6*(a*a*sqrt(3))/4;

  printf("Objetosc graniastoslupa prawidlowego czworokatnego wynosi = %f\n", (pole*hFig)/3);
}

void objWalca(){
  printf("Podaj promien podstawy: ");
  scanf("%f", &r);
  printf("Podaj wysokosc: ");
  scanf("%d", &hFig);

  printf("Objetosc walca wynosi = %f\n", 3.14*r*r*hFig);
}


void objStozka(){
  printf("Podaj promien podstawy: ");
  scanf("%f", &r);
  printf("Podaj wysokosc: ");
  scanf("%d", &hFig);

  printf("Objetosc walca wynosi = %f\n", (3.14*r*r*hFig)/3);
}

void objKuli(){
  printf("Podaj promien kuli: ");
  scanf("%f", &r);

  printf("Objetosc graniastoslupa prawidlowego szesciokatnego wynosi = %f\n",(4*3.14*r*r*r)/3);
}
