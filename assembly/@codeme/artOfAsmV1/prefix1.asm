; prefix1.asm
;
;  Dead simple cmpsb implementation of prefix operation.
;
; prefix1.asm
;
; On Entry:
;
;   RSI     Points at prefix string.
;   RDI     Points at source string object (large string)
;
; On Exit:
;
;   ZF=1 if "prefix" is a prefix of "source"
;   ZF=0 if "prefix" is not a prefix of "source"
;
; This function always clears the direction flag (and leaves
; it clear on exit).

            include    string.inc

            .code
prefix1     proc
            push    rcx
            push    rsi
            push    rdi

; Compare through the length of prefix

            mov     ecx, [rsi-sohs].strObject.strLength
            
; Zero-length strings are a prefix of anything.

            test    ecx, ecx
            jz      isPrefix
                        
            cld
    repe    cmpsb

; Note: ZF will be set if we branch here from
; the JZ instruction above. Otherwise, flags
; are set according to cmpsb.

isPrefix:   pop     rdi
            pop     rsi
            pop     rcx
            ret
            
prefix1     endp
            end
