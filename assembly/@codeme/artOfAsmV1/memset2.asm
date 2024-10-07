; memset2.asm
;
;  memset function using stosb instruction.

            include zstrings.inc
            .code

memset2     proc
            push    rdi
            push    rcx
            
            cld
    rep     stosb
    
            pop     rcx
            pop     rdi
            ret
memset2     endp
            end
