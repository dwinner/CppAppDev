; prefix2.asm
;
;  SSE variant of the prefix function.
;
; On Entry:
;
;   RSI     Points at prefix string.
;   RDI     Points at source string object (large string)
;
; On Exit:
;
;   ZF=1 if source1 is a prefix of source2
;   ZF=0 if source1 is not a prefix of source2

            include    string.inc

            .code
prefix2     proc
xmm0Save    textequ <[rsp]>
xmm1Save    textequ <[rsp+16]>

            push    rax
            push    rbx
            push    rcx
            push    rsi
            push    rdi
            sub     rsp, 32
            movdqu  xmm0Save, xmm0
            movdqu  xmm1Save, xmm1

; Use the length of the prefix string.

            mov     ecx, [rsi-sohs].strObject.strLength
            
; Compare 16 bytes at a time until we reach the end of
; the string(s) or they are not equal at some point

            xor      rbx, rbx
cmpPrfx:    movdqa   xmm0, [rsi][rbx*1]
            pcmpeqb  xmm0, [rdi][rbx*1]
            pmovmskb eax, xmm0
            cmp      ax, 0FFFFh     ;All bytes equal?
            jne      misMatch
            add      rbx, 16
            cmp      rbx, rcx
            jb       cmpPrfx
            
; We've just exhausted all the characters
; in the prefix string.

strsEqual:  movdqu  xmm0, xmm0Save
            movdqu  xmm1, xmm1Save
            add     rsp, 32
            cmp     rax, rax        ;Force ZF=1
            jmp     allDone
            
; Drop down here when the block of 16 bytes
; in prefix don't match the corresponding
; byte in source. Compare any remaining
; bytes in prefix to the corresponding
; bytes in source: 

misMatch:   not     ax              ;Compute position of 1st
            bsf     eax, eax        ; non-match.
            lea     ebx, [ebx][eax]
            
; EBX contains the index of the first character that
; does not match between the two strings. ECX contains
; the current prefix string length.

            cmp     ebx, ecx
            jae     strsEqual
            
strsNE:     movdqu  xmm0, xmm0Save
            movdqu  xmm1, xmm1Save
            add     rsp, 32         ;Sets ZF=0
allDone:    pop     rdi
            pop     rsi
            pop     rcx
            pop     rbx
            pop     rax
            ret
prefix2     endp
            end
