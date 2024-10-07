; findChar1.asm
;
;    SSE-based strchr function (will run on
; all x86-64 CPUs).
;
; Inputs:
;
;   RSI-    String to search (haystack).
;   RCX-    Offset in haystack to begin search.
;    AL-    Character to search for.
;
; Returns:
;
;   RAX:    Offset into haystack where character was found.
;           (-1 if character was not found.)
;
;   ZF=1    Character was found in haystack.
;   ZF=0    Character was not found in haystack. 
           

            include    string.inc

            .code
findChar1   proc

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

; An empty haystack string always fails:

            cmp     [rsi-sohs].strObject.strLength, 0
            je      notFound
            
; Make sure that the starting offset is not
; beyond the end of the string:

            cmp     ecx, [rsi-sohs].strObject.strLength
            jae     notFound
            
; Add the offset to the starting address. Note that
; RSI will no longer be 16-byte aligned after this.
                    
            add     rsi, rcx
            
; Replicate the character to match throughout
; XMM1:

            mov     ah, al
            mov     bl, al          ;Save for later
            movd    xmm1, eax
            pshuflw xmm1, xmm1, 0
            pshufd  xmm1, xmm1, 0
            
; Use XMM0 to search for zero bytes (rather than
; use the string's length to end the operation).

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

; Search through the source string for the character to match.
            
FCloop:     add      rsi, 16        ;Move on to next block
            movdqa   xmm2, xmm1     ;Match chars
            movdqa   xmm3, xmm0     ;Zero byte
            pcmpeqb  xmm2, xmmword ptr [rsi]
            pcmpeqb  xmm3, xmmword ptr [rsi]
            por      xmm3, xmm2     ;0 or match byte
            pmovmskb edx, xmm3      ;Get 16 boolean flags
            test     edx, edx       ;ZF=1 if no match
            jz       FCloop

matched:
            bsf     edx, edx        ;Search for match
            add     rdx, rsi        ;offset plus address
            cmp     bl, [rdx]       ;Match the char?
            jne     notFound

            
; Restore registers:

            movdqu  xmm0, xmm0Save
            movdqu  xmm1, xmm1Save
            movdqu  xmm2, xmm2Save
            movdqu  xmm3, xmm3Save
            add     rsp, 64
            pop     rsi             ; Restore original source
            
; Compute the offset to the matching character:
            
            mov     rax, rdx
            sub     rax, rsi

            pop     rdx
            pop     rcx
            pop     rbx
            cmp     ebx, ebx        ;Set ZF=1
            ret

notFound:   movdqu  xmm0, xmm0Save
            movdqu  xmm1, xmm1Save
            movdqu  xmm2, xmm2Save
            movdqu  xmm3, xmm3Save
            mov     rax, -1         ;Return nonsense value.
            add     rsp, 64         ;This clears ZF.
            pop     rsi
            pop     rdx
            pop     rcx
            pop     rbx
            ret
findChar1   endp
            end
