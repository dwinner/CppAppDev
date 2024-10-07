            
;***************************************************************
;            
; strlen7.asm
;
;  string length based on SSE instructions
;
; RSI-      Points at string
;
; Returns:
;
; RAX-      String Length

            include zstrings.inc

            .code

strlen7     proc
xmm0Save    textequ <[rsp]>
xmm1Save    textequ <[rsp+16]>

            push    rcx
            push    rsi
            sub     rsp, 32
            movdqu  xmm0Save, xmm0
            movdqu  xmm1Save, xmm1
            
            pxor    xmm0, xmm0      ;XMM0=0
            
; Align the source address on a 16-byte boundary

            mov     rcx, rsi
            and     rsi, -16        ;0ff...f0h
            
; Create a mask to zero out byte comparisons that
; occur before the start of the actual string:

            and     rcx, 0fh        ;Cnt extra bytes
            or      eax, -1         ;EAX= 0ffffffffh
            shl     eax, cl         ;Mask for start of str
            
            test    ecx, ecx        ;Already aligned?
            jz      ZeroLoop2
            
; 1st comparison- May compare a few bytes before the
; beginning of the actual string (up to 15). However,
; this code uses the mask in EAX to eliminate those
; comparisons (in case they match).

            movdqa   xmm1, xmm0     ;Search for 0 byte
            pcmpeqb  xmm1, xmmword ptr [rsi]
            pmovmskb ecx, xmm1      ;Get 16 boolean flags
            and      eax, ecx       ;Mask out bytes before str
            jnz      matched
 
; At this point, RSI is aligned on a 16-byte boundary.
                       
ZeroLoop:   add      rsi, 16
ZeroLoop2:  movdqa   xmm1, [rsi]
            pcmpeqb  xmm1, xmm0
            pmovmskb rax, xmm1
            test     eax, eax       ;See if any zero bytes.
            jz       ZeroLoop       ;Branch if no zero bytes. 

matched:    bsf      rax, rax
            add      rax, rsi       ;Adrs of 0 byte

            movdqu   xmm0, xmm0Save
            movdqu   xmm1, xmm1Save
            add      rsp, 32
            pop      rsi
            pop      rcx
            sub      rax, rsi       ;Compute length
            ret

strlen7     endp
            end