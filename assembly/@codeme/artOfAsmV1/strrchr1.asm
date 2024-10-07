; strrchr1.asm
;
;  Naive strrchr function.
;
; RSI-      Points at string
; AL-       Character to search for
;
; Returns:
;
; RAX-      Position of char, or NULL if not present
;
; Also searches forward in the string, but
; does not quit until it sees the zero
; terminating byte. Tracks the address
; of the last matching character it has
; seen.

            include zstrings.inc
            
            .code
strrchr1    proc
            push    rsi
            push    rdi
            xor     rdi, rdi        ;Assume no match
            dec     rsi             ;Make up for inc, below
srch4Char:  inc     rsi
            cmp     al, [rsi]
            jne     try0
            mov     rdi, rsi        ;Note last match
            
try0:       cmp     byte ptr [rsi], 0
            jne     srch4Char
            mov     rax, rdi
            pop     rdi
            pop     rsi
            ret

strrchr1    endp
            end
