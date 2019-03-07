// liczenie najdluzszego ciagu jedynek w binarnej liczbie
#include <stdio.h>

int main(int argc, char const *argv[]) {
  /* code */
  int x = 0xFE0FE; // %0 11110000001111111000
  int x2= 7; // %1


  asm volatile (
	".intel_syntax noprefix;"
	    "mov eax, %0;" //ecx - wynik, ebx- tymczasowy wynik
	    "xor ebx,ebx; "
	    "petla:"
	    "shl eax;"
	    "jc a;"
	    "cmp ecx,ebx;"
	    "js b;"
	    "cmp eax, 0;"
	    "jz koniec;"
	    "xor ebx,ebx;"
	    "jmp petla;"
	    "b: mov ecx, ebx;"
	    "cmp eax, 0;"
	    "jz koniec;"
	    "xor ebx,ebx;"
	    "jmp petla;"
	    "a: inc ebx;"
	    "jmp petla;"
		"koniec: mov %1, ecx;"
    ".att_syntax prefix"
    : "=r" (x2)
    : "r" (x)
    : "eax", "ebx", "ecx"
  );

  printf("x = %i, x2 = %i\n", x, x2);


  return 0;
}
