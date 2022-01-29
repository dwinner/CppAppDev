;16.8 - 8 - Several vertical lines

;This program draws several vertical lines with different color (here for the sake of simplicity gradient blue - gray was used)

;How to set colors:

;Palette has 256 entries (0 for background). One entry can be used only for one color, it's impossible to reset 
; color in the same index during run time.
;
;FOLLOWING CODE DOESN'T WORK:
;.data
;COLOR_INDEX = 1
;rgb_lines db 1, 0, 10, 63; foreground, red, green, blue
;.code
;mov esi, offet rgb_lines
;move ecx, number_of_lines
;L1:
;mov BYTE PTR es:[di], COLOR_INDEX
;loop L1
;change [esi+1]
;change [esi+2]
;change [esi+3]

;COLOR INDEX MUST BE DIFFERENT FOR ALL ENTRIES

;masm611 doesn't allow to use repeat block macros (check below)

.model small
.stack 100h
.386

Mode_06 = 6 ; 640 X 200, 2 colors
Mode_0D = 0Dh ; 320 X 200, 16 colors
Mode_0E = 0Eh ; 640 X 200, 16 colors
Mode_0F = 0Fh ; 640 X 350, 2 colors
Mode_10 = 10h ; 640 X 350, 16 colors
Mode_11 = 11h ; 640 X 480, 2 colors
Mode_12 = 12h ; 640 X 480, 16 colors
Mode_13 = 13h ; 320 X 200, 256 colors
Mode_6A = 6Ah ; 800 X 600, 16 colors

VIDEO_PALLETE_PORT = 3C8h
COLOR_SELECTION_PORT = 3C9h
SET_VIDEO_MODE = 0
GET_VIDEO_MODE = 0Fh
VIDE0_SEGMENT = 0A000h
WAIT_FOR_KEYSTROKE = 10h

comment @
rgb_lines struct
foreground db 1
red db 0
green db 5
blue db 10
rgb_lines ends
@

lines = 31

.data

comment @
lines_color label ptr rgb_lines
repeat lines
foreground = foreground + 1
red = red + 1
green = green + 1
blue = blue + 1
rgb_lines <foreground, red, green, blue>
endm
@

saveMode BYTE ? 
xVal WORD 10
yVal WORD 10
rgb_backgr db 0, 0, 0, 35; - set background, red, green, blue

rgb_lines db 1, 0, 10, 63; foreground, red, green, blue

.code
main proc

mov ax, @data
mov ds, ax

;Saves the current video mode, switches to a
; new mode, and points ES to the video segment.
mov ah,GET_VIDEO_MODE
int 10h
mov saveMode,al
mov ah,SET_VIDEO_MODE
mov al,Mode_13
int 10h
push VIDE0_SEGMENT
pop es

;Sets the screen's background color
mov esi, offset rgb_backgr
call set_color

mov ecx, lines; draw 31 vertical lines
mov esi, offset rgb_lines
L1:
push ecx

call set_color

;draw vertical line
mov ax,320; 320 for video mode 13h
mul yVal
add ax,xVAl
mov di,ax ; AX contains buffer offset
mov cx,180; draw vertical line from Y = 10 to Y = 190
DP1:
mov al, byte ptr [esi]
mov BYTE PTR es:[di],al;COLOR_INDEX
add di,320
loop DP1

add xVal, 10

;change color
mov esi, offset rgb_lines
inc byte ptr [esi]; change color palette index
inc byte ptr [esi+1]; change red
inc byte ptr [esi+2]; change green
dec byte ptr [esi+3]; change blue

pop ecx
loop L1

;Waits for a key to be pressed and restores
; the video mode to its original value.
mov ah,WAIT_FOR_KEYSTROKE
int 16h
mov ah,SET_VIDEO_MODE ; reset video mode
mov al,saveMode ; to saved mode
int 10h

mov ah, 4ch
int 21h

main endp

set_color proc
mov dx,VIDEO_PALLETE_PORT
mov al,byte ptr [esi];PALLETE_INDEX_BACKGROUND
out dx,al
mov dx,COLOR_SELECTION_PORT
mov al,byte ptr [esi+1] ; red
out dx,al
mov al,byte ptr [esi+2] ; green
out dx,al
mov al,byte ptr [esi+3] ; blue
out dx,al
ret
set_color endp

end main