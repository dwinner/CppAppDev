; 8.11 - 10 - Show procedure parameters

; This program doesn t use INVOKE and PROTO directives

INCLUDE Irvine32.inc

; .386
;.model flat, stdcall
;.stack 4096
; ExitProcess proto, dwExitCode:dword

.data

prompt byte "Stack parameters:", 0
prompt1 byte "---------------------", 0
prompt3 byte "ebp + ", 0

.code
main PROC

mov edx, OFFSET prompt
call WriteString

call Crlf

mov edx, OFFSET prompt1
call WriteString

call Crlf

push 1234h
push 5000h
push 6543h
call MySample

call Crlf
call Crlf

; invoke ExitProcess, 0
exit
main ENDP

MySample proc
push ebp
mov ebp, esp
mov ecx, 3; number of parameters to display
mov edi, 8; address of first parameter
L1:
mov edx, OFFSET prompt3
call WriteString
mov eax, edi
call WriteDec
mov al, ':'
call WriteChar
mov ebx, ebp
add ebx, edi
mov eax, ebx
call WriteHex
mov al, '='
call WriteChar
mov eax, [ebx]
call WriteHex
call Crlf
add edi, type dword
loop L1
mov esp, ebp
pop ebp
ret
MySample endp

END main