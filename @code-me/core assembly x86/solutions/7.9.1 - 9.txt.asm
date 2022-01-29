; 7.9.1 - 9 - extended substraction
; the maint trick of this program is the resulting value of substraction
; if it is negative, then carry flag is set
; the value of carry flag can be checked by JC or just by substracting the carry flag from some control register

; INCLUDE Irvine32.inc

.386
.model flat, stdcall
.stack 4096
ExitProcess proto, dwExitCode:dword

.data

val1 DWORD 362047A1h
val2 DWORD 4A2630B2h
result DWORD 0
minus dword 0; if outcome is ffffffffh, then value is negative

.code
main PROC

call program

invoke ExitProcess, 0
main ENDP

program proc
pushad

mov ebx, 0; control register
mov ecx, type dword
mov esi, offset val1
mov edi, offset val2
mov edx, offset result
clc

top :
mov al, BYTE PTR[esi]
sbb al, BYTE PTR[edi]
pushfd
mov BYTE PTR[edx], al
inc esi
inc edi
inc edx
popfd
loop top

; jc 'to some label'

sbb ebx, 0; if carry is set, then its value is substracted from ebx
mov minus, ebx

popad

ret
program endp

; exit

END main