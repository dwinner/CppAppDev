;16.8 - 4 - Lines scrolling in opposite directions

;Random line are generated using array, which was previously filled with pseudo-random numbers.

;This program uses 1 loop for downward moving lines and one loop for upward moving lines.

;However, when functions AH 06/07 INT 10h are used at the same time, only apical symbols are changed, 
;whole lines stay unchanged.

.model small
.stack 100h
.386

array_length = 10

.data

column1 db 79d
color1 db 0fh
row1 db 24d

column db 0
color db 1
row db 0
char db 21h

init_columns db 0
init_vmode db 0
init_page db 0

array1 db array_length dup (0)

.code
main proc

mov ax, @data
mov ds, ax

;fill array with random numbers
mov ecx, array_length
mov esi, offset array1
L51:
push ecx
L52:
call wait_millisec
;get current time
mov ah, 0
int 1ah
mov ax, dx
mov dx, 0
mov bx, 8
div bx
cmp dx, 5
jb L52
mov byte ptr [esi], dl
inc esi
pop ecx
loop L51

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

mov ecx, array_length
mov esi, offset array1
L1:
push ecx

;set cursor position
mov ah, 2
mov dl, column
mov dh, row
mov bh, 0
int 10h

;write char and attribute
call random_ascii 
mov ah, 9
mov bh, 0
mov bl, color
mov cx, 1
int 10h

mov al, column
add al, byte ptr [esi]
mov column, al
inc esi

inc color

pop ecx
loop L1

mov ecx, array_length
mov esi, offset array1
L2:
push ecx

;set cursor position
mov ah, 2
mov dl, column1
mov dh, row1
mov bh, 0
int 10h

;write char and attribute
call random_ascii 
mov ah, 9
mov bh, 0
mov bl, color1
mov cx, 1
int 10h

mov al, column1
sub al, byte ptr [esi]
mov column1, al
inc esi

dec color1

pop ecx
loop L2

;scroll upwards
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

;scroll downwards
mov al, row1
cmp al, 4
ja L31
;scroll one line
mov ah, 7
mov al, 1; 1 line
mov cx, 0
mov dh, 24
mov dl, 79
mov bh, 7
int 10h
jmp L32

L31:
dec row1

L32:
mov column1, 79
mov color1, 0fh

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

wait_millisec proc
mov ah, 86h
mov dx, 20000d; low word
mov cx, 0;upper word
int 15h
ret
wait_millisec endp

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