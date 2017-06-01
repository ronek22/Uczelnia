#include <stdio.h>
#include <stdlib.h>

int a,b,h;
float r;

void polKwa(){

  printf("Podaj bok kwadratu: ");
  scanf("%d", &a);

  printf("Pole kwadratu wynosi = %d\n", a*a);
}

void polPro()
{

  printf("Podaj bok a: ");
  scanf("%d", &a);
  printf("Podaj bok b: ");
  scanf("%d", &b);

  printf("Pole prostokata wynosi = %d\n", a*b);
}

void polTro(){

  printf("Podaj podstawe trojkata: ");
  scanf("%d", &a);
  printf("Podaj wysokosc trojkata: ");
  scanf("%d", &h);

  printf("Pole trojkata wynosi = %d\n", (a*h)/2);
}

void polKol(){

  printf("Podaj promien kola: ");
  scanf("%f", &r);

  printf("Pole kola wynosi = %f\n", 3.14*r*r);
}

void polTra(){

  printf("Podaj bok a: ");
  scanf("%d", &a);
  printf("Podaj bok b: ");
  scanf("%d", &b);
  printf("Podaj wysokosc: ");
  scanf("%d", &h);

  printf("Pole trapezu wynosi = %d\n", ((a+b)*h)/2);
}
void polRom(){

  printf("Podaj bok: ");
  scanf("%d", &a);
  printf("Podaj wysokosc: ");
  scanf("%d", &h);

  printf("Pole rombu wynosi = %d\n", a*h);
}
void polRow(){

  printf("Podaj bok: ");
  scanf("%d", &a);
  printf("Podaj wysokosc: ");
  scanf("%d", &h);

  printf("Pole rombu wynosi = %d\n", a*h);
}
