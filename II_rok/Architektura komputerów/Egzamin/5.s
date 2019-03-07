.intel_syntax noprefix
  .text
  .globl main

main: 
  mov eax,offset messg
  push eax
  call policz
  add esp,4

  push eax
  mov eax,offset printf_arg1
  push eax 
  call printf
  add esp,8
exit:
  mov eax,0
  ret

//do napisania znajdz
policz:
	xor eax,eax
	push ebx # tu bedzie string
	mov ebx,[esp+8]
spr:
	cmpb [ebx],0
	je koniec
	cmpb [ebx],'A'
	jl next
	cmpb [ebx],'Z'
	jg next
	inc eax
	inc ebx
	jmp spr
next:
	inc ebx
	jmp spr
koniec:
	pop ebx
	ret

  .data
messg:
  .asciz "ALOHPrzykladowy_teKst_zAdaniA"
printf_arg1:
  .asciz "%i"
