; 9.10 - 9 - Binary search(OPTIMIZED)

;Improvements:

; LOCAL MID can be removed completely without affecting any register or command.
; EBX can be liberated adding pArray directly to ESI.
; EDI can be liberated comparing content of EDX directly to searchVal.

; EBX is used as substituent for LOCAL FIRST.
;ECX is used as substituent for LOCAL LAST.

INCLUDE Irvine32.inc

BinarySearch proto,
pArray:PTR DWORD,
Count : DWORD,
searchVal : DWORD

; .386
;.model flat, stdcall
;.stack 4096
; ExitProcess proto, dwExitCode:dword

.data

array1 dword 1,3,4,5,6,7,8,9

.code
main PROC

invoke BinarySearch, addr array1, lengthof array1, 8

; invoke ExitProcess, 0
exit
main ENDP

BinarySearch PROC USES ebx ecx edx esi,
pArray:PTR DWORD,
Count : DWORD,
searchVal : DWORD

mov ebx, 0
mov eax, Count
dec eax
mov ecx, eax
L1:
mov eax, ebx
cmp eax, ecx
jg L5
mov eax, ecx
add eax, ebx
shr eax, 1
mov esi, eax
shl esi, 2
add esi, pArray
mov edx, [esi]
cmp edx, searchVal
jge L2
inc eax
mov ebx, eax
jmp L1
L2:
jle L9
dec eax
mov ecx, eax
jmp L1
L5 :
mov eax, -1
L9 : 
ret
BinarySearch ENDP

END main