#include <stdio.h>

int main(){
  int n,k,i,j;

  printf("Wczytaj n i k po spacji.");
  scanf("%i %i",&n,&k);

  double a[n*k],b[k*n];

  for(i=0;i<n;i++){
    for(j=0;j<k;j++){
      printf("Podaj a[%d][%i]: ", i,j);
      scanf("%lf", &a[i*k+j]);
    }
  }

  printf("\nMacierz A\n" );
  for(i=0;i<n;i++){
    for(j=0;j<k;j++){
      printf("%.2lf\t", a[i*k+j]);
    }
    printf("\n");
  }

  for(i=0;i<k;i++){
    for(j=0;j<n;j++){
      b[i*n+j]=a[j*k+i];
    }
  }

  printf("\nMacierz B\n");

  for(i=0;i<k;i++){
    for(j=0;j<n;j++){
      printf("%.2lf\t", b[i*n+j]);
    }
    printf("\n");
  }






  return 0;
}
