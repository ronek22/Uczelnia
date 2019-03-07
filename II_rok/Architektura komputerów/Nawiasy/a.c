#include <stdio.h>

int main(){
char *s ="((abc) ∗ (ab+(ab)∗(cdx7)))−xxab((()))c";
int x,y;
// [pq][^a]+a

asm volatile (
	".intel_syntax noprefix;"
	"mov eax,%1;"
	"lea ebx,[eax];" //adres od stringa do ebx
	"xor eax,eax;" // ebx - wskaznik na string,ecx - currentDepth, edx - MaxDepth
	"xor ecx,ecx;"
	"xor edx,edx;"
	"loop:"
		"mov al,[ebx];"
		"or al, al;" // sprawdzanie czy koniec slowa
		"jz print;"  // jesli koniec skocz do print
    "cmp al, '(';"
    "je increase;"
    "cmp al,')';"
    "je decrease;"
    "inc ebx;" // nastepny znak
    "jmp loop;"

  "increase:"
  "inc ecx; cmp edx,ecx;js changeMax;inc ebx;jmp loop;"

  "changeMax:"
  "mov edx,ecx; inc ebx; jmp loop;"

  "decrease:"
  "dec ecx;inc ebx;jmp loop;"
  "print:"
	"mov %0, edx;"
	".att_syntax prefix;"
	: "=r" (x)
	: "r" (s)
	: "eax", "ebx", "ecx", "edx"
);

  printf("%d", x);
	return 0;

}
