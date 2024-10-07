; substring1.asm
;
;  Dead simple movsb implementation of substring operation.
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
; This function always clears the direction flag (and leaves
; it clear on exit).

            include string.inc

            .code
substring1  proc
            push    rcx
            push    rsi
            push    rdi
	
	mov	eax, eax	;Clear RAX HO bits
	mov	ecx, ecx	;Clear RCX HO bits
            
; Verify that the starting index is not beyond the
; end of the source1 string:

            cmp     eax, [rsi-sohs].strObject.strLength
            ja      strOvfl
            
; Verify that the starting index plus the desired substring
; length, is less than the length of the source string:

            add     rax, rcx
            cmp     eax, [rsi-sohs].strObject.strLength
            ja      strOvfl
            
; Restore starting index:

            sub     rax, rcx
            
            
; Point RSI at the start of the substring:

            add     rsi, rax
            
; Verify that the substring's length will fit into
; the destination string (length is passed in ECX):

            cmp     ecx, [rdi-sohs].strObject.maxLength
            ja      strOvfl
            
; Set the new length of the destination string:

            mov     [rdi-sohs].strObject.strLength, ecx
                    
            cld
    rep     movsb
    
; Emit a zero byte at the end of the substring:

            mov     byte ptr [rdi], 0

            pop     rdi
            pop     rsi
            pop     rcx
            clc             ;Indicate success.
            ret
            
strOvfl:    pop     rdi
            pop     rsi
            pop     rcx
            pop     rax
            stc             ;Indicate failure
            ret
substring1  endp
            end
