; zeroOrMoreCset.asm
;
; RSI-      Points at source string
; EAX-      Starting offset
; RDI-      Points at character set
;
; Returns:
;
; RAX-      Index of first character not in cset.
;           0 if no chars in cset, string length
;           if all chars in cset.
;
; CF=1      Carry set if there was an error in the inputs
; CF=0      Carry clear if successful operation.

               include string.inc
            
               .code
               align   4
zeroOrMoreCset proc

               push    rbx
               push    rcx
               push    rbx
               push    rsi
               push    rdi
            
               mov  eax, eax        ;Clear HO bits of RAX.
            
; If the starting offset beyond the end of the string,
; then we must always return failure:

            cmp     eax, [rsi-sohs].strObject.strLength
            ja      failed
            
            
; While character at [RSI] is in the set pointed at
; by [RDI], skip over the characters:

            dec     rsi
zmLoop:     inc     rsi
            movzx   rcx, byte ptr [rsi]
            cmp     cl, 0           ;End of str, no match
            je      success
            mov     ebx, ecx
            and     ecx, 7
            shr     ebx, 3
            mov     eax, 1
            shl     eax, cl
            test    [rdi][rbx*1], al
            jnz     zmLoop 
            
            
success:    mov     rax, rsi
            pop     rdi
            pop     rsi
            pop     rbx
            pop     rcx
            pop     rbx
            sub     rax, rsi
            clc                     ;Indicate success
            ret
            
            
failed:     pop     rdi
            pop     rsi
            pop     rbx
            pop     rcx
            pop     rbx
            xor     rax, rax        ;Return zero.
            stc                     ;Indicate failure
            ret
            
zeroOrMoreCset endp
               end
