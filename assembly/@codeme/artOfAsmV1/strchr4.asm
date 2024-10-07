; strchr4.asm
;
;    SSE-based strchr function (will run on
; all x86-64 CPUs).
;
; Inputs:
;
;   RSI-    String to search
;    AL-    Character to search for
;
; Returns:
;
;   RAX:    Pointer to position in string
;           where the character was found,
;           NULL if no character was found. 

            include zstrings.inc
            
            .code
strchr4     proc

xmm0Save    textequ <xmmword ptr [rsp]>
xmm1Save    textequ <xmmword ptr [rsp+16]>
xmm2Save    textequ <xmmword ptr [rsp+32]>
xmm3Save    textequ <xmmword ptr [rsp+48]>

; Preserve registers this function modifies:

            push    rbx
            push    rcx
            push    rdx
            push    rsi
            sub     rsp, 64
            movdqu  xmm0Save, xmm0
            movdqu  xmm1Save, xmm1
            movdqu  xmm2Save, xmm2
            movdqu  xmm3Save, xmm3
                    
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
            
            xor     rcx, rcx        ;Zero, for later
            
; 1st comparison- May compare a few bytes before the
; beginning of the actual string (up to 15). However,
; this code uses the mask in EAX to eliminate those
; comparisons (in case they match).

            movdqa   xmm2, xmm0     ;Search for 0 byte
            movdqa   xmm3, xmm1     ;Search for match byte
            pcmpeqb  xmm2, xmmword ptr [rsi]
            pcmpeqb  xmm3, xmmword ptr [rsi]
            por      xmm3, xmm2     ;0 or match byte
            pmovmskb edx, xmm3      ;Get 16 boolean flags

            and      edx, eax       ;Mask out bytes before str
            jnz      matched

            
cmpLoop:    add      rsi, 16        ;Move on to next block
            movdqa   xmm2, xmm1     ;Match chars
            movdqa   xmm3, xmm0     ;Zero byte
            pcmpeqb  xmm2, xmmword ptr [rsi]
            pcmpeqb  xmm3, xmmword ptr [rsi]
            por      xmm3, xmm2     ;0 or match byte
            pmovmskb edx, xmm3      ;Get 16 boolean flags
            test     edx, edx       ;ZF=1 if no match
            jz       cmpLoop

matched:
            bsf     edx, edx        ;Search for match
            add     rdx, rsi        ;offset plus address
            cmp     bl, [rdx]       ;Match the char?
            cmovnz   rdx, rcx       ;RCX = NULL
            mov     rax, rdx
            
; Restore registers:

            movdqu  xmm0, xmm0Save
            movdqu  xmm1, xmm1Save
            movdqu  xmm2, xmm2Save
            movdqu  xmm3, xmm3Save
            add     rsp, 64
            pop     rsi
            pop     rdx
            pop     rcx
            pop     rbx
            ret
strchr4     endp
            end
