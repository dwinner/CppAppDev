; 8.11 - 10 - Show procedure parameters

INCLUDE Irvine32.inc

; .386
;.model flat, stdcall
;.stack 4096
; ExitProcess proto, dwExitCode:dword

MySample proto,
first : dword,
second : dword,
third : dword

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

invoke MySample, 1234h, 5000h, 6543h

call Crlf
call Crlf

; invoke ExitProcess, 0
exit
main ENDP

MySample proc,
first:dword,
second:dword,
third:dword
paramCount = 3
call ShowParams
mov eax, first
mov eax, second
mov eax, third
ret
MySample endp

ShowParams proc
mov ecx, paramCount; number of parameters to display
mov edi, 8; address of first parameter
L1 :
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
ret
ShowParams endp

END main