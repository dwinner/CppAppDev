; 8.10.2 - 7
; create local variable that is an array of 9 dwords

; INCLUDE Irvine32.inc

.386
.model flat, stdcall
.stack 4096
ExitProcess proto, dwExitCode:dword

.data

arr dword 1, 2, 3, 4, 5, 6, 7, 8, 9
lengthOfArr = ($ - arr) / type arr

.code
main PROC

mov esi, offset arr
call AddThree

invoke ExitProcess, 0
; exit
main ENDP

; this procedure reserve space for an array in stack
;and fills it with an elements from the array in memory
AddThree proc
local pArray [lengthOfArr]: dword
mov ecx, lengthOfArr
add esp, 4
L1:
push [esi]
add esi, type arr
add esp, 8
loop L1
mov eax, pArray
mov ebx, [pArray+4]
ret
AddThree endp

END main