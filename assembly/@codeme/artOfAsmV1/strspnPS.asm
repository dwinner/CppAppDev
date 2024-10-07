; strspnPS.asm
;
;  Bit set (power set) version.
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
strspnPS    proc
cset        textequ <[rsp]>

            push    rsi
            push    rdi
            sub     rsp, 32 ;Make room for 256 bits
            
; Create an empty set:

            xor     rax, rax
            mov     cset, rax
            mov     cset[8], rax
            mov     cset[16], rax
            mov     cset[24], rax
            
; Initialize the set with the characters pointed at
; by RDI:

            dec     rdi
            jmp     enterCset
            
initCset:   movzx   eax, byte ptr [rdi]
            bts     cset, rax
            
enterCset:  inc     rdi
            cmp     byte ptr [rdi], 0
            jne     initCset

            
; While character at [RSI] is in the set pointed at
; by [RDI], skip over the characters:

            dec     rsi
ssLp:       inc     rsi
            movzx   rax, byte ptr [rsi]
            cmp     al, 0           ;End of str, no match
            je      allDone
            bt      cset, rax       ;See if char in set
            jc      ssLp            ;While char in cset
            
            
allDone:    mov     rax, rsi
            add     rsp, 32
            pop     rdi
            pop     rsi
            sub     rax, rsi
            ret
strspnPS    endp
            end
