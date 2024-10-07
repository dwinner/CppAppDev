; Listing 9-12
;
; Exponent output helper function
;
; Cut and pasted from Listing 9-10

;*************************************************************
;
; expToBuf-
;
;  Unsigned integer to buffer.
; Used to output up to 4-digit exponents.
;
; Inputs:
;
;    EAX:   Unsigned integer to convert
;    ECX:   Print width 1-4
;    RDI:   Points at buffer.
;
;    FPU:	Uses FPU stack.
;
; Returns:
;
;    RDI:	Points at end of buffer.
;

expToBuf    proc

expWidth    equ     <[rbp+16]>
exp         equ     <[rbp+8]>
bcd         equ     <[rbp-16]>

            push    rdx
            push    rcx     ;At [RBP+16]
            push    rax     ;At [RBP+8]
            push    rbp
            mov     rbp, rsp
            sub     rsp, 16

; Verify exponent digit count is in the range 1-4:

            cmp     rcx, 1
            jb      badExp
            cmp     rcx, 4
            ja      badExp
            mov     rdx, rcx
            
; Verify the actual exponent will fit in the number of digits:

            cmp     rcx, 2
            jb      oneDigit
            je      twoDigits
            cmp     rcx, 3
            ja      fillZeros       ;4 digits, no error
            cmp     eax, 1000
            jae     badExp
            jmp     fillZeros
            
oneDigit:   cmp     eax, 10
            jae     badExp
            jmp     fillZeros
            
twoDigits:  cmp     eax, 100
            jae     badExp
            
            
; Fill in zeros for exponent:

fillZeros:  mov     byte ptr [rdi+rcx*1-1], '0'
            dec     ecx
            jnz     fillZeros
            
; Point RDI at the end of the buffer:

            lea     rdi, [rdi+rdx*1-1]
            mov     byte ptr [rdi+1], 0
            push    rdi                 ;Save pointer to end

; Quick test for zero to handle that special case:

            test    eax, eax
            jz      allDone
            
; The number to convert is non-zero.
; Use BCD load and store to convert
; the integer to BCD:

            fild    dword ptr exp   ;Get integer value
            fbstp   tbyte ptr bcd   ;Convert to BCD
            
; Begin by skipping over leading zeros in
; the BCD value (max 10 digits, so the most
; significant digit will be in the HO nibble
; of byte 4).

            mov     eax, bcd        ;Get exponent digits
            mov     ecx, expWidth   ;Number of total digits
            
OutputExp:  mov     dl, al
            and     dl, 0fh
            or      dl, '0'
            mov     [rdi], dl
            dec     rdi
            shr     ax, 4
            jnz     OutputExp


; Zero-terminte the string and return:
            
allDone:    pop     rdi
            leave
            pop     rax
            pop     rcx
            pop     rdx
            clc
            ret
            
badExp:     leave
            pop     rax
            pop     rcx
            pop     rdx
            stc
            ret
            
expToBuf    endp

