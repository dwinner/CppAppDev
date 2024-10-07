; Listing 9-18
;
; 128-bit unsigned decimal string to numeric conversion

        option  casemap:none

false       =       0
true        =       1
tab         =       9
nl          =       10

            .const
ttlStr      byte    "Listing 9-18", 0
fmtStr1     byte    "strtou128: String='%s' value=%I64x%I64x", nl, 0
           
oStr      byte    "340282366920938463463374607431768211455", 0

            
            .code
            externdef printf:proc
            
; Return program title to C++ program:

            public  getTitle
getTitle    proc
            lea     rax, ttlStr
            ret
getTitle    endp




; strtou128-
;  Converts string data to a 128-bit unsigned integer.
;
; Input-
;   RDI-    Pointer to buffer containing string to convert
;
; Output-
;   RDX:RAX-Contains converted string (if success), error code
;           if an error occurs.
;
;   RDI-    Points at first char beyond end of numeric string.
;           If error, RDI's value is restored to original value.
;           Caller can check character at [RDI] after a
;           successful result to see if the character following
;           the numeric digits is a legal numeric delimiter.
;
;   C       (carry flag) Set if error occurs, clear if
;           conversion was successful. On error, RAX will
;           contain 0 (illegal initial character) or
;           0ffffffffffffffffh (overflow).

strtou128   proc
accumulator equ     <[rbp-16]>
partial     equ     <[rbp-24]>
            push    rcx      ;Holds input char
            push    rdi      ;In case we have to restore RDI
            push    rbp
            mov     rbp, rsp
            sub     rsp, 24  ;Accumulate result here
            
            xor     edx, edx ;Zero extends!
            mov     accumulator, rdx
            mov     accumulator[8], rdx
                        
; The following loop skips over any whitespace (spaces and
; tabs) that appear at the beginning of the string.

            dec     rdi      ;Because of inc below.
skipWS:     inc     rdi
            mov     cl, [rdi]
            cmp     cl, ' '
            je      skipWS
            cmp     al, tab
            je      skipWS
            
; If we don't have a numeric digit at this point,
; return an error.

            cmp     cl, '0'  ;Note: '0' < '1' < ... < '9'
            jb      badNumber
            cmp     cl, '9'
            ja      badNumber
            
; Okay, the first digit is good. Convert the string
; of digits to numeric form:

convert:    and     ecx, 0fh ;Convert to numeric in RCX

; Multiple 128-bit accumulator by 10

            mov     rax, accumulator 
            mul     ten
            mov     accumulator, rax
            mov     partial, rdx    ;Save partial product
            mov     rax, accumulator[8]
            mul     ten
            jc      overflow1
            add     rax, partial
            mov     accumulator[8], rax
            jc      overflow1

; Add in the current character to the 128-bit accumulator
            
            mov     rax, accumulator
            add     rax, rcx
            mov     accumulator, rax
            mov     rax, accumulator[8]
            adc     rax, 0
            mov     accumulator[8], rax
            jc      overflow2
            
;Move on to next character

            inc     rdi      
            mov     cl, [rdi]
            cmp     cl, '0'
            jb      endOfNum
            cmp     cl, '9'
            jbe     convert

; If we get to this point, we've successfully converted
; the string to numeric form:

endOfNum:
            
; Because the conversion was successful, this procedure
; leaves RDI pointing at the first character beyond the
; converted digits. As such, we don't restore RDI from
; the stack. Just bump the stack pointer up by 8 bytes
; to throw away RDI's saved value; must also remove

            mov     rax, accumulator
            mov     rdx, accumulator[8]
            leave
            add     rsp, 8   ;Remove original RDI value
            pop     rcx      ;Restore RCX
            clc              ;Return success in carry flag
            ret
            
; badNumber- Drop down here if the first character in
;            the string was not a valid digit.

badNumber:  xor     rax, rax
            xor     rdx, rdx
            jmp     errorExit     

overflow1:  mov     rax, -1
	cqo
            jmp     errorExit
                                
overflow2:  mov     rax, -2  ;0FFFFFFFFFFFFFFFEh
            cqo		 ;Just to be consistent.
errorExit:  leave            ;Remove accumulator from stack
            pop     rdi
            pop     rcx
            stc              ;Return error in carry flag
            ret
                    
ten         qword   10

strtou128   endp

            
                    
            
; Here is the "asmMain" function.

        
            public  asmMain
asmMain     proc
            push    rbp
            mov     rbp, rsp
            sub     rsp, 64         ;Shadow storage
            

; Test hexadecimal conversion:
            
            lea     rdi, oStr
            call    strtou128
	jc	badConversion
            
            lea     rcx, fmtStr1
            mov     r8, rdx
            mov     r9, rax
            lea     rdx, oStr
            call    printf
	jmp	allDone
	
convErr	byte	"Conversion error: %zd", nl, 0

badConversion:
	lea	rcx, convErr
	mov	rdx, rax
	call	printf            
 

             
allDone:    leave
            ret     ;Returns to caller
asmMain     endp
            end