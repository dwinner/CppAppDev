; substring2.asm
;
;  A second version that uses SSE registers to copy the
; data (rather than the movsb instruction).
;
; On Entry:
;
;   RSI     Points at source string object
;   EAX     Contains index into string to starting position.
;   ECX     Contains length of substring to extract.
;   RSI     Points at destination string object.
;
; On Exit:
;
;   Carry is set if there was an error (string
;   overflow- an attempt to store too many characters
;   into the destination string).
;
; This function can clear the direction flag if it
; falls back to using the movsb instruction.

            include string.inc

            .code
substring2  proc

xmmSave0    textequ <[rsp]>
rsiSave     textequ <[rsp+16]>
rdiSave     textequ <[rsp+24]>
rcxSave     textequ <[rsp+32]>

; If there are fewer than 16 bytes to copy, just
; use the movsb version and skip all the overhead
; of using the SSE instructions.

            cmp     rcx, 16
            jb      substring1
            
            push    rbx     ;Pushes must appear in this
            push    rcx     ; EXACT order!
            push    rdi     
            push    rsi     
            sub     rsp, 16
            movdqu  xmmSave0, xmm0
	
	mov	ecx, ecx	;Clear RCX HO bits
	mov	eax, eax	;Clear RAX HO bits
            
; Verify that the starting index is not beyond the
; end of the source1 string:

            cmp     eax, [rsi-sohs].strObject.strLength
            ja      strOvfl
            
; Verify that the starting index plus the desired substring
; length, is less than the length of the source string:

            add     rax, rcx
            cmp     eax, [rsi-sohs].strObject.strLength
            ja      strOvfl
            
; Compute the maximum address where we can load 16
; bytes from the source string. Note that we don't
; have to worry about the destination string, as this
; code always stores data at the start of it's data
; area, so there is always a buffer of 16 bytes available.

            mov     ebx, [rsi-sohs].strObject.maxLength
            lea     rbx, [rsi][rbx*1 - 16]
            
; Restore starting index.

            sub     rax, rcx
            
; Point RSI at the start of the substring:

            add     rsi, rax
            
; Verify that the substring's length will fit into
; the destination string (length is passed in ECX):

            cmp     ecx, [rdi-sohs].strObject.maxLength
            ja      strOvfl
            
; Set the new length of the destination string:

            mov     [rdi-sohs].strObject.strLength, ecx
            
; Merge RSI+RDI so we only have to increment one pointer:

            sub     rdi, rsi
            
            test    rcx, rcx
            jz      emptyStr
            jmp     tstEndSSE

; As long as there are at least 16 characters left
; in the string, go ahead an use a MOVDQU instruction
; to copy 16 bytes.

copy16:     
            movdqu  xmm0, [rsi]
            movdqu  [rdi][rsi*1], xmm0
            add     rsi, 16
tstEndSSE:  
            sub     rcx, 16
            js      mayHaveMore
            cmp     rsi, rbx
            jbe     copy16
            
; At this point, there are fewer than 16 bytes left in
; the source string. If RCX is positive, there are still
; a few bytes left to copy. Use movsb to copy them.

mayHaveMore:
            add     rcx, 16  ;Recover from last SUB.
            jz      emptyStr ;If len was multiple of 16 chars.
            add     rdi, rsi ;Repair damage done to RDI.
            
            cld
    rep     movsb            ;Copy remaining bytes in string.


; Zero-terminate the string before we're done:
            
emptyStr:   
            mov     rdi, rdiSave    ;Get original dest pointer.
            mov     ebx, rcxSave    ;Get original length.
            mov     byte ptr [rdi][rbx*1], 0
            
; Restore registers:
                            
            movdqu  xmm0, xmmSave0
            add     rsp, 16
            pop     rsi
            pop     rdi
            pop     rcx
            pop     rbx
            clc             ;Return success
            ret

; Drop down here if the substring won't fit in the
; destination string or if the index into the source
; string (plus length) would exceed the length of 
; the source string.
            
strOvfl:    movdqu  xmm0, xmmSave0
            add     rsp, 16
            pop     rsi
            pop     rdi
            pop     rcx
            pop     rbx
            stc             ;Return failure
            ret
substring2  endp            
            end
