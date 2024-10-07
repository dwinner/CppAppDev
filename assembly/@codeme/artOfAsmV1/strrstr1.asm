; strrstr1.asm
;
;  Naive strrstr function.
;
; RSI-      Points at haystack (string to search through)
; RDI-      Points at needle (string to search for)
;
; Returns:
;
; RAX-      Position of last occurrence of needle in haystack,
;           or NULL if not present

            include zstrings.inc
            
            .code

strrstr1    proc
            push    rbp
            push    rbx
            push    rcx
            push    rsi
            push    rdi
            
            mov     rbp, rsi        ;Original start of haystk.
            
            xor     rcx, rcx        ;Assume no match.
            
            mov     al, [rdi]       ;Get 1st char of needle.
            dec     rsi             ;Make up for inc, below.
srch4End:   inc     rsi             ;Next haystack char.
            cmp     al, [rsi]
            je      foundChar
            cmp     byte ptr [rsi], 0
            jne     srch4End
            
; We've reached the end of the string.
; Start searching backwards for the needle.
; If RCX is null at this point, the needle
; doesn't exist in the haystack.

            test    rcx, rcx
            jz      allDone

; Compare needle to chars at RCX. If they
; match through the end of the needle, we're
; done (and successful). Otherwise, back up
; to the next occurrence of the 1st needle char.

cmpNeedle:  mov     rsi, rcx
            mov     rbx, rdi
            sub     rsi, rdi
            dec     rbx
cmpNdlLp:   inc     rbx
            mov     ah, [rbx]       ;Needle char
            cmp     ah, 0           ;At end of needle?
            je      allDone
            cmp     ah, [rsi][rbx*1] ;Hay char match?
            je      cmpNdlLp

; This substring in haystack did not match the needle.
; search backwards in haystack until we find the 1st
; character of the needle.

srchBack:   dec     rcx
            cmp     rcx, rbp
            jb      noMatch
            cmp     al, [rcx]       ;Match 1st char of needle?      
            jne     srchBack
            jmp     cmpNeedle

noMatch:    xor     rcx, rcx        
allDone:    mov     rax, rcx
            pop     rdi
            pop     rsi
            pop     rcx
            pop     rbx
            pop     rbp
            ret              ;Return NULL in RAX
            
; At this point, we've matched the first character
; of the needle. Save a pointer to this position
; in haystack; unless it's the end of the haystack,
; in which case we can quit.

foundChar:  cmp     al, 0
            je      allDone
            mov     rcx, rsi
            jmp     srch4End

strrstr1    endp
            end
