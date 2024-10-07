; strstr4.asm
;
;  SSE version of the strstr function that will
; run on any x86-64 CPU.
;
; RSI-      Points at haystack (string to search through)
; RDI-      Points at needle (string to search for)
;
; Returns:
;
; RAX-      Position of substring, or NULL if not present

            include zstrings.inc

            .code
strstr4     proc
saveNeedle  textequ <rbx>
hayPtr      textequ <r8>
tempHay     textequ <r9>

xmm0Save    textequ <[rsp]>
xmm1Save    textequ <[rsp+16]>
xmm2Save    textequ <[rsp+32]>
xmm3Save    textequ <[rsp+48]>


            push    rbx
            push    rcx
            push    rdx
            push    rsi
            push    rdi
            push    r8
            push    r9
                
            sub     rsp, 64
            movdqu  xmm0Save, xmm0
            movdqu  xmm1Save, xmm1
            movdqu  xmm2Save, xmm2
            movdqu  xmm3Save, xmm3
            

            mov     dl, [rdi]
            mov     saveNeedle, rdi
            mov     hayPtr, rsi

; Empty needle string?
                
            test    dl, dl
            jnz     ndlNotEmpty
            
            mov     rax, rsi
            jmp     allDone


; Replicate the first character in needle
; throughout XMM3:

ndlNotEmpty:
            movzx   eax, dl
            xorps   xmm2, xmm2
            mov     ah, al
            movd    xmm0, eax
            pshuflw xmm1, xmm0, 0
            pshufd  xmm3, xmm1, 0

; Scan through haystack 16 bytes at a time looking
; for the first character in needle:

cmp16Lp:    mov     rax, hayPtr     ;See if hayPtr is at
            and     rax, 0FFFh      ; end of MMU page.
            cmp     rax, 0FF0h
            ja      endOfPage
            
            movdqu  xmm0, xmmword ptr [hayPtr]
            movdqa  xmm1, xmm0
            pcmpeqb xmm0, xmm3      ;Check for 1st needle char.
            pcmpeqb xmm1, xmm2      ;Check for 0 byte.
            por     xmm1, xmm0      ;Zero or needle char.
            pmovmskb eax, xmm1
            test    eax, eax
            jnz     gotMatch
            
; None of the bytes matched a zero or the 1st needle char
; so skip ahead 16 characters in the haystack and try again.

            add     hayPtr, 16
            jmp     cmp16Lp


; If we found a zero or matched character, locate the
; position of that character:

gotMatch:   bsf     eax, eax
            add     hayPtr, rax

; See if zero byte in next haystack position. If so,
; we've failed to match the needle character.

endOfPage:  cmp     byte ptr [hayPtr], 0
            jz      matchFailed
            
; See if the haystack character matches the
; needle character. If not, we've failed to
; match the needle substring.

            cmp     dl, [hayPtr]
            jnz     noMatch
            
            mov     tempHay, hayPtr
            mov     rdi, saveNeedle

cmpOWords:  mov     rax, rdi        ;See if the needle string
            and     rax, 0FFFh      ; will cross a 16-byte
            cmp     rax, 0FF0h      ; boundary.
            ja      atEndPage
            
            mov     rax, tempHay    ;See if the haystack string
            and     rax, 0FFFh      ; will cross a 16-byte
            cmp     rax, 0FF0h      ; boundary
            ja      atEndPage
            
; Compare 16 bytes between the needle and haystack:

            movdqu  xmm1, xmmword ptr [rdi]
            movdqu  xmm0, xmmword ptr [tempHay]
            pcmpeqb xmm0, xmm1      ;Search for a matched char.
            pcmpeqb xmm1, xmm2      ;Search for a zero byte.
            pcmpeqb xmm0, xmm2      ;Inverts matched char masks.
            por     xmm0, xmm1      ;1s where we don't match or
            pmovmskb eax, xmm0      ; have a zero byte.
            test    eax, eax
            jnz     endMatch
            
            add     tempHay, 16
            add     rdi, 16
            jmp     cmpOWords


; AT this point, we've seen a zero byte
; or an unmatched character. Adjust hay
; pointer and needle pointer to the
; point where we saw the zero or match
;char:

endMatch:
            bsf     ecx, eax
            add     tempHay, rcx
            add     rdi, rcx

; Compare the characters a byte at a time
; until we find a match or failure.

atEndPage:  mov     al, [rdi]
            test    al, al          ;Check for end of needle.
            jz      matchedStr      ;Done if at end of needle.
            
            cmp     [tempHay], al   ;Does the character match
            jnz     noMatch         ; next haystack char?
            
            inc     tempHay         ;Move on to next haystack
            inc     rdi             ; and needle char.
            jmp     cmpOWords


noMatch:    inc     hayPtr
            jmp     cmp16Lp


matchedStr: mov     rax, hayPtr
            jmp     allDone

matchFailed:
            xor     eax, eax
allDone:    movdqu  xmm0, xmm0Save
            movdqu  xmm1, xmm1Save
            movdqu  xmm2, xmm2Save
            movdqu  xmm3, xmm3Save
            add     rsp, 64
            pop     r9
            pop     r8
            pop     rdi
            pop     rsi
            pop     rdx
            pop     rcx
            pop     rbx
            ret
strstr4     endp
            end
