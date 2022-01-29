; 7.10.2 - Extended substraction

INCLUDE Irvine32.inc

; .386
;.model flat, stdcall
;.stack 4096
; ExitProcess proto, dwExitCode:dword

.data

op2 BYTE 34h, 12h, 98h, 74h, 06h, 0A4h, 0B2h, 0A2h
op1 BYTE 02h, 45h, 23h, 00h, 00h, 87h, 10h, 80h
sum BYTE 9 dup(0)

.code
main PROC

call Extended_Sub

call ShowNumber

call Crlf

; invoke ExitProcess, 0
exit
main ENDP

Extended_Sub PROC

pushad

mov esi, OFFSET op1
mov edi, OFFSET op2
mov ebx, OFFSET sum
mov ecx, LENGTHOF op1

clc

L1:
mov al, [esi]
sbb al, [edi]
pushfd
mov [ebx], al
inc esi
inc edi
inc ebx
popfd
loop L1

mov byte ptr [ebx], 0
sbb byte ptr [ebx], 0
popad

ret
Extended_Sub ENDP

ShowNumber PROC

pushad

mov esi, offset sum + lengthof sum - 1
mov ecx, lengthof sum
mov ebx, TYPE BYTE
L2 :
mov al, [esi]
call WriteHexB
dec esi
loop L2

popad

ret
ShowNumber ENDP

END main