; hstrCpy1.asm
;
; strCpy1-
;
;  Dead simple movsb implementation of string copy operation.
;
; On Entry:
;
;   RSI     Points at source string object
;   RSI     Points at destination string object.
;
; On Exit:
;
;   Carry is set if there was an error (string
;   overflow- an attempt to store too many characters
;   into the destination string).
;
; This function always clears the direction flag (and leaves
; it clear on exit).

            include string.inc

            .code
strCpy1     proc
            push    rcx
            push    rsi
            push    rdi
            
; Verify that the source string's current length is less
; than or equal to the destination string's maximum length.
;
; Remember- loading a 32-bit value into ECX zero-extends
;           the value through RCX. Therefore, the following
;           mov instruction initializes RCX for movsb.

            mov     ecx, [rsi-sohs].strObject.strLength
            cmp     [rdi-sohs].strObject.maxLength, ecx
            jb      allDone ;Note: same as "jc allDone"
            
            inc     ecx     ;Include the zero byte.
            
            cld     ;Generally could assume this is clear
    rep     movsb

            clc     ;Indicate success.
allDone:    pop     rdi
            pop     rsi
            pop     rcx
            ret
strCpy1     endp
            end
