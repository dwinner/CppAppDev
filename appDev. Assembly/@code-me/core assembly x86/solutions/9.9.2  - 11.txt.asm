; 9.9.2 - 11

INCLUDE Irvine32.inc

; .386
;.model flat, stdcall
;.stack 4096
; ExitProcess proto, dwExitCode:dword

.data

myArray dword 1,2,3
myArrayLength = ($-myArray)
dword 4,5,6
dword 7,8,9

.code
main PROC

row_index = 2
column_index = 2
mov ebx, offset myArray
add ebx, row_index*myArrayLength
mov edi, column_index
mov eax, [ebx+edi*type myArray]

;alternative
row_index = 2
column_index = 2
mov ebx, row_index
mov eax, myArrayLength
mul bl
mov edi, column_index
mov ecx, myArray[eax+edi*type myArray]

; invoke ExitProcess, 0
exit
main ENDP

END main