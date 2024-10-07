; strrchr3.asm
;
;  strrchr using the PCMPISTRI instruction
;
; RSI-      Points at string
; AL-       Character to search for
;
; Returns:
;
; RAX-      Position of char, or NULL if not present

            include zstrings.inc
            
            .code

strrchr3    proc
xmm0Save    textequ <[rsp]>
xmm1Save    textequ <[rsp+16]>

            push    rcx
            push    rsi
            push    rdi
            sub     rsp, 32
            movdqu  xmm0Save, xmm0
            movdqu  xmm1Save, xmm1

            xor     rdi, rdi        ;Assume no match

; Replicate char to match throughout xmm0:

            and     rax, 0ffh
            movq    xmm0, rax       ;Char to 0..7   
            
; If the char to match is 0ffh, use the maskOut0s1 table
; as our mask bits, else use maskOut0s.
;
; Need to get RSI aligned on a 16-byte
; boundary before using pcmpistri instruction:
; Force RSI to the start of the current 16-byte block.
;
; The following (possibly) looks at data before the
; start of the string. It fills those bytes in XMM1
; with either 01h or 0ffh so that they don't match
; a 0 byte or the match character.

            cmp     al, 0ffh
            jne     useMaskOut0s
            lea     rcx, maskOut0s1
            mov     rax, rsi
            and     rsi, -16      ;0fff...f0h
            and     rax, 0fH      ;Offset to start of data
            shl     rax, 4        ; for index into maskOut0s
            movdqa  xmm1, [rsi]   ;Get bytes to check
            por     xmm1, [rcx][rax*1] ;Remove garbage
            pand    xmm1, [rcx][rax*1] ;Remove garbage
            jmp     doCmp
            
useMaskOut0s:       
            lea     rcx, maskOut0s
            mov     rax, rsi
            and     rsi, -16      ;0fff...f0h
            and     rax, 0fH      ;Offset to start of data
            shl     rax, 4        ; for index into maskOut0s
            movdqa  xmm1, [rsi]   ;Get bytes to check
            por     xmm1, [rcx][rax*1] ;Remove garbage


doCmp:      pcmpistri xmm0, xmm1, EqualAny+MSBIndex
            jz        has0Byte
            jc        testECX
            
            
src4Lp:     add       rsi, 16

; Fetch next 16 bytes of string and see if any one
; of them is zero. Note that zero flag is set if
; any byte pointed at by RSI is zero, carry flag
; is set if any byte in [RSI] is the match char.
; JA = jmp if no carry and not zero. 

            pcmpistri xmm0, [rsi], EqualAny+MSBIndex
            ja        src4Lp
            jz        has0Byte
            
testECX:    cmp       ecx, 16       ;=16 if no match
            jae       noMatch         
            
; Compute pointer to matched char as the address
; of the current 16-byte block plus the index
; to the matched char:


            lea     rdi, [rsi][rcx*1]
            jmp     src4Lp

; If we matched a zero byte, see if we
; also matched the match character.
            
has0Byte:   cmp     ecx, 16
            jae     noMatch
            lea     rdi, [rsi][rcx*1]
            
            
noMatch:    mov     rax, rdi
            movdqu  xmm0, xmm0Save
            movdqu  xmm1, xmm1Save
            add     rsp, 32
            pop     rdi
            pop     rsi
            pop     rcx
            ret             
strrchr3     endp
            end
