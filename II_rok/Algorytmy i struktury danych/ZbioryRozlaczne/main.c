#include<stdio.h>
#include<stdlib.h>

typedef struct wezel {
  int klucz;
  struct wezel *rodzic;
  int rank;
}* Wezel;

Wezel MakeSet(int k){
  Wezel x = (struct wezel*) malloc(sizeof(struct wezel));
  x->klucz=k;
  x->rodzic=x;
  x->rank=0;
  return x;
}

Wezel FindSet(Wezel x){
  if(x != x->rodzic)
  {
    x->rodzic = FindSet(x->rodzic);
  }
  return x->rodzic;
}

void Union(Wezel x, Wezel y){
  if(x->rank > y->rank)
  {
    y->rodzic = x;
  }
  else
  {
    x->rodzic = y;
    if(x->rank==y->rank)
    {
      y->rank = y->rank+1;
    }
  }
}

int main(void){
  Wezel Z[10];
  Z[0] = MakeSet(0);
  Z[1] = MakeSet(1);
  Z[2] = MakeSet(2);
  Z[3] = MakeSet(3);
  Z[4] = MakeSet(4);
  Z[5] = MakeSet(5);
  Z[6] = MakeSet(6);
  Z[7] = MakeSet(7);
  Z[8] = MakeSet(8);
  Z[9] = MakeSet(9);

  printf("Test MakeSeta: \n");
  printf("Z[0]: k:%d r:%d\nZ[1]: k:%d r:%d\nZ[2]: k:%d r:%d\nZ[3]: k:%d r:%d\n",
  Z[0]->klucz, Z[0]->rank, Z[1]->klucz, Z[1]->rank, Z[2]->klucz, Z[2]->rank, Z[3]->klucz, Z[3]->rank);
  printf("\nUnion test \n");


  //przyklad ze slajdu
  printf("Polaczone zbiory o rownych rangach(ranga wzrasta o 1):\n");
  Union(FindSet(Z[1]), FindSet(Z[2]));
  printf("Union(FindSet(Z[1]), FindSet(Z[2]));\n");
  printf("Z[1]: klucz:%d rank:%d\nZ[2]: klucz:%d rank:%d\nZ[2]->rodzic->klucz:%d\nZ[1]->rodzic->klucz:%d\n\n", Z[1]->klucz, Z[1]->rank, Z[2]->klucz, Z[2]->rank, Z[2]->rodzic->klucz, Z[1]->rodzic->klucz);
  Union(FindSet(Z[3]), FindSet(Z[4]));
  printf("Union(FindSet(Z[3]), FindSet(Z[4]))\n");
  printf("Polaczone zbiory o roznych rangach:\n");
  Union(FindSet(Z[5]), FindSet(Z[4]));
  printf("Union(FindSet(Z[5]), FindSet(Z[4]));\n");
  printf("Z[5]: klucz:%d rank:%d\nZ[4]: klucz:%d rank:%d\nZ[4]->rodzic->klucz:%d\nZ[5]->rodzic->klucz:%d\nZ[3]->rodzic->klucz:%d\n", Z[5]->klucz, Z[5]->rank, Z[4]->klucz, Z[4]->rank, Z[4]->rodzic->klucz, Z[5]->rodzic->klucz, Z[3]->rodzic->klucz);

  return 0;
}
