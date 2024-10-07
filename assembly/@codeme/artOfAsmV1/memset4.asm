; memset4-
;
;  AVX version, using aligned accesses:

            include zstrings.inc
            .code


memset4     proc
saveYMM0    textequ <[rsp]>
temp        textequ <[rsp+32]>

            push    rdi
            push    rdx
            push    rcx
            push    rbx
            push    rax
            
; Set aside 32 bytes on the stack
; to preserve YMM0.

            sub     rsp, 64
            vmovupd  saveYMM0, ymm0

            
; Replicate the byte in AL throughout
; the 16 bytes at [rsp+64] we this
; code can load that data into XMM
; register a little later:

            mov     ah, al
            movd    xmm0, eax
            pshuflw xmm0, xmm0, 0
            pshufd  xmm0, xmm0, 0
            movdqu  temp, xmm0
            movdqu  temp[16], xmm0
            vmovupd ymm0, ymmword ptr temp
            movq    rax, xmm0       ;Need value in all 8 bytes
            
; If we're filling less than 16 bytes,
; skip all the address alignment code.

            cmp     rcx, 32
            jb      fillLT32
            
; First of all, get the output address
; aligned on a block of 32 bytes so
; we can use aligned moves. This code
; does this in a sneaky way: We know
; we're writing at least 32 bytes, so
; this code writes XMM0 (unaligned) to
; the address in RDI. It then adds 32
; to the address and ANDs RDI with -32
; (0FFFF...FE0h), which aligns RDI
; to the next 32-byte boundary after
; the original RDI address.

            vmovupd [rdi], ymm0
            mov     rbx, rdi
            add     rdi, 32
            and     rdi, -32

            
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

; The loop below writes 64 bytes at a time.
; Make sure we're initializing at least
; 64 bytes before falling into the loop.

            cmp     rcx, 32
            jb      fillLT32
            
; Fill blocks of 32 bytes:

loop32:     vmovupd [rdi], ymm0
            add     rdi, 32
            sub     rcx, 32         ;Note: like a CMP
            cmp     rcx, 32
            jae     loop32
            
; Less than 32 bytes at this point

fillLT32:   lea     rbx, jmpTable32
            jmp     qword ptr [rbx][rcx*8]
            
jmpTable32  qword    b0,  b1,  b2,  b3
            qword    b4,  b5,  b6,  b7
            qword    b8,  b9, b10, b11
            qword   b12, b13, b14, b15
            qword   b16, b17, b18, b19
            qword   b20, b21, b22, b23
            qword   b24, b25, b26, b27
            qword   b28, b29, b30, b31

; b12- write 12 bytes to memory at RDI:
; b8-  write 8 bytes to memory at RDI:
; b4-  write 4 bytes to memory at RDI:
;
; Note: dword-aligning the start of these
; cases improves performance.
             
            align   dword       
b28:        mov     [rdi+24], eax
b24:        mov     [rdi+16], rax
b16:        mov     [rdi+8], rax
            mov     [rdi], rax

            align   dword
b20:        mov     [rdi+16], eax
            mov     [rdi+8], rax
            mov     [rdi], rax
            jmp     b0
            
            align   dword
b12:        mov     [rdi+8], eax
b8:         mov     [rdi], rax
            jmp     b0
            
            align   dword
b4:         mov     [rdi], eax
            jmp     b0
                    

; b13- write 13 bytes to memory at RDI:
; b9-  write 9 bytes to memory at RDI:
; b5-  write 5 bytes to memory at RDI:

            align   dword
b29:        mov     [rdi+25], eax
b25:        mov     [rdi+17], rax
b17:        mov     [rdi+9], rax
            mov     [rdi+1], rax
            mov     [rdi], al
            jmp     b0

            align   dword
b21:        mov     [rdi+17], eax
            mov     [rdi+9], rax
            mov     [rdi+1], rax
            mov     [rdi], al
            jmp     b0

            align   dword
b13:        mov     [rdi+9], eax
b9:         mov     [rdi+1], rax
            mov     [rdi], al
            jmp     b0

            align   dword
b5:         mov     [rdi+1], eax
            mov     [rdi], al
            jmp     b0


; b14- write 14 bytes to memory at RDI:
; b10- write 10 bytes to memory at RDI:
; b6-  write 6 bytes to memory at RDI:
; b2-  write 2 bytes to memory at RDI:

            align   dword
b30:        mov     [rdi+26], eax
b26:        mov     [rdi+18], rax
b18:        mov     [rdi+10], rax
            mov     [rdi+2], rax
            mov     [rdi], ax
            jmp     b0

            align   dword
b22:        mov     [rdi+18], eax
            mov     [rdi+10], rax
            mov     [rdi+2], rax
            mov     [rdi], ax
            jmp     b0

            align   dword
b14:        mov     [rdi+10], eax
b10:        mov     [rdi+2], rax
            mov     [rdi], ax
            jmp     b0

            align   dword
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
b7:         mov     [rdi+3], eax
            mov     [rdi+1], ax
            mov     [rdi], al
            jmp     b0
            
            align   dword
b31:        mov     [rdi+27], eax
b27:        mov     [rdi+19], rax
            mov     [rdi+11], rax
            mov     [rdi+1],   ax
            mov     [rdi],     al
            jmp     b0

            align   dword
b23:        mov     [rdi+19], eax
b19:        mov     [rdi+9],  rax
            mov     [rdi+1],  rax
            mov     [rdi],     al
            jmp     b0

            align   dword
b15:        mov     [rdi+11], eax
b11:        mov     [rdi+3], rax
b3:         mov     [rdi+1], ax
b1:         mov     [rdi], al



; Restore registers and return:

b0:         vmovupd ymm0, saveYMM0    
            add     rsp, 64
            pop     rax
            pop     rbx
            pop     rcx
            pop     rdx
            pop     rdi
            ret
memset4     endp
            end
