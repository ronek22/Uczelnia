
// kompilowac z opcjami -lrt -lm: gcc L1.c -lrt -lm
#include <time.h>
#include <stdio.h>
#include <math.h>
#define MAX 60000l
#define MLD 1000000000.0 //10**9


// F(n) - czas dzialania
// F(n) = (n-2)((1/2)*n)*c
double procedura1(int n){
 float x=0;
 int i,j,k;

 for(i=n-1;i>1;i--) {
  if((i % 2) == 1) {
    for(j=1;j<i+1;j++) ;
    for(k=i+1;k<n+1;k++) x=x+1;
    }
 }
 return x;
}

double procedura2(int A[],int n){
  float x = 0, suma;
  int d,g,i;

  for(d=1;d<n+1;d++){
    for(g=d;g<n+1;g++){
      suma=0.0;
      for(i=d;i<g+1;i++){
        suma += A[i];
      }
      x = fmax(x,suma);
    }
  }
  return x;
}

double procedura3(int n){
  int i,j;
  for(i=1; i<sqrt(n)+1;i++){
    j=1;
    while(j<sqrt(n)){
      j=j+j;
    }
  }
}

main(){
  struct timespec tp0, tp1;
  double Tn,Fn,x;
  int n;
  int A[MAX];
  for(n=0;n<MAX;n++) A[n]=n;
for(n=2;n<33000;n=2*n){

clock_gettime(CLOCK_PROCESS_CPUTIME_ID,&tp0);

// przykladowe obliczenia
//    x=procedura1(n);
      x=procedura1(n);

// zgadywana funkcja
//        Fn=5*n ; // np. funkcja liniowa
//      Fn=((double)n)*n*n ;
//      Fn=n*log(n);
//      Fn=n*n*sqrt(n);
      Fn=n*n;
//     Fn=n*n/1000 ;

clock_gettime(CLOCK_PROCESS_CPUTIME_ID,&tp1);

  Tn=(tp1.tv_sec+tp1.tv_nsec/MLD)-(tp0.tv_sec+tp0.tv_nsec/MLD);
  printf("n: %5d \t czas: %3.5lf \t wspolczynnik: %3.5lf\n",n,Tn, Fn/Tn);
}

printf("Procedura2\n");
for(n=2;n<2048;n=2*n){

clock_gettime(CLOCK_PROCESS_CPUTIME_ID,&tp0);

// przykladowe obliczenia
//    x=procedura1(n);
      x=procedura2(A,n);

// zgadywana funkcja
//        Fn=5*n ; // np. funkcja liniowa
      Fn=((double)n)*n*n ;
//      Fn=n*log(n);
//      Fn=n*n*sqrt(n);
//      Fn=n*n;
//     Fn=n*n/1000 ;

clock_gettime(CLOCK_PROCESS_CPUTIME_ID,&tp1);

  Tn=(tp1.tv_sec+tp1.tv_nsec/MLD)-(tp0.tv_sec+tp0.tv_nsec/MLD);
  printf("n: %5d \t czas: %3.5lf \t wspolczynnik: %3.5lf\n",n,Tn, Fn/Tn);
}


printf("Procedura3\n");
for(n=2;n<33000;n=2*n){

clock_gettime(CLOCK_PROCESS_CPUTIME_ID,&tp0);

// przykladowe obliczenia
//    x=procedura1(n);
      x=procedura3(n);

// zgadywana funkcja
//        Fn=5*n ; // np. funkcja liniowa
//      Fn=((double)n)*n*n ;
      Fn=n*log(n);
//      Fn=n*n*sqrt(n);
//      Fn=n*n;
//     Fn=n*n/1000 ;

clock_gettime(CLOCK_PROCESS_CPUTIME_ID,&tp1);

  Tn=(tp1.tv_sec+tp1.tv_nsec/MLD)-(tp0.tv_sec+tp0.tv_nsec/MLD);
  printf("n: %5d \t czas: %3.5lf \t wspolczynnik: %3.5lf\n",n,Tn, Fn/Tn);
}

}
