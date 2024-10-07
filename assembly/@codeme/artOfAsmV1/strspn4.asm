; strspn4.asm
;
;  SSE version.
;
; RSI-      Points at source string
; RDI-      Points at character set string
;
; Returns:
;
; RAX-      Index of first character not in cset.
;           0 if no chars in cset, string length
;           if all chars in cset.
;
; Defaults to strspnPS if the character set string
; is longer than 64 characters.

            include zstrings.inc

            .code
strspn4     proc
xmm0Save    textequ <[rsp]>
xmm1Save    textequ <[rsp+16]>
xmm2Save    textequ <[rsp+32]>
xmm3Save    textequ <[rsp+48]>
xmm4Save    textequ <[rsp+64]>
xmm5Save    textequ <[rsp+80]>
xmm6Save    textequ <[rsp+96]>

            push    rbx
            push    rcx
            push    r15
            push    rdi
            push    rsi
            sub     rsp, 112

            movdqu  xmm0Save, xmm0
            movdqu  xmm1Save, xmm1
            movdqu  xmm2Save, xmm2
            movdqu  xmm3Save, xmm3
            movdqu  xmm4Save, xmm4
            movdqu  xmm5Save, xmm5
            movdqu  xmm5Save, xmm6

            xor     rcx, rcx        ;Count cset bytes
            call    get16AtRDI
            movdqa  xmm2, xmm0
            jc      noMore
            
            call    get16AtRDI
            movdqa  xmm3, xmm0
            jc      noMore
            
            call    get16AtRDI
            movdqa  xmm4, xmm0
            jc      noMore

            call    get16AtRDI
            movdqa  xmm5, xmm0
            jc      noMore
            
; If we get to this point, there are more than 64
; characters in the cset. Fall back to the bit map
; algorithm.

            movdqu  xmm0, xmm0Save
            movdqu  xmm1, xmm1Save
            movdqu  xmm2, xmm2Save
            movdqu  xmm3, xmm3Save
            movdqu  xmm4, xmm4Save
            movdqu  xmm5, xmm5Save
            movdqu  xmm6, xmm5Save
            add     rsp, 112
            pop     rsi
            pop     rdi
            pop     r15
            pop     rcx
            pop     rbx
            jmp     strspnPS
            

            
; Compute the number of XMM registers it takes to hold
; the cset string. This procedure will use this value
; to choose an optimal code sequence to test the
; source string. Note that the number of registers
; is computed as NumRegs = (numBytes+15) / 16.
; However, this is used as an index into a qword
; table, so we must multiply the result by 8.
; In integer arithmetic, this turns out to be
; NumRegs = (numBytes + 15) AND 0FFFF...FF0h.
; Note that this leaves RCX containing a value
; in the range 0..4 (as the maximum number of
; bytes is 64).

noMore:     add     rcx, 15  
            and     rcx, -16
            shr     rcx, 1
            
; Transfer control to one of four different code
; sections to optimally handle the string check:

            lea     rax, spnJmpTbl
            jmp     qword ptr [rax][rcx*1]
            
spnJmpTbl   qword   csetEmpty, useXmm2, useXmm23
            qword   useXmm234, useXmm2345

; Okay, start reading the characters from the source
; string. We're going to read them a byte at a time
; (sadly, can't process more than 1 at a time, the
; vector code is in handling the cset string).
;
;
; Handle the case where a single XMM register (XMM2)
; holds the cset string:

useXmm2:    mov     r15, rsi        ;Save ptr to start.
            dec     rsi
testStr2:   inc     rsi
            movzx   eax, byte ptr [rsi]
            cmp     al, 0           ;See if we're done.
            je      foundEnd

; Replicate the character in AL through the XMM0 register.

            mov       ah, al        
            movd      xmm0, eax     
            punpcklbw xmm0, xmm0    
            pshufd    xmm0, xmm0, 0
            
; Now we check to see if the character appears anywhere
; in the cset.

            pcmpeqb xmm0, xmm2      ;Appear in 1st 16 bytes?
            
; See if there was a match at all:

            pmovmskb eax, xmm0
            test     eax, eax
            jnz      testStr2
            jmp      foundEnd
            
;--------------------------------------------------
; Handle the case where there are two XMM registers
; holding the cset string:  

