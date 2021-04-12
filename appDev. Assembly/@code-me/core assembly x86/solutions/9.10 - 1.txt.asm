; 9.10 - 1 - Improved Str_cpy procedure
;N - maximal number of symbols to be copied

INCLUDE Irvine32.inc

Str_copyN proto,
source:PTR BYTE,
target : PTR BYTE,
N : dword

; .386
; .model flat, stdcall
; .stack 4096
; ExitProcess proto, dwExitCode:dword

.data

array1 byte "abcdefghigh", 0
array1length = ($ - array1)
array2 byte array1length dup(0)

.code
main PROC

INVOKE Str_copyN, ADDR array1, ADDR array2, 5

mov edx, OFFSET array1
call WriteString
call Crlf
mov edx, OFFSET array2
call WriteString
call Crlf

; invoke ExitProcess, 0
exit
main ENDP

Str_copyN PROC USES eax ecx esi edi,
source:PTR BYTE, 
target : PTR BYTE,
N:dword

INVOKE Str_length, source
cmp eax, N
jb L1
mov ecx, N
mov esi, source
mov edi, target
cld
rep movsb
mov byte ptr [edi], 0
L1:
ret
Str_copyN ENDP

END main