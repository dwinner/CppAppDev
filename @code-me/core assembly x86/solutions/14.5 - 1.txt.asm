;14.5 - 1 - Read a text file

;Program reads .txt file's content to buffer and then print it from buffer to console.

; This program was run under WinXP using masm32 link16.exe program

.model small
.stack 100h

maxLength = 127

.data
fileName db "C:\iczelion\readme.txt"; file is in the same folder as .exe file

inputBuffer db maxLength dup(0)
bytesRead word 0

handle dw 0; file handle

.code
main proc

mov ax, @data
mov ds, ax

; This part opens existing file and returns handle to AX
mov ax, 716Ch
mov bx, 2
mov cx, 0
mov dx, 1
mov si, offset fileName
int 21h

mov handle, ax

L1:
;Read an array of bytes from device or file
mov ah, 3Fh
mov bx, handle
mov cx, maxLength
mov dx, offset inputBuffer
int 21h
mov bytesRead, ax

; Write an array of bytes to output console
mov ah, 40h
mov bx, 1
mov cx, bytesRead
mov dx, offset inputBuffer
int 21h

;When the end of file is reached, the value in AX (bytesRead) should be lower then maxLength
mov cx,maxLength
mov ax, bytesRead 
cmp cx, ax
ja L2

jmp L1

L2:

mov ah, 4ch
int 21h
main endp
end main