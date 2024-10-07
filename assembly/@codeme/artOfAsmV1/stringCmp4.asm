; stringCmp4.asm
;
;  String comparison using pcmpistri instruction.
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
stringCmp4  proc

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
            jc        different2    ;Not equal
            
; At this point, the zero flag must be set, so there
; must have been a zero byte in src1 or src2. As the
; characters also match, the strings must be equal.

same:       xor     rdi, rdi        ;Force ZF=1
            jmp     exit
            

; Branch to this point from the code where we were
; aligning RSI to a 16-byte boundary and found a
; different character (between RSI and RDI).

different2: add     rsi, rcx
exit:       movdqu  xmm0, xmm0Save
            add     rsp, 16
            mov     al, [rsi]
            cmp     al, [rdi][rsi*1]
            pop     rcx
            pop     rdi
            pop     rsi
            pop     rax
            ret
            
stringCmp4  endp
            end
