; get16AtRDI-
;
; Common code for strspn4 and strcspn4
;
; Fetches 16 bytes from the cset pointed at by RDI
; and puts them in XMM0. Stops if there is a zero 
; terminating byte. Adds number of actual bytes 
; (up to zero-terminating byte) to RCX. Returns 
; carry set if a zero byte was encountered. Leaves 
; RDI pointing at the next block of 16 bytes if 
; there wasn't a zero-terminating byte.
;
; Uses XMM1, RAX, and R15 as temps.

            include zstrings.inc

            .code
get16AtRDI  proc
            pxor    xmm1, xmm1
            mov     rax, rdi
            and     rax, 0fffh
            cmp     rax, 0ff0h
            ja      mustReadBytes
            
; Have at least 16 bytes before end of MMU page.
; Read all 16 here:

            movdqu   xmm0, [rdi]
            pcmpeqb  xmm1, xmm0     ;Check for a 0 byte.
            pmovmskb eax, xmm1
            test     eax, eax
            jnz      has0Byte

; Got 16 cset bytes in XMM0. Adjust RDI and RCX
; and return to caller:

            add     rdi, 16
            add     rcx, 16
            clc                     ;No 0 byte yet.
            ret
            
; Found a zero byte in XMM0. Need to mask out
; all bytes beyond that point and adjust
; RDI and RCX appropriately. (note: bsf zero
; extends into RAX).

has0Byte:   bsf      eax, eax       ;Find zero byte.
            add      rcx, rax       ;Count bytes to 0 byte.
            
; Use the maskOut0s table to zero out all bytes
; beyond the zero-terminating byte:

            shl      rax, 4
            lea      r15, maskOut0s
            pand     xmm0, [r15][rax*1]
; Note: no need to update RDI because we've found the
; zero byte.

            stc                     ;Found zero byte
            ret

; If we get to this point, we're near the end of an
; MMU page and we need to read the bytes one at a time
; until we read 16 bytes or find a zero byte. This is 
; to avoid accessing data in an inaccessible MMU page.

mustReadBytes:
            pxor    xmm0, xmm0
            xor     r15, r15        ;Count bytes here
            jmp     test4Zero
            
byteLp:     pslldq  xmm0, 1 ;Make room for new byte.
            pinsrb  xmm0, eax, 0
            inc     r15             ;Count bytes
            inc     rdi             ;Move on to next byte
            inc     rcx             ;Adjust for new byte
            cmp     r15, 16
            jae     got16

test4Zero:  movzx   eax, byte ptr [rdi]
            test    eax, eax
            jnz     byteLp
            stc                     ;Found zero byte
            ret

got16:
            clc                     ;Processed 16 bytes
            ret                     ; w/o a zero byte.              
            
            
get16AtRDI  endp
            end
