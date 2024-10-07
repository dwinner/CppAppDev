            
;***************************************************************
;            
; strlen4.asm
;
;  An optimized 64-bit assembly strlen function.
;
; RSI-      Points at string
;
; Returns:
;
; RAX-      String Length

            include zstrings.inc

            .code
            

sevenFs     qword   7f7f7f7f7f7f7f7fh
eighties    qword   8080808080808080h
ones        qword   0101010101010101h

strlen4     proc
zstrp       textequ <[rsp+24]>
            
            push    rsi
            push    rbx
            push    rcx
            push    rdx
            
            mov     rbx, sevenFs
            mov     rcx, eighties
            mov     rdx, ones
            
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
; The following code unrolls 8 loop iterations (total of
; 64 bytes per loop iteration). See the comments for the
; 32-bit strlen function-same operation, just extended
; to 64 bits.
           
RSIisAligned:
            sub     rsi, 64         ;Unroll loop 8 times         
ZeroLoop:   add     rsi, 64         ; so add 64, not 8,         
ZeroLoop2:                          ; here.

; Unrolling the loop 8 times takes a lot
; of code. Use a macro to reduce the amount
; of cut & paste that takes place here:

unroll4     macro   ofs
            local   dest
dest        catstr  <MightBeZero>, %ofs
            mov     rax, [rsi+ofs]      
            and     rax, rbx        
            sub     rax, rdx        
            and     rax, rcx        
            jnz     dest
            endm
            
; "unroll4 0" expands to:
;   mov     rax, [rsi+0]  
;   and     rax, rbx
;   sub     rax, rdx
;   and     rax, rcx
;   jz      MightBeZero0

            unroll4 0
            unroll4 8
            unroll4 16
            unroll4 24
            unroll4 32
            unroll4 40
            unroll4 48

; Special case for offset 56:
            
            mov     rax, [rsi+56]  
            and     rax, rbx
            sub     rax, rdx
            and     rax, rcx
            jz      ZeroLoop
            
; Okay, we've found a 00 or 80 byte in positions
; 56..63.  Check for the location of the zero byte, if any.
            
            add     rsi, 56
            jmp     MightBeZero0;

; If we get to this point, we've found a 00h or 80h byte in
; positions 8..15:

MightBeZero8:       
            add     rsi, 8
            jmp     MightBeZero0

; If we get to this point, we've found a 00h or 80h byte in
; positions 16..23:

MightBeZero16:      
            add     rsi, 16
            jmp     MightBeZero0

; If we get to this point, we've found a 00h or 80h byte in
; positions 24..31:

MightBeZero24:      
            add     rsi, 24
            jmp     MightBeZero0


; If we get to this point, we've found a 00h or 80h byte in
; positions 32..39:

MightBeZero32:      
            add     rsi, 32
            jmp     MightBeZero0

; If we get to this point, we've found a 00h or 80h byte in
; positions 40..47:

MightBeZero40:      
            add     rsi, 40
            jmp     MightBeZero0

; If we get to this point, we've found a 00h or 80h byte in
; positions 48..55:

MightBeZero48:      
            add     rsi, 48

; If we get to this point, we've found a 00h or 80h byte in
; positions 0..7 or we've branched here from one of the
; above conditions. Have to figure out if we have an actual
; 00h byte (meaning we're done) or a 80h byte.

MightBeZero0:
            mov     rax, [rsi]      ; Get the original 8 bytes.

; See if the first byte contained zero.

            cmp     al, 0           
            je      SetRSI

; See if byte 1 contained zero.

            cmp     ah, 0           
            je      SetRSI1
            
; See if byte 2 contained a zero.

            test    eax, 0FF0000h   
            je      SetRSI2
            
; See if byte 3 contained a zero.

            test    eax, 0FF000000h 
            je      SetRSI3
            
; Swap the HO and LO dwords:

            bswap   rax
             
; See if byte 4 contained a zero.

            test    eax, 0FF000000h 
            je      SetRSI4

; See if byte 5 contained a zero.

            test    eax, 0FF0000h   
            je      SetRSI5

; See if byte 6 contained a zero.

            cmp     ah, 0           
            je      SetRSI6

; See if byte 7 contained a zero.

            cmp     al, 0
            je      SetRSI7
            
            
            
            
; Well, it must have been an 80 byte we encountered.
; (Fortunately, they are rare in ASCII strings, so all this
; extra computation rarely occurs).  Jump back into the zero
; loop and continue processing.

            add     rsi, 8          
            jmp     ZeroLoop2       
            
; The following compute the length of the string by subtracting
; the current RSI value from the original value and then adding
; zero, one, two, or three, depending on where we branched out
; of the MightBeZero0 sequence above. Use a macro to replace
; a lot of duplicated code:

unroll4a    macro   ofs
            local   lbl
lbl         catstr  <SetRSI>, %ofs
lbl:
            sub     rsi, zstrp      ; Compute length
            lea     rax, [rsi+ofs]  ; +offset 
            pop     rdx
            pop     rcx
            pop     rbx
            pop     rsi
            ret
            endm
            
; "unroll4a 7" expands to
;
;SetRSI7:
;           sub     rsi, zstrp      ; Compute length
;           lea     rax, [rsi+7]    ; +7 
;           pop     rdx
;           pop     rcx
;           pop     rbx
;           pop     rsi
;           ret

            unroll4a 7
            unroll4a 6
            unroll4a 5
            unroll4a 4
            unroll4a 3
            unroll4a 2
            unroll4a 1

; SetRSI is a special case because it doesn't
; have a "0" suffix:
            
SetRSI:
            mov     rax, rsi
            sub     rax, zstrp      ; Compute length.
            pop     rdx             ; No extra addition as
            pop     rcx             ;  zero was in LO byte.
            pop     rbx
            pop     rsi             
            ret
                    
strlen4     endp
            end