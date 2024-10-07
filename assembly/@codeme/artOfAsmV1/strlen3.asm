            
;***************************************************************
;            
; strlen3.asm
;
;  An optimized 32-bit assembly strlen function.
; (Based on AMD's old 32-bit optimization guide.)
;
; RSI-      Points at string
;
; Returns:
;
; RAX-      String Length

            include zstrings.inc

            .code
strlen3     proc
zstrp       textequ <[rsp]>
            
            push    rsi
            
            ; We need to get RSI dword-aligned before proceeding:

            test    rsi, 3
            jz      RSIisAligned
            
            alignRSI 3              ;Was byte 3
            alignRSI 3              ;Was byte 2
            
            cmp     byte ptr [rsi], 0
            je      SetRSI
            inc     rsi             ; After this, RSI is aligned.
            
            
RSIisAligned:
            sub     rsi, 32         ;Counteracts add below.
ZeroLoop:   add     rsi, 32         ;Skip chars already processed.
ZeroLoop2:
            mov     eax, [rsi]      ;Next 4 chars -> EAX.
            
; Clear HO bits. Note that this maps 80h and 00h to 0FFh.

            and     eax, 7f7f7f7fh
            
; Subtracting 1 from all 4 bytes produces 0FFh if the value
; was originally 0 or 80h. For all other values we get a
; positive result.

            sub     eax, 01010101h

; Test the sign bits of the four bytes. Remember, only
; original values 00h and 80h will have their HO bits
; set. If ANDing with 80808080h produces a non-zero
; value, then we have 00h or 80h in the original byte.

            and     eax, 80808080h
            jnz     MightBe0
            
; The following are all in-line expansions
; of the above (we'll process 32 bytes on
; each iteration of this loop).
;
; Use a macro to reduce the amount of
; cut & paste code here. 

unroll3     macro   ofs
            local   dest
dest        catstr  <MightBeZero>, %ofs
            mov     eax, [rsi+ofs]    
            and     eax, 7f7f7f7fh  
            sub     eax, 01010101h  
            and     eax, 80808080h
            jnz     dest
            endm

; "unroll3 4" expands to:   
;            mov     eax, [rsi+4]  
;            and     eax, 7f7f7f7fh
;            sub     eax, 01010101h
;            and     eax, 80808080h
;            jnz     MightBeZero4

            unroll3 4   ;Goto MightBeZero4  if 0/80h present
            unroll3 8   ;Goto MightBeZero8  if 0/80h present
            unroll3 12  ;Goto MightBeZero12 if 0/80h present
            unroll3 16  ;Goto MightBeZero16 if 0/80h present
            unroll3 20  ;Goto MightBeZero20 if 0/80h present
            unroll3 24  ;Goto MightBeZero24 if 0/80h present
            
; Special case for 28:

            mov     eax, [rsi+28]  
            and     eax, 7f7f7f7fh
            sub     eax, 01010101h
            and     eax, 80808080h
            jz      ZeroLoop
            
            
; The following code handles the case where we found an 80
; or a 00 byte.  We need to determine whether it was a zero
; byte and the exact position of the zero byte.  If it was a
; 80 byte, then we've got to continue processing characters
; in the string.
 
addRSI      macro   addAmt
            add     rsi, addAmt
            jmp     MightBe0
            endm
            
; The "unroll3" macro transfers control to one of the
; following labels if it determines there is a 00h
; or 80h byte in one of the 4 bytes it has processed.
; The following macro expansions add their parameter
; argument to RSI and then transfer control to
; MightBe0. These expansions simply reduce the
; number of lines of text appearing in the book. 

               addRSI 28
MightBeZero4:  addRSI 4
MightBeZero8:  addRSI 8
MightBeZero12: addRSI 12
MightBeZero16: addRSI 16
MightBeZero20: addRSI 20

; If we get to this point, we've found a zero byte in
; positions 24..27:

MightBeZero24:      
            add     rsi, 24

; If we get to this point, we've found a zero byte 
; or an 80h byte in positions 0..3 or we've branched 
; here from one of the above conditions. We have to
; manually test for 0 to ensure that the original
; value wasn't 80h.

MightBe0:
            mov     eax, [rsi]      ; Get the original 4 bytes.

; See if the first byte contained zero.

            cmp     al, 0           
            je      SetRSI

; See if byte 1 contained zero.

            cmp     ah, 0           
            je      SetRSI1
            
; See if byte 2 contained a zero.

            test    eax, 0FF0000h   
            je      SetRSI2

; See if the H.O. byte contained zero.

            test    eax, 0FF000000h 
            je      SetRSI3;
            
; Well, it must have been an 80 byte we encountered.
; (Fortunately, they are rare in ASCII strings, so all this
; extra computation rarely occurs).  Jump back into the zero
; loop and continue processing.

            add     rsi, 4          
            jmp     ZeroLoop2       
            
; The following compute the length of the string by subtracting
; the current RSI value from the original value and then adding
; zero, one, two, or three, depending on where we branched out
; of the MightBeZero0 sequence above.

SetRSI3:
            sub     rsi, zstrp      ; Compute length
            lea     rax, [rsi+3]    ; +3
            pop     rsi
            ret
            
SetRSI2:
            sub     rsi, zstrp      ; Compute length
            lea     rax, [rsi+2]    ; +2 
            pop     rsi
            ret
            
SetRSI1:
            sub     rsi, zstrp      ; Compute length
            lea     rax, [rsi+1]    ; +1 
            pop     rsi
            ret
            
SetRSI:
            mov     rax, rsi
            sub     rax, zstrp      ; Compute length.  
            pop     rsi             ; No extra addition as
            ret                     ; zero was in L.O. byte.
                    
strlen3     endp
            end