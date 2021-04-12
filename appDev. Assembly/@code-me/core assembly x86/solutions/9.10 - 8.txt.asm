; 9.10 - 8 - Bubble sort - exchange flag

INCLUDE Irvine32.inc

BubbleSort proto,
pArray:PTR DWORD,
Count : DWORD

; .386
;.model flat, stdcall
;.stack 4096
; ExitProcess proto, dwExitCode:dword

.data

array1 dword 1,2,3,4,5,6,7,9,8,0

.code
main PROC

invoke BubbleSort, addr array1, lengthof array1

mov esi, offset array1
mov ecx, lengthof array1
L10:
mov eax, [esi]
call WriteDec
mov al, ' '
call WriteChar
add esi, 4
loop L10

call Crlf
call Crlf

; invoke ExitProcess, 0
exit
main ENDP

BubbleSort PROC USES eax ecx esi,
pArray:PTR DWORD,
Count : DWORD
mov ecx, Count
dec ecx
mov ebx, 0; exchange flag
L1 : push ecx
mov esi, pArray
L2 : mov eax, [esi]
cmp[esi + 4], eax
jg L3
xchg eax, [esi + 4]
mov ebx, 1
mov[esi], eax
L3 : add esi, 4
loop L2
pop ecx
cmp ebx, 0
jz L4; exit loop if exchange flag is 0
loop L1
L4 : ret
BubbleSort ENDP

END main