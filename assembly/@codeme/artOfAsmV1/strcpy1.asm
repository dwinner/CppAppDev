; strcpy1.asm
;
;  Naive string copy
;
; On entry:
;
;  RSI-     Points at source string
;  RDI-     Points at destination buffer.

            include zstrings.inc
            
            .code
strcpy1     proc
            push    rsi
            push    rdi
            push    rax
            
strcpyLp:   mov     al, [rsi]
            mov     [rdi], al
            inc     rdi
            inc     rsi
            cmp     al, 0
            jne     strcpyLp
            
            pop     rax
            pop     rdi
            pop     rsi
            ret
strcpy1     endp
            end
