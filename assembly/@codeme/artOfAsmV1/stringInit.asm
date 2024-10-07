; stringInit.asm
;
;   Fills a string with a multiple copies of a
; single character.
;
; AL  contains initializer character.
; ECX contains the number of characters to copy.
; RDI points at destination string.
;
; Note: clears the direction flag
;
; Returns:
;
;  Carry flag set if string overflow would occur.
;  Carry flag clear if everything was okay.

            include string.inc

            .code
            externdef free:proc
            
stringInit  proc
            push    rcx
            push    rdi
            cmp     ecx, [rdi-sohs].strObject.maxLength
            ja      allDone
            
; Save ECX value as new length:

            mov     [rdi-sohs].strObject.strLength, ecx
            
; See if we're creating an empty string:

            test    ecx, ecx
            jz      emptyStr
            
            cld
    rep     stosb
    
emptyStr:   mov     byte ptr [rdi], 0
            stc             ;Return success
            
allDone:    cmc
            pop     rdi
            pop     rcx
            ret
stringInit  endp
            end
