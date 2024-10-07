; strrchr2-
;
;  An optimized 64-bit assembly strrchr function.
;
; RSI-      Points at string
; AL-       Character to search for
;
; Returns:
;
; RAX-      Position of char, or NULL if not present

            include zstrings.inc
            
            .code
strrchr2    proc
            push    rdi            
            push    rsi
            push    rbx
            push    rcx
            push    rdx
            push    rbp
            xor     rbp, rbp        ;Assume no match
                     
            mov     rdi, sevenFs
            mov     rcx, eighties
            mov     rdx, ones
            
; Copy the character to match throughout
; the RBX register (8 copies):

            and     eax, 0ffh
            mov     ah, al
            mov     ebx, eax
            shl     eax, 16
            or      eax, ebx
            mov     ebx, eax
            bswap   rax
            or      rbx, rax
 
; We need to get RSI qword-aligned before proceeding.
; Here's a helper macro to reduce source code size:

qrAlign     macro
            local   try0
            test    rsi, 7
            jz      RSIisAligned;

; Need to skip at least 1 byte to achieve
; alignment. See if it's the matching
; byte or zero byte:
            
            cmp     bl, byte ptr [rsi]
            jne     try0
            mov     rbp, rsi
            
try0:       cmp     byte ptr [rsi], 0
            je      SetRSI0
            inc     rsi
            endm

;
; May need to advance as many as 7 bytes
; to achieve qword alignment. Note that
; the matched byte or a zero byte could
; occur on these 7, so we have to manually
; check for these values.
;
; Check byte 0's address:

            qrAlign
            
; Check byte 1..7's address:

            qrAlign
            qrAlign
            qrAlign
            qrAlign
            qrAlign
            qrAlign
            qrAlign
             
            
; The following code grabs 8 bytes at a time and checks
; to see if any of them are the matched by or a zero byte.
            
RSIisAligned:
            sub     rsi, 8          ; To counteract add immediately below.
ZeroLoop:   add     rsi, 8          ; Skip chars this loop just processed.
            mov     rax, [rsi]      ; Get next 8 chars into RAX.

; This sequence sets any bytes to zero that
; are equal to the match byte:

            xor     rax, rbx        ; Convert matching char to zero.
            and     rax, rdi        ; Clear H.O. bit (note:80->00!)
            sub     rax, rdx        ; 00 and 80->FF, all others have pos val.
            and     rax, rcx        ; Test all H.O. bits.  If any are set, then
            jnz     MightMatch      ;  we've got a 00 or 80 byte.
            
; This code checks all 8 bytes to see
; if any of them contain 0 (or 80h).

            mov     rax, [rsi]      ; Same as above, but checking for
            and     rax, rdi        ; a zero byte.  
            sub     rax, rdx  
            and     rax, rcx  
            jz      ZeroLoop  

            
; If we get to this point, we've matched the char in
; positions 0..7, we've matched a zero byte, we've
; matched 80h, or we've matched (80h xor matchchar).
; Check for zero or matched char; quit if we find it.
; Otherwise continue loop:

MightMatch:
            mov     rax, [rsi]      ; Get the original 8 bytes.

; Did a zero byte come before the
; matched byte? If so, bail.

            cmp     al, 0 
            je      SetRSI0
            
; See if 1st byte matched. If it did,
; then we need to save a pointer to
; that byte (in RBP):

            cmp     al, bl
            jne     tryByte1
            mov     rbp, rsi          

; Is the second byte a zero?
            
tryByte1:   cmp     ah, 0
            je      SetRSI0
            
; If not, is it the match byte?

            cmp     ah, bh            
            jne     tryByte2
            
; If it matched, save a pointer to
; the byte.

            lea     rbp, [rsi+1]

; Check the third and fourth bytes
; to see if they are zero or the
; match byte:
            
tryByte2:   shr     rax, 16
            cmp     al, 0
            je      SetRSI0
            cmp     al, bl            
            jne     tryByte3
            lea     rbp, [rsi+2]
            
tryByte3:   cmp     ah, 0
            je      SetRSI0

            cmp     ah, bh            
            jne     tryByte4
            lea     rbp, [rsi+3]

; Check the fifth and sixth bytes
; to see if they are zero or the
; match byte:

tryByte4:   shr     rax, 16
            cmp     al, 0
            je      SetRSI0
            
            cmp     al, bl            
            jne     tryByte5
            lea     rbp, [rsi+4]
            
tryByte5:   cmp     ah, 0
            je      SetRSI0
            cmp     ah, bh            
            jne     tryByte6
            lea     rbp, [rsi+5]
 
; Check the seventh and eighth
; bytes to see if they are zero
; or the match byte:
           
tryByte6:   shr     rax, 16
            cmp     al, 0
            je      SetRSI0
            cmp     al, bl            
            jne     tryByte7
            lea     rbp, [rsi+6]
            
tryByte7:   cmp     ah, 0
            je      SetRSI0
            cmp     ah, bh
            jne     ZeroLoop
            
            lea     rbp, [rsi+7]
            jmp     ZeroLoop

; At this point, RBP contains a
; pointer to the last byte we
; matched (or it contains NULL
; if we didn't match at all).
            
SetRSI0:    mov     rax, rbp 
            pop     rbp
            pop     rdx
            pop     rcx
            pop     rbx
            pop     rsi
            pop     rdi
            ret
                    
strrchr2    endp
            end
