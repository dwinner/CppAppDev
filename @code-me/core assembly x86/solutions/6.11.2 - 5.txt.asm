; 6.11.2 - 5 - Table - driven selection - Boolean calculator

INCLUDE Irvine32.inc

; .386
; .model flat, stdcall
;.stack 4096
; ExitProcess proto, dwExitCode:dword

.data
CaseTable BYTE 'A'
DWORD Process_A
DWORD Process_AA
EntrySize = ($ - CaseTable)
BYTE 'B'
DWORD Process_B
DWORD Process_BB
BYTE 'C'
DWORD Process_C
DWORD Process_CC
BYTE 'D'
DWORD Process_D
DWORD Process_DD
NumberOfEntries = ($ - CaseTable) / EntrySize

prompt BYTE "Press capital A for AND, B for OR, C for NOT, D for XOR, E for exit: ", 0

msgA BYTE "AND function: ", 0
msgB BYTE "OR function: ", 0
msgC BYTE "NOT function: ", 0
msgD BYTE "XOR function: ", 0

msgE BYTE "Bye-bye: ", 0

.code

main PROC
L5:
mov edx, OFFSET prompt
call WriteString
call ReadChar
cmp al, 'E'
je L20
mov ebx, OFFSET CaseTable

L1 :
cmp al, [ebx]
jne L2
call NEAR PTR[ebx + 1]
call WriteString
call Crlf
call Crlf
call NEAR PTR[ebx + 5]
jmp L5
L2 :
inc esi
add ebx, EntrySize
jmp L1

L20:
mov edx, OFFSET msgE
call WriteString
call Crlf

exit
main ENDP

Process_A PROC
mov edx, OFFSET msgA
ret
Process_A ENDP
Process_AA PROC
ret
Process_AA ENDP

Process_B PROC
mov edx, OFFSET msgB
ret
Process_B ENDP
Process_BB PROC
ret
Process_BB ENDP

Process_C PROC
mov edx, OFFSET msgC
ret
Process_C ENDP
Process_CC PROC
ret
Process_CC ENDP

Process_D PROC
mov edx, OFFSET msgD
ret
Process_D ENDP
Process_DD PROC
ret
Process_DD ENDP

; invoke ExitProcess, 0
END main