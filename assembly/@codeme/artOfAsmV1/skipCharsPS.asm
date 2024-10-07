; skipCharsPS.asm
;
;  Bit set (power set) version.
;
; RSI-      Points at source string
; EAX-      Starting offset
; RDI-      Points at character set string
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
skipCharsPS proc
cset        textequ <[rsp]>

            push    rbx
            push    rcx
            push    rbx
            push    rsi
            push    rdi
            sub     rsp, 32 ;Make room for 256 bits
	
	mov	eax, eax 	;Clear HO bits of RAX.
            
; If the starting offset beyond the end of the string,
; then we must always return failure:

            cmp     eax, [rsi-sohs].strObject.strLength
            ja      skipFailed
            
; Empty character set string? If so, we return success
; with an offset of zero (skipped no characters).
                
            cmp     byte ptr [rdi], 0
            je      allDone         ; cset string.        

; Skip to the starting offset in the source string:

            add     rsi, rax        ;RAX=starting offset.

; Create an empty set:

            xor     rax, rax
            mov     cset, rax
            mov     cset[8], rax
            mov     cset[16], rax
            mov     cset[24], rax
            
; Initialize the set with the characters pointed at
; by RDI:

            dec     rdi
            jmp     enterCset
            
initCset:   movzx   ecx, byte ptr [rdi]
            mov     ebx, ecx
            and     ecx, 7
            shr     ebx, 3
            mov     eax, 1
            shl     eax, cl
            lea     rcx, cset
            or      [rcx][rbx*1], al 
            
enterCset:  inc     rdi
            cmp     byte ptr [rdi], 0
            jne     initCset

            
; While character at [RSI] is in the set pointed at
; by [RDI], skip over the characters:

            dec     rsi
ssLp:       inc     rsi
            movzx   rcx, byte ptr [rsi]
            cmp     cl, 0           ;End of str, no match
            je      allDone
            mov     ebx, ecx
            and     ecx, 7
            shr     ebx, 3
            mov     eax, 1
            shl     eax, cl
            lea     rcx, cset
            test    [rcx][rbx*1], al
            jnz     ssLp 
            
            
allDone:    mov     rax, rsi
            add     rsp, 32
            pop     rdi
            pop     rsi
            pop     rbx
            pop     rcx
            pop     rbx
            sub     rax, rsi
            clc                     ;Indicate success
            ret
            
            
skipFailed: add     rsp, 32
            pop     rdi
            pop     rsi
            pop     rbx
            pop     rcx
            pop     rbx
            xor     rax, rax        ;Return zero.
            stc                     ;Indicate failure
            ret
            
skipCharsPS endp
             end
