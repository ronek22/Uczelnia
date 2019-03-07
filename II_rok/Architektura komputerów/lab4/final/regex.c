#include <stdio.h>

int main(){
char *s = "";
int x,y;
// [pq][^a]+a

asm volatile (
	".intel_syntax noprefix;"
	"mov eax,%2;"
	"lea ebx,[eax];" //adres od stringa do ebx
	"xor eax,eax;" // ebx - wskaznik na string,ecx - dlugosc, edx - pozycja
	"xor ecx,ecx;"
	"xor edx,edx;"
	"loop:"
		"mov al,[ebx];"
		"or al, al;" // sprawdzanie czy koniec slowa
		"jz print;"  // jesli koniec skocz do print
		"inc dl;" // zwieksz pozycje
		"cmp ah, 0;" // jesli ah != 0 skocz do notA
		"jne notA;"
		"cmp al,'q';"
		"je PQ;"
		"cmp al,'p';"
		"je PQ;"
		"jmp koniec;"
		"notA:cmp al,'a';"
		"je lastA;"
		"inc ecx;"
		"koniec:"
			"inc ebx;" // nastepny znak
			"jmp loop;"
		"lastA: cmp ecx, 1; je zerowanie;inc ecx; jmp print;"
		// zerwowanie licznikow, gdy znalazl a zaraz po p lub q
		"zerowanie:xor ecx,ecx; xor ah,ah; mov dh,1; jmp koniec;"
		"PQ: mov dh, dl;inc ah; inc ecx;jmp koniec;"
	"print:"
	"cmp ecx,3;"
	"js wyjscie;"
	"shr edx,8;" // przesuniecie edx o 8 w prawo, zeby wartosc ostatniego indeksu zostala usunieta
	"dec edx;" // dlatego, ze licznik liczyl od 1 do n
	"jmp end;"

	"wyjscie:"
	"xor edx,edx;xor ecx,ecx;"
	"mov %0, edx;"
	"mov %1, ecx;"

	"end:"
	"mov %0, edx;"
	"mov %1, ecx;"


	".att_syntax prefix;"
	: "=r" (x), "=r" (y)
	: "r" (s)
	: "eax", "ebx", "ecx", "edx"
);

//	if(y > 3){
	printf("Pozycja: %d, dlugosc = %d\n", x,y);
//	} else
//		printf("Nie znaleziono patternu\n");
	return 0;

}
