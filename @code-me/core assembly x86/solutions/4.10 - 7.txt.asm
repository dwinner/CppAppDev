; AddVariables.asm - Chapter 3 example.

.386
.model flat, stdcall
.stack 4096
ExitProcess proto, dwExitCode:dword

.data

; p. 136 Programming exercises, ex. 7 - Copy a String in Reverse Order

source BYTE "This is the source string", 0
space dword 0
target BYTE SIZEOF source DUP('#')

.code
main PROC

mov esi, offset source + sizeof source - type source
mov edi, offset target
mov ecx, sizeof source
L1:
mov al, [esi]
mov [edi], al
dec esi
inc edi
loop L1

invoke ExitProcess,0
main endp
end main