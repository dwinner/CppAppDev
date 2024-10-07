; strcspn3.asm
;
;  pcmpistrm  version.
;
; RSI-      Points at source string
; RDI-      Points at character set string
;
; Returns:
;
; RAX-      Index of first character that matches
;           a character in the set; string length
;           if no characters in the string are
;           present in the cset.
;
; This code is nearly identical to strspn3. The major
; difference is the fact that it inverts the sense
; of the tests to skip over non-matching characters
; rather than matching characters.
;
; The comments have been removed for brevity, except
; where there are major differences from strspn. See
; the strspn3 code for details.
            
            include zstrings.inc

            .code

                       
strcspn3    proc
xmm0Save    textequ <[rsp]>
xmm1Save    textequ <[rsp+16]>
xmm2Save    textequ <[rsp+32]>
xmm3Save    textequ <[rsp+48]>
cset        textequ <[rsp+64]>

origRSI     textequ <[rbp+8]>

            push    rbx
            push    rcx
            push    r15
            push    rdi
            push    rsi
            push    rbp
            mov     rbp, rsp
            sub     rsp, 320
            and     rsp, -16
            movdqa  xmm0Save, xmm0
            movdqa  xmm1Save, xmm1
            movdqa  xmm2Save, xmm2
            movdqa  xmm3Save, xmm3
            
            xor     r15, r15
            mov     rcx, -16
copyCSLp:   add     rcx, 16
            lea     rax, [rdi][rcx*1]
            and     rax, 0fffh
            cmp     rax, 0ff0h
            jbe     canCopy16
            
test4zero:  cmp     byte ptr [rdi][rcx*1],0
            je      copyDone
            lea     rax, [rdi][rcx*1]
            test    rax, 0fh 
            jz      canCopy16
            mov     al, [rdi][rcx*1]
            mov     cset[rcx*1], al
            inc     rcx
            jmp     test4zero       
            
canCopy16:  cmp     rcx, 240
            ja      csetTooLarge

            pxor    xmm0, xmm0
            movdqu  xmm1, [rdi][rcx*1]
            movdqu  cset[rcx*1], xmm1
            pcmpeqb xmm0, xmm1
            ptest   xmm0, xmm0
            jz      copyCSLp  

            add     rcx, 15 
copyDone:   mov     byte ptr cset[rcx*1], 0 ;Mark end of set

; We've built the character set. Now start searching for
; characters in the source string and see if they are not
; members of the character set.

            mov       rcx, rsi
            and       rsi, -16   
            and       rcx, 0fh   
            movdqa    xmm1, [rsi]
            
            lea     rbx, maskOut0s
            shl     rcx, 4
            por     xmm1, [rbx][rcx*1]
            movdqa    xmm2, cset
            pcmpistrm xmm2, xmm1, spnFlags
            movdqa    xmm3, xmm0 
            js        csetHasNull
            movdqa    xmm2, cset[16]
            pcmpistrm xmm2, xmm1, spnFlags
            por       xmm3, xmm0
            js        csetHasNull
            movdqa    xmm2, cset[32]
            pcmpistrm xmm2, xmm1, spnFlags 
            por       xmm3, xmm0
            js        csetHasNull
            movdqa    xmm2, cset[48]
            pcmpistrm xmm2, xmm1, spnFlags
            por       xmm3, xmm0
            js        csetHasNull
            movdqa    xmm2, cset[64]
            pcmpistrm xmm2, xmm1, spnFlags
            por       xmm3, xmm0
            js        csetHasNull
            movdqa    xmm2, cset[80]
            pcmpistrm xmm2, xmm1, spnFlags 
            por       xmm3, xmm0
            js        csetHasNull
            movdqa    xmm2, cset[96]
            pcmpistrm xmm2, xmm1, spnFlags 
            por       xmm3, xmm0
            js        csetHasNull
            movdqa    xmm2, cset[112]
            pcmpistrm xmm2, xmm1, spnFlags 
            por       xmm3, xmm0
            js        csetHasNull
            movdqa    xmm2, cset[128]
            pcmpistrm xmm2, xmm1, spnFlags 
            por       xmm3, xmm0
            js        csetHasNull
            movdqa    xmm2, cset[144]
            pcmpistrm xmm2, xmm1, spnFlags 
            por       xmm3, xmm0
            js        csetHasNull
            movdqa    xmm2, cset[160]
            pcmpistrm xmm2, xmm1, spnFlags 
            por       xmm3, xmm0
            js        csetHasNull
            movdqa    xmm2, cset[176]
            pcmpistrm xmm2, xmm1, spnFlags
            por       xmm3, xmm0
            js        csetHasNull
            movdqa    xmm2, cset[192]
            pcmpistrm xmm2, xmm1, spnFlags 
            por       xmm3, xmm0
            js        csetHasNull
            movdqa    xmm2, cset[208]
            pcmpistrm xmm2, xmm1, spnFlags 
            por       xmm3, xmm0
            js        csetHasNull
            movdqa    xmm2, cset[224]
            pcmpistrm xmm2, xmm1, spnFlags 
            por       xmm3, xmm0
            js        csetHasNull
            movdqa    xmm2, cset[224]
            pcmpistrm xmm2, xmm1, spnFlags
            por       xmm3, xmm0
            js        csetHasNull
            movdqa    xmm2, cset[240]
            pcmpistrm xmm2, xmm1, spnFlags 
            por       xmm3, xmm0

