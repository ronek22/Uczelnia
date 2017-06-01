#include <stdio.h>
#include <stdlib.h>

int a,b,c,d,h;
float r;

void obwKwa()
{
  printf("Podaj bok kwadratu: ");
  scanf("%d", &a);
  printf("Obwod kwadratu wynosi = %d\n", 4*a);
}

void obwPro()
{
  printf("Podaj a: ");
  scanf("%d", &a);
  printf("Podaj b: ");
  scanf("%d", &b);
  printf("Obwod prostokata wynosi = %d\n", 2*a+2*b);
}

void obwTro(){
  printf("Podaj a: ");
  scanf("%d", &a);
  printf("Podaj b: ");
  scanf("%d", &b);
  printf("Podaj c: ");
  scanf("%d", &c);
  printf("Obwod trojkata wynosi = %d\n", a+b+c);
}

void obwKol(){
  printf("Podaj promien kola: ");
  scanf("%f", &r);
  printf("Obwod kola wynosi = %f\n", 3.14*2*r);
}

void obwTra()
{
  printf("Podaj a: ");
  scanf("%d", &a);
  printf("Podaj b: ");
  scanf("%d", &b);
  printf("Podaj c: ");
  scanf("%d", &c);
  printf("Podaj d: ");
  printf("Obwod trapezu wynosi = %d\n", a+b+c+d);

}
void obwRom(){
  printf("Podaj bok rombu: ");
  scanf("%d", &a);
  printf("Obwod rombu wynosi = %d\n", 4*a);
}

void obwRow(){
  printf("Podaj a: ");
  scanf("%d", &a);
  printf("Podaj b: ");
  scanf("%d", &b);
  printf("Obwod rownlegloboku wynosi = %d\n", 2*a+2*b);
}
