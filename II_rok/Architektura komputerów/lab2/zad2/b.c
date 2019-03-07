#include <stdio.h>

int main(void){

// gcc -save-temps
	// int x = 0x80000000;
  //  int x = 0;
  int x = 0x40000000;
	int x2 = 99;

	asm volatile (
		".intel_syntax noprefix;"
    "mov eax,%1;"
    "mov ebx,0;" // xor ebx,ebx;
    "shl eax;"
    "jnc a1;"
    "add ebx,1;" // inc ebx;
    "a1: shl eax;"
    "jnc a2;"
    "add ebx,1;" // inc ebx;
    "a2: mov %0, ebx;"
		".att_syntax prefix;"
		: "=r" (x2)
		: "r" (x)
		: "eax","ebx"
	);

	printf("x=%d x2=%d\n", x, x2);

	return 0;
}
