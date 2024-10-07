; strspn3.asm
;
;  pcmpistrm  version.
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
; is longer than 240/255 characters.

            include zstrings.inc

            .code
strspn3     proc
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
            sub     rsp, 320        ;256 chars + 4 XMM regs
            and     rsp, -16
            movdqa  xmm0Save, xmm0
            movdqa  xmm1Save, xmm1
            movdqa  xmm2Save, xmm2
            movdqa  xmm3Save, xmm3
            
            xor     r15, r15        ;Counts bytes in string
            
; Build the character set up in the XMM registers:

            mov     rcx, -16
copyCSLp:   add     rcx, 16
            lea     rax, [rdi][rcx*1]
            and     rax, 0fffh
            cmp     rax, 0ff0h
            jbe     canCopy16
            
; We're in the last 15 bytes of an MMU page.
; See if there is a zero byte amoung them:

test4zero:  cmp     byte ptr [rdi][rcx*1],0
            je      copyDone
            lea     rax, [rdi][rcx*1]
            test    rax, 0fh        ;If 0, we've crossed an
            jz      canCopy16       ;MMU page and can copy 16.
            mov     al, [rdi][rcx*1]
            mov     cset[rcx*1], al
            inc     rcx
            jmp     test4zero       
            
; Copy 16 bytes of cset. However, if we're about to copy
; more than 256 characters, bail with failure:

