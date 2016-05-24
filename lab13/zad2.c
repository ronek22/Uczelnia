#include <stdio.h>

int main(){
//wiersz x kolumna
//a[n][m]
//b[m][k]
//c[n][k]
  int n,m,k,i,j,l;

  printf("Wczytaj n,m,k po spacji.");
  scanf("%i %i %i",&n,&m,&k);

  double a[100],b[100],c[100];

  for(i=0;i<n;i++){
    for(j=0;j<m;j++){
      printf("Podaj a[%d][%i]: ", i,j);
      scanf("%lf", &a[i*m+j]);
    }
  }

  for(i=0;i<m;i++){
    for(j=0;j<k;j++){
      printf("Podaj b[%d][%i]: ", i,j);
      scanf("%lf", &b[i*k+j]);
    }
  }


  for(i=0;i<n;i++){
    for(j=0;j<k;j++){
      c[i*n+j]=0;
      for(l=0;l<m;l++){
        c[i*n+j]=a[j*m+l] * b[i*m+l];
      }
    }
  }

  for(i=0;i<n;i++){
    for(j=0;j<k;j++){
      printf("%.2lf\t", c[i*k+j]);
    }
    printf("\n");
  }



  return 0;
}
