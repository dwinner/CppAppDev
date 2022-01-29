; 11.8 - 11 - Linked List

; This program works in a following manner : procedure HeapAlloc first obtains a pointer to heap storage.
; This pointer is passed to esi.First dword cell of heap storage is filled with some arbitrary number
; (here the content of ECX), second cell is filled with the address of the third cell, which in its turn
; contains next arbitrary number.

; (1)ecx1--address2--->(2)ecx2--address3--->(3)ecx3--address4--->... ...(X)ecxX--addressY

;This linked list is ended with NULL tail node.

INCLUDE Irvine32.inc

TotalNodeCount = 15

.data

hHeap HANDLE ? ; heap handle
pArray DWORD ?

.code
main PROC

invoke GetProcessHeap
mov hHeap, eax

INVOKE HeapAlloc, hHeap, HEAP_ZERO_MEMORY, 1000
mov pArray, eax

mov esi, pArray
mov ecx, TotalNodeCount
L1:
mov[esi], ecx
add esi, type dword
mov eax, esi
mov[esi], eax
add esi, type dword
loop L1
mov esi, 0; tail node NULL

mov esi, pArray
mov ecx, TotalNodeCount
L2:
mov eax, [esi]
call WriteDec
mov al, ':'
call WriteChar
add esi, type dword
mov eax, [esi]
call WriteHex
call Crlf
add esi, type dword
loop L2
mov eax, [esi]
call WriteDec

call Crlf

exit
main ENDP
END main