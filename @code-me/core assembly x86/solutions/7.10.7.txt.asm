; 7.10.7 - Multiplication using only shifting and addition.

; NB!!!Only multipliers less than 65536dec can be used for this program.

; In order to understand how this program works,
;let s consider multiplication of 2 binary numbers:
; 0101010b
; 1010101b

; First step : 0101010b x 1b = 0101010b
; Second step : 0101010b x 0b = 0b
; Third step : 0101010b x 100b = 0101010 00b
; .........
; Last step : 0101010b x 1000000b = 0101010 000000b
; Product of multiplication is a sum of all steps : 0101010b + 0b + 0101010 00b + ...

;Implementation:
;Multiplier is moved in EAX
; Multiplicand is moved in EBX,
;shr ebx, if CF=1, then shl eax.

INCLUDE Irvine32.inc

; .386
; .model flat, stdcall
; .stack 4096
; ExitProcess proto, dwExitCode:dword

.data

val1 dword 65535d
val2 dword 65535d
product dword 0

.code
main PROC

call MulByAddition

; invoke ExitProcess, 0
exit
main ENDP

MulByAddition proc

pushfd
pushad

mov edi, 0; counter for SHL multiplier
mov ebx, val1; multiplicand

mov ecx, 32

L1:
push ecx
mov ecx, edi
clc; set CF = 0 before performing SHR opration
shr ebx, 1; multiplicand shifted to the right, if CF=1, then SHL eax
jnc L2
mov eax, val2; multiplier
shl eax, cl
add product, eax
L2:
inc edi
pop ecx
loop L1

popad
popfd

ret
MulByAddition endp

END main