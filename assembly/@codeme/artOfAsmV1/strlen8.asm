            
;***************************************************************
;            
; strlen8.asm
;
;  string length based on AVX instructions
;
; RSI-      Points at string
;
; Returns:
;
; RAX-      String Length

            include zstrings.inc

            .code

;  string length based on AVX instructions

strlen8     proc
ymm0Save    textequ <[rsp]>
ymm1Save    textequ <[rsp+32]>

            push    rcx
            push    rsi
            sub     rsp, 64
            vmovupd ymm0Save, ymm0
            vmovupd ymm1Save, ymm1

            vpxor   ymm0, ymm0, ymm0        ;YMM0=0
            
; Get RSI 32-byte aligned:
; Align the source address on a 16-byte boundary

            mov     rcx, rsi
            and     rsi, -32        ;0ff...E0h
            
; Create a mask to zero out byte comparisons that
; occur before the start of the actual string:

            and     rcx, 1fh        ;Cnt extra bytes
            or      eax, -1         ;EAX= 0ffffffffh
            shl     eax, cl         ;Mask for start of str
            
            test    ecx, ecx
            jz      ZeroLoop2       ;Already aligned?
            
; 1st comparison- May compare a few bytes before the
; beginning of the actual string (up to 15). However,
; this code uses the mask in EAX to eliminate those
; comparisons (in case they match).

            vmovdqa   ymm1, ymm0    ;YMM1 = 0
            vpcmpeqb  ymm1, ymm1, ymmword ptr [rsi]
            vpmovmskb ecx, ymm1
            and       eax, ecx      ;Mask out bytes before str
            jnz       matched
 
; At this point, RSI is aligned on a 32-byte boundary.
            
ZeroLoop:   add       rsi, 32
ZeroLoop2:  vmovdqa   ymm1, ymmword ptr [rsi]
            vpcmpeqb  ymm1, ymm1, ymm0
            vptest    ymm1, ymm1            ;Set ZF if any 0s.
            jz        ZeroLoop
            vpmovmskb rax, ymm1

matched:    bsf       rax, rax
            add       rax, rsi              ;Adrs of 0 byte
            
            vmovupd ymm0, ymm0Save
            vmovupd ymm1, ymm1Save
            add     rsp, 64
            pop     rsi
            pop     rcx
            sub     rax, rsi              ;Compute length
            ret

strlen8     endp
            end