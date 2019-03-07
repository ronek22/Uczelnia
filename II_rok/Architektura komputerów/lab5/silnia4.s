// elo 320
// 221
	.intel_syntax noprefix
	.globl main
	.text

main:
	//dupa
	mov ecx, 4 #dupa
	call silnia

	push eax
	push offset msg
	call printf
	add esp,8

	mov eax,0
	ret

silnia:
	push ecx ##n silnia
	push edx
	cmp ecx, 0
	jne dalej
	mov eax,1
	pop edx
	pop ecx
	ret
dalej:
	mov edx,ecx
	dec ecx
	call silnia
	mul edx
	pop edx
	pop ecx
	ret

	.data
	msg: .asciz "silnia=%d\n"
