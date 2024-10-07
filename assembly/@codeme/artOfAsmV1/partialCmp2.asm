; partialCmp2.asm
;
;  SSE variant of the partial compare function.
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
partialCmp2 proc
xmm0Save    textequ <[rsp]>
xmm1Save    textequ <[rsp+16]>

partial     textequ <rsi>   ;Makes it easier to track the
sourcePtr   textequ <rdi>   ; source and partial strings.

            push    rax
            push    rbx
            push    rcx
            push    rsi
            push    rdi
            sub     rsp, 32
            movdqu  xmm0Save, xmm0
            movdqu  xmm1Save, xmm1
 
           	mov	eax, eax	;Clear HO bits of RAX
	
; If starting offset is beyond the end of the source string,
; then the partial string is always greater than the source
; string (source is effectively an empty string).
;
; See comments in partCmp1 concerning philosophy...

            cmp     eax, [sourcePtr-sohs].strObject.strLength
            ja      isGT
            
; Zero-length partial strings match (ZF=1) any source string.


            mov     ecx, [partial-sohs].strObject.strLength
            test    ecx, ecx
            jz      isEqual
            
; If the length of the partial string plus the
; starting offset is greater than the length of
; the source string, then we only compare to
; the end of the source string (plus the zero
; byte, if the strings are equal to that point).


            lea     rbx, [rcx][rax*1]       ;RBX=RAX+RCX
            cmp     ebx, [sourcePtr-sohs].strObject.strLength
            jb      goodLength
            
; If string would go beyond the end of source, limit
; the size to the end of the source string (include
; the zero byte, to get a valid comparison if the strings
; match up to the zero byte).

            mov     ecx, [sourcePtr-sohs].strObject.strLength
            sub     rcx, rax ;Shrink length by start posn.
            inc     rcx      ;Include zero byte in compare.

;Begin compare at specified offset.

goodLength: add     sourcePtr, rax 

; Need to see if we can compare 16 bytes at a time throughout
; the whole partial string without the possibility of running
; off the end of the source string. Given the definition of
; strObject, we know the following:
;
; 1. We actually have 
;      source.maxLength + (16-((source.maxLength+1) mod 16))
;    bytes we can access in the source string.
;
; 2. Access to source characters will likely be unaligned
;    (to a 16-byte boundary). 
;
; 3. Worst-case scenario is that the code will attempt
;    to load 16 bytes starting from the very last
;    character in source (whose length is maxLength-1).
;    Fortunately, the strObject data type allocates 16
;    extra padding bytes to account for this situation.
;            
; Compare 16 bytes at a time until we reach the end of
; the string(s) or they are not equal at some point

            xor      rbx, rbx
cmp16:      movdqu   xmm0, [sourcePtr][rbx*1]
            pcmpeqb  xmm0, [partial][rbx*1]
            pmovmskb eax, xmm0
            cmp      ax, 0FFFFh     ;All bytes equal?
            jne      misMatch
            add      rbx, 16
            cmp      rbx, rcx
            jb       cmp16
            
; We've just exhausted all the characters
; in the source1 string at least to the zero
; byte (and probably beyond). All characters
; were equal (including the zero bytes). So
; the strings must be equal.

strsEqual:  
            movdqu  xmm0, xmm0Save
            movdqu  xmm1, xmm1Save
            add     rsp, 32
            pop     rdi
            pop     rsi
            pop     rcx
            pop     rbx
            pop     rax
            cmp     ecx, ecx        ;Force ZF=1
            ret
            
; Drop down here when the block of 16 bytes
; in source1 don't match the corresponding
; byte in source2. Find the first byte that
; doesn't match and use that for the string
; comparison.


misMatch:   not     ax
            bsf     eax, eax
            lea     rbx, [rbx][rax]
            
; If the mismatch is beyond the end of the string
; (including beyond the zero byte), then the 
; strings are equal.

            cmp     ebx, ecx
            jae     strsEqual
                        
testLast:   
            movdqu  xmm0, xmm0Save
            movdqu  xmm1, xmm1Save
            add     rsp, 32
            mov     al, [partial][rbx*1] ;Set flags based on
            cmp     al, [sourcePtr][rbx*1] ; last byte.
            pop     rdi
            pop     rsi
            pop     rcx
            pop     rbx
            pop     rax
            ret
            
isGT:       
            movdqu  xmm0, xmm0Save
            movdqu  xmm1, xmm1Save
            add     rsp, 32         ;Forces ZF=0
            stc                     ;GT is CF=1, ZF=0
            pop     rdi
            pop     rsi
            pop     rcx
            pop     rbx
            pop     rax
            ret
            
isEqual:    
            movdqu  xmm0, xmm0Save
            movdqu  xmm1, xmm1Save
            add     rsp, 32
            cmp     rax, rax        ;Force ZF=1
            pop     rdi
            pop     rsi
            pop     rcx
            pop     rbx
            pop     rax
            ret

partialCmp2 endp
            end
