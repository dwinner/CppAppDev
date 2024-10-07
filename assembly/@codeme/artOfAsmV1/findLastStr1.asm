; findLastStr1.asm
;
;  SSE version of the findLastStr function that will
; run on any x86-64 CPU.
;
; RSI-      Points at haystack (string to search through).
; RAX-      Offset into haystack to form search fence (don't search
;           before this offset).
; RDI-      Points at needle (string to search for).
;
; Returns:
;
; RAX-      Index into haystack where substring was found
;           (-1 if not found).
;
; ZF=1      If string found.
; ZF=0      If string not found.

	include	string.inc
	
            .code
             align   4
flsMaskTbl   word    0ffffh, 0fffeh, 0fffch, 0fff8h 
             word    0fff0h, 0ffe0h, 0ffc0h, 0ff80h 
             word    0ff00h, 0fe00h, 0fc00h, 0f800h 
             word    0f000h, 0e000h, 0c000h, 08000h
             word    0ffffh 

             align   4
findLastStr1 proc
saveNeedle   textequ <rbx>
fence        textequ <r13>
hayPtr       textequ <r14>
tempHay      textequ <r15>

xmm0Save     textequ <[rsp]>
xmm1Save     textequ <[rsp+16]>
xmm2Save     textequ <[rsp+32]>
xmm3Save     textequ <[rsp+48]>


             push    rbx
             push    rcx
             push    rsi
             push    rdi
             push    r12
             push    r13
             push    r14
             push    r15
                 
             sub     rsp, 64
             movdqu  xmm0Save, xmm0
             movdqu  xmm1Save, xmm1
             movdqu  xmm2Save, xmm2
             movdqu  xmm3Save, xmm3
            
; Zero out XMM2 to check for zero bytes:

             pxor    xmm2, xmm2
            
; If the starting offset plus the needle length is beyond 
; the end of the string, then we must always fail:

            mov     ecx, [rdi-sohs].strObject.strLength
            add     ecx, eax
            cmp     ecx, [rsi-sohs].strObject.strLength
            ja      matchFailed
            
; Get the first needle character so we can use findChar
; to quickly locate the first character of the needle
; in the haystack:

            mov     r12b, [rdi]
            mov     saveNeedle, rdi

; Compute fence address:

            lea     fence, [rsi][rax*1]

; Empty needle string?
; Empty needle string always matches and returns
; the length of the haystack as the offset.
; Note: remember EAX gets zero-extended below.

            mov     eax, [rsi-sohs].strObject.strLength
            add     rsi, rax        
            test    r12b, r12b
            jz      emptyNdl

; Skip to the ending offset in the haystack string
; (Haystack string length minus needle length)
            
            mov     rcx, rsi        ;Save ptr to end
            mov     eax, [rdi-sohs].strObject.strLength
            sub     rsi, rax
            mov     hayPtr, rsi

; Replicate the first character in needle
; throughout XMM3:

            movzx   eax, r12b
            mov     ah, al
            movd    xmm0, eax
            pshuflw xmm1, xmm0, 0
            pshufd  xmm3, xmm1, 0                                    

; Scan through haystack 16 bytes at a time looking
; for the first character in needle:

cmp16Lp:    movdqu  xmm0, xmmword ptr [hayPtr]
            movdqa  xmm1, xmm0
            pcmpeqb xmm0, xmm3      ;Check for 1st needle char.
            pmovmskb eax, xmm0
            test    eax, eax
            jnz     gotMatch
            
; None of the bytes matched a zero or the 1st needle char
; so skip back 16 characters in the haystack and try again.

prev16:     sub     hayPtr, 16
            cmp     hayPtr, fence
            ja      cmp16Lp
            
; If we drop below the fence, then mask out garbage
; characters after the compare:

            mov      rcx, fence     ;Compute number of bytes
            sub      rcx, hayPtr    ; before the fence
            movdqu   xmm0, xmmword ptr [hayPtr]
            pcmpeqb  xmm0, xmm3     ;Check for 1st needle char.
            pmovmskb eax, xmm0
            lea      rdi, flsMaskTbl
            and      ax, [rdi][rcx*2]
            jz       matchFailed

; If we found 1st needle character, locate the
; position of that character:

gotMatch:   bsf     eax, eax
            lea     rcx, [hayPtr+16]        ;End of pcmpeqb
            lea     tempHay, [hayPtr][rax*1]

; See if the haystack character matches the
; needle character. If not, we've failed to
; match the needle substring. Note that there
; could be multiple matches in the current 16-byte
; block. So we have to compare bytes up to the
; address held in RCX. 

matchLp:
            cmp     r12b, [tempHay]
            je      matchedChr
            inc     tempHay
            cmp     tempHay, rcx
            jb      matchLp
            jmp     prev16
            
; Matched a char in the current 16-byte block:
            
matchedChr: 
            mov     rdi, saveNeedle
            mov     rcx, tempHay    ;Save, in case no match.

; Compare the needle string to the current
; position in the haystack 16 bytes at a time:
            
cmpNldHay:
            movdqu   xmm1, xmmword ptr [rdi]
            movdqu   xmm0, xmmword ptr [tempHay]
            pcmpeqb  xmm0, xmm1      ;Search for a matched char.
            pmovmskb eax, xmm0
            not      ax              ;Switched to unmatched.
            test     eax, eax        ;Note HO 16 bits are 0.
            jnz      ndlNEhay
            
; Quick test- was there a zero byte in needle and haystack
; (special case when needle matches the end of haystack).

            pcmpeqb  xmm1, xmm2     ;XMM2 is all zeros
            pmovmskb eax, xmm1
            test     eax, eax
            jnz      ndlMatched
            
            add     tempHay, 16
            add     rdi, 16
            jmp     cmpNldHay


; AT this point, we've seen a zero byte
; or an unmatched character. If needle
; is pointing at the zero byte, then
; we've matched.

ndlNEhay:   bsf     eax, eax
            cmp     byte ptr [rdi][rax*1], 0
            je      ndlMatched
            mov     tempHay, rcx
            inc     tempHay
            jmp     matchLp

ndlMatched: mov     rax, rcx        ;Set to saved tempHay
            jmp     success

matchFailed:
            or      rax, -1
            movdqu  xmm0, xmm0Save
            movdqu  xmm1, xmm1Save
            movdqu  xmm2, xmm2Save
            movdqu  xmm3, xmm3Save
            add     rsp, 64         ;Clears ZF
            pop     r15
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

emptyNdl:    mov    hayPtr, rsi     
matchedStr:  mov    rax, hayPtr
success:     movdqu xmm0, xmm0Save
             movdqu xmm1, xmm1Save
             movdqu xmm2, xmm2Save
             movdqu xmm3, xmm3Save
             add    rsp, 64
             pop    r15
             pop    r14
             pop    r13
             pop    r12
             pop    rdi
             pop    rsi
             sub    rax, rsi        ;Set offset
             pop    rcx
             pop    rbx
             cmp    eax, eax        ;Set ZF=1
             ret
findLastStr1 endp
             end