canCopy16:  cmp     rcx, 240
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
; the zero terminating byte. Just add 15 to RCX at this point
; to guarantee we have a zero byte in the string on the stack
; (this is always beyond, or at the end of, the cset string
; we've just created).

            add     rcx, 15 
            
copyDone:   mov     byte ptr cset[rcx*1], 0 ;Mark end of set

; We've built the character set. Now start searching for
; characters in the source string and see if they are members
; of the character set.
;
; Begin by aligning RSI on a 16-byte boundary so we
; don't have to check for MMU page crossings. Handle
; the first 16 bytes as a special case because there
; are (possible) garbage bytes we're reading before
; the actual string (because of 16-byte alignment).

            mov       rcx, rsi
            and       rsi, -16      ;Round down to 16 bytes.
            and       rcx, 0fh      ;Bytes before string.
            movdqa    xmm1, [rsi]   ;No fear, it's aligned.
            
; Fill in the garbage bytes before the string with 0FFh chars
; to ensure we don't accidentally match any zeros here:

            lea     rbx, maskOut0s
            shl     rcx, 4          ;*16 as index into maskOut0s.
            por     xmm1, [rbx][rcx*1] ;Fill in garbage bytes.

; Generate, in XMM3, a byte mask with 0FFh bytes in all the
; locations (in the string in XMM1) that match a character
; in cset:

            movdqa    xmm2, cset
            pcmpistrm xmm2, xmm1, spnFlags
            movdqa    xmm3, xmm0      ;Save mask
            js        csetHasNull     ;Bail if EOS
            
            movdqa    xmm2, cset[16]  ;Bytes 16-31.
            pcmpistrm xmm2, xmm1, spnFlags
            por       xmm3, xmm0      ;Merge results
            js        csetHasNull
            
            movdqa    xmm2, cset[32]  ;Bytes 32-47.
            pcmpistrm xmm2, xmm1, spnFlags 
            por       xmm3, xmm0
            js        csetHasNull
            
            movdqa    xmm2, cset[48]  ;Bytes 48-63.
            pcmpistrm xmm2, xmm1, spnFlags
            por       xmm3, xmm0
            js        csetHasNull
            
            movdqa    xmm2, cset[64]  ;Bytes 64-79.
            pcmpistrm xmm2, xmm1, spnFlags
            por       xmm3, xmm0
            js        csetHasNull
            
            movdqa    xmm2, cset[80]  ;Bytes 80-95.
            pcmpistrm xmm2, xmm1, spnFlags 
            por       xmm3, xmm0
            js        csetHasNull
            
            movdqa    xmm2, cset[96]  ;Bytes 96-111.
            pcmpistrm xmm2, xmm1, spnFlags 
            por       xmm3, xmm0
            js        csetHasNull
            
            movdqa    xmm2, cset[112] ;Bytes 112-127.
            pcmpistrm xmm2, xmm1, spnFlags 
            por       xmm3, xmm0
            js        csetHasNull
            
            movdqa    xmm2, cset[128] ;Bytes 128-143.
            pcmpistrm xmm2, xmm1, spnFlags 
            por       xmm3, xmm0
            js        csetHasNull
            
            movdqa    xmm2, cset[144] ;Bytes 144-159.
            pcmpistrm xmm2, xmm1, spnFlags 
            por       xmm3, xmm0
            js        csetHasNull
            
            movdqa    xmm2, cset[160] ;Bytes 160-175.
            pcmpistrm xmm2, xmm1, spnFlags 
            por       xmm3, xmm0
            js        csetHasNull
            
            movdqa    xmm2, cset[176] ;Bytes 176-191.
            pcmpistrm xmm2, xmm1, spnFlags
            por       xmm3, xmm0
            js        csetHasNull
            
            movdqa    xmm2, cset[192] ;Bytes 192-207.
            pcmpistrm xmm2, xmm1, spnFlags 
            por       xmm3, xmm0
            js        csetHasNull
            
            movdqa    xmm2, cset[208] ;Bytes 208-223.
            pcmpistrm xmm2, xmm1, spnFlags 
            por       xmm3, xmm0
            js        csetHasNull
            
            movdqa    xmm2, cset[224] ;Bytes 224-239.
            pcmpistrm xmm2, xmm1, spnFlags 
            por       xmm3, xmm0
            js        csetHasNull
            
            movdqa    xmm2, cset[224] ;Bytes 224-239.
            pcmpistrm xmm2, xmm1, spnFlags
            por       xmm3, xmm0
            js        csetHasNull
            
            movdqa    xmm2, cset[240] ;Bytes 240-255.
            pcmpistrm xmm2, xmm1, spnFlags 
            por       xmm3, xmm0

; At this point, we've reached the end of the cset string.
; Note that if there was a zero byte in the source string,
; then that will not match a character in the cset, so we
; will leave this code with the "jb nonMatch" instruction,
; below.

csetHasNull:
            
            
; At this point, XMM3 contains the bytemask for matching the
; 1st 1-15 chars of the string (RSI) against the cset. There
; are 1 bits in all the character positions that matches (this
; algorithm needs to skip over those characters). There may
; or may not be 1 bits in the garbage byte positions (probably
; not, that depends on whether the 0FFh character is part of
; the matching character set). We want to skip over those
; bytes, so just force those bits to 1s at this point.
;
; Note: this code assumes that RCX still contains the number
; of garbage bytes multiplied by 16.

            por     xmm3, [rbx][rcx*1] ;Fill garbage bytes.
            
; Convert byte mask to bit mask:

            pmovmskb  eax, xmm3


; Okay, skip over the matched characters in the first part
; of the string. Note that RCX contains the number of bytes
; before the start of the string.

            shr     rcx, 4          ;Restore original count.
            mov     ebx, -1         ;0s in garbage bit
            shl     ebx, cl         ; positions, 1s elsewhere.
            not     ax              ;Invert, to skip matched.
            and     eax, ebx        ;Clear garbage bits

            bsf     ax, ax          ;Find 1st non-match
            jz      cmp16Lp         ;If they all matched
            cmp     ax, 16          ;See if a non-match in 16
            jb      nonMatch        ; characters.
            
; At this point, all the characters at [RSI] matched,
; so we have to move forward 16 bytes. Because we're
; now 16-byte aligned, we don't have to go through
; all the craziness we had to deal with earlier.

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
            not       ax            ;Scan for first clr bit.
            bsf       eax, eax      ;Find first non-match. 
            jz        cmp16Lp       ;Repeat if all matched.
            
; If there was a non-match, eax contains the offset to
; the character that did not match. The index becomes
; RSI-origRSI-RCX (garbage count) + RAX.

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
            jmp     strspnPS
            
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
strspn3     endp
            end
