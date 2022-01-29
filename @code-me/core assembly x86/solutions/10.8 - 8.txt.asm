; 10.8 - 8 - Drunkard�s Walk with Probabilities(SKETCH)

; In this sketch the direction is predefined.

INCLUDE Irvine32.inc
INCLUDE Macros.inc

WalkMax = 30
StartX = 15
StartY = 15

DrunkardWalk STRUCT
path COORD WalkMax DUP(<0, 0>)
pathsUsed WORD 0
DrunkardWalk ENDS

DisplayPosition PROTO currX : WORD, currY : WORD

; .386
; .model flat, stdcall
; .stack 4096
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

mov eax, WalkMax; this section defines the coordinates of the lost cellphone
call RandomRange
mov ebx, eax

Again :

mov ax, currX
mov(COORD PTR[edi]).X, ax
mov ax, currY
mov(COORD PTR[edi]).Y, ax

INVOKE DisplayPosition, currX, currY

;Here direction (inc currY) is favorised
mov eax, 8
call RandomRange
.IF(eax >= 0) && (eax <= 4)
inc currY
.ELSEIF eax == 5
dec currY
.ELSEIF(eax >= 6) && (eax <= 7)
inc currX
.ELSE
dec currX
.ENDIF

add edi, TYPE COORD

loop Again

popad
ret
TakeDrunkenWalk ENDP

DisplayPosition PROC currX : WORD, currY : WORD
pushad

mov dh, byte ptr currX
mov dl, byte ptr currY
call Gotoxy

.IF ecx == WalkMax
mov al, '@'; shows the starting point
.ELSEIF ecx == ebx
mov al, '&'; shows the place where the cellphone was lost
.ELSEIF ecx == 1
mov al, '#'; shows the final point
.ELSE
mov al, '*';shows the path
.ENDIF
call WriteChar

popad
ret
DisplayPosition ENDP

END main