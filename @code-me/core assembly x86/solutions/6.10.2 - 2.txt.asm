; AddVariables.asm - Chapter 3 example.

.386
.model flat,stdcall
.stack 4096
ExitProcess proto,dwExitCode:dword

.data
firstval dword 10101001110010101100110010011001b

.code
main proc

mov eax, 0
mov ebx, 0
mov esi, offset firstval
mov ax, word ptr [esi]
add esi, type word
mov bx, word ptr [esi]
xor ah, al
xor bl, ah
xor bh, bl

	invoke ExitProcess,0
main endp
end main