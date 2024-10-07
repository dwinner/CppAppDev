; skipCset.asm
;
;  Bit set (power set) version.
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
	include	aoalib.inc
            
            .code
             align   4
skipCset    proc
cset        textequ <[rsp]>

            push    rbx
            push    rcx
            push    rsi
            push    rdi
	
	mov	eax, eax 	;Clear HO bits of RAX.
            
; If the starting offset beyond the end of the string,
; then we must always return failure:

            cmp     eax, [rsi-sohs].strObject.strLength
            ja      skipFailed
            
            
; While character at [RSI] is in the set pointed at
; by [RDI], skip over the characters:

	lea	rsi, [rsi][rax-1]
ssLp:       inc     rsi
            movzx   rcx, byte ptr [rsi]
            cmp     cl, 0           ;End of str, success
            je      allDone
            mov     ebx, ecx
            and     ecx, 7
            shr     ebx, 3
            mov     eax, 1
            shl     eax, cl
            test    [rdi][rbx*1], al
            jnz     ssLp
	
            
allDone:    mov     rax, rsi            
            pop     rdi
            pop     rsi
            pop     rcx
            pop     rbx
            sub     rax, rsi
            clc                     ;Indicate success
            ret
            
            
skipFailed: pop     rdi
            pop     rsi
            pop     rcx
            pop     rbx
            xor     rax, rax        ;Return zero.
            stc                     ;Indicate failure
            ret
            
skipCset    endp
            end
