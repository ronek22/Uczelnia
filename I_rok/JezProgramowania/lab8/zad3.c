#include <stdio.h>
#define CZYT(a,lf) printf("Podaj wartosc " #a " : "); scanf("%"#lf, &a); printf(#a " ma wartosc: %" #lf "\n", a);

int main(){
  int a;
  double b;

  CZYT(a,i);
  CZYT(b,lf);

  return 0;
}
