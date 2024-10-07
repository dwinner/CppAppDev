; findStr1.asm-
;
;  SSE version of the findStr function that will
; run on any x86-64 CPU.
;
; RSI-      Points at haystack (string to search through).
; RAX-      Offset into haystack to start search.
; RDI-      Points at needle (string to search for).
;
; Returns:
;
; RAX-      Index into haystack where substring was found
;           (-1 if not found).
;
; ZF=1      If string found.
; ZF=0      If string not found.

            include    string.inc

            .code
findStr1    proc
saveNeedle  textequ <rbx>
hayPtr      textequ <r12>
tempHay     textequ <r13>
needleChar  textequ <r14b>

xmm0Save    textequ <[rsp]>
xmm1Save    textequ <[rsp+16]>
xmm2Save    textequ <[rsp+32]>
xmm3Save    textequ <[rsp+48]>


            push    rbx
            push    rcx
            push    rsi
            push    rdi
            push    r12
            push    r13
            push    r14
                
            sub     rsp, 64
            movdqu  xmm0Save, xmm0
            movdqu  xmm1Save, xmm1
            movdqu  xmm2Save, xmm2
            movdqu  xmm3Save, xmm3
            
; If the starting offset plus the needle length is beyond 
; the end of the string, then we must always fail:

            mov     ecx, [rdi-sohs].strObject.strLength
            add     ecx, eax
            cmp     ecx, [rsi-sohs].strObject.strLength
            ja      matchFailed
            
; Get the first needle character so we can use findChar
; to quickly locate the first character of the needle
; in the haystack:

            mov     needleChar, [rdi]
            mov     saveNeedle, rdi

; Empty needle string?
                
            cmp     needleChar, 0
            cmove   rax, rsi        ;Only do this if empty
            je      success         ; needle string.        

; Skip to the starting offset in the haystack string:

            add     rsi, rax        ;RAX=starting offset.
            mov     hayPtr, rsi

; Replicate the first character in needle
; throughout XMM3:

            movzx   eax, needleChar
            xorps   xmm2, xmm2
            mov     ah, al
            movd    xmm0, eax
            pshuflw xmm1, xmm0, 0
            pshufd  xmm3, xmm1, 0

; Scan through haystack 16 bytes at a time looking
; for the first character in needle:

            sub      hayPtr, 16
cmp16Lp1:   add      hayPtr, 16
cmp16Lp:    movdqu   xmm0, xmmword ptr [hayPtr]
            movdqa   xmm1, xmm0
            pcmpeqb  xmm0, xmm3      ;Check for 1st needle char.
            pcmpeqb  xmm1, xmm2      ;Check for 0 byte.
            por      xmm1, xmm0      ;Zero or needle char.
            pmovmskb eax, xmm1
            test     eax, eax
            jz       cmp16Lp1
            

; If we found a zero or matched 1st character, locate the
; position of that character:

            bsf     eax, eax
            add     hayPtr, rax

; See if zero byte in next haystack position. If so,
; we've failed to match the 1st needle character.
  
            cmp     byte ptr [hayPtr], 0
            jz      matchFailed
            
; See if the haystack character matches the
; needle character. If not, we've failed to
; match the needle substring.

            cmp     needleChar, [hayPtr]
            je      cmpStrs
            inc     hayPtr
            jmp     cmp16Lp

            
; Compare 16 bytes at a time to see if we've found
; the needle string. Fortunately, we're guaranteed
; to have at least 16 bytes beyond the end of the
; last character in needle and haystack, so we don't
; have to worry about MMU page crossing. 

cmpStrs:    lea     tempHay, [hayPtr-16]
            lea     rdi, [saveNeedle-16]
next16OW:   add     tempHay, 16
            add     rdi, 16
cmpOWords:  movdqu  xmm1, xmmword ptr [rdi]
            movdqu  xmm0, xmmword ptr [tempHay]
            pcmpeqb xmm0, xmm1      ;Search for a matched char.
            pcmpeqb xmm1, xmm2      ;Search for a zero byte.
            pcmpeqb xmm0, xmm2      ;Inverts matched char masks.
            por     xmm0, xmm1      ;1s where we don't match or
            pmovmskb eax, xmm0      ; have a zero byte.
            test    eax, eax
            jz      next16OW


; AT this point, we've seen a zero byte
; or an unmatched character. Adjust hay
; pointer and needle pointer to the
; point where we saw the zero or match
; char:

            bsf     ecx, eax
            add     tempHay, rcx
            add     rdi, rcx

; Compare the characters a byte at a time
; until we find a match or failure.
  
            mov     al, [rdi]
            test    al, al          ;Check for end of needle.
            jz      matchedStr      ;Done if at end of needle.
            
            inc     tempHay         ;Assume it matches and
            inc     rdi             ; move on to next char pair.
            cmp     al, [tempHay-1] ;Does the needle char match
            jz      cmpOWords       ; the haystack char?

; If the needle and haystack strings don't match, continue
; looking for the first needle char in the haystack starting
; at the next hayPtr position:
            
            inc     hayPtr
            jmp     cmp16Lp

; Come down here if the needle cannot be found in the
; haystack.

matchFailed:
            or      rax, -1
            movdqu  xmm0, xmm0Save
            movdqu  xmm1, xmm1Save
            movdqu  xmm2, xmm2Save
            movdqu  xmm3, xmm3Save
            add     rsp, 64         ;Clears ZF
            pop     r14
            pop     r13
            pop     r12
            pop     rdi
            pop     rsi
            pop     rcx
            pop     rbx
            ret

; If we were successful, return an index to
; the character in the haystack where the
; match occurred:
            
matchedStr: mov     rax, hayPtr
success:    movdqu  xmm0, xmm0Save
            movdqu  xmm1, xmm1Save
            movdqu  xmm2, xmm2Save
            movdqu  xmm3, xmm3Save
            add     rsp, 64
            pop     r14
            pop     r13
            pop     r12
            pop     rdi
            pop     rsi
            sub     rax, rsi        ;Set offset
            pop     rcx
            pop     rbx
            cmp     eax, eax        ;Set ZF=1
            ret
findStr1    endp
              end
