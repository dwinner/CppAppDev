; stringCmp2.asm
;
;  SSE variant of the stringCmp function.
;
; On Entry:
;
;   RSI     Points at source1 string object
;   RSI     Points at source2 string object.
;
; On Exit:
;
;   Condition code flags are set based on the comparison.

            include string.inc

            .code
stringCmp2  proc
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
            
; Use the length of the source1 string (choice is
; arbitrary, could use source2 length as well).

            mov     ecx, [rsi-sohs].strObject.strLength
            
; Compare 16 bytes at a time until we reach the end of
; the string(s) or they are not equal at some point

            xor      rbx, rbx
cmp16:      movdqa   xmm0, [rsi][rbx*1]
            pcmpeqb  xmm0, [rdi][rbx*1]
            pmovmskb eax, xmm0
            cmp      ax, 0FFFFh     ;All bytes equal?
            jne      misMatch
            add      rbx, 16
            cmp      rbx, rcx
            jb       cmp16
            
; We've just exhausted all the characters
; in the source1 string at least to the zero
; byte (and probably beyond). All characters
; were equal (including the zero bytes). So
; the strings must be equal.

strsEqual:  movdqu  xmm0, xmm0Save
            movdqu  xmm1, xmm1Save
            add     rsp, 32
            pop     rdi
            pop     rsi
            pop     rcx
            pop     rbx
            pop     rax
            cmp     rax, rax        ;Force ZF=1
            ret
            
; Drop down here when the block of 16 bytes
; in source1 don't match the corresponding
; byte in source2. Find the first byte that
; doesn't match and use that for the string
; comparison.


misMatch:   not     ax
            bsf     eax, eax
            lea     rbx, [rbx][rax]
            
; If the mismatch is beyond the end of the string
; (including beyond the zero byte), then the 
; strings are equal.

            cmp     ebx, ecx
            ja      strsEqual
                        
            movdqu  xmm0, xmm0Save
            movdqu  xmm1, xmm1Save
            add     rsp, 32
            mov     al, [rsi][rbx*1] ;Set flags based on
            cmp     al, [rdi][rbx*1] ; compare of last byte.
            pop     rdi
            pop     rsi
            pop     rcx
            pop     rbx
            pop     rax
            ret
stringCmp2  endp
            end
