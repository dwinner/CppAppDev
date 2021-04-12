; 12.7 - 7 - Showing Register Status Values

;NB!FSTENV instruction doesn t work properly! Impossible to obtain correct Tag Word value

; FPU fas 8 80 - bit registers R0 - R7.
; The very first value is always loaded to R7.Next value goes to R6, etc.
; Tag Word indicates the content of each register.
; Tag Word(15 - 14 bits) = R7, ... (01 - 00 bits) = R0.
; finit-- > all bits are set to 1.
; When first value is loaded, (15 - 14 bits) change their value.
; Second loaded value changes content of(13 - 12 bits), etc.

; 00 - valid value;
; 01 - zero value;
; 10 - invalid value;
; 11 - empty.

; Also, tag word can be used to indicate which register is currently st(0).

; Otherwise, Status word TOP field(13 - 11 bits) also can be used to determine st(0).

include Irvine32.inc

; .386
; .model flat, stdcall
;.stack 4096
; ExitProcess PROTO, dwExitCode:DWORD

.data

fpuenv FPU_ENVIRON <>

A real8 - 1.0
B real8 0.0

prompt byte "st(0) = R", 0
st0reg byte 0

prompt1 byte " Register contains valid non-zero value", 0
prompt2 byte " Register contains zero", 0
prompt3 byte " Register contains special value", 0
prompt4 byte " Register is empty", 0

.code
main PROC

finit

fld A
fld B

FSTENV fpuenv.tagWord
FSTSW fpuenv.statusWord

call ShowFPUStack
call Crlf

mov ax, fpuenv.statusWord
shr ax, 11
and ax, 00111b
or al, 30h
mov st0reg, al

mov edx, offset prompt
call WriteString

mov al, st0reg
call WriteChar
call Crlf
call Crlf

mov ecx, 8
mov edi, 0
L1:
push ecx
mov al, 'R'
call WriteChar
mov eax, edi
or al, 30h
call WriteChar
push edi
mov bx, fpuenv.tagWord
mov ecx, edi
add ecx, edi
shr bx, cl
and bl, 0011b
.if bl == 0
mov edx, offset prompt1
call WriteString
.elseif bl == 1
mov edx, offset prompt2
call WriteString
.elseif bl == 2
mov edx, offset prompt3
call WriteString
.elseif bl == 3
mov edx, offset prompt4
call WriteString
.endif
call Crlf
pop edi
inc edi
pop ecx
loop L1

call Crlf

exit
main ENDP
END main