; copy16.asm
;
; Common code used by strcpy2 and strcpy3:
;
; ECX -     Number of bytes to copy - 1 (e.g., 0=1 byte, 
;           1=2 bytes,etc.).
; RSI -     Source address.
; RDI+RDI-  Dest address.

            include zstrings.inc
            
            .code
copy16      proc

            lea       rax, s3JmpTbl
            jmp       qword ptr [rax][rcx*8]
            
s3JmpTbl    qword     cpy1,  cpy2,  cpy3
            qword     cpy4,    cpy5,  cpy6,  cpy7
            qword     cpy8,    cpy9,  cpy10, cpy11
            qword     cpy12,   cpy13, cpy14, cpy15
            qword     cpy16
            
; Copy 1 to 16 bytes from [RSI] to [RDI][RSI*1] based
; on the value in ECX (which is byte count - 1).
            
cpy3:       mov     ax, [rsi+1]
            mov     [rdi][rsi*1+1], ax
cpy1:       mov     al, [rsi]
            mov     [rdi][rsi*1], al
            jmp     allDone
            
cpy2:       mov     ax, [rsi]
            mov     [rdi][rsi*1], ax
            jmp     allDone
            
cpy4:       mov     eax, [rsi]
            mov     [rdi][rsi*1], eax
            jmp     allDone

cpy5:       mov     eax, [rsi]
            mov     [rdi][rsi*1], eax
            mov     al, [rsi+4]
            mov     [rdi][rsi*1+4], al
            jmp     allDone

cpy7:       mov     al, [rsi+6]
            mov     [rdi][rsi*1+6], al
cpy6:       mov     eax, [rsi]
            mov     [rdi][rsi*1], eax
            mov     ax, [rsi+4]
            mov     [rdi][rsi*1+4], ax
            jmp     allDone
            
cpy9:       mov     al, [rsi+8]
            mov     [rdi][rsi*1+8], al
cpy8:       mov     rax, [rsi]
            mov     [rdi][rsi*1], rax
            jmp     allDone

cpy11:      mov     al, [rsi+10]
            mov     [rdi][rsi*1+10], al
cpy10:      mov     ax, [rsi+8]
            mov     [rdi][rsi*1+8], ax
            mov     rax, [rsi]
            mov     [rdi][rsi*1], rax
            jmp     allDone

cpy13:      mov     al, [rsi+12]
            mov     [rdi][rsi*1+12], al
cpy12:      mov     rax, [rsi]
            mov     [rdi][rsi*1], rax
            mov     eax, [rsi+8]
            mov     [rdi][rsi*1+8], eax
            jmp     allDone
            
cpy15:      mov     al, [rsi+14]
            mov     [rdi][rsi*1+14], al
cpy14:      mov     ax, [rsi+12]
            mov     [rdi][rsi*1+12], ax
            mov     rax, [rsi]
            mov     [rdi][rsi*1], rax
            mov     eax, [rsi+8]
            mov     [rdi][rsi*1+8], eax
            jmp     allDone
            
cpy16:      mov     rax, [rsi]
            mov     [rdi][rsi*1], rax
            mov     rax, [rsi+8]
            mov     [rdi][rsi*1+8], rax
            

; Restore registers and leave:

allDone:    
            ret
copy16      endp
            end
