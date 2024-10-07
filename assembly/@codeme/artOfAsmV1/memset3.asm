; memset3-
;
;  SSE version, using aligned accesses:

            include zstrings.inc
            .code


memset3     proc
saveXMM0    textequ <[rsp]>
            push    rdi
            push    rdx
            push    rcx
            push    rbx
            push    rax
            
; Set aside 16 bytes on the stack
; to preserve XMM0.

            sub     rsp, 16
            movdqu  saveXMM0, xmm0

            
; Replicate the byte in AL throughout
; the 16 bytes in XMM:

            mov     ah, al
            movd    xmm0, eax
            pshuflw xmm0, xmm0, 0
            pshufd  xmm0, xmm0, 0
            movq    rax, xmm0       ;Need value in all 8 bytes
            
; If we're filling less than 16 bytes,
; skip all the address alignment code.

            cmp     rcx, 16
            jb      fillLT16
            
; First of all, get the output address
; aligned on a block of 16 bytes so
; we can use aligned moves. This code
; does this in a sneaky way: We know
; we're writing at least 16 bytes, so
; this code writes XMM0 (unaligned) to
; the address in RDI. It then adds 16
; to the address and ANDs RDI with -16
; (0FFFF...FF0h), which aligns RDI
; to the next 16-byte boundary after
; the original RDI address.

            movdqu  [rdi], xmm0
            mov     rbx, rdi
            add     rdi, 16
            and     rdi, -16

            
; This code also has to decrement the
; byte count by the number of bytes
; up to the next aligned address.
; Subtracting the new RSI value from
; the original RSI value (in RBX)
; produces the negation of this count.
; Adding that to RCX decrements RCX
; by the appropriate amount.

            sub     rbx, rdi
            add     rcx, rbx 

; The loop below writes 16 bytes at a time.
; Make sure we're initializing at least
; 64 bytes before falling into the loop.

            cmp     rcx, 16
            jb      fillLT16
            
; Fill blocks of 16 bytes:

loop64:     movdqa  [rdi],    xmm0
            add     rdi, 16
            sub     rcx, 16
            cmp     rcx, 16
            jae     loop64
            
; Less than 16 bytes at this point

fillLT16:   lea     rbx, jmpTable
            jmp     qword ptr [rbx][rcx*8]
            
jmpTable    qword    b0,  b1,  b2,  b3
            qword    b4,  b5,  b6,  b7
            qword    b8,  b9, b10, b11
            qword   b12, b13, b14, b15

; b12- write 12 bytes to memory at RDI:
; b8-  write 8 bytes to memory at RDI:
; b4-  write 4 bytes to memory at RDI:
;
; Note: dword-aligning the start of these
; cases improves performance.
             
            align   dword       
b12:        mov     [rdi+8], eax
b8:         mov     [rdi+4], eax
b4:         mov     [rdi], eax
            jmp     b0
                    

; b13- write 13 bytes to memory at RDI:
; b9-  write 9 bytes to memory at RDI:
; b5-  write 5 bytes to memory at RDI:

            align   dword
b13:        mov     [rdi+9], eax
b9:         mov     [rdi+5], eax
b5:         mov     [rdi+1], eax
            mov     [rdi], al
            jmp     b0


; b14- write 14 bytes to memory at RDI:
; b10- write 10 bytes to memory at RDI:
; b6-  write 6 bytes to memory at RDI:
; b2-  write 2 bytes to memory at RDI:

            align   dword
b14:        mov     [rdi+10], eax
b10:        mov     [rdi+6], eax
b6:         mov     [rdi+2], eax
b2:         mov     [rdi], ax
            jmp     b0

; b15- write 15 bytes to memory at RDI:
; b11- write 11 bytes to memory at RDI:
; b7-  write 7 bytes to memory at RDI:
; b3-  write 3 bytes to memory at RDI:
; b1-  write 1 byte to memory at RDI:
; b0-  no bytes to write.

            align   dword
b15:        mov     [rdi+11], eax
b11:        mov     [rdi+7], eax
b7:         mov     [rdi+3], eax
b3:         mov     [rdi+1], ax
b1:         mov     [rdi], al

; Restore registers and return:

b0:         movupd  xmm0, saveXMM0    
            add     rsp, 16
            pop     rax
            pop     rbx
            pop     rcx
            pop     rdx
            pop     rdi
            ret
memset3     endp
            end
