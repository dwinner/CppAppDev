; strstr3.asm
;
;  strstr function using pcmpistri instruction.
;
; RSI-      Points at haystack (string to search through)
; RDI-      Points at needle (string to search for)
;
; Returns:
;
; RAX-      Position of substring, or NULL if not present

            include zstrings.inc
            
            .code
strstr3     proc

xmm0Save    textequ <[rsp]>
xmm1Save    textequ <[rsp+16]>
xmm2Save    textequ <[rsp+32]>

            push    rbp     ;Just used as a gen-purpose reg.
            push    rbx
            push    rcx
            push    rsi
            push    rdi
            sub     rsp, 48
            movdqu  xmm0Save, xmm0
            movdqu  xmm1Save, xmm1
            movdqu  xmm2Save, xmm2
            
            mov     bh, [rdi] ;1st needle char.
            
; See if needle pointer is within 15 bytes
; of the end of an MMU page:

            mov     rax, rdi
            and     rax, 0FFFh
            cmp     rax, 0FF0h
            ja      atEOP

; if not at end of page, grab the first 16 bytes
; of the needle:
            
            movdqu  xmm0, xmmword ptr [rdi]
            jmp     cmp16


atEOP:      
            xorps   xmm0, xmm0      ;Clear needle accumulator
            mov     rcx, rdi        ;RCX indexes through ndl.
            mov     bl, bh          ;Copy 1st needle char.

; Grab the first 16 bytes of the needle (or fewer, if
; needle is smaller than 16 bytes) and put them in XMM0.

            mov     bp, 16
BuildNeedle16:
            movzx   eax, bl
            psrldq  xmm0, 1         ;Shift XMM0 right one BYTE.
            pinsrb  xmm0, eax, 15   ;Insert AL into byte 15
            
            test    bl, bl          ;At end of needle?
            jz      was0Byte
            
; Fetch next needle character if not already at end
; of needle.

            mov       bl, byte ptr [rcx+1]
            inc       rcx

was0Byte:   
            sub       bp, 1
            jnz       BuildNeedle16


; Compare 16 bytes of the needle against the
; current haystack position:

cmp16:
            mov       rax, rsi      ;Ensure we're not at the
            and       rax, 0FFFh    ; last 16 bytes of the
            cmp       rax, 0FF0h    ; current haystack page.
            ja        endOfHayPg
            
            movdqu    xmm1, xmmword ptr [rsi]
            pcmpistri xmm0, xmm1, EqualOrder
            jbe       foundEnd

; If no match, move ahead 16 bytes.
            
            add       rsi, 16
            jmp       cmp16
            
            
; Matched substring, or found a zero byte in haystack.
; ECX contains the index to the start of the match.

foundEnd:   jnc       matchFailed   ;If zero byte found.
            mov       eax, ecx      ;Zero extends!
            add       rsi, rcx      ;Point at start of match.       

; We've matched the first part of the needle against the
; haystack characters. Now let's see if the rest of the
; needle matches:

matchedHay: mov       rdx, rsi      ;RDX moves ahead in haystk.
            mov       rbp, rdi      ;RBP moves ahead in needle.

pcmpLp:     mov       rax, rdx      ;Haystk at end of page?
            and       rax, 0FFFh
            cmp       rax, 0FF0h
            ja        endOfPage
            
            mov       rax, rbp      ;Needle at end of page?
            and       rax, 0FFFh
            cmp       rax, 0FF0h
            ja        endOfPage

; Grab the next 16 bytes from the needle and haystack.
; Then compare them.

            movdqu    xmm1, xmmword ptr [rdx]
            movdqu    xmm2, xmmword ptr [rbp]
            pcmpistri xmm2, xmm1, EqualOrder
            jno       noMatchHay    ;OF set if match at posn 0.
            js        ndlHasNull    ;SF set if NULL in XMM2
            
; Current 16 bytes match, move on another 16 bytes:

            add       rdx, 16
            add       rbp, 16
            jmp       pcmpLp

; If there are fewer than 16 chars left on the current
; MMU page holding the haystack, we have to compare the
; characters one at a time:

endOfHayPg: cmp     byte ptr [rsi], 0 ;End of haystack?
            jz      matchFailed
            cmp     bh, [rsi]         ;BH has 1st needle char
            jz      matchedHay

noMatchHay: inc     rsi     ;Move ahead one character and try
            jmp     cmp16   ; to match 16 bytes again.


; At end of MMU page for either haystack or needle.
; Must process characters a byte at a time until we
; get to the new MMU page (on both pointers, if needed).

endOfPage:  mov     al, [rbp]       ;Get needle char
            cmp     al, 0           ;At end of needle?
            je      ndlHasNull
            
            cmp     al, [rdx]       ;Needle = haystack?
            jnz     noMatchHay
            
; As long as the needle and haystack characters match,
; process additional characters in the needle and haystk.

            inc     rdx
            inc     rbp
            jmp     pcmpLp



matchFailed:xor     rsi, rsi        ;Return NULL if no match.
ndlHasNull: mov     rax, rsi        ;RSI=start of match.
allDone:    movdqu  xmm0, xmm0Save
            movdqu  xmm1, xmm1Save
            movdqu  xmm2, xmm2Save
            add     rsp, 48
            pop     rdi
            pop     rsi
            pop     rcx
            pop     rbx
            pop     rbp
            ret

strstr3     endp
            end
