; 9.10 - 14 - Trimming a set of characters(MODIFIED)

; This program trims all filter characters from source string.

INCLUDE Irvine32.inc

Trim_set proto,
str1: ptr byte,
str2 : ptr byte

; .386
; .model flat, stdcall
; .stack 4096
; ExitProcess proto, dwExitCode:dword

.data

string1 BYTE "H!a@l$l%o&W!o@r#l&d!!@#$%&", 0
string2 byte "!@#$%&", 0

.code
main PROC

invoke Trim_set, addr string1, addr string2

mov edx, offset string1
call WriteString

call Crlf
call Crlf

; invoke ExitProcess, 0
exit
main ENDP

Trim_set proc uses eax ebx ecx esi edi,
str1: ptr byte,
str2:ptr byte

; counts the length of of string without 0.
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

; looks for the filter character from the beginning of the source string.
; when character is found, jmp L5.
mov ecx, ebx
inc ecx
mov esi, str1
L3 :
mov edi, str2
L31 :
mov byte ptr al, [esi]
mov byte ptr dl, [edi]
cmp dl, 0
je L4
cmp al, dl
je L5
inc edi
jmp L31
L4 :
inc esi
loop L3

jmp L10

; moves all the elements behind filter character in 1 position
; towards the beginning of the source string :
; "Hello@W#o!", 0-- > "HelloW#o!", 0
; When operation is finished, jumps back to prinicpal loop.
L5:
push ecx
dec ecx
mov edi, esi
inc edi
push esi
L6 :
mov byte ptr bl, [edi]
cmp ecx, 0
je L7
mov byte ptr[esi], bl
inc esi
inc edi
dec ecx
jmp L6
L7 :
mov byte ptr[esi], 0
pop esi
pop ecx
dec ecx
jmp L3

L10 :

ret
Trim_set endp

END main