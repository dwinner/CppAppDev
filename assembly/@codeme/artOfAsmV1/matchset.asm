; matchSet.asm
;
;  AL-      Character to test
;  RDI-     Points at a string containing a set of 
;           characters
;
; returns
;
;  AL-      zero if no match, non-zero character code 
;           if match.

            include zstrings.inc

            .code
matchSet    proc
            push    rdi
            dec     rdi
cmpLp:      inc     rdi
            cmp     byte ptr [rdi], 0
            je      noMatch
            
            cmp     al, [rdi]
            jne     cmpLp
            pop     rdi
            ret
            
noMatch:    pop     rdi
            xor     eax, eax
            ret
matchSet    endp
            end