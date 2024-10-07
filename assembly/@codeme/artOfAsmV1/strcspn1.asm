; strcspn1.asm
;
;  Naive strcspn function.
;
; RSI-      Points at source string
; RDI-      Points at character set string
;
; Returns:
;
; RAX-      Index of first character not in cset.
;           0 if no chars in cset, string length
;           if all chars in cset.

            include zstrings.inc

            .code
strcspn1    proc
            push    rsi
            push    rdi
            
; While character at [RSI] is in the set pointed at
; by [RDI], skip over the characters:

            dec     rsi
            xor     eax, eax
ssLp:       inc     rsi
            mov     al, [rsi]
            call    noMatchSet
            
            test    eax, eax
            jnz     ssLp
            
            mov     rax, rsi          ;Assume not at end
            cmp     byte ptr [rsi], 0 ;At end of string?
            jne     allDone
            
allDone:    mov     rax, rsi
            pop     rdi
            pop     rsi
            sub     rax, rsi
            ret
strcspn1    endp
            end
