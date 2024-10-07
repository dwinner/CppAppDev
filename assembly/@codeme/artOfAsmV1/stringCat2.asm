; stringCat2.asm
;
;  A stringCat version that uses SSE registers to copy the
; data (rather than the movsb instruction).
;
; On Entry:
;
;   RSI     Points at source string object
;   RDI     Points at destination string object.
;
; On Exit:
;
;   Carry is set if there was an error (string
;   overflow- an attempt to store too many characters
;   into the destination string).

            include    string.inc

            .code
stringCat2  proc

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

            mov     ecx, [rdi-sohs].strObject.strLength
            mov     ebx, [rsi-sohs].strObject.strLength
            add     ebx, ecx
            cmp     [rdi-sohs].strObject.maxLength, ebx
            jb      badStr         ;Same as "jc allDone"

; Save new length in destination string:

            mov     [rdi-sohs].strObject.strLength, ebx
            
; Retrieve original source length:
            
            mov     ebx, [rsi-sohs].strObject.strLength
            
; Point the destination pointer to the end of the existing
; destination string (RCX contains the length of the
; destination string at this point).

            add     rdi, rcx
            
            xor     rcx, rcx        ;Initialize string index
            test    ebx, ebx
            jz      emptyStr
            
            inc     ebx             ;Copy zero byte, too.
            jmp     tstEndBuf

whlGE0:     
            movdqa  xmm0, [rsi][rcx*1]
            movdqu  [rdi][rcx*1], xmm0
            add     ecx, 16

tstEndBuf:  cmp     ecx, ebx        ;See if we've transferred
            jb      whlGE0          ; all the data yet.          

; Zero-terminate the string before we're done:
            
emptyStr:   movdqu  xmm0, xmmSave0
            add     rsp, 16
            pop     rdi
            pop     rsi
            pop     rcx
            pop     rbx
            clc                     ;Return success.
            ret
            
badStr:     movdqu  xmm0, xmmSave0
            add     rsp, 16
            pop     rdi
            pop     rsi
            pop     rcx
            pop     rbx
            stc
            ret
stringCat2  endp            
            end
