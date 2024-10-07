; stringInsert.asm
;
; Inserts a source string into a destination string
; at a specified offset.
;
; RSI-      Pointer to source string (strObject).
; RDI-      Pointer to destination string.
; EAX-      Index into destination for insertion.
;
; Returns with the carry flag set if there was an error:
;
; 1) Index into destination is greater than the length
;    of the destination string.
;
; 2) The length of the destination plus the length of the
;    source is greater than the maximum length of the
;    destination.
;
; 3) If RSI and RDI point at the same string.

            option     casemap:none
            include    string.inc
            include    aoalib.inc

            .code
stringInsert proc
             push   rax
             push   rcx
             push   rsi
             push   rdi

             mov	eax, eax        ;Clear HO bits of RAX

; First, see if the offset (in RAX) is out of range
; (greater than the length of the destination string):

            cmp     eax, [rdi-sohs].strObject.strLength
            ja      error
            
; Next, see if the length of the source plus the length
; of the destination is greater than the maximum length
; of the destination string.
;
; Remember: operations on 32-bit registers zero-extend
; into the HO 32 bits of the corresponding 64-bit
; register.

            mov     ecx, [rdi-sohs].strObject.strLength
            add     ecx, [rsi-sohs].strObject.strLength
            cmp     ecx, [rdi-sohs].strObject.maxLength
            ja      error
            
; Source and destination strings must not be the same:

            cmp     rdi, rsi
            je      error
            
; Okay, it is legitimate to insert the source into the
; destination string. First, make room in the destination
; by moving all the characters starting at position RAX
; up in memory. The number of bytes to move is
;       dest.length - offset + 1

            mov     ecx, [rdi-sohs].strObject.strLength
            sub     ecx, eax
            push    rcx
            
            mov     ecx, [rsi-sohs].strObject.strLength
            lea     rsi, [rdi][rax*1]               ;Move start
            add     rdi, rax                        ;Move dest
            add     rdi, rcx
            pop     rcx
            inc     rcx                             ;Copy 0 byte
            call    decMove         ;Open up room for source
            
; Restore registers from stack:

            mov     rdi, [rsp]      ;RDI on stack
            mov     rsi, [rsp+8]    ;RSI on stack
            
; Compute the new length of the destination string
; as the sum of the source and destination lengths:

            mov     ecx, [rsi-sohs].strObject.strLength
            add     [rdi-sohs].strObject.strLength, ecx
            
; Store the source string into the destination at the
; offset passed in the EAX register:

	mov	eax, [rsp+24]	;RAX on stack
            add     rdi, rax   
            call    incMove
             
alldone:    clc             ;Return success
            pop     rdi
            pop     rsi
            pop     rcx
            pop     rax
            ret

; Come down here if there was an error with the arguments.

error:       stc
             pop    rdi
             pop    rsi
             pop    rcx
             pop    rax
             ret
stringInsert endp
             end
