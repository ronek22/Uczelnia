.intel_syntax noprefix
  .text
  .globl main

main: 
  mov eax,offset messg
  push eax
  call policz

  push eax
  mov eax,offset printf_arg1
  push eax 
  call printf

  add esp,8
exit:
  mov eax,0
  ret

policz:
  push esi
  mov esi,[esp+8]
  push ecx
  push edx
  # w ecx liczymy lokalny maks
  # w eax bedzie globalny maks
  # w dl bedzie powtarzajaca sie literka
  mov eax,0

  reset:
    mov ecx,0
    mov dl,[esi]
    cmpb dl,0
    je koniecstring
    inc esi
    cmpb dl,' '
    je reset

  sprawdzpowtorki:
    inc ecx
    cmpb dl,[esi] 
    jne koniecpowtorki
    inc esi
    jmp sprawdzpowtorki

  koniecpowtorki:
    cmp ecx,eax
    jle reset
    mov eax,ecx
    jmp reset

  koniecstring:
    pop edx
    pop ecx
    pop esi
    ret 4



  .data
messg:
  .asciz "ccca"
printf_arg1:
  .asciz "%i"
