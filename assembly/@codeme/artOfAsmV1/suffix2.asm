; suffix2.asm
;
;  SSE variant of the suffix function.
;
; On Entry:
;
;   RSI     Points at suffix string.
;   RDI     Points at source string object (large string)
;
; On Exit:
;
;   ZF=1 if suffix (RSI) is a suffix of source (RDI)
;   ZF=0 if suffix (RSI) is not a suffix of source (RDI)

            include    string.inc

            .code
suffix2     proc
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

; Compare through the length of suffix.
; Bail if suffix's length is longer than source.

            mov     ecx, [rsi-sohs].strObject.strLength
            cmp     ecx, [rdi-sohs].strObject.strLength
            ja      strsNE
            
; Make source's starting index equal to its original
; starting address plus its length, minus the length
; of the source1 string:

            mov     eax, [rdi-sohs].strObject.strLength
            add     rdi, rax
            sub     rdi, rcx
            
; Special case for zero-length suffix string.

            test    ecx, ecx
            jz      strsEqual
                        
; Compare 16 bytes at a time until we reach the end of
; the string(s) or they are not equal at some point.
; Note that RDI is probably NOT 16-byte aligned at this
; point whereas RSI is 16-byte aligned.

            xor      rbx, rbx
cmpSufx:    movdqu   xmm0, [rdi][rbx*1]
            pcmpeqb  xmm0, [rsi][rbx*1]
            pmovmskb eax, xmm0
            cmp      ax, 0FFFFh     ;All bytes equal?
            jne      misMatch
            add      rbx, 16
            cmp      rbx, rcx
            jb       cmpSufx
            
; We've just exhausted all the characters
; in the suffix string.

strsEqual:  movdqu  xmm0, xmm0Save
            movdqu  xmm1, xmm1Save
            add     rsp, 32
            cmp     eax, eax        ;Force ZF=1
            jmp     allDone
            
; Drop down here when the block of 16 bytes
; in suffix don't match the corresponding
; byte in source. Compare any remaining
; bytes in suffix to the corresponding
; bytes in source: 

misMatch:   not     ax              ;Compute position of 1st
            bsf     eax, eax        ; non-match.
            lea     rbx, [rbx][rax]
            
; If we've matched at least the number
; of characters in suffix then we have success. 
; We can match more because there might be 
; garbage after both strings that just happens 
; to match.

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
suffix2     endp
            end
