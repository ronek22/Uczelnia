#include <stdio.h>

int main(void){

  int x = -1;
	int x2 = 99;

	asm volatile (
		".intel_syntax noprefix;"
    "mov eax, %1;"
    "xor ebx,ebx;"
    // for(i=0;i<32;i++)

    "petla:"
    "shl eax;"
    "jnc a1;"
    "inc ebx;"
    "a1: cmp eax,0;" // lub and eax,eax lub or eax,eax, gdy 0 zapali flage z
    "jnz petla;"
    "mov %0, ebx;"
		".att_syntax prefix;"
		: "=r" (x2)
		: "r" (x)
		: "eax","ebx"
	);

	printf("x=%d x2=%d\n", x, x2);

	return 0;
}
