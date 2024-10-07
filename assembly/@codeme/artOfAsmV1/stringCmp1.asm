; stringCmp1.asm
;
;  Dead simple cmpsb implementation of string compare
;  operation.
;
; On Entry:
;
;   RSI     Points at source1 string object
;   RSI     Points at source2 string object.
;
; On Exit:
;
;   Condition code flags are set based on the comparison.
;
; This function always clears the direction flag (and leaves
; it clear on exit).

            include string.inc

            .code

stringCmp1  proc
            push    rcx
            push    rsi
            push    rdi

; Compare through the length of the shorter string, plus one.

            mov     ecx, [rsi-sohs].strObject.strLength
            cmp     ecx, [rdi-sohs].strObject.maxLength 
            jb      gotShorter
            mov     ecx, [rdi-sohs].strObject.maxLength 
            
gotShorter: inc     ecx     ;Include the zero byte.

            cld     ;Generally could assume this is clear
    repe    cmpsb

            pop     rdi
            pop     rsi
            pop     rcx
            ret
stringCmp1  endp
            end
