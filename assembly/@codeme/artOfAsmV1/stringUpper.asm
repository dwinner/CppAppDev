; stringUpper.asm
;
; Converts all (ASCII) lower case alphabetic
; characters appearing in a string to upper case.
;
; RDI-      Pointer to string.

            option  casemap:none
            include string.inc
            include aoalib.inc

            .code
stringUpper proc
xmm0Save    textequ <[rsp]>
xmm1Save    textequ <[rsp+16]>
xmm2Save    textequ <[rsp+32]>
xmm3Save    textequ <[rsp+48]>
xmm4Save    textequ <[rsp+64]>
xmm5Save    textequ <[rsp+80]>
xmm6Save    textequ <[rsp+96]>

            push    rax
            push    rcx
            push    rdi
            sub     rsp, 112
            movdqu  xmm0Save, xmm0
            movdqu  xmm1Save, xmm1
            movdqu  xmm2Save, xmm2
            movdqu  xmm3Save, xmm3
            movdqu  xmm4Save, xmm4
            movdqu  xmm5Save, xmm5
            movdqu  xmm6Save, xmm6
            
            movdqa  xmm2, lcA
allAs       textequ <xmm2>

            movdqa  xmm3, lcZ
allZs       textequ <xmm3>

            movdqa  xmm4, upperMask
uMask       textequ <xmm4>

            pcmpeqb xmm6, xmm6      ;All 1 bits
all1s       textequ <xmm6>
            

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
; 4) It inverts the mask (0FFh where not 'a'..'z', 0 where
;    it is 'a'..'z').
; 5) It converts the 0 bytes to 0dfh bytes (ANDing
;    lowercase characters with 0dfh converts them to
;    uppercase).
; 6) It converts the lowercase characters and stores them
;    back into the string (also stores the unconverted
;    characters back into the string; though this, obviously,
;    has no effect on the string).

            mov     ecx, [rdi-sohs].strObject.strLength
            add     rcx, 16
upperLp:    sub     rcx, 16 
            movdqa  xmm0, [rdi]
            movdqa  xmm5, xmm0
            movdqa  xmm1, allZs     ;lcZ
            pcmpgtb xmm1, xmm0      ;Test for <= 'z'
            pcmpgtb xmm0, allAs     ;Test for >= 'a'
            pand    xmm0, xmm1      ;'a' <= XMM0 <= 'z'
            pxor    xmm0, all1s     ;Invert mask
            por     xmm0, uMask     ;Create uppercase mask

            pand    xmm5, xmm0      ;Convert lc->UC
            movdqa  [rdi], xmm5     ;Save result
            add     rdi, 16
            cmp     rcx, 16
            jae     upperLp
            
            
            movdqu  xmm0, xmm0Save
            movdqu  xmm1, xmm1Save
            movdqu  xmm2, xmm2Save
            movdqu  xmm3, xmm3Save
            movdqu  xmm4, xmm4Save
            movdqu  xmm5, xmm5Save
            movdqu  xmm6, xmm6Save
            add     rsp, 112
            pop     rdi
            pop     rcx
            pop     rax
            ret
stringUpper endp
            end
