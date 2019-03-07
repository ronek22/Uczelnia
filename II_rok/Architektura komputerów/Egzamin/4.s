.intel_syntax noprefix
  .text
  .globl main

main: 
  mov ebx,3
  push ebx
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
  push ecx
  push ebx

  cmp ebx,0
  jne rekurencja
  mov eax,[esp+12] ; # zwracam m
  jmp koniec

rekurencja:
  mov ecx,0 #przygotowujemy miejsce do liczenia wyniku aktualnej funkcji

  #przygotowanie arguntow do wywolania rekurencyjnego:
  dec ebx ; #zmniejsz n 
  mov eax,[esp+12] ; #pobierz m
  add ecx,eax ; #dodaj m do wyniku aktualnej funkcji; teraz ecx = m
  inc eax ; #zwieksz m
  push eax ; # i wrzuc zwiekszone m jako arg funkcji wylicz

  call policz
  add ecx,eax ; # do wyniku aktualnej funkcji dodajemy wynik wywolania rekurencyjnego
    # teraz ecx = m + wylicz(n-1,m+1)

  mov eax,ecx #wiec wrzucam ecx do returna (eax'a)

koniec:
  pop ebx
  pop ecx
  ret 4


  .data
printf_arg1:
  .asciz "%i"
