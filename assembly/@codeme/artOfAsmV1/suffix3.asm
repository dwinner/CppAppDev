; suffix3.asm
;
;  pcmpistri variant of the suffix function.
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
suffix3     proc

xmm0Save    textequ <[rsp]>

            push    rax
            push    rbx
            push    rsi
            push    rdi
            push    rcx
            sub     rsp, 16
            movdqu  xmm0Save, xmm0
            
; Compare through the length of suffix

            mov     ebx, [rdi-sohs].strObject.strLength
            mov     ecx, [rsi-sohs].strObject.strLength
            cmp     ecx, ebx
            ja      strsNE
            
; Make source's starting index equal to its original
; starting address plus its length, minus the length
; of the source1 string:

            mov     eax, [rdi-sohs].strObject.strLength
            add     rdi, rax
            sub     rdi, rcx
            
; Special case for zero-length suffix string.

            test      ecx, ecx
            jz        same
            
            sub       rdi, rsi
            sub       rsi, 16            
scLoop:     add       rsi, 16       ;On to next block.
            movdqa    xmm0, [rsi]
            pcmpistri xmm0, [rsi][rdi*1], scFlags
            ja        scLoop        ;Equal, no zero bytes
            jnc       same          ;Zero byte in suffix. 
            
; There was a mismatch. Locate the differing characters
; (at offset RCX from RSI) and see if there was a zero
; byte or an otherwise mismatched pair. The suffix
; matched if it's a zero byte:

            add     rsi, rcx
            cmp     byte ptr [rsi], 0
            jne     exit
            
same:       xor     rdi, rdi        ;Forces ZF=1
exit:       movdqu  xmm0, xmm0Save
            add     rsp, 16
            mov     al, [rsi]
            cmp     al, [rdi][rsi*1]
            pop     rcx
            pop     rdi
            pop     rsi
            pop     rbx
            pop     rax
            ret

; If the suffix string is longer than the source
; string, then force ZF to be zero on return.

strsNE:     movdqu  xmm0, xmm0Save
            add     rsp, 16         ;Forces ZF=0
            pop     rcx
            pop     rdi
            pop     rsi
            pop     rbx
            pop     rax
            ret
            
suffix3     endp
            end