csetHasNull:
            por       xmm3, [rbx][rcx*1]
            pmovmskb  eax, xmm3


; The following code differs from the strspn code. 
; It inverts all the bits in the mask because we're 
; skipping non-matching characters rather than
; skipping matching characters.
;
; Note: not((not ax) or (not bx)) == ax and bx

            shr     rcx, 4
            mov     bx, -1
            shl     bx, cl
            and     ax, bx
            
            bsf     ax, ax          ;Find 1st non-match
            jz      cmp16Lp         ;If they all matched
            cmp     ax, 16          ;See if a match in the
            jb      nonMatch        ; 16 characters.
            
cmp16Lp:    add       rsi, 16       ;Move on to next block
            movdqa    xmm1, [rsi]

            pxor      xmm3, xmm3    ;Zero out accumulator.
            xor       rbx, rbx      ;Index into cset.
scanCset:   movdqa    xmm2, cset[rbx*1]
            pcmpistrm xmm2, xmm1, spnFlags
            por       xmm3, xmm0    ;Save mask

            js        csetHasNull2  ;Bail if end of cset.
            add       rbx, 16       ;On to next cset blk.
            cmp       rbx, 240
            jbe       scanCset
            
            
; Drop down here when we're done processing the cset.
; Note that if there was a zero byte in the source string,
; that zero byte will fail to match and we'll exit the
; cmp16Lp.

csetHasNull2:
            pmovmskb  eax, xmm3     ;Convert bytes to bits.
            bsf       ax, ax        ;Find first non-match. 
            jz        cmp16Lp       ;Repeat if all matched.
            
; If there was a non-match, eax contains the offset to
; the character that did not match. The index becomes
; RSI-origRSI-RCX (garbage count) + RAX.

            movzx   rax, ax
            sub     rsi, origRSI
            add     rax, rsi
            jmp     allDone



; csetTooLarge-
;
; If we get to this point, the character set string was
; longer than 240 characters. This function only reserves
; 255 characters on the stack for the cset string, so
; fall back to the power set implementation this happens.

csetTooLarge:
            movdqa  xmm0, xmm0Save
            movdqa  xmm1, xmm1Save
            movdqa  xmm2, xmm2Save
            movdqa  xmm3, xmm3Save
            leave
            pop     rsi
            pop     rdi
            pop     r15
            pop     rcx
            pop     rbx
            jmp     strcspnPS
            
; Come down here if there was a non-match in the first
; block of 16-chars. We have to adjust the index by
; subtracting the size of the garbage area in front of
; the string (that we included when 16-byte aligning
; RSI):

noMatchAtAll:
            mov     rax, rcx        ;Force zero result.
nonMatch:   sub     rax, rcx            
allDone:    movdqa  xmm0, xmm0Save
            movdqa  xmm1, xmm1Save
            movdqa  xmm2, xmm2Save
            movdqa  xmm3, xmm3Save
            leave
            pop     rsi
            pop     rdi
            pop     r15
            pop     rcx
            pop     rbx
            ret
strcspn3    endp
            end
