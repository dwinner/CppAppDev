;14.5 - 6 - Text matching program (slight modification)

;User is prompted to enter string to find.
; This program looks for some pattern string in source file. 
;if string is found, it is marked with @-&.

;Function int 21h ah 42h (move file pointer) is used to move pointer
;in source file, but it's not necessary. Apparently, DOS automatically move 
; pointer in source file.

;Procedure write_dec_byte performs 8-bit division

.model small
.stack 100h

buffer = 256
pattern_length = 100

.data

;keyboard struct
maxInput db pattern_length
inputCount db 0
string db pattern_length dup(0)

filename db "C:\iczelion\readme.txt", 0

handle dw 0

input_buffer byte buffer dup(0)
bytes_read dw 0

file_name_msg db "Please enter string to find: $"
fail_msg db "ERROR! $"
end_msg db 0dh, 0ah, "==END==$"
numb_lines_msg db "Number of lines in document $"
pattern_lines_msg db "Requested pattern appears on lines $"
crlf db 0dh, 0ah, "$"

count db 1; counts number of lines of source doc
line_number db 20 dup(0)
line_number_count db 0

offsetHi dw 0
offsetlo dw 0

.code
main proc

mov ax, @data
mov ds, ax

;crlf
mov ah, 9
mov dx, offset crlf
int 21h

;file_name_msg
mov ah, 9
mov dx, offset file_name_msg
int 21h

;read string to find
mov ah, 0ah
mov dx, offset maxInput
int 21h

;crlf
mov ah, 9
mov dx, offset crlf
int 21h

;open file
mov ax, 716ch
mov bx, 0
mov cx, 0
mov dx, 1
mov si, offset filename
int 21h
jc failed
mov handle, ax

L10:

;move file pointer
mov ah, 42h
mov al, 0
mov bx, handle
mov cx, offsetHi
mov dx, offsetlo
int 21h

;read an array from file
mov ah, 3fh
mov bx, handle
mov cx, buffer
mov dx, offset input_buffer
int 21h
mov bytes_read, ax

; search for pattern
; found pattern is delimited by @ and &
;this block also saves the number of line, on which the string was found
mov si, offset input_buffer
mov cx, bytes_read
L0:
push cx
push si
mov al, byte ptr [si]
cmp al, 0ah; check whether it's a new line
jne L5
mov al, count; counter keeps the line number
inc al
mov count, al
L5:
mov di, offset string; set up loop to find the string
mov cx, 0
mov cl, inputCount
;mov cx, lengthof string
L1:
mov al, byte ptr [si]
mov bl, byte ptr [di]
cmp al, bl
jne L2
inc di
inc si
loop L1
mov bx, 0; delimit the string found in text
mov bl, inputCount
sub si, bx
dec si
mov al, "@"
mov [si], al
add si, bx	
inc si
mov al, "&"
mov [si], al	
mov si, offset line_number; save the line number
mov ax, 0
mov al, line_number_count
add si, ax
mov bl, count
mov byte ptr [si], bl
inc ax
mov line_number_count, al
L2:
pop si
inc si
pop cx
loop L0

;write string to device
mov ah, 40h
mov bx, 1; console handle
mov cx, bytes_read
mov dx, offset input_buffer
int 21h

;increase file pointer
mov ax, offsetlo
cmp ax, 0ffh
je L8
add ax, bytes_read
mov offsetlo, ax
jmp L9
L8:
mov ax, offsetHi
add ax, bytes_read
mov offsetHi, ax
L9:

;check the end of file
mov ax, buffer
mov bx, bytes_read
cmp ax, bx
ja exit

jmp L10

jmp exit

failed:

;error message
mov ah, 9
mov dx, offset fail_msg
int 21h

exit:

;crlf
mov ah, 9
mov dx, offset crlf
int 21h

;numb_lines_msg
mov ah, 9
mov dx, offset numb_lines_msg
int 21h

;write total number of lines in document
mov al, count
mov ah, 0
mov bl, 0ah
mov cx, 2
L12:
mov dx, 0
div bl
or ah, 30h
mov dl, ah
mov ah, 0
push dx
loop L12
or al, 30h
mov dx, 0
mov dl, al
push dx
mov cx, 3
L13:
mov ah, 2
pop dx
int 21h
loop L13

;crlf
mov ah, 9
mov dx, offset crlf
int 21h

;pattern_lines_msg
mov ah, 9
mov dx, offset pattern_lines_msg
int 21h

mov si, offset line_number
L20:
mov al, [si]
cmp al, 0
je L21
call write_dec_byte
mov ah, 2
mov dl, ','
int 21h
inc si
jmp L20
L21:

;crlf
mov ah, 9
mov dx, offset crlf
int 21h

;end message
mov ah, 9
mov dx, offset end_msg
int 21h

mov ah, 4ch
int 21h

main endp

write_dec_byte proc
mov ah, 0
mov bl, 0ah
mov cx, 2
L30:
mov dx, 0
div bl
or ah, 30h
mov dl, ah
mov ah, 0
push dx
loop L30
or al, 30h
mov dx, 0
mov dl, al
push dx
mov cx, 3
L31:
mov ah, 2
pop dx
int 21h
loop L31
ret
write_dec_byte endp

end main

