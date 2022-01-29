; 8.11 - 4  - FindThrees Procedure (UNOPTIMIZED)

INCLUDE Irvine32.inc

; .386
;.model flat, stdcall
;.stack 4096
; ExitProcess proto, dwExitCode:dword

.data

array1 dword 1,2,3,3,3,3,4,3,2,3,3,2,1

.code
main PROC

push offset array1
push lengthof array1

call FindThrees

call Crlf
call Crlf

; invoke ExitProcess, 0
exit
main ENDP

FindThrees proc
push ebp
mov ebp, esp
mov esi, [ebp+12]
mov ecx, [ebp+8]
mov ebx, 0
L1:
mov eax, [esi]
cmp eax, 3
jne L2
mov ebx, [esi+type array1]
cmp ebx, 3
jne L2
mov edx, [esi + 2*type array1]
cmp edx, 3
je L4
L2:
add esi, type array1
loop L1
L4:
mov eax, [ebp + 8]
cmp ecx, 0
je L5
sub eax, ecx
call WriteDec
jmp L6
L5:
mov eax, 0
call WriteDec
L6:
mov esp, ebp
pop ebp
ret
FindThrees endp

END main