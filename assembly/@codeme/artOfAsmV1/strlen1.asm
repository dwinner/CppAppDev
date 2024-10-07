            
;***************************************************************
;            
; strlen1.asm
;
;  Naive string length function.
;
; RSI-      Points at string
;
; Returns:
;
; RAX-      String Length

            include zstrings.inc

            .code
strlen1     proc
            push    rsi
            push    rcx
            mov     cl, 0
            mov     rax, -1
strLenLp:   inc     rax
            cmp     cl, [rsi][rax*1]
            jnz     strLenLp
            pop     rcx
            pop     rsi
            ret
strlen1     endp
            end