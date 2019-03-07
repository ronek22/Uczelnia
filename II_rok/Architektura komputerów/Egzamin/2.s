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
//  push esi #wrzucam na stos esi, po to aby zostalo skasowano po wykonaniu funkcji
  mov esi,[esp+4]  #do esi przypusuje argument
  mov eax,0
  spacjousuwacz:
    inc esi
    cmpb [esi-1],' '
    je spacjousuwacz
    cmpb [esi-1],0
    je koniecstring
    inc eax
    jmp wyraz
  wyraz:
	add esi,1
    cmpb [esi-1],' '
    je spacjousuwacz
    cmpb [esi-1],0
    je koniecstring
//    inc esi
    jmp wyraz
  koniecstring:
//    pop esi
    ret 4


  .data
messg:
  .asciz "Przykladab trescbc zadadd aloha  "
printf_arg1:
  .asciz "%i"
