; skipToChar1.asm
;
;  pcmpistrm  version.
;
; RSI-      Points at source string
; RDI-      Points at character set string
; EAX-	Offset into source string.
;
; Returns:
;
; RAX-      Index of first character that matches
;           a character in the set; string length
;           if no characters in the string are
;           present in the cset.
;
; This code is nearly identical to skipChars1. The major
; difference is the fact that it inverts the sense
; of the tests to skip over non-matching characters
; rather than matching characters. A second difference
; is that this code jumps to skipToCharPS if the
; character set is too large. Other than that, this
; function is almost character-for-character the same
; as skipChars1            

                       

	 include string.inc
	 
            .code
             align   4
skipToChar1 proc
xmm0Save    textequ <[rsp]>
xmm1Save    textequ <[rsp+16]>
xmm2Save    textequ <[rsp+32]>
xmm3Save    textequ <[rsp+48]>
cset        textequ <[rsp+64]>

origRSI     textequ <[rbp+8]>

            push    rbx
            push    rcx
	push	r14
	push	rdi
            push    rsi
            push    rbp
            mov     rbp, rsp
            sub     rsp, 320        ;256 chars + 4 XMM regs
            and     rsp, -16	;Align stack
            movdqa  xmm0Save, xmm0
            movdqa  xmm1Save, xmm1
            movdqa  xmm2Save, xmm2
            movdqa  xmm3Save, xmm3
	
	mov	eax, eax	;Clear HO RAX bits.
            
; If the starting offset beyond the end of the string,
; then we must always return failure:

            cmp     eax, [rsi-sohs].strObject.strLength
            ja      skipFailed
            
; Empty character set string? If so, we return success
; with an offset of zero (skipped no characters).
                
            cmp     byte ptr [rdi], 0
            je      allDone         ; cset string.        

; Skip to the starting offset in the source string:

            add     rsi, rax        ;RAX=starting offset.

; Build the character set up in the cset string:

            mov     rcx, -16
	xor	r14, r14
copyCSLp:   add     rcx, 16
            cmp     rcx, 240
            ja      csetTooLarge
            
; Okay, copy the next 16 bytes of the cset string. 
; Check for a zero-terminating byte among them:

            pxor    xmm0, xmm0
            movdqu  xmm1, [rdi][rcx*1]
            movdqu  cset[rcx*1], xmm1
            pcmpeqb xmm0, xmm1      ;1 bits where we have zeros.
            ptest   xmm0, xmm0      ;Check to see if any 0 bytes.
            jz      copyCSLp        ;Branch if no 0 bytes.

; If we got a zero byte, we can ignore everything after that
; as the pcmpistrm instruction ignores all characters beyond
; the zero-terminating byte. Just add 15 to RCX at this point
; to guarantee we have a zero byte in the string on the stack
; (this is always beyond, or at the end of, the cset string
; we've just created).

	pmovmskb r14, xmm0	;Find the zero byte
	bsf	 r14, r14
	add	 r14, rcx	;Compute size of cset
	mov      byte ptr cset[r14*1], 0 ;Mark end of set

; Generate, in XMM3, a byte mask with 0FFh bytes in all the
; locations (in the string in XMM1) that match a character
; in cset:

; At this point, all the characters at [RSI] matched,
; so we have to move forward 16 bytes.

	sub	  rsi, 16
cmp16Lp:    add       rsi, 16       ;Move on to next block
            movdqu    xmm1, [rsi]

            pxor      xmm3, xmm3    ;Zero out accumulator.
            xor       rbx, rbx      ;Index into cset.
scanCset:   movdqa    xmm2, cset[rbx*1]
            pcmpistrm xmm2, xmm1, spnFlags
            por       xmm3, xmm0    ;Save mask
            js        csetHasNull   ;Bail if end of cset.

            add       rbx, 16       ;On to next cset blk.
            cmp       rbx, 240
            jbe       scanCset
            
            
; Drop down here when we're done processing the cset.
; Note that if there was a zero byte in the source string,
; that zero byte will fail to match and we'll exit the
; cmp16Lp.
;
; Note that when comparing this code with skipChars1, the
; difference is the absence of a NOT AX instruction after
; the PMOVMSKB instruction, below.

csetHasNull:
            pmovmskb  eax, xmm3     ;Convert bytes to bits.
            bsf       eax, eax      ;Find first match. 
            jz        cmp16Lp       ;Repeat if all matched.
            
; If there was a match, eax contains the offset to
; the character that matched. The index becomes
; RSI-origRSI + RAX.

            sub     rsi, origRSI
            add     rax, rsi
            jmp     allDone



; csetTooLarge-
;
; If we get to this point, the character set string was
; longer than 240 characters. This function only reserves
; 255 characters on the stack for the cset string, so
; call the bit map variant to do the work (or use any
; other version you care to use).
;
; This is where the second difference from skipChars1
; occurs. The JMP instruction below transfers control
; to skipToCharPS rather than skipCharsPS.

csetTooLarge:
            movdqa  xmm0, xmm0Save
            movdqa  xmm1, xmm1Save
            movdqa  xmm2, xmm2Save
            movdqa  xmm3, xmm3Save
            leave
            pop     rsi
            pop     rdi
	pop	r14
            pop     rcx
            pop     rbx
            jmp     skipToCharPS
 
 
skipFailed: xor	rax, rax	;Return failure
	stc
            jmp	exitSkip
           
allDone:    clc			;Return success
exitSkip:	movdqa  xmm0, xmm0Save
            movdqa  xmm1, xmm1Save
            movdqa  xmm2, xmm2Save
            movdqa  xmm3, xmm3Save
            leave
            pop     rsi
            pop     rdi
	pop	r14
            pop     rcx
            pop     rbx
            ret
	
skipToChar1 endp
            end
