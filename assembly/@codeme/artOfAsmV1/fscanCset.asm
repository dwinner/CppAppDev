; fscanCset.asm
;
; Fast character set scanning algorithm using
; pcmpistri instructions. Matches zero or more
; characters in the source string from the
; specified character set.
;
; On entry:
;
;  RSI-     Pointer to source string to scan.
;  RAX-     Offset into source string to begin scan.
;  RDI-     Pointer to pcset variable containing character
;           set fields to use (if anyTag and/or rangeTag
;           fields are not -1, then this algorithm will
;           uses the anyStr and/or rangeStr fields as
;           pcmpistri operands).
;
; On Exit
;
;  RAX-     Offset into string where first character
;           that is not a member of pcset was found.
;
; CF=0      Successful scan (even if no characters
;           matched).
; CF=1      Illegal operands on input.


            include    aoalib.inc
            include    cset.inc

            
            .code
            
fscanCset   proc
xmm0Save    textequ <[rsp]>
xmm1Save    textequ <[rsp+16]>

            push    rcx
            push    rsi
            push    rdi
            sub     rsp, 32
            movdqu  xmm0Save, xmm0
            movdqu  xmm1Save, xmm1
            
            mov     eax, eax        ;Zero extend EAX into RAX
            
; Check for index out of range:

            cmp     eax, [rsi-sohs].strObject.strLength
            ja      failure
            
; Determine which of the four cases we have to deal with:
;
; 1. anyTag and rangeTag are both -1
; 2. anyTag is valid, rangeTag is -1
; 3. anyTag is -1, rangeTag is valid
; 4. Both anyTag and rangeTag are valid

            mov     ecx, -1
            cmp     ecx, [rdi].pcset.pcs.tags.anyTag
            jne     anyTagValid
            cmp     ecx, [rdi].pcset.pcs.tags.rangeTag
            jne     anyIRangeV
            
; Both are invalid, must fall back to powerset scanning
; algorithm:

            add     rsp, 32 ;No need to restore XMM regs
            pop     rdi
            pop     rsi
            pop     rcx
            jmp     skipCset

; The anyTag field is valid. Check to see if the rangeTag
; field is also valid:
            
anyTagValid:
            cmp     ecx, [rdi].pcset.pcs.tags.rangeTag
            jne     bothValid
            
;----------------------------------------------------
;
; At this point, anyStr is valid but rangeStr is not.
; NegPolarity means the carry flag will be clear if all
; of the 16 bytes at [rsi][rax*1] are found in anyStr.
; The carry flag will be set if any one of the bytes
; at [rsi][rax*1] is not found in anyStr.

            movdqa    xmm0, [rdi].pcset.pcs.pstrs.anyStr
            sub       rax, 16      ;Counteract add, below
anyLp:      add       rax, 16
            pcmpistri xmm0, [rsi][rax*1], EqualAny+NegPolarity
            jnc       anyLp

; RCX contains index into xmm1 where the match failed (that is
; the offset to the first character that is not a member
; of the anyStr set). Bump the offset (in RAX) up to that
; character:

            add     rax, rcx
            jmp     success

;-------------------------------------------------------
;
; At this point, rangeStr is valid, anyStr is not valid.
; NegPolarity with EqualRange means the carry flag will 
; be clear if all of the 16 bytes at [rsi][rax*1] are 
; within one of the ranges found in rangeStr.
; The carry flag will be set if any one of the bytes
; at [rsi][rax*1] is outside the eight ranges found
; in rangeStr.
            
anyIRangeV:
            movdqa    xmm0, [rdi].pcset.pcs.pstrs.rangeStr
            sub       rax, 16      ;Counteract add, below
rangeLp:    add       rax, 16
            pcmpistri xmm0, [rsi][rax*1], EqualRange+NegPolarity
            jnc       rangeLp

; RAX+RCX contains index into xmm1 where the match failed:

            add     rax, rcx
            jmp     success

;--------------------------------------------------------
;            
; At this point, both anyStr and rangeStr are valid. 
; Match characters in the string until *both* the range 
; match and the any match fail to match any characters 
; at all. 
            
bothValid:
            movdqa    xmm0, [rdi].pcset.pcs.pstrs.rangeStr
            movdqa    xmm1, [rdi].pcset.pcs.pstrs.anyStr
bothLp:     pcmpistri xmm0, [rsi][rax*1], EqualRange+NegPolarity
            add       rax, rcx
            test      ecx, ecx      ;Any matches?
            jz        noRanges

; Range compare has matched.
            
rangeSucceeded:
            pcmpistri xmm1, [rsi][rax*1], EqualAny+NegPolarity
            add       rax, rcx
            test      ecx, ecx      ;Any matches?
            jnz       bothLp        ;Both range and any matched.
            
; At this point, the any match has failed. See if the range
; match also fails:

            pcmpistri xmm0, [rsi][rax*1], EqualRange+NegPolarity
            add       rax, rcx
            test      ecx, ecx      ;Any matches?
            jnz       rangeSucceeded
            jmp       success       ;Both range/any failed

; Come down here if pcmpistri did not match any characters
; in the range. If the next instruction also fails to match
; anything, then we're done.
            
noRanges:   pcmpistri xmm1, [rsi][rax*1], EqualAny+NegPolarity
            add       rax, rcx
            test      rcx, rcx
            jnz       bothLp

; At this point, both range and any have failed to match.
; RAX contains index into xmm1 where the match failed.
; Return with RAX containing the index of the character
; that did not match.

success:    movdqu  xmm0, xmm0Save
            movdqu  xmm1, xmm1Save
            add     rsp, 32
            pop     rdi
            pop     rsi
            pop     rcx
            clc             ;Return success
            ret

; Haven't modified XMM registers, no
; need to waste time or space restoring them:
            
failure:    add     rsp, 32
            pop     rdi
            pop     rsi
            pop     rcx
            stc             ;Return failure
            ret
fscanCset   endp
            end
