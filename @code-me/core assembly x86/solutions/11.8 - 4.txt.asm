; 11.8 - 4 - Random Screen Fill

; This program fills each cell of screen with a random character in a random color.
; Assign a 50 % probability that the color of any character will be WHITE.

; GetConsoleScreenBufferInfo is used to retrieve the size(area or number of characters) of current screen.
; This vakue is passed to loop counter which fills all the cells with random characters.

; First part of loop uses RandomRange to determine whether the color is white.
; SetConsoleTextAttribute is used then to set the color of a cell.
; Wrapper of function(invoke SetConsoleTextAttribute, OutHandle, 0f0h) is used in order to
; preserve all registers, etc and avoid the conflict with other procedures.
; Second RandomRange is used to determine random color in range from 0 to 0ffh.
;Finally, wrapper of WriteConsole is used to print char.

INCLUDE Irvine32.inc
INCLUDE Macros.inc
INCLUDE GraphWin.inc

; If procedure has a LOCAL variable, don t show it in PROTO!!!
CharOutput proto,
CharHandle:handle,
CharBuffer:ptr byte,

;CharOutput proc uses eax ebx ecx edx esi esi,
;CharHandle:handle,
;CharBuffer:ptr byte
;local CharWritten:ptr dword


MySetColor proto,
ColorHandle:handle,
colorAttributes : word

;.386
;.model flat, stdcall
;.stack 4096
;ExitProcess proto, dwExitCode:dword

.data

OutHandle handle 0

csbi CONSOLE_SCREEN_BUFFER_INFO <>

.code
main PROC

;get output handle
invoke GetStdHandle, STD_OUTPUT_HANDLE
mov OutHandle, eax

;obtain the size (area) of current screen
invoke GetConsoleScreenBufferInfo, OutHandle, addr csbi
mov ax, csbi.srWindow.Right
mov bx, csbi.srWindow.Bottom
mul bx

;move previously calculated area to ecx
mov ecx, 0
mov cx, ax
call Randomize
L1:
mov eax, 10; if eax<5 then color is white (0f0h)
call RandomRange
cmp eax, 5
ja L2
mov ax, 0f0h
invoke MySetColor, OutHandle, ax
jmp L3
L2:
mov eax, 0ffh;the range of all possible color combinations
call RandomRange
invoke MySetColor, OutHandle, ax
L3:
mov eax, 256
call RandomRange
invoke CharOutput, OutHandle, eax
loop L1

call MyCrlf

call MyCrlf1

; invoke ExitProcess, 0

exit
main ENDP

CharOutput proc uses eax ebx ecx edx esi esi,
CharHandle:handle,
CharBuffer:ptr byte
local CharWritten:ptr dword
mov CharBuffer, eax
invoke WriteConsole, CharHandle, addr CharBuffer, 1, addr CharWritten, NULL
ret
CharOutput endp

MySetColor proc uses eax ebx ecx edx esi esi,
ColorHandle:handle,
colorAttributes: word
invoke SetConsoleTextAttribute, ColorHandle, colorAttributes
ret
MySetColor endp

MyCrlf proc,
OutHandle1:handle,
buffer1:ptr byte,
CharWritten1:ptr dword
invoke GetStdHandle, STD_OUTPUT_HANDLE
mov OutHandle1, eax
mov buffer1, 0Dh
invoke WriteConsole, OutHandle1, addr buffer1, 1, addr CharWritten1, NULL
mov buffer1, 0Ah
invoke WriteConsole, OutHandle1, addr buffer1, 1, addr CharWritten1, NULL
ret
MyCrlf endp

MyCrlf1 proc,
OutHandle2:handle
local buffer2[2]: ptr byte,
CharWritten2:ptr dword
lea esi, buffer2
mov byte ptr [esi], 0Dh
inc esi
mov byte ptr[esi], 0Ah
invoke GetStdHandle, STD_OUTPUT_HANDLE
mov OutHandle2, eax
invoke WriteConsole, OutHandle2, addr buffer2, 2, addr CharWritten2, NULL
ret
MyCrlf1 endp

END main