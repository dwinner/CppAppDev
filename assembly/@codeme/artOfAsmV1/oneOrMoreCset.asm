; oneOrMoreCset.asm
;
; Matches one or more characters from a set at
; the specified offset into a string.
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
oneOrMoreCset proc

              push    rbx
              push    rcx
              push    rbx
              push    rsi
              push    rdi
            
              mov   eax, eax        ;Clear HO bits of RAX.
            
; If the starting offset at or beyond the end of the string,
; then we must always return failure:

            cmp     eax, [rsi-sohs].strObject.strLength
            jae     failed

; Must match at least one character for this
; function to succeed:
            
            movzx   rcx, byte ptr [rsi]
            mov     ebx, ecx
            and     ecx, 7
            shr     ebx, 3
            mov     eax, 1
            shl     eax, cl
            test    [rdi][rbx*1], al
            jnz     failed 
            
            
; While character at [RSI] is in the set pointed at
; by [RDI], skip over the characters:

omLoop:     inc     rsi
            movzx   rcx, byte ptr [rsi]
            cmp     cl, 0           ;End of str, succeed
            je      success
            mov     ebx, ecx
            and     ecx, 7
            shr     ebx, 3
            mov     eax, 1
            shl     eax, cl
            test    [rdi][rbx*1], al
            jnz     omLoop 
            
            
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
            
oneOrMoreCset endp
              end
