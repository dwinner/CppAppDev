; 10.8 - 5 - mReadInt Macro(version B)

; This macro reads some integer(X) and its type(eltType, 0 for word or 1 for dword),
; and then saves the integer to corresponding memory operand.

; if, elseif combination is used.

INCLUDE Irvine32.inc
INCLUDE Macros.inc

mReadInt Macro Z, eltType, Xword, Ydword
mov eax, Z
if (eltType eq 0)
mov Xword, ax
elseif(eltType eq 1)
mov Ydword, eax
endif
endm

; .386
; .model flat, stdcall
; .stack 4096
; ExitProcess proto, dwExitCode:dword

.data

argument1 word 0
argument2 dword 0

.code
main PROC

mReadInt 12345678h, 1, argument1, argument2

; invoke ExitProcess, 0
exit
main ENDP

END main