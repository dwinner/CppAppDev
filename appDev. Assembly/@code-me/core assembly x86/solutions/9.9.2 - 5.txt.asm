; 9.9.2 - 5 - scasw

INCLUDE Irvine32.inc

unmatch proto,
ScanValue:word

	; .386
	;.model flat, stdcall
	;.stack 4096
	; ExitProcess proto, dwExitCode:dword

	.data

	sourcew word 100h, 200h, 300h, 400h

	.code
	main PROC

	invoke unmatch, 300h

	; invoke ExitProcess, 0
	exit
	main ENDP

	unmatch proc uses ecx,
	ScanValue:word

	mov edi, OFFSET sourcew
	mov ax, ScanValue
	cld
	mov ecx, LENGTHOF sourcew
	inc ecx
	repne scasw

	cmp ecx, 0
	je L1
	dec ecx
	mov eax, lengthof sourcew
	sub eax, ecx
	dec eax; eax will contain the index of unmatching element
	sub edi, type sourcew
	mov ebx, edi;offset of matching element

L1 :
ret
unmatch endp

END main