; 11.8 - 8 - Block animation

; Square is composed of 4 points, their coordiantes are defined by SQUARE structure.
; Inner loop is used to draw the square.
; Outer loop is used to set random coordiantes, which are added to coordiantes, set in SQUARE structure.

INCLUDE Irvine32.inc
INCLUDE Macros.inc
INCLUDE GraphWin.inc

square struct
LeftTop coord <0, 0>
RightTop coord <1, 0>
LeftBottom coord <0, 1>
RightBottom coord <1, 1>
square ends

; .386
; .model flat, stdcall
; .stack 4096
; ExitProcess proto, dwExitCode:dword

.data

OutHandle handle 0

text byte 0dbh, 0
textwritten dword 0

CursorPosition coord <0, 0>
RandomIncrement coord <0, 0>

CursorFinal coord <0,0>

sq square <>

csbi CONSOLE_SCREEN_BUFFER_INFO <>

.code
main PROC

call Randomize

invoke GetStdHandle, STD_OUTPUT_HANDLE
mov OutHandle, eax

invoke GetConsoleScreenBufferInfo, outHandle, addr csbi

mov edx, 20; set counter for repeating squares
L2:
push edx
cmp edx, 0
je L3
mov eax, 0
mov ax, csbi.srWindow.Right; increment for X - axis is determied by the width of console window
call RandomRange
mov RandomIncrement.X, ax
mov ax, csbi.srWindow.Bottom; increment for Y - axis is determined by the height of cosnole window
call RandomRange
mov RandomIncrement.Y, ax
mov ecx, sizeof square
shr ecx, 2; set counter for square drawing
mov esi, offset sq
sub esi, type word
L1:
add esi, type word
mov ax, [esi]
add ax, RandomIncrement.X; previously calculated increment is added to coordinate X
mov CursorPosition.X, ax
add esi, type word
mov ax, [esi]
add ax, RandomIncrement.Y
mov CursorPosition.Y, ax; previously calculated increment is added to coordinate Y
pushad
pushfd
invoke SetConsoleCursorPosition, OutHandle, CursorPosition
mov eax, 0Fh; random colors are used for each part of square
call RandomRange
invoke SetConsoleTextAttribute, OutHandle, ax
invoke WriteConsole, OutHandle, addr text, 1, addr textwritten, NULL
popfd
popad
loop L1
invoke Sleep, 500
call ClearScreen; homemade procedure is used
pop edx
dec edx
jmp L2

L3:

invoke SetConsoleCursorPosition, outHandle, CursorFinal

; invoke ExitProcess, 0

exit
main ENDP

ClearScreen proc uses eax ebx ecx edx esi edi; see Ex.3
local BufferArea: word, CursCoord: coord, space: byte, ClearScreenWritten: dword
mov eax, 0
mov ax, csbi.srWindow.Bottom
mov ebx, 0
mov bx, csbi.srWindow.Right
mul bx
mov BufferArea, ax
mov CursCoord.X, 0
mov CursCoord.Y, 0
mov space, 20h

invoke SetConsoleCursorPosition, outHandle, CursCoord

mov ecx, 0
mov cx, BufferArea
L5 :
push ecx
invoke WriteConsole, outHandle, addr space, 1, addr ClearScreenWritten, NULL
pop ecx
loop L5
ret
ClearScreen endp

END main