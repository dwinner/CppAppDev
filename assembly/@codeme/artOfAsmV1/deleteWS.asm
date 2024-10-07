; deleteWS.asm
;
; Deletes leading white space characters
; from a string.
;
; RDI-      Pointer to string.

            option  casemap:none
            include string.inc
            include aoalib.inc


; For most common data sets, there won't be any
; leading WS, or there will only be a few WS characters.
; The following is a very simple implementation (the "naive"
; implementation) which is probably the most efficient
; for this type of data. If your data sets commonly have
; lots of leading white space characters, you might want
; to consider modifying this function to use SSE instructions
; or the PCMPISTRM instruction.

            .code
deleteWS    proc
            push    rcx
            push    rsi
            push    rdi

; Get ptr to the first character:
            
            mov     rsi, rdi
            
; Special case for the empty string

            cmp     byte ptr [rdi], 0
            je      allDone
            
; While we're not at the end of the string and
; we see white space characters, skip forward in the
; string:

            dec     rsi
cmpLp:      inc     rsi
            mov     cl, [rsi]
            cmp     cl, 0           ;End of string?
            je      EOS
            cmp     cl, ' '
            je      cmpLp
            cmp     cl, tab
            je      cmpLp
            
; Found a character that is not WS. Delete
; the WS chars at the beginning of the string

            mov     rcx, rsi
            sub     rcx, rdi        ;Number of chars to delete.
            sub     ecx, [rdi-sohs].strObject.strLength

            neg     ecx             ;New string length
            mov     [rdi-sohs].strObject.strLength, ecx
            inc     ecx             ;Include zero byte.
            call    incMove         ;Remove WS'

; Must adjust final string length:

            jmp     allDone 
                         
; If we hit the end of the string, turn it into
; the empty string:

EOS:        mov     [rdi-sohs].strObject.strLength, 0
            mov     byte ptr [rdi], 0

; Restore registers and return to caller
             
allDone:    pop     rdi
            pop     rsi
            pop     rcx
            ret
deleteWS    endp
            end
