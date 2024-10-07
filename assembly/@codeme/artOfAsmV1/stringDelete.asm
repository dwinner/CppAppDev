; stringDelete.asm
;
; Deletes a substring from a larger string.
;
; RDI-      Pointer to destination string.
; EAX-      Index into destination for deletion.
; ECX-      Number of characters to delete from string
;
; Returns with the carry flag set if there was an error:
;
; 1) Index into destination is greater than the length
;    of the destination string.
;
; 2) The index plus the deletion length is greater than
;    the size of the destination string.

            option     casemap:none
            include    string.inc
            include    aoalib.inc

            .code
stringDelete proc
             push   rax
             push   rcx
             push   rsi
             push   rdi

             mov    eax, eax        ;Clear HO bits of RAX
             mov    ecx, ecx        ;Clear HO bits of RCX

; First, see if the offset (in RAX) is out of range
; (greater than the length of the destination string):

            cmp     eax, [rdi-sohs].strObject.strLength
            ja      error
            
; Next, see if the index plus the deletion length is
; greater than the size of the destination string.
;
; Remember: operations on 32-bit registers zero-extend
; into the HO 32 bits of the corresponding 64-bit
; register.

            mov     esi, eax
            add     esi, ecx
            cmp     esi, [rdi-sohs].strObject.strLength
            ja      error
            jne     removeChars
            
; Special case: if the caller is deleting all the characters
; from the offset in RAX to the end of the string, just adjust
; the length, store a new zero-terminating byte, and return.

            sub     [rdi-sohs].strObject.strLength, ecx
            mov     ecx, [rdi-sohs].strObject.strLength
            mov     byte ptr [rdi][rcx*1], 0
            jmp     allDone

; If we're removing characters, use a decMove
; operation to copy the characters beyond the
; deleted block over the top of the deletion block.
            
removeChars:push    rbx

; Compute new length:

            mov     ebx, [rdi-sohs].strObject.strLength
            sub     ebx, ecx
            mov     [rdi-sohs].strObject.strLength, ebx
            
; Compute movement addresses.

            lea     rdi, [rdi][rax*1]
            lea     rsi, [rdi][rcx*1]
            
; Compute the length of the block of data to move:

            sub     ebx, eax
            mov     ecx, ebx
            inc     ecx     ;Include zero byte.
                    
; Move the trailing block of bytes over the deleted
; block:

            call    incMove
            pop     rbx            
            
             
allDone:    clc             ;Return success
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
stringDelete endp
             end
