	.intel_syntax noprefix
	.globl main
	.text

main:
	mov eax, 10

	push eax
	call silnia ## silnia z 10
	add esp, 4 ## 1 pozycja zajeta przez wynik, wiec jedna zdejmuje

	push eax
	push offset msg
	call printf
	add esp,8

	mov eax,0
	ret

silnia:
	push ebp ## ebp wskaznik do danych w segmencie stosu
	mov ebp, esp
	push ecx
	push edx
	mov eax, [ebp+8]
	cmp eax,0
	jne dalej
	mov eax, 1
	pop edx
	pop ecx
	pop ebp
	ret
dalej:
	push eax
	dec eax
	push eax
	call silnia
	add esp, 4
	pop ecx
	mul ecx
	pop edx
	pop ecx
	pop ebp
	ret

	.data
	msg: .asciz "silnia=%d\n"
