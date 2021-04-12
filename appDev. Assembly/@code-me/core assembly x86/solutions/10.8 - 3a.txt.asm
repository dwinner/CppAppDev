; 10.8 - 3 - mWritestringAttr Macro

; NB!Registers, immediate and memory values are allowed;

INCLUDE Irvine32.inc
INCLUDE Macros.inc

mMove32 Macro X, Y
push eax
mov eax, X
mov Y, eax
pop eax
endm

; .386
; .model flat, stdcall
; .stack 4096
; ExitProcess proto, dwExitCode:dword

.data

source dword 12345678h
destination dword 0

.code
main PROC

mMove32 11335577h, destination

mov eax, 11223344h
mMove32 eax, destination

; invoke ExitProcess, 0
exit
main ENDP

END main