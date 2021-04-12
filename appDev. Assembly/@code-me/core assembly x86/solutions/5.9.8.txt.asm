; 5.9.8 - Color Matrix

comment @
.386
.model flat, stdcall
.stack 4096
ExitProcess PROTO, dwExitCode:DWORD
@

INCLUDE Irvine32.inc

.data
char1 byte 'a', 0
count dword ?
CurrentColor word ?

.code
main PROC

mov eax, 0
mov ecx, 4
mov ebx, 0
L1:
	mov ah, bh; ah should be in outer loop
	mov count, ecx; save ecx of outer loop
	mov ecx, 4
	L2:
		mov al, bl; al should be in inner loop
		call SetTextColor
		call Clrscr
		mov edx, OFFSET char1
		call WriteString
		call Crlf
		add bl, 4h
		mov CurrentColor, ax; save current ah and al values before implement Delay
		mov eax, 100
		call Delay
		mov ax, CurrentColor
		loop L2
	add bh, 1h
	mov ecx, count
loop L1

exit

; INVOKE ExitProcess, 0

main ENDP
END main