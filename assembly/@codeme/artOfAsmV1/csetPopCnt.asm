; csetPopCnt.asm
;
; Population count using SSE instructions
; (but not popcnt).

            include    cset.inc

repeatCnt   =               10000

            .code
            
            align   16
mask0101    oword   55555555555555555555555555555555h
mask0011    oword   33333333333333333333333333333333h
mask1111    oword   0f0f0f0f0f0f0f0f0f0f0f0f0f0f0f0fh
mask00ff    oword   00ff00ff00ff00ff00ff00ff00ff00ffh
maskffff    oword   0000ffff0000ffff0000ffff0000ffffh
maskdw      oword   00000000ffffffff00000000ffffffffh


            
;**********************************************************
;
; csetPopCnt-
;
;  Computes the number of members in a cset.
;
; On Entry:
;
;     RSI-  Points at the character set variable.
;
; On exit:
;
;     RAX-  Contains the number of members (1 bits) in
;           the character set variable.


csetPopCnt  proc
xmm0Save    textequ <[rsp]>
xmm1Save    textequ <[rsp+16]>

            push    rbx
            push    rcx
            push    rsi
            sub     rsp, 32
            movdqu  xmm0Save, xmm0
            movdqu  xmm1Save, xmm1
            
; Get population count in first 128 bits:

            movdqa  xmm0, [rsi]
            call    popCnt128
            mov     ecx, eax
            
; Quick optimization: most of the time cset
; variables only contain ASCII characters
; as members. Therefore, the HO 128 bits
; often contain all zeros. Test for this
; condition and spare the time needed to
; compute zero for the HO oword:

            mov     rbx, [rsi+16]
            or      rbx, [rsi+24]
            jz      skipHO128

; The HO 128 bits do not contain all zeros. 
; Get population count in HO 128 bits.

            movdqa  xmm0, [rsi+16]
            call    popCnt128
            add     eax, ecx
                    
skipHO128:  movdqu  xmm0, xmm0Save
            movdqu  xmm1, xmm1Save
            add     rsp, 32
            pop     rsi
            pop     rcx
            pop     rbx
            ret
csetPopCnt  endp

; Utility routine that counts the number of
; bits in the XMM0 register. Returns result
; in EAX.

popCnt128   proc

; Add together even/odd bits:

            movdqa  xmm1, xmm0
            psrlq   xmm1, 1
            pand    xmm1, mask0101
            pand    xmm0, mask0101
            paddb   xmm0, xmm1
                    
; Add together pairs of two bits:

            movdqa  xmm1, xmm0
            psrlq   xmm1, 2
            pand    xmm1, mask0011
            pand    xmm0, mask0011
            paddb   xmm0, xmm1
                    
; Add together pairs of four bits:

            movdqa  xmm1, xmm0
            psrlq   xmm1, 4
            pand    xmm1, mask1111
            pand    xmm0, mask1111
            paddb   xmm0, xmm1
                    
; Add together pairs of eight bits:

            movdqa  xmm1, xmm0
            psrlq   xmm1, 8
            pand    xmm1, mask00ff
            pand    xmm0, mask00ff
            paddw   xmm0, xmm1
                    
; Add together pairs of 16 bits:

            movdqa  xmm1, xmm0
            psrlq   xmm1, 16
            pand    xmm1, maskffff
            pand    xmm0, maskffff
            paddw   xmm0, xmm1
                    
; Add together pairs of 32 bits:

            movdqa  xmm1, xmm0
            psrlq   xmm1, 32
            pand    xmm1, maskdw
            pand    xmm0, maskdw
            paddd   xmm0, xmm1
                    
; Add together the remaining two qwords:

            movd    eax, xmm0
            pextrw  ebx, xmm0, 4
            add     eax, ebx 
            ret
popCnt128   endp
            end
