.intel_syntax noprefix
  .globl main
  .text

main:
pop eax #return address
pop eax #return argc
pop eax #return argv
mov eax,[eax+4] #argv[1]
sub esp,12 #return stack to right position
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
mov edx, offset mesg
push edx
call printf
add esp,8
ret
mov edx,0
ret

.data
mesg: .asciz "%d\n"
