            
;***************************************************************
;            
; strlen5.asm
;
;  (Modified) GLIBC variant of 64-bit strlen function
;
; RSI-      Points at string
;
; Returns:
;
; RAX-      String Length

            include zstrings.inc

            .code

magicBits   =       0fefefefefefefeffh
hiMagic     =       08080808080808080h
loMagic     =       00101010101010101h

strlen5     proc
            push    rbx
            push    rdx
            push    rcx
            push    rsi
            mov     rbx, loMagic
            mov     rdx, hiMagic
            
; We need to get RSI qword-aligned before proceeding:
; Note that by qword-aligning RSI, we ensure that
; reading 8 bytes at a time will never cross a
; 4 KB boundary (so we won't get any page faults
; because we read beyond the string and into the
; next page in memory, that might not be present).
            
            test    rsi, 7                  ;Already aligned?
            jz      RSIisAligned
            
            alignRSI 7                      ;Was byte 7
            alignRSI 7                      ;Was byte 6
            alignRSI 7                      ;Was byte 5
            alignRSI 7                      ;Was byte 4
            alignRSI 7                      ;Was byte 3
            alignRSI 7                      ;Was byte 2
                        
            cmp     byte ptr [rsi], 0       ;EOS
            je      SetRSI
            inc     rsi                     ;Was at byte 1.
            
 
; At this point, RSI is aligned on an 8-byte boundary.

RSIisAligned:
            sub     rsi, 8
lenLoop:    add     rsi, 8
            mov     rax, [rsi]
            sub     rax, rbx        ;loMagic
            and     rax, rdx        ;hiMagic
            jz      lenLoop
            
; Got to this point because one of the 8 byte
; contained 0. However, there are a few other
; values that could lead to this point, so we
; have to explicitly test for an actual zero.
;
; Get the original 8 bytes.

            mov     rax, [rsi]      

; See if the first byte contained zero.

            cmp     al, 0           
            je      SetRSI

; See if byte 1 contained zero.

            cmp     ah, 0           
            je      SetRSI1

; See if byte 2 contained zero.

            test    eax, 0FF0000h   
            je      SetRSI2

; See if byte 3 contained zero.

            test    eax, 0FF000000h 
            je      SetRSI3
            
; Swap HO and LO dwords:

            bswap   rax


; See if byte 4 contained zero.

            test    eax, 0FF000000h 
            jz      SetRSI4         

; See if byte 5 contained zero.

            test    eax, 0FF0000h   
            jz      SetRSI5

; See if byte 6 contained zero.

            cmp     ah, 0           
            je      SetRSI6

; See if byte 7 contained zero.

            cmp     al, 0           
            jne     lenLoop         ;Branch if it was not 0.         


; If a zero in byte 7, compute length
; and return.
 
unroll5     macro   ofs
            local   lbl
lbl         catstr  <SetRSI>, %ofs
lbl:
            lea     rax, [rsi+ofs]
            pop     rsi
            sub     rax, rsi
            pop     rdx
            pop     rcx
            pop     rbx
            ret
            endm
            
; Note: code above must drop down into expansion
; of "unroll5 7", which expands to:
;
; SetRSI7:
;           lea     rax, [rsi+7]
;           pop     rsi
;           sub     rax, rsi
;           pop     rdx
;           pop     rcx
;           pop     rbx
;           ret

            
            unroll5 7
            
            unroll5 4
            unroll5 3
            unroll5 2
            unroll5 1
            unroll5 5
            unroll5 6
            
; SetRSI is a special case.
;            
; If a zero in byte 0, compute length
; and return.
            
SetRSI:     mov     rax, rsi
            pop     rsi
            sub     rax, rsi
            pop     rdx
            pop     rcx
            pop     rbx
            ret
strlen5     endp
            end