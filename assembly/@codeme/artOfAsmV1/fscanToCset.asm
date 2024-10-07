; fscanToCset.asm
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
            
fscanToCset proc
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
            jmp     skipToCset

; The anyTag field is valid. Check to see if the rangeTag
; field is also valid:
            
anyTagValid:
            cmp     ecx, [rdi].pcset.pcs.tags.rangeTag
            jne     bothValid
            
;---------------------------------------------------
;            
; At this point, anyStr is valid but rangeStr is not.

            movdqa    xmm0, [rdi].pcset.pcs.pstrs.anyStr
            sub       rax, 16      ;Counteract add, below
anyLp:      add       rax, 16
            pcmpistri xmm0, [rsi][rax*1], EqualAny
            jz        EOS
            jnc       anyLp

; RAX+RCX contains index into xmm1 where the match occurred:

            add     rax, rcx
            jmp     success

; Hit end of string. Could have been a match, though.
; Check carry flag to see if there was a match:
            
EOS:        jc      foundMatch
            mov     eax, [rsi-sohs].strObject.strLength
            jmp     success

;---------------------------------------------------
;            
; At this point, rangeStr is valid, anyStr is not valid.
            
anyIRangeV:
            movdqa    xmm0, [rdi].pcset.pcs.pstrs.rangeStr
            sub       rax, 16      ;Counteract add, below
rangeLp:    add       rax, 16
            pcmpistri xmm0, [rsi][rax*1], EqualRange
            jz        EOS
            jnc       rangeLp

; RAX+RCX contains index into xmm1 where the match occurred:

foundMatch: add     rax, rcx
            jmp     success

            
;---------------------------------------------------
;            
; At this point, both anyStr and rangeStr are valid. 
; Match characters in the string until *both* the range 
; match and the any match fail to match any characters 
; at all. 
            
bothValid:  movdqa    xmm0, [rdi].pcset.pcs.pstrs.rangeStr
            movdqa    xmm1, [rdi].pcset.pcs.pstrs.anyStr
            
bothLp:     pcmpistri xmm0, [rsi][rax*1], EqualRange
            jnc       rangeFailed
            push      rcx
            pcmpistri xmm1, [rsi][rax*1], EqualAny
            jnc       anyFailed

; Down here both of the pcmpistri instructions
; have matched a character. Choose the smaller of the
; two match indexes, add it to the offset, and try again
; until the matched character is the very 1st character
; at the offset position:

            cmp       rcx, [rsp]
            jb        have1st
            mov       rcx, [rsp]
have1st:    add       rsp, 8        ;Remove range value
            
; Because we matched, we know that rcx is not 16 (meaning
; we didn't match anything). As we've found the first
; matching character, we can leave this function.

            add     rax, rcx
            jmp     success
            
; EqualRange failed, still have to try EqualAny to see
; if it can find a matching character:

rangeFailed:
            pcmpistri xmm1, [rsi][rax*1], EqualAny
            jnc       bothFailed    ;Branch if both have failed
            
; Range failed, but Any succeeded. Use Any's value as the
; return result:

            add     rax, rcx
            jmp     success
            
; Down here, Range succeeded and Any has failed. Note
; that Range's match position is still sitting on the
; top of the stack. Pop it off and use that as our
; return value.
            
anyFailed:  pop     rcx
            add     rax, rcx
            jmp     success
            
; If both EqualRange and EqualAny comparisons have failed,
; we need to check for an end of string condition (zero
; terminating byte). If pcmpistri has seen one, then
; we return with the index of the end of the string.
; If pcmpistri has not seen a zero byte, then we need to
; add 16 to EAX and restart the scan.

bothFailed: jz      hasEOS
            add     rax, rcx        ;RCX contains 16
            jmp     bothLp

hasEOS:     mov     eax, [rsi-sohs].strObject.strLength
                    
            
; At this point, RAX contains index into xmm1 where the 
; match occurred. Return with RAX containing the index 
; of the character that matched.

success:    
            movdqu  xmm0, xmm0Save
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
fscanToCset endp
            end
