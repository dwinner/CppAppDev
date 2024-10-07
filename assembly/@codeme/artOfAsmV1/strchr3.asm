; strchr3.asm
;
;  strchr using the PCMPISTRI function
;
; RSI-      Points at string
; AL-       Character to search for
;
; Returns:
;
; RAX-      Position of char, or NULL if not present

            include zstrings.inc
            
            .code
strchr3     proc
xmm0Save    textequ <[rsp]>
xmm1Save    textequ <[rsp+16]>

            push    rcx
            push    rsi
            sub     rsp, 32
            movdqu  xmm0Save, xmm0
            movdqu  xmm1Save, xmm1

; Put char to match in xmm0:

            and     rax, 0ffh
            movq    xmm0, rax
            
; If the char to match is 0ffh, use the maskOut0s1 table
; as our mask bits, else use maskOut0s.
; Need to get RSI aligned on a 16-byte
; boundary before using pcmpistri instruction:
; Force RSI to the start of the current 16-byte block.

            cmp     al, 0ffh
            jne     useMaskOut0s
            lea     rcx, maskOut0s1
            mov     rax, rsi
            and     rsi, -16      ;0fff...f0h
            and     rax, 0fH      ;Offset to start of data
            shl     rax, 4        ; for index into maskOut0s
            movdqa  xmm1, [rsi]   ;Get bytes to check
            pand    xmm1, [rcx][rax*1] ;Remove garbage and
            por     xmm1, [rcx][rax*1] ; replace it with 01h.
            jmp     doCmp

useMaskOut0s:       
            lea     rcx, maskOut0s
            mov     rax, rsi
            and     rsi, -16      ;0fff...f0h
            and     rax, 0fH      ;Offset to start of data
            shl     rax, 4        ; for index into maskOut0s
            movdqa  xmm1, [rsi]   ;Get bytes to check
            por     xmm1, [rcx][rax*1] ;Remove garbage
            
doCmp:      xor       rax, rax      ;Assume no match.
            pcmpistri xmm0, xmm1, EqualAny
            ja        sl4Lp
            xor       rax, rax
            cmp       ecx, 16
            jae       noMatch
            jmp       hadMatch
            
            
sl4Lp:      add     rsi, 16

; Fetch next 16 bytes of string and see if any one
; of them is zero. Note that zero flag is set if
; any byte pointed at by RSI is zero, carry flag
; is set if any byte in [RSI] is the match char.
; JA = jmp if no carry and not zero. 

            pcmpistri xmm0, [rsi], EqualAny
            ja        sl4Lp
            xor       rax, rax      ;Assume no match
            cmp       ecx, 16       ;If no match
            jae       noMatch         
            
; Compute pointer to matched char as the address
; of the current 16-byte block plus the index
; to the matched char:

hadMatch:   lea     rax, [rsi][rcx*1]
noMatch:    movdqu  xmm0, xmm0Save
            movdqu  xmm1, xmm1Save
            add     rsp, 32
            pop     rsi
            pop     rcx
            ret             
strchr3     endp
            end
