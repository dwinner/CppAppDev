; stringLower.asm
;
; Converts all (ASCII) upper case alphabetic
; characters appearing in a string to lower case.
;
; RDI-      Pointer to string.

            option  casemap:none
            include string.inc
            include aoalib.inc

            .code
stringLower proc
xmm0Save    textequ <[rsp]>
xmm1Save    textequ <[rsp+16]>
xmm2Save    textequ <[rsp+32]>
xmm3Save    textequ <[rsp+48]>
xmm4Save    textequ <[rsp+64]>
xmm5Save    textequ <[rsp+80]>

            push    rax
            push    rcx
            push    rdi
            sub     rsp, 96
            movdqu  xmm0Save, xmm0
            movdqu  xmm1Save, xmm1
            movdqu  xmm2Save, xmm2
            movdqu  xmm3Save, xmm3
            movdqu  xmm4Save, xmm4
            movdqu  xmm5Save, xmm5
            
            movdqa  xmm2, UCa
allAs       textequ <xmm2>

            movdqa  xmm3, UCz
allZs       textequ <xmm3>
            
            movdqa  xmm4, lowerMask
lcMask      textequ <xmm4>
            
; The following loop processes the characters in the
; string 16 characters at a time. Note that strObject
; strings are always 16-byte aligned and there are
; at least 16 bytes of padding after the zero terminating
; byte (so it's legal to "convert" characters beyond the
; current end of the string).
;
; This code works as follows:
;
; 1) It creates a mask containing 0FFh bytes wherever the
;    ASCII code is greater than or equal to 'a'.
; 2) It creates a second mask containing 0FFh bytes
;    wherever the ASCII code is less than or equal to 'z'.
; 3) It ANDs the two masks to create 0FFh bytes wherever
;    the ASCII code is in the range 'a'..'z'.
; 4) It converts the 0FFh bytes to 020h bytes (ORing
;    uppercase characters with 020h converts them to
;    lowercase).
; 5) It converts the uppercase characters and stores them
;    back into the string (also stores the unconverted
;    characters back into the string; though this, obviously,
;    has no effect on the string).

            mov     ecx, [rdi-sohs].strObject.strLength
            add     rcx, 16
lowerLp:    sub     rcx, 16
            movdqa  xmm0, [rdi]
            movdqa  xmm1, allZs
            movdqa  xmm5, xmm0
            pcmpgtb xmm1, xmm0      ;Test for <= 'Z'
            pcmpgtb xmm0, allAs     ;Test for >= 'A'
            pand    xmm0, xmm1      ;'A' <= XMM0 <= 'Z'
            pand    xmm0, lcMask    ;Create lowercase mask

            por     xmm5, xmm0      ;Convert UC->lc
            movdqa  [rdi], xmm5     ;Save result
            add     rdi, 16
            cmp     rcx, 16
            jae     lowerLp

            movdqu  xmm0, xmm0Save
            movdqu  xmm1, xmm1Save
            movdqu  xmm2, xmm2Save
            movdqu  xmm3, xmm3Save
            movdqu  xmm4, xmm4Save
            movdqu  xmm5, xmm5Save
            add     rsp, 96
            pop     rdi
            pop     rcx
            pop     rax
            ret
stringLower endp
            end
