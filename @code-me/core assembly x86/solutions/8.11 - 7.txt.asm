; 8.11 - 7 - Greatest common divisor

; This program is based on Euclid s algorithm.
; Let s suppose there are two numbers A and B.If A and B have GCD,
; then A - B = C can also be divided by the same GCD.
; How to implement this idea to calculation of GDP ?
; Let s suppose that A is greater than B.Substraction A - B gives C.
; Now we have numbers B and C.Now substraction is performed one more time.
; ................
; Substraction is performed until both numbers are equal.This is GCD.

INCLUDE Irvine32.inc

; .386
; .model flat, stdcall
; .stack 4096
; ExitProcess proto, dwExitCode:dword

.data

prompt byte "Please enter first number: ", 0
prompt1 byte "Please enter second number: ", 0
prompt2 byte "Greatest common divisor is ", 0

.code
main PROC

; Input of two numbers. 1st is placed in ebx, 2nd in eax.

mov edx, OFFSET prompt
call WriteString

call ReadDec
mov ebx, eax

call Crlf

mov edx, OFFSET prompt1
call WriteString

call ReadDec

call Crlf

;Greater number is placed in eax, smaller in ebx

cmp eax, ebx
ja L3
xchg eax, ebx

L3:
call gcd

mov edx, OFFSET prompt2
call WriteString

call WriteDec

call Crlf
call Crlf

; invoke ExitProcess, 0
exit
main ENDP

gcd proc
sub eax, ebx
cmp eax, ebx; if numbers are equal, this is GCD
je L1
cmp eax, ebx; eax should always contain greater number
ja L2
xchg eax, ebx
L2:
call gcd
L1:
ret
gcd endp

END main