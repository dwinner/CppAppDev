; 11.8 - 1 - ReadString

; This is a wrapper around Win32 ReadConsole.
; In order to understand, how does this wrapper work, it would be better to explain
; how ReadConsole saves a string.
; Let s suppose the nNumberOfCharsToRead = 10 and user inputs exactly 10 digits.
; In this case string contains only input digits without null byte.
; If user inputs less than 10 digits, in this case function ReadConsole automatically
; inserts 0dh, 0ah at the end of the string(actually, this is ENTER key code).
; Interestingly, lpNumberOfCharsRead counts 0dh, 0ah as a part of string, so,
; if the user input 8 digits, lpNumberOfCharsRead = 8 + 0dh, 0ah = 10.
; Therefore, in order to insert a NULL byte at the end of the string, a loop should be used
;to search 0dh byte. 

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

mov edx, offset buffer
mov eax, sizeofbuffer
call MyReadString

; invoke ExitProcess, 0

exit
main ENDP

MyReadString proc,
NumberOfCharsRead: ptr dword,
InpHandle: handle,
buffsize:dword

mov buffsize, eax

push STD_INPUT_HANDLE
call GetStdHandle
mov InpHandle, eax

invoke ReadConsole, InpHandle, edx, buffsize, addr NumberOfCharsRead, NULL

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

ret
MyReadString endp

END main