; skipToCharPS.asm
;
;  Bit set version.
;
; RSI-      Points at source string
; RDI-      Points at character set string
; EAX-	Starting offset in source string
;
; Returns:
;
; RAX-      Index of first character that matches
;           a character in the set; string length
;           if no characters in the string are
;           present in the cset.
;
; CF=1      Carry set if there was an error in the inputs
; CF=0      Carry clear if successful operation.

             include string.inc
             
            .code
             align   4
skipToCharPS proc
cset         textequ <[rsp]>

             push    rbx
             push    rcx
             push    rsi
             push    rdi
             sub     rsp, 32 ;Make room for 256 bits
            
	mov	eax, eax ;Clear HO RAX bits.
	
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
            jz      ssLp 
            
            
allDone:    mov     rax, rsi
            add     rsp, 32
            pop     rdi
            pop     rsi
            pop     rcx
            pop     rbx
            sub     rax, rsi
            clc                     ;Return success
            ret
            
; Jump down here if there was a failure to match:
            
skipFailed:  add     rsp, 32
             pop     rdi
             pop     rsi
             pop     rcx
             pop     rbx
             xor     rax, rax       ;Return 0 on failure
             stc                    ;Return failure
             ret
skipToCharPS endp
             end
