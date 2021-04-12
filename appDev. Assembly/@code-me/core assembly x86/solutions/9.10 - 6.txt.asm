; 9.10 - 6 - character frequency table

; Input to the procedure should be a pointer to a string
; and a pointer to an array of 256 doublewords initialized
; to all zeros.Each array position is indexed by its
; corresponding ASCII code.When the procedure returns,
; each entry in the array contains a count of how many
; times the corresponding character occurred in the string.

; The subtlety of this program :
; Target is a byte array;
; Frequency table is a dword array.
; For exemple, 'A' = 41h.If frequency table is ordinary byte array,
; then 'A' should be placed in 41st byte[offset frequency + 41h].
; Since frequency table is a dword array, the hexadecimal value of
; corresponding symbol should be multiplyed by 4 [offset frequency + 4*41h].

INCLUDE Irvine32.inc

Get_frequencies proto,
target: ptr byte,
freqTable : dword

; .386
; .model flat, stdcall
; .stack 4096
; ExitProcess proto, dwExitCode:dword

.data

array1 BYTE "`123456     [poiuytrewasdf     ,mnbvcxz`123   0-';lkjhgf    bnm,.", 0
frequency DWORD 256 DUP(0)

.code
main PROC

INVOKE Get_frequencies, ADDR array1, ADDR frequency

mov ecx, 256
mov edi, offset frequency
L3:
mov eax, [edi]
; add eax, 30h
call WriteDec
mov al, ' '
call WriteChar
add edi, type frequency
loop L3

call Crlf

; invoke ExitProcess, 0
exit
main ENDP

Get_frequencies proc,
target: ptr byte,
freqTable:dword
mov esi, target
L1 :
mov edi, freqTable
mov eax, 0
mov al, [esi]
cmp al, 0
je L2
shl eax, 2; multiply by 4 the value in eax to fit dword array
add edi, eax; offset of current symbol in dword array
mov ebx, [edi]; compiler doesn t accept expression inc [edi]
inc ebx
mov[edi], ebx
inc esi
jmp L1
L2 :
ret
Get_frequencies endp

END main