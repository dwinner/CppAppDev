; partialCmp1.asm
;
;  Dead simple cmpsb implementation of partial compare 
;  operation.
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
;
; This function always clears the direction flag (and leaves
; it clear on exit).

            include    string.inc

            .code
partialCmp1 proc

partialPtr  textequ <rsi>   ;Makes it easier to track the
sourcePtr   textequ <rdi>   ; source and partial strings.

            push    rax
            push    rbx
            push    rcx
            push    rsi
            push    rdi
	
	mov	eax, eax	;Clear HO bits of RAX
            
; If staring offset is beyond the end of the source string,
; then the partial string is always greater than the source
; string (source is effectively an empty string).
;
; Note: in theory, this should return an exception flag.
; However, this function already uses the flags to return
; the comparison status, so we'll go with the "soft" error
; approach and treat an out of bounds index as a zero-length
; string.

            cmp     eax, [sourcePtr-sohs].strObject.strLength
            ja      isGT
            
; Zero-length partial strings match (ZF=1) any source string.

            mov     ecx, [partialPtr-sohs].strObject.strLength
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

; Begin compare at specified offset. CMPSB flag results
; are the flags this function returns here.

goodLength: add     sourcePtr, rax 

            cld
    repe    cmpsb

            pop     rdi
            pop     rsi
            pop     rcx
            pop     rbx
            pop     rax
            ret
            
isEqual:    cmp     ecx, ecx        ;Force ZF=1.
            pop     rdi
            pop     rsi
            pop     rcx
            pop     rbx
            pop     rax
            ret
            
isGT:       add     rsp, 0          ;Force ZF=0
            stc                     ;GT is CF=1, ZF=0
            pop     rdi
            pop     rsi
            pop     rcx
            pop     rbx
            pop     rax
            ret
partialCmp1 endp
            end
