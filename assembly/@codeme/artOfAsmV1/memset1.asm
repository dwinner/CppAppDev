; memset1.asm
;
;  Naive memset function.

            include zstrings.inc

            .code
memset1     proc
            push    rcx
            
; If number of bytes to copy is zero,
; don't enter loop:

            test    rcx, rcx
            jz      noMemset
            
memsetLp:   mov     [rdi][rcx*1 - 1], al
            dec     rcx
            jnz     memsetLp
            
noMemset:   pop     rcx
            ret
memset1     endp
            end
