; deleteTrailingWS.asm
;
; Deletes trailing white space string.
;
; RDI-      Pointer to string.

            option  casemap:none
            include string.inc
            include aoalib.inc


; For most common data sets, there won't be any
; trailing WS, or there will only be a few WS characters.
; The following is a very simple implementation (the "naive"
; implementation) which is probably the most efficient
; for this type of data. If your data sets commonly have
; lots of trailing white space characters, you might want
; to consider modifying this function to use SSE instructions
; or the PCMPISTRM instruction.

                 .code
deleteTrailingWS proc
                 push    rax
                 push    rsi
                 push    rdi

; Get ptr to the last character:
            
            mov     esi, [rdi-sohs].strObject.strLength
            add     rsi, rdi
            
; While we're not at the beginning of the string and
; we see white space characters, skip backwards in the
; string:

cmpLp:      dec     rsi
            cmp     rsi, rdi
            jb      BOS
            
            mov     al, [rsi]
            cmp     al, ' '
            je      cmpLp
            cmp     al, tab
            je      cmpLp
            
; Found a character that is not WS. Zero terminate the
; string and compute the new length: 

            mov     byte ptr [rsi+1], 0
            sub     rsi, rdi
            inc     esi
            mov     [rdi-sohs].strObject.strLength, esi
            jmp     allDone
                 
; If we hit the beginning of the string, turn it into
; the empty string:

BOS:        mov     [rdi-sohs].strObject.strLength, 0
            mov     byte ptr [rdi], 0

; Restore registers and return to caller
             
allDone:         pop     rdi
                 pop     rsi
                 pop     rax
                 ret
deleteTrailingWS endp
                 end
