; strcmp1.asm
;
;  Naive string compare
;
; On entry:
;
;  RSI-     Points at first (left) source string
;  RDI-     Points at second (right) source string.
;
; On exit:
;
;  RAX:     <0 if left < right
;           =0 if left == right
;           >0 if left > right

            include zstrings.inc
            
            .code

strcmp1     proc
            push    rsi
            push    rdi
            xor     rax, rax        ;Clear HO bytes
 
strcmpLp:   mov     al, [rsi]
            cmp     al, 0
            je      cmpDone
            inc     rdi
            inc     rsi
            sub     al, [rdi-1]     ;Sets flags like cmp
            je      strcmpLp

; Strings are not equal at this point

            movsx   rax, al
            pop     rdi
            pop     rsi
            ret

; Reached a zero-terminating byte.
; Set result (-, 0, +):
            
cmpDone:    sub     al, [rdi]
            movsx   rax, al
            pop     rdi
            pop     rsi
            ret
strcmp1     endp
            end
