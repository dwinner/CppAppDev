; 10.8 - 7 - Professor s lost phone (Modified program)

; MODIFICATION:
; Instead of showing the coordiantes of professor s step, program prints '*'.
; Starting point is marked with '@', final point with '#'.
; Professor can walk only to the south or to the east.

; TASK(lost cellphone) :
; RandomRanage is seeded with WaklMax value.
; Current loop counter is compared to random value.
;When OK, then drop the cellphone (marked with '&').

INCLUDE Irvine32.inc
INCLUDE Macros.inc

WalkMax = 30
StartX = 3
StartY = 3

DrunkardWalk STRUCT
path COORD WalkMax DUP(<0, 0>)
pathsUsed WORD 0
DrunkardWalk ENDS

DisplayPosition PROTO currX : WORD, currY : WORD

; .386
;.model flat, stdcall
;.stack 4096
; ExitProcess proto, dwExitCode:dword

.data

aWalk DrunkardWalk <>

.code
main PROC

call Randomize
mov esi, OFFSET aWalk
call TakeDrunkenWalk

; push cursor away from the path
mov dh, 0
mov dl, 0
call Gotoxy

; invoke ExitProcess, 0
exit
main ENDP

TakeDrunkenWalk PROC
LOCAL currX : WORD, currY : WORD

pushad
mov edi, esi
add edi, OFFSET DrunkardWalk.path
mov ecx, WalkMax
mov currX, StartX
mov currY, StartY

mov eax, WalkMax
call RandomRange
mov ebx, eax

Again :

mov ax, currX
mov(COORD PTR[edi]).X, ax
mov ax, currY
mov(COORD PTR[edi]).Y, ax

mov dh, byte ptr currX
mov dl, byte ptr currY
call Gotoxy

.IF ecx == WalkMax
mov al, '@'
.ELSEIF ecx == ebx
mov al, '&'
.ELSEIF ecx == 1
mov al, '#'
.ELSE
mov al, '*'
.ENDIF
call WriteChar

mov eax, 4
call RandomRange
.IF eax == 0
inc currY
.ELSEIF eax == 1
add currY, 2
.ELSEIF eax == 2
inc currX
.ELSE
add currX, 2
.ENDIF

add edi, TYPE COORD
loop Again

Finish :
mov(DrunkardWalk PTR[esi]).pathsUsed, WalkMax
popad
ret
TakeDrunkenWalk ENDP

END main