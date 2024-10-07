; stringCaseCmp.asm
;
;  SSE variant of the stringCaseCmp function.
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
            include aoalib.inc

               .code
stringCaseCmp  proc
xmm0Save       textequ <[rsp]>
xmm1Save       textequ <[rsp+16]>
xmm2Save       textequ <[rsp+32]>
xmm3Save       textequ <[rsp+48]>
xmm4Save       textequ <[rsp+64]>
xmm5Save       textequ <[rsp+80]>
xmm6Save       textequ <[rsp+96]>

; Preserve all the registers and initialize
; xmm2, xmm3, and xmm4 with constants this
; function uses.

            push    rax
            push    rbx
            push    rcx
            push    rsi
            push    rdi
            sub     rsp, 112
            movdqu  xmm0Save, xmm0
            movdqu  xmm1Save, xmm1
            movdqu  xmm2Save, xmm2
            movdqu  xmm3Save, xmm3
            movdqu  xmm4Save, xmm4
            movdqu  xmm5Save, xmm5
            movdqu  xmm6Save, xmm6
            
            movdqa  xmm2, UCa
allAs       textequ <xmm2>

            movdqa  xmm3, UCz
allZs       textequ <xmm3>
            
            movdqa  xmm4, lowerMask
lcMask      textequ <xmm4>
               
            
; Use the length of the source1 string (choice is
; arbitrary, could use source2 length as well).

            mov     ecx, [rsi-sohs].strObject.strLength
            
; Compare 16 bytes at a time until we reach the end of
; the string(s) or they are not equal at some point.
; Convert the uppercase characters to lower case before
; the conversion (to ensure a case insensitive comparison).

            xor     rbx, rbx
cmp16:      movdqa  xmm0, [rsi][rbx*1]
            movdqa  xmm1, allZs
            movdqa  xmm5, xmm0
            pcmpgtb xmm1, xmm0      ;Test for <= 'Z'
            pcmpgtb xmm0, allAs     ;Test for >= 'A'
            pand    xmm0, xmm1      ;'A' <= XMM0 <= 'Z'
            pand    xmm0, lcMask    ;Create lowercase mask
            por     xmm5, xmm0      ;Convert UC->lc
            
            movdqa  xmm0, [rdi][rbx*1]
            movdqa  xmm0, [rdi]
            movdqa  xmm1, allZs
            movdqa  xmm6, xmm0
            pcmpgtb xmm1, xmm0      ;Test for <= 'Z'
            pcmpgtb xmm0, allAs     ;Test for >= 'A'
            pand    xmm0, xmm1      ;'A' <= XMM0 <= 'Z'
            pand    xmm0, lcMask    ;Create lowercase mask
            por     xmm6, xmm0      ;Convert UC->lc
            
; Okay, 16 bytes from the two source strings are
; in xmm5 and xmm6. Any upper case characters have
; also been converted to lower case. So now we can
; do a straight comparison.

            pcmpeqb  xmm5, xmm6
            pmovmskb eax, xmm5
            cmp      ax, 0FFFFh     ;All bytes equal?
            jne      misMatch
            add      rbx, 16
            cmp      rbx, rcx
            jb       cmp16
            
; We've just exhausted all the characters
; in the source1 string at least to the zero
; byte (and probably beyond). All characters
; were equal. Check the lengths and base the
; result on a comparison of the two strings'
; lengths.

strsEqual:  movdqu  xmm0, xmm0Save
            movdqu  xmm1, xmm1Save
            movdqu  xmm2, xmm2Save
            movdqu  xmm3, xmm3Save
            movdqu  xmm4, xmm4Save
            movdqu  xmm5, xmm5Save
            movdqu  xmm6, xmm6Save
            add     rsp, 112
            pop     rdi
            pop     rsi

            mov     eax, [rsi-sohs].strObject.strLength
            cmp     eax, [rdi-sohs].strObject.strLength

            pop     rcx
            pop     rbx
            pop     rax
            ret
            
; Drop down here when the block of 16 bytes
; in source1 don't match the corresponding
; byte in source2. Find the first byte that
; doesn't match and use that for the string
; comparison.


misMatch:   not     ax
            bsf     eax, eax
            lea     rbx, [rbx][rax]
            
; If the mismatch is beyond the end of the string
; (including beyond the zero byte), then the 
; strings are equal.

            cmp     ebx, ecx
            ja      strsEqual
                  
; Set flags based on (case insensitive) comparison
; of the first byte that did not match. However,
; must first restore XMM registers because cleaning
; up the stack affects the flags.
         
               movdqu  xmm0, xmm0Save
               movdqu  xmm1, xmm1Save
               movdqu  xmm2, xmm2Save
               movdqu  xmm3, xmm3Save
               movdqu  xmm4, xmm4Save
               movdqu  xmm5, xmm5Save
               movdqu  xmm6, xmm6Save
               add     rsp, 112
               mov     al, [rsi][rbx*1]
               mov     ah, [rdi][rbx*1] ; compare of last byte.
               cmp     al, 'A'
               jb      notUpper1
               cmp     al, 'Z'
               ja      notUpper1
               or      al, 20h      ;UC->lc
               
notUpper1:     cmp     ah, 'A'
               jb      notUpper2
               cmp     ah, 'Z'
               ja      notUpper2
               or      ah, 20h      ;UC->lc
               
notUpper2:     pop     rdi          ;Need original pointers
               pop     rsi          ; before comparing lengths.
               cmp     al, ah
               jne     notEqual

; If the strings were equal to the last character,
; we must compare the lengths of the original strings
; to determine comparison result:
               
               mov     eax, [rsi-sohs].strObject.strLength
               cmp     eax, [rdi-sohs].strObject.strLength
               
notEqual:      pop     rcx
               pop     rbx
               pop     rax
               ret
stringCaseCmp  endp
               end
