; findChar2.asm
;
;  findChar using the PCMPISTRI function
;
; Inputs:
;
;   RSI-    String to search (haystack).
;   RCX-    Offset in haystack to begin search.
;    AL-    Character to search for.
;
; Returns:
;
;   RAX:    Offset into haystack where character was found.
;           (-1 if character was not found.)
;
;   ZF=1    Character was found in haystack.
;   ZF=0    Character was not found in haystack. 

            
            
            include    string.inc

            .code
findChar2     proc
xmm0Save    textequ <[rsp]>
xmm1Save    textequ <[rsp+16]>

            push    rcx
            push    rsi
            sub     rsp, 32
            movdqu  xmm0Save, xmm0
            movdqu  xmm1Save, xmm1
            
; An empty haystack string always fails:

            cmp     [rsi-sohs].strObject.strLength, 0
            je      noMatch
            
; Make sure that the starting offset is not
; beyond the end of the string:

            cmp     ecx, [rsi-sohs].strObject.strLength
            jae     noMatch
            
; Add the offset to the starting address. Note that
; RSI will no longer be 16-byte aligned after this.
                    
            add     rsi, rcx
            
; Put char to match in xmm0:

            and     eax, 0ffh
            movd    xmm0, eax
            
; If the char to match is 0ffh, use the maskOut0s1 table
; as our mask bits, else use maskOut0s.

            cmp     al, 0ffh
            jne     useMaskOut0s
            
; Char to match is 0ffh, so replace garbage bytes
; at the beginning of the string with 01h (which
; won't match):

            lea     rcx, maskOut0s1
            mov     rax, rsi
            and     rsi, -16      ;0fff...f0h
            and     rax, 0fH      ;Offset to start of data
            shl     rax, 4        ; for index into maskOut0s
            movdqa  xmm1, [rsi]   ;Get bytes to check
            por     xmm1, [rcx][rax*1] ;Remove garbage and
            pand    xmm1, [rcx][rax*1] ; replace by 01h
            jmp     do1stCmp

; Char to match is not 0FFh, so replace garbage bytes
; at the start of the string with 0FFh so they won't match.
            
useMaskOut0s:       
            lea     rcx, maskOut0s
            mov     rax, rsi
            and     rsi, -16      ;0fff...f0h
            and     rax, 0fH      ;Offset to start of data
            shl     rax, 4        ; for index into maskOut0s
            movdqa  xmm1, [rsi]   ;Get bytes to check
            por     xmm1, [rcx][rax*1] ;Remove garbage
             

; Do first comparison of 16 bytes, with any garbage bytes
; at the beginning masked out:
            
do1stCmp:   pcmpistri xmm0, xmm1, EqualAny
            ja        FCloop        ;No match and no 0 byte.

; Had a match or found a zero byte. If there was no match
; but there was a zero byte, ECX will contain 16.

            cmp       ecx, 16
            jae       noMatch
            jmp       hadMatch

; Fetch next 16 bytes of string and see if any one
; of them is zero. Note that zero flag is set if
; any byte pointed at by RSI is zero, carry flag
; is set if any byte in [RSI] is the match char.
; JA = jmp if no carry and not zero. 

FCloop:     add       rsi, 16
            pcmpistri xmm0, [rsi], EqualAny
            ja        FCloop

; ECX will contain offset to matched char, or
; 16 if there was not match and pcmpistri encountered
; a zero byte:

            cmp       ecx, 16       ;If no match
            jae       noMatch         
            
; Compute pointer to matched char as the address
; of the current 16-byte block plus the index
; to the matched char:

hadMatch:   lea     rax, [rsi][rcx*1]
            movdqu  xmm0, xmm0Save
            movdqu  xmm1, xmm1Save
            add     rsp, 32
            pop     rsi
            sub     rax, rsi        ;Compute offset.
            pop     rcx
            cmp     eax, eax        ;Set ZF=1
            ret
                         
noMatch:    movdqu  xmm0, xmm0Save
            movdqu  xmm1, xmm1Save
            add     rsp, 32
            pop     rsi
            pop     rcx
            or      rax, -1         ;-1 offset, ZF=0
            ret             
findChar2   endp
            end
