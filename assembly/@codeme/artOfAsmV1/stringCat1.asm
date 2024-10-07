; stringCat1.asm
;
;  Dead simple movsb implementation of string 
;  concatenation operation.
;
; On Entry:
;
;   RSI     Points at source string object
;   RDI     Points at destination string object 
;           to append source at the end.
;
; On Exit:
;
;   Carry is set if there was an error (string
;   overflow- an attempt to store too many characters
;   into the destination string).
;
; This function always clears the direction flag (and leaves
; it clear on exit).

            include    string.inc

            .code
stringCat1  proc
            push    rax
            push    rcx
            push    rsi
            push    rdi
 
           
; Compute the sum of the source and destination lengths
; and verify that this is less than or equal to the
; destination maxLen

            mov     eax, [rdi-sohs].strObject.strLength
            mov     ecx, [rsi-sohs].strObject.strLength
            add     eax, ecx
            cmp     [rdi-sohs].strObject.maxLength, eax
            jb      allDone ;Note: same as "jc allDone"

; Save away new length:

            mov     [rdi-sohs].strObject.strLength, eax
            sub     eax, ecx ;Restore original dest length.


; Add destination's length to the destination pointer
; so we can append the source string to the end
; of the destination.
            
            add     rdi, rax 

; Increment the source length (number of bytes to copy)
; to include copying the zero byte from the source.
            
            inc     ecx     ;Include the zero byte.
            
; Save away new length:

            cld     ;Generally could assume this is clear
    rep     movsb

            clc     ;Indicate success.
allDone:    pop     rdi
            pop     rsi
            pop     rcx
            pop     rax
            ret
stringCat1  endp
            end
