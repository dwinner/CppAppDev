; 7.10.1

INCLUDE Irvine32.inc

; .386
; .model flat, stdcall
; .stack 4096
; ExitProcess proto, dwExitCode:dword

.data

DECIMAL_OFFSET = 5
decimal_one BYTE "100123456789765", 0
decimal_one_size = ($ - decimal_one) -1

.code
main PROC

mov ebx, DECIMAL_OFFSET
mov ecx, decimal_one_size

mov edx, OFFSET decimal_one
sub ecx, ebx
L1:
mov al, [edx]
call WriteChar
inc edx
loop L1

mov al, '.'
call WriteChar

mov edx, OFFSET decimal_one + decimal_one_size - DECIMAL_OFFSET
mov ecx, ebx
L2:
mov al, [edx]
call WriteChar
inc edx
loop L2

call Crlf

; invoke ExitProcess, 0
exit
main ENDP

END main