;16.8 - 6 - Draw parabole (more improvement + animation)

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

.data

x_ord dw 320
y_ord dw 20
x_abs dw 100
y_abs dw 300
ordinate dw 300
abscisse dw 440
curr_x_left dw 0
curr_x_right dw 0

saveMode db 0
color db 0fh

.code
main proc

mov ax, @data
mov ds, ax

; Save the current video mode.
mov ah,0Fh
int 10h
mov saveMode, al

; Switch to a graphics mode.
mov ah,0 ; set video mode
mov al,Mode_10
int 10h

;draw abscisse
movzx ecx, abscisse
mov di, y_abs
mov si, x_abs
call draw_horizont

;draw ordinate
movzx ecx, ordinate
mov di, y_ord
mov si, x_ord
call draw_vertic

; draw parabole
movzx ecx, abscisse
shr ecx, 2; divide by 4
mov di, y_abs
mov ax, x_ord
mov curr_x_left, ax
mov curr_x_right, ax
L3 :
push ecx

mov ax, curr_x_left
mov cx, ax
sub ax, x_ord
call draw_parabole
inc curr_x_left

mov cx, curr_x_right
mov ax, x_ord
sub ax, curr_x_right
call draw_parabole
dec curr_x_right

call wait_millisec

pop ecx
loop L3

;wait key
mov ah, 0
int 16h

; Restore the starting video mode.
mov ah,0 ; set video mode
mov al,saveMode ; saved video mode
int 10h

mov ah, 4ch
int 21h

main endp

draw_parabole proc
mov dx, 0
mov bx, ax
mul bx
shr ax, 6; otherwise parabole is too steep
mov dx, di
sub dx, ax
mov ax, 0
mov ah, 0ch
mov al, color
dec al
mov bh, 0
int 10h
ret
draw_parabole endp

draw_horizont proc
L1:
push ecx
mov ah, 0ch
mov al, color
mov bh, 0
mov dx,di
mov cx,si
int 10h
inc si
pop ecx
loop L1
ret
draw_horizont endp

wait_millisec proc
mov ah, 86h
mov dx, 500000d; low word
mov cx, 0;upper word
int 15h
ret
wait_millisec endp

draw_vertic proc
L2:
push ecx
mov ah, 0ch
mov al, color
mov bh, 0
mov dx,di
mov cx,si
int 10h
inc di
pop ecx
loop L2
ret
draw_vertic endp

end main