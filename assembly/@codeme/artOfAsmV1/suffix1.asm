; suffix1.asm
;
;  Dead simple cmpsb implementation of suffix operation.
;
; On Entry:
;
;   RSI     Points at suffix string.
;   RDI     Points at source string object (large string)
;
; On Exit:
;
;   ZF=1 if "suffix" is a suffix of "source"
;   ZF=0 if "suffix" is not a suffix of "source"
;
; This function always clears the direction flag (and leaves
; it clear on exit).

            include    string.inc

            .code
suffix1     proc
            push    rax
            push    rcx
            push    rsi
            push    rdi

; Compare through the length of suffix (RSI)

            mov     ecx, [rsi-sohs].strObject.strLength
            cmp     ecx, [rdi-sohs].strObject.strLength
            ja      exitSuffix
            
; Make source's starting index equal to its original
; starting address plus its length, minus the length
; of the suffix string:

            mov     eax, [rdi-sohs].strObject.strLength
            add     rdi, rax
            sub     rdi, rcx
            
; Special case for zero-length suffix string.
; The empty string is the suffix of any string.

            test    ecx, ecx
            jz      exitSuffix

            cld
    repe    cmpsb

; If we fall through to this point, then the ZF was
; set by CMPSB. If we branch here via JZ, then the
; ZF was set by the TEST instruction. If we branch
; here from JA, then the zero flag was cleared by
; the CMP instruction.

exitSuffix: pop     rdi
            pop     rsi
            pop     rcx
            pop     rax
            ret
suffix1     endp
            end
