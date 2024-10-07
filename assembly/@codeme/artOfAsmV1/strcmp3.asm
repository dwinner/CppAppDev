; strcmp3.asm
;
; SSE version
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
strcmp3     proc

xmm0Save    textequ <[rsp]>
xmm1Save    textequ <[rsp+16]>
xmm2Save    textequ <[rsp+32]>
xmm3Save    textequ <[rsp+48]>
xmm4Save    textequ <[rsp+64]>
xmm5Save    textequ <[rsp+80]>

            push    rsi
            push    rdi
            push    rcx
            sub     rsp, 96
            movdqu  xmm0Save, xmm0
            movdqu  xmm1Save, xmm1
            movdqu  xmm2Save, xmm2
            movdqu  xmm3Save, xmm3
            movdqu  xmm4Save, xmm4
            movdqu  xmm5Save, xmm5

; Make RDI dependent on RSI so we can
; step through RDI by incrementing RSI:

            sub     rdi, rsi
            
; Okay, 16-byte align string 1 (pointed
; at by RSI):

paraAlign:  test    rsi, 0fh        ;Aligned on 16-byte
            jz      scLoop2         ; boundary?

            mov     al, [rsi]       ;Do the chars match?
            cmp     al, [rdi][rsi*1]
            jne     different2
            
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
; src2 block, then use movdqa/movdqu/pcmpeqb to compare the 
; 16 bytes at src1 (which we know is completely on an MMU 
; page as RSI is 16-byte aligned) against the 16 bytes at 
; src2 (RDI+RSI). Load src1 bytes into XMM1 and use src2 as
; the pcmpistri operand (because we can use movdqa for
; src1, as it is aligned, and pcmpistri allows non-aligned
; accesses).
            
isAligned:  movdqa    xmm2, [rsi]
            movdqu    xmm3, [rdi][rsi*1]
            
; Search for a zero byte in src1 or src2:

            movdqa    xmm4, xmm2    
            pcmpeqb   xmm4, xmm3    ;XMM4=bytes that match  
            
            pcmpeqb   xmm2, xmm0
            pcmpeqb   xmm3, xmm0
            por       xmm2, xmm3    ;XMM2=0 bytes
            pmovmskb  eax, xmm2
            
; See if the bytes in src1 are equal to the bytes in src2:

            pmovmskb  ecx, xmm4
            not       cx            ;1 bits where no match.
            test      eax, eax      ;Any 0 bytes?
            jnz       has0Byte
            bsf       ecx, ecx      ;Find no match posns.
            jz        scLoop        ;ZF=1 if no set bits.
            jmp       different

; Determine whether we have a zero byte or a byte that
; didn't match. That will be the character we compare
; on. Note that if we have both zero bytes and non-match
; bytes, the first one takes precedence.
            
has0Byte:
            
            bsf     eax, eax        ;1 bits on 0 bytes      
            bsf     ecx, ecx        ;1 bytes on no matches
            jnz     hadNoMatch
            mov     ecx, 16         ;if all chars matched
hadNoMatch: 
            cmp     eax, ecx        ;Whomever is smaller, wins.
            ja      different
            mov     ecx, eax        ;No match before 0 byte
            jmp     different
            
                        
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

lt16inPage:
	jrcxz   isAligned
cmpUpTo16:  mov     al, [rsi]
            cmp     al, [rdi][rsi*1]
            jne     different2
            inc     rsi
            cmp     al, 0
            je      same
            dec     rcx
            jnz     cmpUpTo16
            jmp     paraAlign

; Branch to this point from the code where we were
; aligning RSI to a 16-byte boundary and found a
; different character (betwen RSI and RDI).

different:  add     rsi, rcx        
different2: mov     al, [rsi]
            sub     al, [rdi][rsi*1]
            movsx   rax, al
exit:       movdqu  xmm0, xmm0Save
            movdqu  xmm1, xmm1Save
            movdqu  xmm2, xmm2Save
            movdqu  xmm3, xmm3Save
            movdqu  xmm4, xmm4Save
            movdqu  xmm5, xmm5Save
            add     rsp, 96
            pop     rcx
            pop     rdi
            pop     rsi
            ret
strcmp3     endp
            end
