.intel_syntax noprefix
  .globl _start
  .text

_start:
mov eax, [esp+8] #pobranie do rejestru argumentu
lea ebx,[eax]
xor eax,eax
xor ecx,ecx
xor edx,edx


loop:
  mov al,byte ptr [ebx]
  or al,al
  jz result #nawiasy obliczone
  cmp al,'('
  je increase
  cmp al,')'
  je decrease
  inc ebx
  jmp loop

increase:
inc ecx
cmp edx,ecx
js changeMax
inc ebx
jmp loop

changeMax:
mov edx,ecx
inc ebx
jmp loop

decrease:
dec ecx
inc ebx
jmp loop

result:
//przeniesienie wyniku do eax, ze wzgledu na wyswietlanie
mov eax, edx # wynik byl w edx, teraz przeniesiony do eax

base:
mov ecx,10 # podstawa mnozenia
xor ebx, ebx # ebx licznik znakow

divide:
// edx - reszta z dzielenie
  xor edx, edx
// dzielenie eax przez ecx, czyli liczby przez 10 (123/10: eax = 12, edx = 3; 12/10: eax = 1, edx = 2, 1/10: eax = 0, edx = 1)
  div ecx
// wrzucenie edx na stos (najpierw 3, potem 2, potem 1)
  push edx
// zwiekszenie licznika wystapien
  inc ebx
// spr czy eax=0
  test eax, eax
// jesli nie jest 0, kontynuuj dzielenie
  jnz divide

to_ASCII:
// sciagam ze stosu ostatnie cyfre liczby i zapisuje w eax
  pop eax
// doanie do eax '0', zeby dzialalo w ASCII
  add eax, '0'
// wrzucenie cyfry do bufora zapisu
  mov [sum], eax
// zmniejszenie licznika o 1
  dec ebx
// spr czy licznik = 0, jesli tak to drukuj
  cmp ebx, 0
  je print

  pop eax
  add eax, '0'
  mov [sum+1], eax
  dec ebx
  cmp ebx, 0
  je print

  pop eax
  add eax, '0'
  mov [sum+2], eax
  dec ebx

print:
// edx-dlug napisu, max 3 cyfry(0-999)
// ecx to bufor wypisu
mov eax, 4
mov	ebx, 1
mov	ecx, offset sum
mov	edx, 3 # dlugosc napisu
int	0x80

//wypisanie konca linii
mov eax,4
mov ebx,1
mov ecx, offset msg
mov edx,1
int 0x80

//return 0
mov eax,1
mov ebx,0
int 0x80



.data
msg: .asciz "\n"
sum: .byte 0,0,0,0
