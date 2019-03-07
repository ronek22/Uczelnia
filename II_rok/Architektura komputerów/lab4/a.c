#include <stdio.h>
#include <string.h>

int main(){
  char *s = "aqr  b qabxx xryc pqr";
  int y,i,dlug=0, poz = 0;
  int x=-1;
  
	int len = strlen(s);
	for(i=0; i<len;i++){
		if((s[i] == 'p' || s[i] == 'q') && dlug<=0){
			poz = i;
			dlug++;
			continue;
		} else if((s[i] != 'a') && poz>0){
			dlug++;
		} else if((s[i] == 'a') && poz>0){
			dlug++;
			if(y < dlug) {
				y=dlug;
				dlug = 0;
				x = poz;
				poz = 0;	
			}
			else 
				dlug = 0;
				poz = 0;
		}
	}  
	
	printf("poz: %d, dlu: %d", x, y);
//  asm volatile (
//    ".intel_syntax noprefix;"
//    "mov eax, %2;" // wczytanie s do eax
//	"xor si, si;"
//	"loop:"
//		"mov al"
//
//
//
//    "print:"
//    "mov %0, ebx;"
//    "mov %1, ecx;"
//    ".att_syntax prefix;"
//    : "=r" (x), "=r" (y)
//    : "r" (s)
//    : "eax", "ebx", "ecx"
//  );

//  printf("%hd,%hd\n", x, y);


  return 0;
}
