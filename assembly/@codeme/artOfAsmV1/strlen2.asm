            
;***************************************************************
;            
; strlen2.asm
;
;  String length function using the scasb instruction.
;
; RSI-      Points at string
;
; Returns:
;
; RAX-      String Length

            include zstrings.inc

            .code
            

strlen2     proc
            push    rcx
            push    rdi
            or      rcx, -1
            mov     rdi, rsi
            mov     al, 0
            cld
    repne   scasb
            mov     rax, rdi
            sub     rax, rsi
            dec     rax
            pop     rdi
            pop     rcx
            ret
strlen2     endp
            end