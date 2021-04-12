; 7.10.6 - Greatest common divisor

INCLUDE Irvine32.inc

; .386
;.model flat, stdcall
;.stack 4096
; ExitProcess proto, dwExitCode:dword

.data

val1 dword 344d
val2 dword 188d
gcd dword 1

.code
main PROC

call CalculateGCD

; invoke ExitProcess, 0
exit
main ENDP

CalculateGCD proc

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

; Smaller number is divided by 2, thus we determine the first possible greatest common divisor (quotient in EAX).
; At the same time we set a counter for the loop
L2:
mov edx, 0
mov ebx, 2
div ebx

mov ecx, eax

; This block checks divisors for the first given number
;ECX is used as a divisor and a counter for the loop
L3:
mov edx, 0
mov eax, val1
div ecx
cmp edx, 0; if there is no reminder in edx, then jump L4. 
je L4
L6:
loop L3

; If loop is finished and no LCD found, jump exit
jmp L7

;This block checks whether the divisor for the first number fits the second one
L4:
mov eax, val2
div ecx
cmp edx, 0; if no reminder in edx, jump L5
je L5
jmp L6

L5:
mov gcd, ecx

L7:

popfd
popad

ret
CalculateGCD endp

END main