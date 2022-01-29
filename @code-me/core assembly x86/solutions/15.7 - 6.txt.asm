;15.7 - 6 - Read sector

;This program prompts user to enter drive name and sector number
;and then display sector's content

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

DISKIO STRUCT
startSector DWORD ? ; starting sector number
numSectors WORD 1 ; number of sectors
bufferOfs WORD OFFSET buffer ; buffer offset
bufferSeg WORD @data ; buffer segment
DISKIO ENDS

SECTOR_SIZE = 512       

.data

buffer BYTE SECTOR_SIZE DUP(0),0
disk_io DISKIO <>
choose_drive db "Please select drive A (type a), B (b) or C (c): $"
crlf db 0dh, 0ah, "$"
drive_name db " :\$"
current_sector db "Current sector is $"
sector_content db "Sector content: $"
error_msg db "ERROR!$"

egdfss ExtGetDskFreSpcStruc <>
total_sector db "Total number of physical sectors $"
choose_sector db "Please choose sector number (format XXXXXXXX): $"
sector_number db 8 dup(0)
sector_number_hex dword 0
ten dword 10d

.code
main proc

mov ax, @data
mov ds, ax
mov es, ax

;choose_drive
mov ah, 9
mov dx, offset choose_drive
int 21h

;input drive letter
mov ah, 1
int 21h
sub al, 20h; transform to uppercase
mov si, offset drive_name
mov byte ptr [si], al

;crlf
mov ah, 9
mov dx, offset crlf
int 21h

;drive_name
mov ah, 9
mov dx, offset drive_name
int 21h

;crlf
mov ah, 9
mov dx, offset crlf
int 21h

;get disk free space
mov egdfss.Level, 0
mov di, offset egdfss
mov cx, sizeof egdfss
mov dx, offset drive_name
mov ax, 7303h
int 21h
jc error

;total_sector
mov ah, 9
mov dx, offset total_sector
int 21h

mov eax, egdfss.TotalPhysSectors 
call hex_to_dec

;crlf
mov ah, 9
mov dx, offset crlf
int 21h

;choose_sector
mov ah, 9
mov dx, offset choose_sector
int 21h

;sector_number
mov si, offset sector_number
mov ecx, lengthof sector_number
L5:
mov ah, 1
int 21h
cmp al, 0dh
je L6
mov byte ptr [si], al
inc si
loop L5
L6:

;dec to hex
mov si, offset sector_number
add si, lengthof sector_number-1
mov ecx, lengthof sector_number
mov edi, 1
L7:
mov edx, 0
mov eax, 0
mov al, [si]
and al, 0fh
mov ebx, edi 
mul ebx
add sector_number_hex, eax
mov eax, ten
mov ebx, edi
mul ebx
mov edi, eax
dec si
loop L7

;set sector
mov eax,sector_number_hex 
mov disk_io.startSector, eax

;crlf
mov ah, 9
mov dx, offset crlf
int 21h

;read disk sector
mov si, offset drive_name
mov dl,byte ptr [si]
sub dl, 40h; 'A' = 41h
mov ax, 7305h
mov cx, 0ffffh
mov bx, offset disk_io
mov si, 0; read sector
int 21h
jc error

;current_sector
mov ah, 9
mov dx, offset current_sector 
int 21h

mov eax, disk_io.startSector
call hex_to_dec

;crlf
mov ah, 9
mov dx, offset crlf
int 21h

;sector_content
mov ah, 9
mov dx, offset sector_content
int 21h

;display sector's content
mov ah, 40h
mov bx, 1
mov cx, lengthof buffer
mov dx, offset buffer
int 21h

;crlf
mov ah, 9
mov dx, offset crlf
int 21h

jmp L1

error:

;error_msg
mov ah, 9
mov dx, offset error_msg
int 21h

;crlf
mov ah, 9
mov dx, offset crlf
int 21h

L1:

mov ah, 4ch
int 21h

main endp

hex_to_dec proc
mov ebx, 0ah
mov ecx, 8
division:
mov edx, 0
div ebx
push edx
loop division
mov ecx, 8
writechar:
mov ah, 2
pop edx
or dl, 30h
int 21h
loop writechar
ret
hex_to_dec endp

end main