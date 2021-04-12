; 10.8 - 9 - Shifting Multiple Doublewords

; Two conditional assembly directives can be used:

; 1st: Parameter DIRECTION is coded by 0 (right shift) and 1 (left shift).
; if (direction eq 0) == > then right shift,
; elseif(direction eq 1) == > left shift,
; endif.

; 2nd: Parameter DIRECTION is coded by RIGHT and LEFT.
; ifidni <direction>, <right>,
; else,
;endif.

INCLUDE Irvine32.inc
INCLUDE Macros.inc

mShiftDoublewords MACRO arrayName, direction, numberOfBits

ifidni <direction>, <right>
; if (direction eq 0)

mov esi, offset arrayName
add esi, sizeof arrayName - type arrayName
mov ecx, lengthof arrayName
L2 :
push ecx
mov ecx, numberOfBits
mov eax, [esi]
mov ebx, [esi - type dword]
shrd eax, ebx, cl
mov[esi], eax
sub esi, type dword
pop ecx
loop L2

else
;elseif (direction eq 1)

mov esi, offset arrayName
mov ecx, lengthof arrayName
L3 :
push ecx
mov ecx, numberOfBits
mov eax, [esi]
mov ebx, [esi + type dword]
shld eax, ebx, cl
mov[esi], eax
add esi, type dword
pop ecx
loop L3

endif

endm

; .386
;.model flat, stdcall
;.stack 4096
; ExitProcess proto, dwExitCode:dword

.data

array1 dword 11223344h, 55667788h, 12345678h

.code
main PROC

mShiftDoublewords array1, left, 16d
; mShiftDoublewords array1, 0, 16d

; invoke ExitProcess, 0
exit
main ENDP

END main