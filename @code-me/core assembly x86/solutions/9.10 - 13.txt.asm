; 9.10 - 13 - Trim leading

; This program trims all symbols from beginning of a string
; to the last trailing character.

; 1st part calculates the length of a string.
; 2nd part points to the end of a string and then looks for the last trailing character.
;3d part fills all positions between beginning of a string and last trailing character with 0.

INCLUDE Irvine32.inc

trim_lead proto,
str1: ptr byte,
char1 : byte

; .386
; .model flat, stdcall
; .stack 4096
; ExitProcess proto, dwExitCode:dword

.data

string1 BYTE "Hello#HELL#Oworld", 0

.code
main PROC

invoke trim_lead, addr string1, '#'

mov edx, esi
call WriteString

call Crlf
call Crlf

; invoke ExitProcess, 0
exit
main ENDP

trim_lead proc uses eax ebx edi,
str1: ptr byte,
char1: byte

; calculates the length of a string
mov edi, str1
mov ebx, 0
L1:
mov byte ptr al, [edi]
cmp al, 0
je L2
inc edi
inc ebx
jmp L1
L2 :

; goes to the end of a string and looks for the 1st trimming character
mov edi, str1
add edi, ebx
L3 :
mov byte ptr al, [edi]
cmp al, char1
je L4
dec edi
jmp L3
L4 :

mov esi, edi
inc esi; points to new string

; fills all bytes prior to trimming character with 0
mov edi, str1
L5 :
cmp edi, esi
je L6
mov byte ptr[edi], 0
inc edi
loop L5
L6 :

ret
trim_lead endp

END main