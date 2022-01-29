; 11.8 - 1 - ReadString

; Explicit stack parameters are used.
; All the parameters are pushed in the stack prior to call the wrapper

INCLUDE Irvine32.inc
INCLUDE Macros.inc
INCLUDE GraphWin.inc

ReadConsole PROTO,
hConsoleInput:HANDLE, ; input handle
lpBuffer:PTR BYTE, ; pointer to buffer
nNumberOfCharsToRead:DWORD, ; number of chars to read
lpNumberOfCharsRead:PTR DWORD, ; ptr to num bytes read
lpReserved:DWORD

; .386
;.model flat, stdcall
;.stack 4096
; ExitProcess proto, dwExitCode:dword

.data

CharsRead dword 0
buffer byte 10 dup(?)
sizeofbuffer dword $-buffer

.code
main PROC

push offset CharsRead;[ebp+16]
push offset buffer; [ebp + 12]
push sizeofbuffer; [ebp + 8]
call MyReadString

; invoke ExitProcess, 0

exit
main ENDP

MyReadString proc
push ebp
mov ebp, esp
sub esp, 4; local variable for InpHandle

push STD_INPUT_HANDLE
call GetStdHandle
mov dword ptr[ebp - 4], eax

push NULL
mov eax, dword ptr[ebp +16]; NumberOfCharsRead
push eax
mov eax, dword ptr[ebp +8]; buffsize
push eax
mov eax, dword ptr[ebp +12]; offset buffer
push eax
mov eax, dword ptr [ebp - 4]; InpHandle
push eax
call ReadConsole

mov esi, offset buffer
mov ecx, sizeofbuffer
mov ebx, 0; set the counter for the string length
L1 :
mov al, byte ptr[esi]
cmp al, 0dh
je L2
inc esi
inc ebx
loop L1

L2 :
mov byte ptr[esi], 0

mov CharsRead, ebx

mov esp, ebp
pop ebp
ret
MyReadString endp

END main