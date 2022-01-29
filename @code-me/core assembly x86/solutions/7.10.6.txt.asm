; 7.10.6 - Lowest common divisor

INCLUDE Irvine32.inc

; .386
;.model flat, stdcall
;.stack 4096
; ExitProcess proto, dwExitCode:dword

.data

val1 dword 26d
val2 dword 169d
lcd dword 0

.code
main PROC

call CalculateLCD

; invoke ExitProcess, 0
exit
main ENDP

CalculateLCD proc

pushad
pushfd

; This block calculates which of two given numbers is the bigger one
mov eax, val1
sub eax, val2
cmp eax, 0
jg L1
mov eax, val1
jmp L2
L1:
mov eax, val2

; Smaller number is divided by 2, thus we determine the upper limit of the lowest common divisor.
; For example, the given number is 25, division by 2 gives 12.
; Obviously divisor 12 + 1 = 13 cannot be used as a common divisor
L2:
mov edx, 0
mov ebx, 2
div ebx
mov ecx, eax

;This block checks divisors for the first given number
L3:
mov edx, 0
mov eax, val1
div ebx
cmp edx, 0; if there is no reminder in edx, then jump L4. Otherwise inc ebx and loop
je L4
L6:
inc ebx
loop L3

; If loop is finished and no LCD found, jump exit
jmp L7

;This block checks whether the divisor for the first number fits the second one
L4:
mov eax, val2
div ebx
cmp edx, 0; if no reminder in edx, jump L5
je L5
jmp L6

L5:
mov lcd, ebx

L7:

popfd
popad

ret
CalculateLCD endp

END main