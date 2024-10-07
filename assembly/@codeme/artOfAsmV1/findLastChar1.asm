; findLastChar1.asm
;
;    SSE-based findLastChar function (will run on
; all x86-64 CPUs).
;
; Inputs:
;
;   RSI-    String to search (haystack).
;   RCX-    Offset in haystack that is a fence for the search
;           (won't search backwards before this offset).
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
findLastChar1 proc

xmm0Save      textequ <xmmword ptr [rsp]>
xmm1Save      textequ <xmmword ptr [rsp+16]>
xmm2Save      textequ <xmmword ptr [rsp+32]>
xmm3Save      textequ <xmmword ptr [rsp+48]>

; Preserve registers this function modifies:

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

; An empty haystack string always fails:

            cmp     [rsi-sohs].strObject.strLength, 0
            je      notFound
            
; Make sure that the starting offset is not
; beyond the end of the string:

            cmp     ecx, [rsi-sohs].strObject.strLength
            jae     notFound
            
; Compute the "fence"-- the address before which
; the matching must stop:

            lea     rdi, [rsi][rcx*1]
            
                    
; Replicate the character to match throughout
; XMM1:

            mov     ah, al
            mov     bl, al          ;Save for later
            movd    xmm1, eax
            pshuflw xmm1, xmm1, 0
            pshufd  xmm1, xmm1, 0
            
            
; Adjust RSI so that it points at the beginning of the
; 16-byte-aligned block that contains the last character
; of the string.

            mov     ecx, [rsi-sohs].strObject.strLength
            lea     rsi, [rsi][rcx*1-1]     ;RSI=RSI+RCX-1
            mov     rcx, rsi
            and     rsi, -16        ;0ff...f0h
            
; Create a mask to zero out byte comparisons that
; occur after the end of the actual string:

            and     rcx, 0fh        ;Limit to chars in block.
            or      eax, -1         ;EAX= 0ffffffffh
            shl     eax, cl         ;Mask for start of str
            not     eax
                        
            xor     rcx, rcx        ;Zero, for later
            
; 1st comparison- May compare a few bytes after the
; end of the actual string (up to 15). However,
; this code uses the mask in EAX to eliminate those
; comparisons (in case they match).

            movdqa   xmm3, xmm1     ;Search for match byte
            pcmpeqb  xmm3, xmmword ptr [rsi]
            pmovmskb edx, xmm3      ;Get 16 boolean flags

            and      edx, eax       ;Mask out bytes after str
            jnz      matched

            
FCloop:     sub      rsi, 16        ;Move on to previous block.
            cmp      rsi, rdi       ;Have we hit the fence?
            jb       atFence        ;Check any leftover bytes.

            movdqa   xmm2, xmm1     ;Match chars
            pcmpeqb  xmm2, xmmword ptr [rsi]
            pmovmskb edx, xmm2      ;Get 16 boolean flags

            test     edx, edx       ;ZF=1 if no match
            jz       FCloop

matched:    bsr     edx, edx        ;Search for last match
            add     rdx, rsi        ;offset plus address
            cmp     bl, [rdx]       ;Match the char?
            jne     notFound

            
; Restore registers:

foundIt:    movdqu  xmm0, xmm0Save
            movdqu  xmm1, xmm1Save
            movdqu  xmm2, xmm2Save
            movdqu  xmm3, xmm3Save
            add     rsp, 64
            pop     rdi
            pop     rsi             ; Restore original source
            
; Compute the offset to the matching character:

            mov     rax, rdx
            sub     rax, rsi

            pop     rdx
            pop     rcx
            pop     rbx
            cmp     ebx, ebx        ;Set ZF=1
            ret 
            
; If we come down here, RSI has decremented below the
; fence address. There *may* be some bytes at the end
; of the 16-byte block that occur before the fence.
; Check for those here:

atFence:      lea     rdx, [rsi+17]   ;Back up again
byteLp:       dec     rdx
              cmp     bl, [rdx]
              je      foundIt
              cmp     rdx, rdi        ;At fence yet?
              jae     byteLp  

notFound:     movdqu  xmm0, xmm0Save
              movdqu  xmm1, xmm1Save
              movdqu  xmm2, xmm2Save
              movdqu  xmm3, xmm3Save
              mov     rax, -1         ;Return nonsense value.
              add     rsp, 64         ;This clears ZF.
              pop     rdi
              pop     rsi
              pop     rdx
              pop     rcx
              pop     rbx
              ret
findLastChar1 endp
              end
