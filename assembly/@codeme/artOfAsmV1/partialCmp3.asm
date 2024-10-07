; partialCmp3.asm
;
;  pcmpestrm variant of the partial comparison function.
;
; On Entry:
;
;   RSI     Points at partial string.
;   RDI     Points at source string object (large string)
;   EAX     Contains offset into source for start of
;           comparison.
;
; On Exit:
;
;   Flags are set based on the comparison.


            include    string.inc

            .code
partialCmp3 proc
xmm0Save    textequ <[rsp]>
xmm1Save    textequ <[rsp+16]>

partial     textequ <rsi>   ;Makes it easier to track the
sourcePtr   textequ <rdi>   ; source and partial strings.

            push    rax
            push    rbx
            push    rcx
            push    rdx
            push    rsi
            push    rdi
            sub     rsp, 32
            movdqu  xmm0Save, xmm0
            movdqu  xmm1Save, xmm1
	
	mov	eax, eax	;Clear HO bits of RAX
            
; Subtract the offset from the length of the source string.
; Saturate it down to 0 if it would go negative:

            mov     edx, [sourcePtr-sohs].strObject.strLength
            sub     rdx, rax
            jns     wasPos
            xor     rdx, rdx
wasPos:     mov     edx, [sourcePtr-sohs].strObject.strLength
            add     sourcePtr, rax  ;Point at start of substr.
            
; partial length goes into EAX,
; Source length goes into EDX (set above, before changing
; the sourcePtr).

            mov     eax, [partial-sohs].strObject.strLength            
            
; Compare 16 bytes at a time until we reach the end of
; the string(s) or they are not equal. 

            xor       rcx, rcx
            mov       rbx, -16
            sub       rax, 16
            sub       rdx, 16
cmp16:      add       rbx, 16
            sub       rax, 16
            sub       rdx, 16
            movdqa    xmm0, [partial][rbx*1]
            pcmpestrm xmm0, [sourcePtr][rbx*1], scFlags
            js        tstExtraBytes ;RAX < 16
            jz        tstExtraBytes ;RDX < 16
            jnc       cmp16         ;Carry set if mismatch

; If we drop through we've got a match failure.
; RCX contains the index into the strings
; where the failure occurred:
;
; If we jump to tstExtraBytes, 
; we've just exhausted all the characters
; in the source string. All characters
; were equal. So the comparison depends
; on whether there are any more characters
; in the partial string. If so, the partial
; string is greater than the source string.

tstExtraBytes:
            dec     rbx
byteLp:     inc     rbx
            mov     al, [partial][rbx*1]
            cmp     al, 0
            je      strsEqual
            cmp     al, [sourcePtr][rbx*1]
            je      byteLp
            
            
allDone:    
            movdqu  xmm0, xmm0Save
            movdqu  xmm1, xmm1Save
            add     rsp, 32
            mov     al, [partial][rbx*1]   ;Set flags based on
            cmp     al, [sourcePtr][rbx*1] ; last compare.
            pop     rdi
            pop     rsi
            pop     rdx
            pop     rcx
            pop     rbx
            pop     rax
            ret
            


strsEqual:  
            mov     sourcePtr, partial        ;Force ZF=1
            xor     rbx, rbx
            jmp     allDone
            
partialCmp3 endp
            end
