#include <stdio.h>

int main(void){

  int x = -1;
	int x2 = 99;

	asm volatile (
		".intel_syntax noprefix;"
    "mov eax, %1;"
    "xor ebx,ebx;"
    // for(i=0;i<32;i++)
    "xor ecx,ecx;"
    "petla:"
    "shl eax;"
    "jnc a1;"
    "inc ebx;"
    "a1: inc ecx;"
    "cmp ecx,32;" // jesli 0, flaga Z zapalona ; zamiast sub cmp, to samo co odejmowanie ale nie zapisuje
    "jnz petla;"
    "mov %0, ebx;"
		".att_syntax prefix;"
		: "=r" (x2)
		: "r" (x)
		: "eax","ebx", "ecx"
	);

	printf("x=%d x2=%d\n", x, x2);

	return 0;
}
