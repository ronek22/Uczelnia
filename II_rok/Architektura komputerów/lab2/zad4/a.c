// Policzyc ile razy w rozwinieciu dwojkowym liczby wystapia dwie jedynki
#include <stdio.h>

int main(void){

	int x = 0xFFFFFFFF;
	int x2 = 99;
		asm volatile (
			".intel_syntax noprefix;"
				"mov eax, %1;"
				"xor ebx,ebx;"
				"petla:"
				"mov ecx, eax;"
				"shl eax;"
				"test ecx,0x80000000;"
				"jz a;"		    
				"test ecx,0x40000000;"
				"jz a;"
				"inc ebx;"
				"a: cmp ecx,0;"
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
