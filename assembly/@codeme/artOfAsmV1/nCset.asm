; nCset.asm
;
; Matches the first n characters in a string
; that are members of a character set
;
; RSI-      Points at source string
; EAX-      Starting offset
; ECX-      n (number of characters to match)
; RDI-      Points at character set
;
; Returns:
;
; RAX-      Index of first character not in cset.
;           0 if no chars in cset, string length
;           if all chars in cset.
;
; CF=1      Carry set if there was an error in the inputs
;           or the string didn't match.
; CF=0      Carry clear if successful operation.

            include string.inc
            
            .code
            align   4
nCset       proc

            push    rbx
            push    rcx
            push    rbx
            push    rsi
            push    rdi
            push    r15
            
            mov  eax, eax        ;Clear HO bits of RAX.
            
; If the starting offset beyond the end of the string,
; then we must always return failure:

            cmp     eax, [rsi-sohs].strObject.strLength
            ja      failed
            
; Need to use ECX for shifting purposes, so put n+1 into r15.
; The "+1" is because the loop below will decrement r15d
; and check for zero before actually testing the character
; to see if it is a member of the character set.

            mov     r15d, ecx
            
; While character at [RSI] is in the set pointed at
; by [RDI], skip over the characters:

            dec     rsi
nLoop:      inc     rsi
            movzx   rcx, byte ptr [rsi]
            cmp     cl, 0           ;End of str, no match
            je      failed
            mov     ebx, ecx
            and     ecx, 7
            shr     ebx, 3
            mov     eax, 1
            shl     eax, cl
            test    [rdi][rbx*1], al
            jz      failed          ;Haven't matched n yet
            dec     r15d            ;Quit (with success)
            jnz     nLoop           ; when we match n chars 
            
success:    mov     rax, rsi
            pop     r15
            pop     rdi
            pop     rsi
            pop     rbx
            pop     rcx
            pop     rbx
            sub     rax, rsi
            clc                     ;Indicate success
            ret
            
            
failed:     pop     r15
            pop     rdi
            pop     rsi
            pop     rbx
            pop     rcx
            pop     rbx
            xor     rax, rax        ;Return zero.
            stc                     ;Indicate failure
            ret
            
nCset       endp
            end
