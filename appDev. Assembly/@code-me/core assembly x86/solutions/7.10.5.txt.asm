; 7.10.5 - Sieve of Eratosthenes

; In order to generate all prime numbers in a given limit,
; each number from 0 to(given limit) is successively
; tested by division on a given set of starting prime numbers(here named divisors 2, 3, 5, 7, etc)

; If actual number can be divided by 2, the program skips all other divisors
; and switches to the next number in range of tested values.
; Otherwise, next divisor is used.
; If actual number can not be divided on a last divisor,
; then it is considered as a prime number.

; In this program the lower limit of range is the last divisor + 1.
; So, divisors and occasional composite numbers between them are not included in range of tested values.

INCLUDE Irvine32.inc

; .386
; .model flat, stdcall
; .stack 4096
; ExitProcess proto, dwExitCode:dword

.data

prompt byte "This program generates all prime numbers in a given limit", 0
prompt1 byte "Please enter the upper limit: ", 0

divisor word 2, 3, 5, 7, 11
divisor_size = ($ - divisor)
divisor_length = divisor_size / type divisor
prime_numbers_length = 220; this value can include all prime numbers between 0 and 1000
prime_numbers word prime_numbers_length dup(0)

.code
main PROC

mov edx, OFFSET prompt
call WriteString
call Crlf

mov edx, OFFSET prompt1
call WriteString

call ReadDec; reads the upper limit of range
call Crlf

mov ecx, eax; upper limit is moved to counter
sub cx, divisor + divisor_size - type divisor; adjustement of counter
; if no adjustment, then range of tested values will be(upper limit + last divisor)

mov eax, 0
mov ax, divisor + divisor_size - type divisor
inc ax; first value to be tested
mov ebx, 0
mov esi, offset prime_numbers

L1:
mov edi, offset divisor
L5:
mov edx, 0; set edx to 0 before the division, otherwise overflow
push ax; save the value in ax before division
mov bx, [edi]
div bx
cmp dx, 0; if remainder is not 0, then L2, check next divisor
jne L2
pop ax; restore the value in ax after division
L4:
inc ax
loop L1

jmp L9; when all the numbers are tested, jump to L9

L2:
pop ax
cmp bx, divisor + divisor_size - type divisor; if not last divisor, then L3
jb L3
mov [esi], ax
add esi, type prime_numbers
jmp L4

L3:
add edi, type divisor
jmp L5

; This block prints divisors (prime numbers by itself) and all the generated prime numbers.
; An array which stores prime numbers, has fixed size(prime_numbers_length).
; If number of prime numbers is lower, than the size of the array,
; upper elements of the array will be filled with 0.
; The program exludes all 0, using CMP 0

L9:
mov ecx, divisor_length
mov edi, offset divisor

L10:
mov eax, 0
mov ax, [edi]
call WriteDec
mov al, ','
call WriteChar
mov al, 20h
call WriteChar
add edi, type divisor
loop L10

mov ecx, prime_numbers_length
mov edi, offset prime_numbers

L11 :
mov eax, 0
mov ax, [edi]
cmp eax, 0
je L12
call WriteDec
mov al, ','
call WriteChar
mov al, 20h
call WriteChar
add edi, type prime_numbers
loop L11

L12 :

call Crlf
call Crlf

; invoke ExitProcess, 0
exit
main ENDP

END main