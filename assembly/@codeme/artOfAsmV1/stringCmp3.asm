; stringCmp3.asm
;
;  pcmpestri variant of the stringCmp function.
;
; On Entry:
;
;   RSI     Points at source1 string object
;   RSI     Points at source2 string object.
;
; On Exit:
;
;   Condition code flags are set based on the comparison.

            include string.inc

            .code
stringCmp3  proc
xmm0Save    textequ <[rsp]>
xmm1Save    textequ <[rsp+16]>

            push    rax
            push    rbx
            push    rcx
            push    rdx
            push    rsi
            push    rdi
            sub     rsp, 32
            movdqu  xmm0Save, xmm0
            movdqu  xmm1Save, xmm1

; Source1 length goes into EAX,
; Source2 length goes into EDX

            mov     eax, [rsi-sohs].strObject.strLength
            inc     eax     ;Include the zero byte.
            
            mov     edx, [rdi-sohs].strObject.strLength
            inc     edx     ;Include the zero byte.
            
            
; Compare 16 bytes at a time until we reach the end of
; the string(s) or they are not equal at some point

            mov       rbx, -16
            add       rax, 16
            add       rdx, 16
cmp16:      add       rbx, 16
            sub       rax, 16
            sub       rdx, 16
            movdqa    xmm0, [rsi][rbx*1]
            pcmpestri xmm0, [rdi][rbx*1], scFlags
            jc        noMatch
            jz        lastMatch
            jns       cmp16

; Fall down here if we're near the end of one of
; the strings.
            
lastMatch:  add       rbx, 16
            movdqa    xmm0, [rsi][rbx*1]
            pcmpestri xmm0, [rdi][rbx*1], scFlags
            jc        noMatch
            
; We've just exhausted all the characters
; in the source1 string at least to the zero
; byte (and probably beyond). All characters
; were equal (including the zero bytes). So
; the strings must be equal.

strsEqual:  mov     rdi, rsi        ;Force ZF=1
            xor     rbx, rbx
            jmp     allDone

; At this point we've got a match failure.
; RCX contains the index into the strings
; where the failure occurred:
            
noMatch:    add     rbx, rcx
            
allDone:    movdqu  xmm0, xmm0Save
            movdqu  xmm1, xmm1Save
            add     rsp, 32
            mov     al, [rsi][rbx*1] ;Set flags based on
            cmp     al, [rdi][rbx*1] ; compare of last byte.
            pop     rdi
            pop     rsi
            pop     rdx
            pop     rcx
            pop     rbx
            pop     rax
            ret
stringCmp3  endp
            end
