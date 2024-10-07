; strchr2-
;
;  An optimized 64-bit assembly strchr function.
;
; RSI-      Points at string
; AL-       Character to search for
;
; Returns:
;
; RAX-      Position of char, or NULL if not present
;
; Also searches forward in the string, but
; does not quit until it sees the zero
; terminating byte. Tracks the address
; of the last matching character it has
; seen.

            include zstrings.inc

            .code
strchr2     proc
zstrp       textequ <[rsp+24]>

            push    rdi            
            push    rsi
            push    rbx
            push    rcx
            push    rdx
            
            mov     rbx, sevenFs
            mov     rcx, eighties
            mov     rdi, ones
            
; Copy the matching character throughout
; RDI (8 copies of the character).

            and     eax, 0ffh
            mov     ah, al
            mov     edx, eax
            shl     eax, 16
            or      eax, edx
            bswap   rax
            or      rdx, rax
            
; We need to get RSI qword-aligned before proceeding.
; May need to skip over as many as three bytes
; to achieve dword alignment.
            
qAlign      macro
            test    rsi, 7
            jz      RSIisAligned;

; Need to skip at least 1 byte to achieve
; alignment. See if it's the matching
; byte or zero byte:
            
            cmp     dl, byte ptr [rsi]
            je      SetRSI
            
            cmp     byte ptr [rsi], 0
            je      SetRSI0
            inc     rsi
            endm
            
; At byte 0, see if qword aligned:

            qAlign
                    
; At byte 1, 2, ..., 6 see if qword aligned:

            qAlign  
            qAlign  
            qAlign  
            qAlign  
            qAlign  
            qAlign  
            
            
; At byte 7. See if it's
; qword aligned.

            test    rsi, 7
            jz      RSIisAligned;
            
            cmp     dl, byte ptr [rsi]
            je      SetRSI
            
            cmp     byte ptr [rsi], 0
            je      SetRSI0
            inc     rsi             ; After this, RSI is aligned.
            
 
; The following loop processes 8 characters
; at a time.
           
RSIisAligned:
            sub     rsi, 8          ; To counteract add immediately below.
ZeroLoop:   add     rsi, 8          ; Skip chars this loop just processed.
ZeroLoop2:
            mov     rax, [rsi]      ; Get next 8 chars into RAX.
            xor     rax, rdx        ; Convert matching char to zero.
            and     rax, rbx        ; Clear H.O. bit (note:80->00!)
            sub     rax, rdi        ; 00 and 80->FF, all others have pos val.
            and     rax, rcx        ; Test all H.O. bits.  If any are set, then
            jnz     MightMatch      ;  we've got a 00 or 80 byte.
            
            mov     rax, [rsi]      ; Same as above, but checking for
            and     rax, rbx        ; a zero byte.  
            sub     rax, rdi  
            and     rax, rcx  
            jz     ZeroLoop  
            
; If we get to this point, we've matched the char in
; positions 0..7, we've matched a zero byte, we've
; matched 80h, or we've matched (80h xor matchchar).
; Check for zero or matched char; quit if we find it.
; Otherwise continue loop:

MightMatch:
            mov     rax, [rsi]      ; Get the original 8 bytes.
            cmp     al, dl         ; See if the first byte matched.
            je      SetRSI
            cmp     al, 0           ;Or do we get a zero byte first?
            je      SetRSI0
            
            cmp     ah, dh         ; See if byte #1 matched.
            je      SetRSI1
            cmp     ah, 0
            je      SetRSI0
            
            shr     rax, 16
            cmp     al, dl         ; See if byte #2 matched.
            je      SetRSI2
            cmp     al, 0
            je      SetRSI0
            
            cmp     ah, dh         ; See if byte #3 matched.
            je      SetRSI3
            cmp     ah, 0
            je      SetRSI0
            
            shr     rax, 16
            cmp     al, dl         ; See if byte #4 matched.
            je      SetRSI4
            cmp     al, 0
            je      SetRSI0
            
            cmp     ah, dh         ; See if byte #5 matched.
            je      SetRSI5
            cmp     ah, 0
            je      SetRSI0
            
            shr     rax, 16
            cmp     al, dl         ; See if byte #6 matched.
            je      SetRSI6
            cmp     al, 0
            je      SetRSI0
            
            cmp     ah, 0
            je      SetRSI0
            cmp     ah, dh         ; See if byte #7 matched.
            jne     ZeroLoop
            
; The following compute the length of the string by subtracting
; the current RSI value from the original value and then adding
; zero, one, two, or three, depending on where we branched out
; of the MightBeZero0 sequence above.

SetRSI7:    lea     rax, [rsi+7]    ; +7 since it was in the H.O. byte.
            jmp     allDone

SetRSI6:    lea     rax, [rsi+6]    ; +6 since it was in byte #6.
            jmp     allDone

SetRSI5:    lea     rax, [rsi+5]    ; +5 since it was in byte #5.
            jmp     allDone

SetRSI4:    lea     rax, [rsi+4]    ; +4 since it was in byte #4.
            jmp     allDone

SetRSI3:    lea     rax, [rsi+3]    ; +3 since it was in byte #3.
            jmp     allDone
            
SetRSI2:    lea     rax, [rsi+2]    ; +2 since it was in byte #2.
            jmp     allDone
            
SetRSI1:    lea     rax, [rsi+1]    ; +1 since it was in byte #1.
            jmp     allDone

SetRSI0:    xor     rsi, rsi        
SetRSI:     mov     rax, rsi
allDone:    pop     rdx
            pop     rcx
            pop     rbx
            pop     rsi             ; zero was in L.O. byte.
            pop     rdi
            ret
                    
strchr2     endp
            end