useXmm23:   mov     r15, rsi        ;Save ptr to start.
            dec     rsi
testStr23:  inc     rsi
            movzx   eax, byte ptr [rsi]
            cmp     al, 0           ;See if we're done.
            je      foundEnd

; Replicate the character in AL through the XMM0 register.

            mov       ah, al        
            movd      xmm0, eax     
            punpcklbw xmm0, xmm0    
            pshufd    xmm0, xmm0, 0
            
; Now we check to see if the character appears anywhere
; in the cset.

            movdqa  xmm1, xmm0
            pcmpeqb xmm1, xmm2      ;Appear in 1st 16 bytes?
            
            pcmpeqb xmm0, xmm3      ;Appear in 2nd 16 bytes?
            por     xmm1, xmm0
            
; See if there was a match at all:

            pmovmskb eax, xmm1
            test     eax, eax
            jnz      testStr23
            jmp      foundEnd
            
            
;-----------------------------------------------
; Handle the case where the cset string requires
; three XMM registers:      

useXmm234:  mov     r15, rsi        ;Save ptr to start.
            dec     rsi
testStr234: inc     rsi
            movzx   eax, byte ptr [rsi]
            cmp     al, 0           ;See if we're done.
            je      foundEnd

; Replicate the character in AL through the XMM0 register.

            mov       ah, al        
            movd      xmm0, eax     
            punpcklbw xmm0, xmm0    
            pshufd    xmm0, xmm0, 0
            
; Now we check to see if the character appears anywhere
; in the cset.

            movdqa  xmm1, xmm0
            pcmpeqb xmm1, xmm2      ;Appear in 1st 16 bytes?
            movdqa  xmm6, xmm1
            
            movdqa  xmm1, xmm0
            pcmpeqb xmm1, xmm3      ;Appear in 2nd 16 bytes?
            por     xmm6, xmm1
            
            movdqa  xmm1, xmm0
            pcmpeqb xmm1, xmm4      ;Appear in 2nd 16 bytes?
            por     xmm6, xmm1
            
; See if there was a match at all:

            pmovmskb eax, xmm6
            test     eax, eax
            jnz      testStr234
            jmp      foundEnd

;-----------------------------------------------
; Handle the case where the cset string requires
; four XMM registers:       

useXmm2345: mov     r15, rsi        ;Save ptr to start.
            dec     rsi
testSt2345: inc     rsi
            movzx   eax, byte ptr [rsi]
            cmp     al, 0           ;See if we're done.
            je      foundEnd

; Replicate the character in AL through the XMM0 register.

            mov       ah, al        
            movd      xmm0, eax     
            punpcklbw xmm0, xmm0    
            pshufd    xmm0, xmm0, 0
            
; Now we check to see if the character appears anywhere
; in the cset.

            movdqa  xmm1, xmm0
            pcmpeqb xmm1, xmm2      ;Appear in 1st 16 bytes?
            movdqa  xmm6, xmm1

            movdqa  xmm1, xmm0
            pcmpeqb xmm1, xmm3      ;Appear in 2nd 16 bytes?
            por     xmm6, xmm1

            movdqa  xmm1, xmm0
            pcmpeqb xmm1, xmm4      ;Appear in 2nd 16 bytes?
            por     xmm6, xmm1
            
            movdqa  xmm1, xmm0
            pcmpeqb xmm1, xmm5      ;Appear in 2nd 16 bytes?
            por     xmm6, xmm1

; See if there was a match at all:

            pmovmskb eax, xmm6
            test     eax, eax
            jnz      testSt2345
            jmp      foundEnd

; If there was no match at all, or we hit the zero byte,
; come down here and compute the index to the match or
; EOS:

; If the character set is empty, return zero:
                    
csetEmpty:  mov     rsi, r15        ;Force zero result
foundEnd:   mov     rax, rsi
            sub     rax, r15
allDone:    movdqu  xmm0, xmm0Save
            movdqu  xmm1, xmm1Save
            movdqu  xmm2, xmm2Save
            movdqu  xmm3, xmm3Save
            movdqu  xmm4, xmm4Save
            movdqu  xmm5, xmm5Save
            movdqu  xmm6, xmm5Save
            add     rsp, 112
            pop     rsi
            pop     rdi
            pop     r15
            pop     rcx
            pop     rbx
            ret
strspn4     endp
            end
