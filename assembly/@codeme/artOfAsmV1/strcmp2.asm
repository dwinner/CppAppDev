; strcmp2.asm
;
;  String comparison using pcmpistri instruction.
;
; On entry:
;
;  RSI-     Points at first (left) source string
;  RDI-     Points at second (right) source string.
;
; On exit:
;
;  RAX:     <0 if left < right
;           =0 if left == right
;           >0 if left > right

            include zstrings.inc
            
            .code
strcmp2     proc

xmm0Save    textequ <[rsp]>
xmm1Save    textequ <[rsp+16]>

            push    rsi
            push    rdi
            push    rcx
            sub     rsp, 32
            movdqu  xmm0Save, xmm0
            movdqu  xmm1Save, xmm1

; Make RDI dependent on RSI so we can
; step through RDI by incrementing RSI:

            sub     rdi, rsi
            
; Okay, 16-byte align string 1 (pointed
; at by RSI):

paraAlign:  test    rsi, 0fh        ;Aligned on 16-byte
            jz      scLoop2         ; boundary?

            mov     al, [rsi]       ;Do the chars match?
            cmp     al, [rdi][rsi*1]
            jne     different
            
; Move on to next character

            inc     rsi
                    
; Check for end of string:

            cmp     al, 0
            jne     paraAlign
            jmp     same
            
            
; RSI is now paragraph aligned. We can fetch blocks of
; 16 bytes at [RSI] without fear of a general protection
; fault. However, we don't know what RDI's alignment is,
; so we have to test to see if it's legal to fetch 16 bytes
; at a time from RDI (which is really [rdi][rsi*1] at this
; point).

            sub       rsi, 16
scLoop:     add       rsi, 16               ;On to next block.
scLoop2:    lea       rcx, [rdi][rsi*1]     ;Check the src2
            and       rcx, 0fffh            ; block to see if
            cmp       rcx, 0fh              ; there are at          
            jbe       lt16inPage            ; least 16 bytes
                                            ; left on MMU page.

; If we have at least 16 bytes left on the MMU page for the
; src2 block, then use pcmpistri to compare the 16 bytes
; at src1 (which we know is completely on an MMU page as
; RSI is 16-byte aligned) against the 16 bytes at src2
; (RDI+RSI). Load src1 bytes into XMM1 and use src2 as
; the pcmpistri operand (because we can use movdqa for
; src1, as it is aligned, and pcmpistri allows non-aligned
; accesses).
            
isAligned:
            movdqa    xmm1, [rsi]
            pcmpistri xmm1, [rsi][rdi*1], scFlags
            ja        scLoop        ;Equal, no zero bytes
            jc        different2    ;Not equal
            
; At this point, the zero flag must be set, so there
; must have been a zero byte in src1 or src2. As the
; characters also match, the strings must be equal.

same:       xor     rax, rax
            jmp     exit
            
; lt16inPage-
;
;  Code transfers to this label when there are fewer
; than 16 characters left in the src2 memory page.
; We must compare byte-by-byte until we hit a zero
; byte or cross the MMU page boundary.
;
; Note that if RCX is zero at this point, then
; RCX is already 16-byte aligned and we can jump
; right back up to the loop above. 

lt16inPage: jrcxz   isAligned
cmpUpTo16:  mov     al, [rsi]
            cmp     al, [rdi][rsi*1]
            jne     different
            inc     rsi
            cmp     al, 0
            je      same
            dec     rcx
            jnz     cmpUpTo16
            jmp     paraAlign

; Branch to this point from the code where we were
; aligning RSI to a 16-byte boundary and found a
; different character (between RSI and RDI).

different2: add     rsi, rcx
different:  mov     al, [rsi]
            sub     al, [rdi][rsi*1]
            movsx   rax, al
exit:       movdqu  xmm0, xmm0Save
            movdqu  xmm1, xmm1Save
            add     rsp, 32
            pop     rcx
            pop     rdi
            pop     rsi
            ret
            
strcmp2     endp
            end
