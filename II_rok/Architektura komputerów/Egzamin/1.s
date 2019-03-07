.intel_syntax noprefix
  .text
  .globl main

main: 
  mov eax,offset messg
  push eax
  call znajdz

  push eax
  mov eax,offset printf_arg1
  push eax 
  call printf

  add esp,8
exit:
  mov eax,0
  ret

//do napisania znajdz
znajdz:
  mov eax,[esp+4]
  petla:
    cmpb [eax],'*'
    je gwiazdka
    cmpb [eax],0
    je koniecstring
    inc eax #adres 2 znaku itd
    jmp petla
  gwiazdka:
    sub eax,[esp+4]
    jmp out
  koniecstring:
    mov eax,-1
  out:
    ret 4
    

  .data
messg:
  .asciz "Przykladowy_tekst"
printf_arg1:
  .asciz "%i"
