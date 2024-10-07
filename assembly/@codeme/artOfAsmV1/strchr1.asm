; strchr1.asm
;
;  Naive strchr function.
;
; RSI-      Points at string
; AL-       Character to search for
;
; Returns:
;
; RAX-      Position of char, or NULL if not present

            include zstrings.inc
            
            .code

strchr1     proc
            push    rsi
            dec     rsi              ;Make up for inc, below
srch4Char:  inc     rsi

; Compare the current string character
; against the match character (in AL) and
; against zero.

            cmp     al, [rsi]
            je      foundChar
            cmp     byte ptr [rsi], 0
            jne     srch4Char
            pop     rsi
            xor     rax, rax
            ret              ;Return NULL in RAX

foundChar:  mov     rax, rsi ;Return ptr to matching char
            pop     rsi
            ret
strchr1     endp
            end
