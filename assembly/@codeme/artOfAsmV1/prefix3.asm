; prefix3.asm
;
;  pcmpistri variant of the prefix function.
;
; On Entry:
;
;   RSI     Points at prefix string.
;   RDI     Points at source string object (large string)
;
; On Exit:
;
;   ZF=1 if prefix (RSI) is a prefix of source (RDI)
;   ZF=0 if prefix (RSI) is not a prefix of source (RDI)

            include string.inc
            
            .code
prefix3     proc

xmm0Save    textequ <[rsp]>

            push    rax
            push    rsi
            push    rdi
            push    rcx
            sub     rsp, 16
            movdqu  xmm0Save, xmm0
            
            
            sub       rdi, rsi
            sub       rsi, 16            
scLoop:     add       rsi, 16               ;On to next block.
            movdqa    xmm0, [rsi]
            pcmpistri xmm0, [rsi][rdi*1], scFlags
            ja        scLoop        ;Equal, no zero bytes
            jnc       same          ;Had a zero byte
            
; Branch to this point from the code where we were
; aligning RSI to a 16-byte boundary and found a
; different character (between RSI and RDI).

different:  add     rsi, rcx
            mov     al, [rsi]
            cmp     al, 0
            jne     notSame
same:       xor     rdi, rdi        ;Forces ZF=1
notSame:    movdqu  xmm0, xmm0Save
            add     rsp, 16
            mov     al, [rsi]
            cmp     al, [rdi][rsi*1]
            pop     rcx
            pop     rdi
            pop     rsi
            pop     rax
            ret
            
prefix3     endp
            end
