; strrchr4-
;
;    SSE-based strrchr function (will run on
; all x86-64 CPUs).
;
; Inputs:
;
;   RSI-    String to search
;    AL-    Character to search for
;
; Returns:
;
;   RAX:    Pointer to last position in string
;           where the character was found,
;           NULL if no character was found. 

            include zstrings.inc
            
            .code
strrchr4    proc

xmm0Save    textequ <xmmword ptr [rsp]>
xmm1Save    textequ <xmmword ptr [rsp+16]>
xmm2Save    textequ <xmmword ptr [rsp+32]>
xmm3Save    textequ <xmmword ptr [rsp+48]>

; Preserve registers this function modifies:

            push    rbp
            push    rbx
            push    rcx
            push    rdx
            push    rsi
            push    rdi
            sub     rsp, 64
            movdqu  xmm0Save, xmm0
            movdqu  xmm1Save, xmm1
            movdqu  xmm2Save, xmm2
            movdqu  xmm3Save, xmm3

            xor     rbp, rbp        ;Assume no match
                    
; Replicate the character to match throughout
; XMM1:

            mov     ah, al
            mov     bl, al          ;Save for later
            movd    xmm1, eax
            pshuflw xmm1, xmm1, 0
            pshufd  xmm1, xmm1, 0
            
; Use XMM0 to search for zero bytes:

            pxor    xmm0, xmm0
            
; Align the source address on a 16-byte boundary

            mov     rcx, rsi
            and     rsi, -16        ;0ff...f0h
            
; Create a mask to zero out byte comparisons that
; occur before the start of the actual string:

            and     rcx, 0fh        ;Cnt extra bytes
            or      eax, -1         ;EAX= 0ffffffffh
            shl     eax, cl         ;Mask for start of str
            
            
; 1st comparison- May compare a few bytes before the
; beginning of the actual string (up to 15). However,
; this code uses the mask in EAX to eliminate those
; comparisons (in case they match).

            movdqa   xmm2, xmm0     ;Search for 0 byte
            pcmpeqb  xmm2, xmmword ptr [rsi]
            pmovmskb edi, xmm2      ;16 zero match flags
            and      edi, eax       ;If no zeros, try
            je       noZeros        ; the match char.

; If we had a zero byte in the current block, manually
; check all the bytes up to the zero for a match
; character:

            add     rsi, rcx
found0:     dec     rsi
quickCmp:   inc     rsi
            cmp     byte ptr [rsi], 0
            je      allDone
            cmp     bl, [rsi]
            jne     quickCmp
            mov     rbp, rsi        ;Track last match
            jmp     quickCmp
            
                 
; If there were no zeros in the first block, check the
; first block for a match char.

noZeros:    
            movdqa   xmm2, xmm1     ;Match chars
            pcmpeqb  xmm2, xmmword ptr [rsi]
            pmovmskb edx, xmm2      ;Get 16 boolean flags
            and      edx, eax       ;Mask out chars before
            jnz      matched        ; string

            
cmpLoop:    
            add      rsi, 16        ;Move on to next block
            movdqa   xmm3, xmm0     ;Zero byte
            pcmpeqb  xmm3, xmmword ptr [rsi]
            pmovmskb rdi, xmm3      ;16 zero match flags
            test     rdi, rdi       ;Bail if we had a 0
            jnz      found0
            
            movdqa   xmm2, xmm1     ;Match chars
            pcmpeqb  xmm2, xmmword ptr [rsi]
            pmovmskb rdx, xmm2      ;Get 16 boolean flags
            test     edx, edx       ;ZF=1 if no match
            jz       cmpLoop
            
; At this point, we didn't see any zeros but we did see
; a match character. Scan backwards in the bit map
; to find the matched character position:

matched:
            bsr     rbp, rdx        ;Track the last
            add     rbp, rsi        ; matched character
            jmp     cmpLoop         ; position in RBP
            
            

allDone:    mov     rax, rbp        ;Return last match posn.
            
; Restore registers:

            movdqu  xmm0, xmm0Save
            movdqu  xmm1, xmm1Save
            movdqu  xmm2, xmm2Save
            movdqu  xmm3, xmm3Save
            add     rsp, 64
            pop     rdi
            pop     rsi
            pop     rdx
            pop     rcx
            pop     rbx
            pop     rbp
            ret
strrchr4    endp
            end
