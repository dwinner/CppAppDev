; 6.11.2 - 2

INCLUDE Irvine32.inc

; .386
;.model flat, stdcall
; .stack 4096
; ExitProcess proto, dwExitCode:dword

.data

j = -15
k = 15
array1 sdword -3, 10, 24, -15, 33, 10, -44, -2, -1, 0, 5, 6
Array1Size = ($ - array1)/type array1
array2 sdword Array1Size dup(0)

.code
main proc

call SumRange

exit
main endp

SumRange proc
mov eax, 0
mov edi, offset array2
mov esi, offset array1
mov ecx, lengthof array1
L1:
mov ebx, j
mov edx, k
cmp [esi], ebx
jl L2
cmp [esi], edx
jg L2
add eax, [esi]
mov ebx, [esi]
mov [edi], ebx
L2:
add esi, type array1
add edi, type array2
loop L1
ret
SumRange endp

; invoke ExitProcess, 0
end main