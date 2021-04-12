;16.8 - 3 - Scroll color columns

;Strings filled with random chars are generated using following method:
;Function INT 1ah is used to get current time.
;Current time is divided by 3 (user can choose any number), reminder is added to current ASCII-code.
;Value of ASCII-code is reset after achieving 255.

;Movement of columns is implemented incrementing row number at the beginning;
;When row number is more than some definite value (here is 20), row number stays constant,
; scrolling line by line is activated instead.

.model small
.stack 100h
.386

.data

column db 0
color db 1
row db 0
char db 21h

init_columns db 0
init_vmode db 0
init_page db 0

.code
main proc

mov ax, @data
mov ds, ax

;get video mode
mov ah, 0fh
int 10h
mov init_vmode, al
mov init_columns, ah
mov init_page, bh

;hide cursor
mov ah, 1
mov ch, 100
mov cl, 6
int 10h

;scroll window upwards
mov ah, 6
mov al, 24;whole screen
mov cx, 0
mov dh, 24
mov dl, 79
mov bh, 7
int 10h

L11:

mov ecx, 15
L1:
push ecx

;write char and attribute
call random_ascii 
mov ah, 9
mov bh, 0
mov bl, color
mov cx, 1
int 10h

;set cursor position
mov ah, 2
mov dl, column
mov dh, row
mov bh, 0
int 10h

mov al, column
add al, 5
mov column, al

inc color

pop ecx
loop L1

mov al, row
cmp al, 20
jb L21
;scroll one line
mov ah, 6
mov al, 1; 1 line
mov cx, 0
mov dh, 24
mov dl, 79
mov bh, 7
int 10h
jmp L22

L21:
inc row

L22:
mov column, 0
mov color, 1

call wait_one_sec

;checks keyboard buffer, exit if ESC
mov ax, 0
mov ah, 11h
int 16h
cmp al, 1bh; ESC pressed?
je quit

jmp L11

quit:

;restore video mode
mov ah, 0
mov al, init_vmode
int 10h

;set initial color
mov ah, 9
mov al, ' '
mov bh, 0
mov bl, 00000111b
mov cx, 1
int 10h

;restore cursor
mov ah,1
mov cx, 0607h
int 10h

mov ah, 4ch
int 21h

main endp

wait_one_sec proc
mov ah, 86h
mov dx, 4240h; low word
mov cx, 0fh;upper word
int 15h
ret
wait_one_sec endp

random_ascii proc
;get current time
mov ah, 0
int 1ah
mov ax, dx
;divide current time by 3
mov dx, 0
mov bx, 3
div bx
mov al, char
cmp al, 255
jne continue
mov char, 21h
continue:
add al, dl
mov char, al
ret
random_ascii endp

end main