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

; pstrlen-
;
;  String length using the PCMPESTRI function.

pstrlen	textequ	<strlen6>
            
            .code
strrstr3    proc

xmm0Save    textequ <[rsp]>
xmm1Save    textequ <[rsp+16]>
xmm2Save    textequ <[rsp+32]>

            push    rbp     ;Just used as a gen-purpose reg.
            push    rbx
            push    rcx
            push    rdi
            push    rsi
            push    r14
            push    r15
            sub     rsp, 48
            movdqu  xmm0Save, xmm0
            movdqu  xmm1Save, xmm1
            movdqu  xmm2Save, xmm2
            
; Sadly, we have to compute the length of both the
; haystack and needle before we start. We need to
; do this because we have to start at the end of the
; haystack and search backwards (we need the needle
; length because we really need to start at
; length(haystack)-length(needle) when searching
; through the haystack).

            mov     r14, rsi ;Save pointer to haystack
            
            xchg    rsi, rdi
            call    pstrlen  ;Get needle length
            mov     r15, rax
            xchg    rsi, rdi

; Zero-length needle always matches the end of the string.

            test    r15, r15
            jz      ndlHasNull

            call    pstrlen  ;Get haystack length.
            
; Zero-length haystack always fails (unless needle is also
; an empty string, which was handled above):

            test    rax, rax
            jz      matchFailed

; Compute address of the end of the haystack string
; where we can start searching.

            mov     rcx, 16  ;Start of search is 16 or R15
            cmp     r15, 16  ; bytes before end of haystk,
            cmova   rcx, r15 ; whichever is greater.
                    

            sub     rax, rcx
            add     rsi, rax ;Point to start of search.
            
            cmp     rsi, r14 ;But don't allow search to
            cmovb   rsi, r14 ; start before haystk string.
            
            
            mov     bh, [rdi] ;1st needle char.
            
; See if needle pointer is within 15 bytes
; of the end of an MMU page:

            cmp     r15, 16
            jae     load16
            mov     rax, rdi
            and     rax, 0FFFh
            cmp     rax, 0FF0h
            ja      atEOP

; If not at end of page, or needle is longer
; than 16 bytes, grab the first 16 bytes
; of the needle:
            
load16:     movdqu  xmm0, xmmword ptr [rdi]
            jmp     cmp16


atEOP:      
            xorps   xmm0, xmm0      ;Clear needle accumulator
            mov     rcx, rdi        ;RCX indexes through ndl.
            mov     bl, bh          ;Copy 1st needle char.

; Needle is shorter than 16 bytes and is near the end of
; an MMY page. 

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
; current haystack position. Note that we don't
; have to worry about crossing MMU page boundaries
; here because we're moving backwards through the
; haystack string.

cmp16:
            movdqu    xmm1, xmmword ptr [rsi]
            pcmpistri xmm0, xmm1, EqualOrder
            jbe       foundEnd

; If no match, move back 16 bytes.
            
            sub       rsi, 16
            cmp       rsi, r14      ;At start of haystk?
            ja        cmp16

; If there are 16 or fewer bytes left, make one additional
; comparison at the start of the haystack.

            mov       rsi, r14
            movdqu    xmm1, xmmword ptr [r14]
            pcmpistri xmm0, xmm1, EqualOrder
            ja        matchFailed ;Will be before haystack.
            
; We're at the beginning of the haystack string.
; We've matched some number of characters in the first
; 16 bytes (starting at RSI+RCX).
; See if the whole needle matches.

            add     rsi, rcx
            mov     r14, rsi        ;Save match posn
            mov     rcx, r15        ;Needle length
    repe    cmpsb                   ;Compare strings
            mov     rsi, r14
            je      ndlHasNull      ;Branch if match
            jmp     matchFailed     ;If no match.
            
            
; Matched substring, or found a zero byte in haystack.
; ECX contains the index to the start of the match.

foundEnd:   mov       eax, ecx      ;Zero extends!
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

noMatchHay: dec     rsi     ;Move back one character and try
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
            pop     r15
            pop     r14
            pop     rsi
            pop     rdi
            pop     rcx
            pop     rbx
            pop     rbp
            ret

strrstr3    endp
            end
