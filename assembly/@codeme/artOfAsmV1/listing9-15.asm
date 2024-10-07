; Listing 9-15
;
; Hexadecimal string to numeric conversion

        option  casemap:none

false       =       0
true        =       1
tab         =       9
nl          =       10

            .const
ttlStr      byte    "Listing 9-15", 0
fmtStr1     byte    "strtoh: String='%s' "
            byte    "value=%I64x", nl, 0
           
fmtStr2     byte    "Error, RAX=%I64x, str='%s'", nl, 0 
fmtStr3     byte    "Error, expected overflow: RAX=%I64x, "
            byte    "str='%s'", nl, 0
             
fmtStr4     byte    "Error, expected bad char: RAX=%I64x, "
            byte    "str='%s'", nl, 0 

hexStr      byte    "1234567890abcdef", 0
hexStrOVFL  byte    "1234567890abcdef0", 0
hexStrBAD   byte    "x123", 0

            
            .code
            externdef printf:proc
            
; Return program title to C++ program:

            public  getTitle
getTitle    proc
            lea     rax, ttlStr
            ret
getTitle    endp




; strtoh-
;  Converts string data to a 64-bit unsigned integer.
;
; Input-
;   RDI-    Pointer to buffer containing string to convert
;
; Output-
;   RAX-    Contains converted string (if success), error code
;           if an error occurs.
;
;   RDI-    Points at first char beyond end of hexadecimal string.
;           If error, RDI's value is restored to original value.
;           Caller can check character at [RDI] after a
;           successful result to see if the character following
;           the numeric digits is a legal numeric delimiter.
;
;   C       (carry flag) Set if error occurs, clear if
;           conversion was successful. On error, RAX will
;           contain 0 (illegal initial character) or
;           0ffffffffffffffffh (overflow).

strtoh      proc
            push    rcx      ;Holds input char
            push    rdx      ;Special mask value
            push    rdi      ;In case we have to restore RDI

; This code will use the value in RDX to test and see if overflow
; will occur in RAX when shifting to the left 4 bits:
            
            mov     rdx, 0F000000000000000h
            xor     eax, eax ;Zero out accumulator.
                        
; The following loop skips over any whitespace (spaces and
; tabs) that appear at the beginning of the string.

            dec     rdi      ;Because of inc below.
skipWS:     inc     rdi
            mov     cl, [rdi]
            cmp     cl, ' '
            je      skipWS
            cmp     al, tab
            je      skipWS
            
; If we don't have a hexadecimal digit at this point,
; return an error.

            cmp     cl, '0'  ;Note: '0' < '1' < ... < '9'
            jb      badNumber
            cmp     cl, '9'
            jbe     convert
            and     cl, 5fh  ;Cheesy LC->UC conversion
            cmp     cl, 'A'
            jb      badNumber
            cmp     cl, 'F'
            ja      badNumber
            sub     cl, 7    ;Maps 41h..46h->3ah..3fh
            
; Okay, the first digit is good. Convert the string
; of digits to numeric form:

convert:    test    rdx, rax ;See if adding in the current
            jnz     overflow ; digit will cause an overflow
            
            and     ecx, 0fh ;Convert to numeric in RCX


; Multiple 64-bit accumulator by 16 and add in new digit:

            shl     rax, 4
            add     al, cl  ;Never overflows outside LO 4 bits
                        
;Move on to next character

            inc     rdi      
            mov     cl, [rdi]
            cmp     cl, '0'
            jb      endOfNum
            cmp     cl, '9'
            jbe     convert
            
            and     cl, 5fh  ;Cheesy LC->UC conversion
            cmp     cl, 'A'
            jb      endOfNum
            cmp     cl, 'F'
            ja      endOfNum
            sub     cl, 7    ;Maps 41h..46h->3ah..3fh
            jmp     convert
            

; If we get to this point, we've successfully converted
; the string to numeric form:

endOfNum:
            
; Because the conversion was successful, this procedure
; leaves RDI pointing at the first character beyond the
; converted digits. As such, we don't restore RDI from
; the stack. Just bump the stack pointer up by 8 bytes
; to throw away RDI's saved value; must also remove

            add     rsp, 8   ;Remove original RDI value
            pop     rdx      ;Restore RDX
            pop     rcx      ;Restore RCX
            clc              ;Return success in carry flag
            ret
            
; badNumber- Drop down here if the first character in
;            the string was not a valid digit.

badNumber:  xor     rax, rax
            jmp     errorExit     

overflow:   or      rax, -1  ;Return -1 as error on overflow
errorExit:  pop     rdi      ;Restore RDI if an error occurs
            pop     rdx
            pop     rcx
            stc              ;Return error in carry flag
            ret
                    
strtoh      endp


            
                    
            
; Here is the "asmMain" function.

        
            public  asmMain
asmMain     proc
            push    rbp
            mov     rbp, rsp
            sub     rsp, 64         ;Shadow storage
            

; Test hexadecimal conversion:
            
            lea     rdi, hexStr
            call    strtoh
            jc      error
            
            lea     rcx, fmtStr1
            mov     r8, rax
            lea     rdx, hexStr
            call    printf
            
; Test overflow conversion:
            
            lea     rdi, hexStrOVFL
            call    strtoh
            jnc     unexpected
            
            lea     rcx, fmtStr2
            mov     rdx, rax
            mov     r8, rdi
            call    printf
            
; Test bad character:
            
            lea     rdi, hexStrBAD
            call    strtoh
            jnc     unexp2
            
            lea     rcx, fmtStr2
            mov     rdx, rax
            mov     r8, rdi
            call    printf
            jmp     allDone
            
unexpected: lea     rcx, fmtStr3
            mov     rdx, rax
            mov     r8, rdi
            call    printf
            jmp     allDone
            
unexp2:     lea     rcx, fmtStr4
            mov     rdx, rax
            mov     r8, rdi
            call    printf
            jmp     allDone
            
error:      lea     rcx, fmtStr2
            mov     rdx, rax
            mov     r8, rdi
            call    printf
            
 

             
allDone:    leave
            ret     ;Returns to caller
asmMain     endp
            end