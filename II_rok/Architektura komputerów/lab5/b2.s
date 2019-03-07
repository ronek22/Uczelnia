.intel_syntax noprefix

	.text
	.globl main

main:
	mov eax, offset mesg
	call nasze_printf
	mov eax, 0
	ret

nasze_printf:
	push eax
	call printf
	add esp, 4 ## drukuje jedna wartosc wiec przesuwam o jedne pole
	ret

	.data
	mesg: .ascii "Hello, world %d\n"
	.byte 0
