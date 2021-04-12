; 15.7 - 3 - Disk free space

;This program prompts user to choose drive and then shows available space in bytes (in HEX)

.model small
.stack 100h
.386

ExtGetDskFreSpcStruc STRUC
StructSize WORD ?
Level WORD ?
SectorsPerCluster DWORD ?
BytesPerSector DWORD ?
AvailableClusters DWORD ?
TotalClusters DWORD ?
AvailablePhysSectors DWORD ?
TotalPhysSectors DWORD ?
AvailableAllocationUnits DWORD ?
TotalAllocationUnits DWORD ?
Rsvd DWORD 2 DUP (?)
ExtGetDskFreSpcStruc ENDS

.data

prompt1 db "Please select drive A:\ (type a), B:\(type b) or C:\(type c) $"
crlf db 0dh, 0ah, "$"
drive_code db ?; 0-A, 1-B, 3-C
prompt_drive db "Current drive is $"
drive_name db " :\", 0

egdfss ExtGetDskFreSpcStruc <>

error_msg db "ERROR!$"
free_space_msg db "Free space in bytes $"
free_space dword 2 dup(0)

.code
main proc

mov ax, @data
mov ds, ax
mov es, ax

;get current drive
mov ah, 19h
int 21h
mov drive_code, al

; Write $-terminated string
mov ah, 9
mov dx, offset prompt_drive
int 21h

;write char
mov ah, 2
mov dl, drive_code
add dl, 41h; ASCII 'A'
int 21h

;crlf
mov ah, 9
mov dx, offset crlf
int 21h

; Write $-terminated string
mov ah, 9
mov dx, offset prompt1
int 21h

;crlf
mov ah, 9
mov dx, offset crlf
int 21h

;read char (a 61h, b 62h, c 63h)
mov ah, 1
int 21h
sub al, 61h;
mov drive_code, al

;crlf
mov ah, 9
mov dx, offset crlf
int 21h

;set drive
mov ah, 0eh
mov dl, drive_code
int 21h

;get current drive
mov ah, 19h
int 21h
mov drive_code, al

; Write $-terminated string
mov ah, 9
mov dx, offset prompt_drive
int 21h

;write char
mov ah, 2
mov dl, drive_code
add dl, 41h; ASCII 'A'
int 21h

;crlf
mov ah, 9
mov dx, offset crlf
int 21h

;transform drive_name
mov si, offset drive_name
mov dl, drive_code
add dl, 41h; ASCII 'A'
mov byte ptr [si],dl  

;free_space_msg
mov ah, 9
mov dx, offset free_space_msg
int 21h

;function 7303h fills ExtGetDskFreSpsStruc
mov egdfss.Level, 0; must be 0
mov di, offset egdfss
mov cx, sizeof egdfss
mov dx, offset drive_name
mov ax, 7303h
int 21h
jc error

;Calculate and return the disk free space, in kilobytes.
;SectorsPerCluster * 512(size of sector) * TotalClusters) / 1024
mov edx, 0
mov eax,egdfss.SectorsPerCluster
shl eax,9 ; mult by 512
mul egdfss.AvailableClusters; product is in EDX:EAX
mov esi, offset free_space
mov [esi], edx
add esi, 4
mov [esi], eax

;write result in hex
mov esi, offset free_space; -----------------------------------------
mov ecx, 2
L5:
push ecx

mov ecx, 8
mov ebx, 28
L6:
push ecx
mov edx, [esi]
mov ecx, ebx
shr edx, cl
and edx, 0fh
cmp dl, 0ah
jb L7
mov edi, 0ah
mov ecx, 6
L8:
cmp edx, edi
je L9
inc edi
loop L8

L7:
or dl, 30h
jmp L10
L9:
add dl, 37h
L10:
mov ah, 2
int 21h

pop ecx
sub ebx, 4
loop L6

add esi, 4
pop ecx
loop L5; ----------------------------------------------------

jmp quit

error:

; Write error_msg
mov ah, 9
mov dx, offset error_msg
int 21h

quit:

mov ah, 4ch
int 21h

main endp
end main