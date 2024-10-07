; csetToRange.asm
;
; Creates a string containing ranges of characters
; from a cset. Each range will consume two byte
; positions in the string: the first character is the
; start of the range, the second character (which could
; be the same as the first if the range has only one
; character) is the end of the range. This function
; concatenates all the ranges in the cset into a
; single string (for use with the PCMPxSTRy instructions).
;
; On Entry:
;
;  RSI-     Points at a character set variable
;  RDI-     Points at a strObject variable whose
;           maxLen value is large enough to accept
;           a string containing all the ranges.
;
; On Exit:
;
; at RDI-   Specified string is filled with the characters
;           (assuming no error).
;
; Carry-    Clear if the operation was successful.
;           Set if there was a string overflow.

             include cset.inc
             include string.inc
             include aoalib.inc

             .code
csetToRange  proc
             push  rax
             push  rbx
             push  rcx
             push  r12
             push  r13
             push  r14
              
; Get the maxLen of the string so we can abort the function
; if the cset grows too long:

            mov     ebx, [rdi-sohs].strObject.maxLength
            xor     r13, r13        ;Current string length
            xor     r14, r14        ;No pre=existing run

            mov     r12, 0          ;Starting ASCII code
            mov     rax, [rsi]      ;First 64 bits to process
            call    emit64          ;Do ASCII codes 0-63
            jc      error           ;Bail if string overflow
	
            mov     r12, 64         ;Starting ASCII code
            mov     rax, [rsi+8]    ;Second 64 bits to process
            call    emit64          ;Do ASCII codes 64-127
            jc      error           ;Bail if string overflow
                        
            mov     r12, 128        ;Starting ASCII code
            mov     rax, [rsi+16]   ;Third 64 bits to process
            call    emit64          ;Do ASCII codes 128-191
            jc      error           ;Bail if string overflow
                        
            mov     r12, 192        ;Starting ASCII code
            mov     rax, [rsi+24]   ;Fourth 64 bits to process
            call    emit64          ;Do ASCII codes 192-255
            jc      error           ;Bail if string overflow
            
            cmp     r14b, 0         ;Check for an open run
            je      finishStr

; If r14b was non-zero, we have an open range. Emit the final 
; two characters to the string (r14b and 0ffh).

            add     r13, 2          ;Adding two chars to string
            cmp     r13, rbx        ;Check for string overflow
            ja      error
            mov     [rdi][r13*1-2], r14b          ;Range start
            mov     byte ptr [rdi][r13*1-1], 0ffh ;End of range
                        
; Must zero-terminate the string and set the string's length.
; Note that the carry flag is clear at this point 
; if there was no error.

finishStr:  mov     [rdi-sohs].strObject.strLength, r13d
            mov     byte ptr [rdi][r13*1], 0
            clc
            jmp     allDone
            
; If there was an error, set the result string to the
; empty string:

error:      mov     byte ptr [rdi], 0
            mov     [rdi-sohs].strObject.strLength, 0
            stc

; Exit the function. Carry will be set if there was a
; string overflow:            
                    
allDone:     pop   r14
             pop   r13
             pop   r12
             pop   rcx
             pop   rbx
             pop   rax
             ret
csetToRange  endp

; Emit64-
;
; RAX contains 64 bits from the character set.
; R12 contains a starting ASCII code (for bit 0
; in RAX). Build a range. Note that this function
; returns CF=1 if there was a string overflow.
;
; On entry, r14b contains the ASCII code of
; any previous cset range (0 if there is no
; current range). 

emit64      proc
            bsf     rcx, rax        ;Are there any chars in this
            jnz     cnvtEnter       ; 64-bit block?
            
; If there were no characters in the 64-bit block, we must
; check to see if the previous call to emit64 had an open
; range.

            cmp     r14b, 0
            je      success
            
; Emit the outstanding block:

            add     r13, 2          ;Adding two chars to string
            cmp     r13, rbx
            jae     failure
            mov     [rdi][r13*1-2], r14b
            dec     r12b            ;Must emit end of last blk
            mov     [rdi][r13*1-1], r12b
            xor     r14, r14
            jmp     success         ;No more to do in this blk
            
; If the incoming range value (in R14b) is zero, then set
; the start of range to the current bit position (in R12)
; plus the first set bit we found (in R13).

cnvtEnter:  cmp     r14b, 0
            jne     dontChange
            lea     r14, [r12][rcx] ;Staring ASCII code.

; Shift the bits down so that the LO bit of RAX is the
; next bit to test in the range:

dontChange: shr     rax, cl ;Move set bit into carry
            shr     rax, 1
	jz	emitTwice

; Now, begin scanning for the first zero bit:
            
look4Zero:  inc     rcx             ;Next character index
            shr     rax, 1          ;See if it's a member
            jz      endOfBits0      ;Bail if end of block
            jc      look4Zero       ;Repeat while member
            
; We've hit the end of the range at this point.
; Emit a pair of characters to the output string.

            add     r13, 2          ;Adding two chars to string
            cmp     r13, rbx        ;Check for string overflow
            ja      failure
            mov     [rdi][r13*1-2], r14b ;Start of range
            lea     r14, [rcx][r12-1]
            mov     [rdi][r13*1-1], r14b   ;End of range
            xor     r14, r14        ;No longer in a range

; Now we have to find the start of the next run of 1s:

look4one:   inc     rcx
            shr     rax, 1
            jz      endOfBits1
            jnc     look4one
            
; We found a 1 bit. Save the character code as the
; start of a run and then start looking for the end
; of the run:

            lea     r14, [rcx][r12]
            jmp     look4Zero

; We get to endOfBits0 if we were searching for a zero
; bit and RAX became zero.

endOfBits0:
            jnc     CFeq0
            
; We were searching for a zero bit when RAX became 0.
; The last bit shifted out was a 1 (obviously, as
; we were searching for a zero in a run of 1s). 

            cmp     rcx, 63         ;Are we at end of blk?
            jae     success         ;Let caller deal with it
            
; Need to end the current outstanding block:

CFeq0:      add     r13, 2          ;Adding two chars to string
            cmp     r13, rbx        ;Check for string overflow
            ja      failure
            mov     [rdi][r13*1-2], r14b ;Start of range
            lea     r14, [rcx][r12]
            mov     [rdi][r13*1-1], r14b ;End of range
            xor     r14, r14             ;No longer in a range
            jmp     success


; We get to endOfBits1 if we were searching for a one
; bit and RAX became zero.    

endOfBits1: jnc     success         ;If current bit was 0, too
            cmp     cl, 63          ;If not at end of block
            jne     emitTwice       ; we have a singleton
            
            lea     r14, [r12][rcx] ;At end of blk, then
            jmp     success         ; carry over range

; Create a singleton range by outputting the same
; character twice:

emitTwice:  add     r13, 2          ;Adding two chars to string
            cmp     r13, rbx        ;Check for string overflow
            ja      failure
            lea     r14, [rcx][r12]
            mov     [rdi][r13*1-2], r14b ;Start of range
            mov     [rdi][r13*1-1], r14b ;End of range
            xor     r14, r14        ;No longer in a range

success:    clc
            ret
            
failure:    stc
            ret
emit64      endp
            end
