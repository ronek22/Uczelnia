.intel_syntax noprefix
  .globl main
  .text

main:
mov eax,offset expr
lea ebx,[eax]
xor eax,eax
xor ecx,ecx
xor edx,edx

loop:
  mov al,[ebx]
  or al,al
  jz print
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

print:
push edx
call printf


data:
mesg: .ascii "%d\n"
expr: .ascii "((x))"
