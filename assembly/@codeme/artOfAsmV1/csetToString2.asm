; csetToString2.asm
;
; Creates a string containing all the characters that
; are members of a given character set. Emits hex values
; for character codes in the range 0h-20h and 80h-0ffh
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
	   include aoalib.inc

              .code
csetToString2 proc
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
            call    emit64Hex       ;Do ASCII codes 0-63
            jc      error           ;Bail if string overflow
	            
            mov     r12, 64         ;Starting ASCII code
            mov     rax, [rsi+8]    ;Second 64 bits to process
            call    emit64Hex       ;Do ASCII codes 64-127
            jc      error           ;Bail if string overflow
	            
            mov     r12, 128        ;Starting ASCII code
            mov     rax, [rsi+16]   ;Third 64 bits to process
            call    emit64Hex        ;Do ASCII codes 128-191
            jc      error           ;Bail if string overflow
	            
            mov     r12, 192        ;Starting ASCII code
            mov     rax, [rsi+24]   ;Fourth 64 bits to process
            call    emit64Hex       ;Do ASCII codes 192-255
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
csetToString2 endp

; emit64Hex-
;
; RAX contains 64 bits from the character set.
; R12 contains a starting ASCII code (for bit 0
; in RAX). For each set bit in RAX, emit a character
; to the string (and check for overflow, the maximum
; length is in EBX).

hexTable	byte	"0123456789ABCDEF"

emit64Hex   proc
	push	r15
	lea	r15, hexTable
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
	cmp	r13b, 20h
	jb	doHex
	cmp	r13b, 80h
	jb	doASCII
doHex:	add	rcx, 3		;Emitting 4 characters
	cmp	rcx, rbx	;Test for string overflow
	jae	failure
	mov	byte ptr [rdi][rcx*1-3], ' '
	push	r13
	shr	r13b, 4
	movzx	r13, r13b
	mov	r13b, [r15][r13]
	mov	[rdi][rcx*1-2], r13b
	pop	r13
	and	r13, 0fh
	mov	r13b, [r15][r13]
	mov     [rdi][rcx*1-1], r13b      ;Append character
	mov	byte ptr [rdi][rcx*1], ' '
	inc	rcx
	jmp	notPresent

doASCII:    mov     [rdi][rcx*1], r13b      ;Append character
            inc     rcx                     ;Bump string len
            
notPresent: test    rax, rax        ;Check for additional chars
            jnz     cnvtLp
            clc
	pop	r15
            ret
            
failure:    stc
	pop	r15
            ret
emit64Hex   endp
            end
