; 7.9.2 - 8 - shift three memory word to the left by 1 bit

; INCLUDE Irvine32.inc

.386
.model flat, stdcall
.stack 4096
ExitProcess proto, dwExitCode:dword

.data

wordArray WORD 810Dh, 0C064h, 93ABh	

.code
main PROC

mov esi, 0
shl wordArray[esi], 1
rcl wordArray[esi + 2], 1
rcl wordArray[esi+4], 1

invoke ExitProcess, 0
main ENDP

; exit

END main