; noMatchSet.asm
;
;  AL-      Character to test
;  RDI-     Points at a string containing a set of 
;           characters
;
; returns
;
;  AL-      zero if match, 1 if we hit the end of the
;           cset without a match.

            include zstrings.inc

            .code
noMatchSet  proc
            push    rdi
            dec     rdi
cmpLp:      inc     rdi
            cmp     byte ptr [rdi], 0
            je      noMatch
            
            cmp     al, [rdi]
            jne     cmpLp
            
; If we had a match, we need to fail:
            
            xor     rax, rax
            pop     rdi
            ret

; If we hit the zero byte, we succeeded.
            
noMatch:    pop     rdi
            mov     eax, 1
            ret
noMatchSet  endp
            end