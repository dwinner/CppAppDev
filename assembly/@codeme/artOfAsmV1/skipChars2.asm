; skipChars2.asm
;
;  SSE version.
;
; RSI-      Points at source string.
; EAX-	Offset to start of search in source.
; RDI-      Points at character set string.
;
; Returns:
;
; RAX-      Index of first character not in cset.
;           0 if no chars in cset, string length
;           if all chars in cset.
;
; CF=0	If successful operation.
; CF=1	If starting offset is out of range.
;
; Defaults to skipCharsPS if the character set string
; is longer than 64 characters.

	include	string.inc
	
            .code
             align   4
skipChars2  proc
xmm0Save    textequ <[rsp]>
xmm1Save    textequ <[rsp+16]>
xmm2Save    textequ <[rsp+32]>
xmm3Save    textequ <[rsp+48]>
xmm4Save    textequ <[rsp+64]>
xmm5Save    textequ <[rsp+80]>
xmm6Save    textequ <[rsp+96]>
origRSI	textequ	<[rsp+112]>

            push    rbx
            push    rcx
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
	
	mov	eax, eax	;Clear HO bits of RAX.

; If the starting offset beyond the end of the string,
; then we must always return failure:

            cmp     eax, [rsi-sohs].strObject.strLength
            ja      skipFailed
            
; Empty character set string? If so, we return success
; with an offset of zero (skipped no characters).
                
            cmp     byte ptr [rdi], 0
            je      csetEmpty       ; cset string.        

; Skip to the starting offset in the source string:

            add     rsi, rax        ;RAX=starting offset.

; Okay, load up the character set into 4 XMM regsters:

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
            pop     rcx
            pop     rbx
            jmp     skipCharsPS
            

            
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

            lea     rax, skipJmpTbl
            jmp     qword ptr [rax][rcx*1]
            
skipJmpTbl  qword   csetEmpty, useXmm2, useXmm23
            qword   useXmm234, useXmm2345

; Okay, start reading the characters from the source
; string. We're going to read them a byte at a time
; (sadly, can't process more than 1 at a time, the
; vector code is in handling the cset string).
;
;
; Handle the case where a single XMM register (XMM2)
; holds the cset string:

useXmm2:    dec     rsi
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

useXmm23:   dec     rsi
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

useXmm234:  dec     rsi
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

useXmm2345: dec     rsi
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
;
; If the character set is empty, return zero:
                    
csetEmpty:  mov     rsi, origRSI    ;Force zero result
foundEnd:   mov     rax, rsi
            sub     rax, origRSI
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
            pop     rcx
            pop     rbx
	clc			;Return success
            ret
	
skipFailed: movdqu  xmm0, xmm0Save
            movdqu  xmm1, xmm1Save
            movdqu  xmm2, xmm2Save
            movdqu  xmm3, xmm3Save
            movdqu  xmm4, xmm4Save
            movdqu  xmm5, xmm5Save
            movdqu  xmm6, xmm5Save
            add     rsp, 112
            pop     rsi
            pop     rdi
            pop     rcx
            pop     rbx
	xor	eax, eax
	stc			;Return failure
            ret
skipChars2  endp
            end
