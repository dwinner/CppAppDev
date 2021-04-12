; 9.9.2 - 4 - cmpsw for 2 arrays of words

; 2 arrays are compared using the following commands:
; mov ecx, lengthof array
; repe cmpsw - comparison is finished when ecx = 0 or unmatching pair is found.

; The problem is when the unmatching pair is in the end of array, anyway ecx = 0.
;This problem can be resolved by 2 methods:
; either incrementing ecx.
; or adding 0 at the end of each array.

INCLUDE Irvine32.inc

; .386
; .model flat, stdcall
; .stack 4096
; ExitProcess proto, dwExitCode:dword

.data

sourcew byte 1, 2, 3, 4
targetw byte 1, 7, 3, 5

.code
main PROC

call unmatch

; invoke ExitProcess, 0
exit
main ENDP

unmatch proc uses esi edi ecx,

mov esi, OFFSET sourcew
mov edi, OFFSET targetw
cld
mov ecx, LENGTHOF sourcew
inc ecx
repe cmpsb

cmp ecx, 0
je L1
dec ecx
mov eax, lengthof targetw
sub eax, ecx
dec eax; eax will contain the index of unmatching element
mov edi, OFFSET targetw
mov bl, [edi + eax*type targetw]; ebx will contain the value of unmatching element

L1 :
ret
unmatch endp

END main