; stringCpy2.asm
;
; stringCpy2-
;
;  A second version that uses SSE registers to copy the
; data (rather than the movsb instruction).
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

            include string.inc

            .code
stringCpy2     proc

xmmSave0    textequ <[rsp]>

            push    rbx
            push    rcx
            push    rsi
            push    rdi
            sub     rsp, 16
            movdqu  xmmSave0, xmm0
            
; Before doing anything else, make sure we won't have
; a string overflow. Remember, loading EBX zero extends
; into RBX.

            mov     ebx, [rsi-sohs].strObject.strLength
            cmp     ebx, [rdi-sohs].strObject.maxLength
            ja      allDone         ;See comments in stringCpy1
            
            push    rbx             ;Save index to end of string.
            
            xor     rcx, rcx        ;Initialize string index
            test    ebx, ebx
            jz      emptyStr

whlGE0:     movdqa  xmm0, [rsi][rcx*1]
            movdqa  [rdi][rcx*1], xmm0
            add     ecx, 16
            cmp     ecx, ebx
            jb      whlGE0          

; Zero-terminate the string before we're done:
            
emptyStr:   pop     rbx     ;Retrieve index to end of string
            mov     byte ptr [rdi][rbx*1], 0                
            stc             ;Return carry clear on success.
            
allDone:    cmc     
            movdqu  xmm0, xmmSave0
            add     rsp, 16
            pop     rdi
            pop     rsi
            pop     rcx
            pop     rbx
            ret
stringCpy2     endp            
            end
