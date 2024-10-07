; findLastChar2.asm
;
;  findLastChar using the PCMPISTRI instruction
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
findLastChar2 proc
xmm0Save      textequ <[rsp]>
xmm1Save      textequ <[rsp+16]>

              push    rcx
              push    rsi
              push    rdi
              sub     rsp, 32
              movdqu  xmm0Save, xmm0
              ;Only save XMM1 if it actually gets used.

; An empty haystack string always fails:

            cmp     [rsi-sohs].strObject.strLength, 0
            je      noMatch
            
; Make sure that the starting offset is not
; beyond the end of the string:

            cmp     ecx, [rsi-sohs].strObject.strLength
            jae     noMatch
            
; Move char to match into xmm0:

            and     rax, 0ffh
            movq    xmm0, rax       ;Char to 0..7   
            
; Compute the "fence"-- the address before which
; the matching must stop:

            lea     rdi, [rsi][rcx*1]
            
; Adjust RSI so that it points at the beginning of the
; 16-byte-aligned block that contains address of the
; last character of the string.

            mov     ecx, [rsi-sohs].strObject.strLength
            lea     rsi, [rsi][rcx*1-1]     ;RSI=RSI+RCX-1
            mov     rcx, rsi
            and     rsi, -16        ;0ff...f0h
            add     rsi, 16         ;Make up for sub, below.
            
flcLoop:    sub     rsi, 16
            cmp     rsi, rdi        ;Have we dropped below
            jb      belowFence      ; the fence yet?

; Fetch next 16 bytes of string and see if any one
; of them is the match character. Note that the carry flag 
; is set if any byte in [RSI] is the match char.
;
; Technically, the zero flag will be set if we encounter
; a zero byte. However, for this particular function we
; don't care as we are working our way backwards
; through the string. 

            pcmpistri xmm0, [rsi], EqualAny+MSBIndex
            jnc       flcLoop
            
; Compute index to matched char as the address
; of the current 16-byte block plus the index
; to the matched char, minus the original
; string's starting address:

setOfs:     lea     rax, [rsi][rcx*1]
setOfs2:    movdqu  xmm0, xmm0Save
            add     rsp, 32
            pop     rdi
            pop     rsi
            sub     rax, rsi        ;Compute offset
            pop     rcx
            cmp     eax, eax        ;ZF=1
            ret  

; If the match failed, restore everything and return
; value in RAX and ZF:
            
noMatch:    movdqu  xmm0, xmm0Save
            add     rsp, 32
            pop     rdi
            pop     rsi
            pop     rcx
            or      rax, -1         ;Ofs=-1 and ZF=0
            ret 
            
; belowFence-
;
;  If this procedure jumps down here, then RSI
; is below the fence address and we must ignore
; all characters below the fence (RDI) during
; the compare. The following code ignores the
; garbage characters below the fence by forcing
; them all to 0FFh prior to the compare, and then
; ignoring any match that occurs below the fence
; position

belowFence: movdqu    xmm1Save, xmm1
            mov       rax, rdi
            sub       rax, rsi
            shl       rax, 4        ;*16 as index into maskOut0s.
            lea       rcx, maskOut0s
            movdqa    xmm1, [rcx][rax*1]    ;Zero out garbage.
            por       xmm1, [rsi]           ;Fetch bytes to cmp.

; See if the match character is present in XMM1:

            pcmpistri xmm0, xmm1, EqualAny+MSBIndex
            movdqu    xmm1, xmm1Save
            jnc       noMatch
            
; We matched. Make sure we didn't match something
; below the fence address:

              lea     rax, [rsi][rcx*1]
              cmp     rax, rdi
              jb      noMatch
              jmp     setOfs2  
findLastChar2 endp
              end
