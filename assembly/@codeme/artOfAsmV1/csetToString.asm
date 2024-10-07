; csetToString.asm
;
; Creates a string containing all the characters that
; are members of a given character set.
;
; On Entry:
;
;  RSI-     Points at a character set variable
;  RDI-     Points at a strObject variable whose
;           maxLen value is large enough to accept
;           a string containing all the characters
;           from the cset.
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

              .code
csetToString  proc
              push  rax
              push  rbx
              push  rcx
              push  r12
              push  r13
              
; Get the maxLen of the string so we can abort the function
; if the cset grows too long:

            mov     ebx, [rdi-sohs].strObject.maxLength
            xor     rcx, rcx        ;Current string length
            
            mov     r12, 0          ;Starting ASCII code
            mov     rax, [rsi]      ;First 64 bits to process
            call    emit64Chars     ;Do ASCII codes 0-63
            jc      error           ;Bail if string overflow
	            
            mov     r12, 64         ;Starting ASCII code
            mov     rax, [rsi+8]    ;Second 64 bits to process
            call    emit64Chars     ;Do ASCII codes 64-127
            jc      error           ;Bail if string overflow
	            
            mov     r12, 128        ;Starting ASCII code
            mov     rax, [rsi+16]   ;Third 64 bits to process
            call    emit64Chars      ;Do ASCII codes 128-191
            jc      error           ;Bail if string overflow
	            
            mov     r12, 192        ;Starting ASCII code
            mov     rax, [rsi+16]   ;Fourth 64 bits to process
            call    emit64Chars     ;Do ASCII codes 192-255
            jc      error           ;Bail if string overflow
	            
; Must zero-terminate the string and set the string's length.
; Note that the carry flag is clear at this point 
; if there was no error.

            mov     [rdi-sohs].strObject.strLength, ecx
            mov     byte ptr [rdi][rcx*1], 0
            jmp     allDone
            
; If there was an error, set the result string to the
; empty string:

error:      mov     byte ptr [rdi], 0
            mov     [rdi-sohs].strObject.strLength, 0
            stc

; Exit the function. Carry will be set if there was a
; string overflow:            
                    
allDone:      pop   r13
              pop   r12
              pop   rcx
              pop   rbx
              pop   rax
              ret
csetToString  endp

; emit64Chars-
;
; RAX contains 64 bits from the character set.
; R12 contains a starting ASCII code (for bit 0
; in RAX). For each set bit in RAX, emit a character
; to the string (and check for overflow, the maximum
; length is in EBX).

emit64Chars proc
            jmp     notPresent

; Search for the first set bit in RAX (we know
; RAX is non-zero at this point). Clear that
; bit and emit the ASCII code corresponding
; to its bit position (plus the offset passed
; in R12) to the end of the string:
            
cnvtLp:     bsf     r13, rax
            btr     rax, r13
            add     r13, r12
                    
            cmp     rcx, rbx        ;Check for string overflow
            jae     failure
            mov     [rdi][rcx*1], r13b      ;Append character
            inc     rcx                     ;Bump string len
            
notPresent: test    rax, rax        ;Check for additional chars
            jnz     cnvtLp
            clc
            ret
            
failure:    stc
            ret
emit64Chars endp
            end
