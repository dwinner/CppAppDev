; strstr2.asm
;
;  strstr function using cmpsb instruction.
;
; RSI-      Points at haystack (string to search through)
; RDI-      Points at needle (string to search for)
;
; Returns:
;
; RAX-      Position of substring, or NULL if not present

            include zstrings.inc

; sseStrlen
;
;  string length based on SSE instructions

sseStrlen   textequ	<strlen7>

; sseStrchr-
;
;    SSE-based strchr function.

sseStrchr	textequ	<strchr4>
            
            .code
strstr2     proc
            push    rbx
            push    rcx
            push    rsi
            push    rdi
            
            xchg    rsi, rdi
            call    sseStrlen
            xchg    rsi, rdi 
            mov     rbx, rax        ;Save needle length
            
            mov     al, [rdi]       ;Get 1st char of needle.
            cmp     al, 0           ;Empty str matches all.
            je      mtchEmpty
            
            dec     rsi             ;Make up for inc, below.
srch4Char:  inc     rsi             ;Next haystack char.
            call    sseStrchr
            mov     rsi, rax
            test    rax, rax
            jnz     foundChar
            
; Hit end of string without finding the first character
; of the needle string.

            pop     rdi
            pop     rsi
            pop     rcx
            pop     rbx
            xor     rax, rax
            ret              ;Return NULL in RAX

; Current character at haystack pointer (RDI)
; matches the first character of the needle.
; See if the rest of the needle string matches
; chars in the haystack:

foundChar:  push    rsi
            push    rdi
            mov     rcx, rbx
    repe    cmpsb
            je      endNeedle
            pop     rdi
            pop     rsi
            jmp     srch4Char       
            
endNeedle:  pop     rdi
            pop     rsi
            mov     rax, rsi
            pop     rsi             ;Restore original needle
            pop     rdi             ; and haystack value.
            pop     rcx
            pop     rbx
            ret     

; If the needle is an empty string, then
; match the haystack regardless of what it is.

mtchEmpty:  pop     rsi
            pop     rdi
            pop     rcx
            pop     rbx
            mov     rax, rsi
            ret

strstr2     endp
            end
