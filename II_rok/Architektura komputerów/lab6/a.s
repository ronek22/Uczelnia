//       {2                              dla n=0
//f(n)=  {0                              dla n=1
//       {0                              dla n=2
//       {2*f(n-1)+f(n-2)-f(n-3)   w pozostałych przypadkach
//(1)Pierwszy argument przekazywany przez rejestr EBX, pozostałe argumenty przekazywane przez stos.
//(2)Wynik zwracany przez rejestr EAX.
//(3)Za uporządkowanie stosu odpowiada wywołujący funkcję.
//(4)Wywoływana funkcja musi zachować wszystkie rejesty(oprócz rejestru, w którym zwracany jest wynik).

.intel_syntax noprefix

	.globl main
	.text

main:
	mov ebx,5       #zmienna n
 //zerowanie rej z wynikiem
	xor eax,eax
//wywołanie funkcji
		push ebx			#przekazanie n przez stos
  	call f            	#wywołanie funkcji
  	add esp, 4			#czyszczenie stosu(wynik zostaje, wiec trzeba usunac)
//wypisanie wyniku
  	push eax
		push offset msg
		call printf
  	add esp,8

	ret
  	mov ebx,0
	ret


//funkcja f
f:
	push ebx
	xor eax,eax	           #zerowanie rejestru z wynikiem
//zapamietane rejestrow na stosie
	push ebp
	mov ebp, esp	   #zapamietanie miejsca stosu
	push ebx
	push ecx	#tymczasowy wynik
//wczytanie zmiennej n przez stos
	mov ebx, [ebp+8]

//przypadki dla n
	cmp ebx,0
	jne a1
	mov eax,2
	jmp koniec
	a1:

	cmp ebx,1
	jne a2
	mov eax,0
	jmp koniec
	a2:

	cmp ebx,2
	jne a3
	mov eax,0
	jmp koniec
	a3:

//2*f(n-1)
	push ebx #zapamietanie wartosci n
	sub ebx,1 #ustawienie ebx na n-1
	push eax #zapamietanie wyniku

	push ebx #parametr n-1 dla funkcji
	call f
	add esp, 4

	pop ecx				#do ecx wpisujemy ostatnia wartość na stosie czyli stary wynik eax
	add eax, eax 		#2*f wiec mnozymy x2
	add eax,ecx			#do wyniku dodajemy stary wynik
	pop ebx				#przywracamy stare n


//f(n-2)
	push ebx
	sub ebx,2
	push eax

	push ebx
	call f
	add esp, 4

	pop ecx
	add eax,ecx
	pop ebx


//-f(n-3)
	push ebx
	sub ebx,3
	push eax

	push ebx
	call f
	add esp, 4

	pop ecx
	sub ecx,eax         #od starego wyniku odejmujemy nowy (bo -f(n-3))
	mov eax,ecx
	pop ebx

koniec:
//przywracanie rejestrów
	pop ecx
	pop ebx
	pop ebp
	ret

	.data
	msg:	.asciz "Wynik = %d\n"
	.byte 0
