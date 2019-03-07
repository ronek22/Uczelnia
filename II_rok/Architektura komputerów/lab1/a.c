#include <stdio.h>

int main(void){

// gcc -save-temps
	int x = 9;
	int x2 = 99;

//	x2 = x+x;
//  x2 = x*20

	asm volatile (
		".intel_syntax noprefix;"
		"mov eax, %1;"
		"add eax, eax;"
		"add eax, eax;"
		"add ebx, eax;"
		"add eax, eax;"
		"add eax, eax;"
		"add eax, ebx"		
		"mov %0, eax;"
		".att_syntax prefix;"
		: "=r" (x2)
		: "r" (x)
		: "eax","ebx"
	);

	printf("x=%d x2=%d\n", x, x2);

	return 0;
}
