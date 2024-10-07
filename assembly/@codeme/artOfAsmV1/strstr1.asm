; strstr1.asm
;
;  Naive strstr function.
;
; RSI-      Points at haystack (string to search through)
; RDI-      Points at needle (string to search for)
;
; Returns:
;
; RAX-      Position of substring, or NULL if not present

            include zstrings.inc
            
            .code
strstr1     proc
            push    rsi
            push    rdi
            
            mov     al, [rdi]       ;Get 1st char of needle.
            cmp     al, 0           ;Empty str matches all.
            je      mtchEmpty
            
            dec     rsi             ;Make up for inc, below.
srch4Char:  inc     rsi             ;Next haystack char.
            cmp     al, [rsi]
            je      foundChar
            cmp     byte ptr [rsi], 0
            jne     srch4Char
            
; Hit end of string without finding the first character
; of the needle string.

            pop     rdi
            pop     rsi
            xor     rax, rax
            ret              ;Return NULL in RAX

; Current character at haystack pointer (RDI)
; matches the first character of the needle.
; See if the rest of the needle string matches
; chars in the haystack:

foundChar:  push    rsi
            push    rdi
            sub     rdi, rsi
cmpStr:     inc     rsi
            mov     al, [rdi][rsi*1] ;Next needle char
            cmp     al, 0     ;End of needle?
            je      endNeedle
            cmp     al, [rsi] ;Needle=haystk?
            je      cmpStr
            
; Characters in needle don't match haystack char.

            pop     rdi
            pop     rsi
            mov     al, [rdi]       ;Get 1st needle char.
            jmp     srch4Char       ;Skip 1 haystk & continue.
            
endNeedle:  pop     rdi
            pop     rsi
            mov     rax, rsi
            pop     rsi             ;Restore original needle
            pop     rdi             ; and haystack value.
            ret     

; If the needle is an empty string, then
; match the haystack regardless of what it is.

mtchEmpty:  pop     rsi
            pop     rdi
            mov     rax, rsi
            ret

strstr1     endp
            end
