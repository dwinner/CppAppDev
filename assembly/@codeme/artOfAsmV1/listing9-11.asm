; Listing 9-11
;
; 
; This was cut and pasted from Listing 9-10


;***********************************************************
;                                                           
; r10ToStr-                                                 
;                                                           
; Converts a REAL10 floating-point number to the       
; corresponding string of digits.  Note that this           
; function always emits the string using decimal            
; notation.  For scientific notation, use the e10ToBuf      
; routine.                                                  
;                                                           
; On Entry:                                                 
;                                                           
; r10-              Real10 value to convert.
;                   Passed in ST(0).                       
;                                                           
; fWidth-           Field width for the number (note that this   
;                   is an *exact* field width, not a minimum         
;                   field width).
;                   Passed in EAX (RAX).                                    
;                                                           
; decimalpts-       # of digits to display after the decimal pt.
;                   Passed in EDX (RDX). 
;                                                           
; fill-             Padding character if the number is smaller   
;                   than the specified field width.
;                   Passed in CL (RCX).                  
;                                                                            
; buffer-           r10ToStr stores the resulting characters in  
;                   this string.
;                   Address passed in RDI.
;
; maxLength-        Maximum string length.
;                   Passed in R8d (R8).                                     
;                                                                            
; On Exit:                                                  
;                                                           
; Buffer contains the newly formatted string.  If the       
; formatted value does not fit in the width specified,      
; r10ToStr will store "#" characters into this string.      
;                                                           
; Carry-    Clear if success, set if an exception occurs.                                                         
;           If width is larger than the maximum length of          
;           the string specified by buffer, this routine        
;           will return with the carry set and RAX=-1,
;           -2, or -3.                                             
;                                                           
;***********************************************************


r10ToStr    proc


; Local variables:

fWidth      equ     <dword ptr [rbp-8]>     ;RAX: uns32
decDigits   equ     <dword ptr [rbp-16]>    ;RDX: uns32
fill        equ     <[rbp-24]>              ;CL: char
bufPtr      equ     <[rbp-32]>              ;RDI: pointer
exponent    equ     <dword ptr [rbp-40]>    ;uns32
sign        equ     <byte ptr [rbp-48]>     ;char
digits      equ     <byte ptr [rbp-128]>    ;char[80]
maxWidth	=	64			;Must be smaller than 80-2

            push    rdi
            push    rbx
            push    rcx
            push    rdx
            push    rsi
            push    rax
            push    rbp
            mov     rbp, rsp
            sub     rsp, 128        ;128 bytes of local vars

; First, make sure the number will fit into the 
; specified string.
            
            cmp     eax, r8d	;r8d=max length 
            jae     strOverflow
            
;  If the width is zero, raise an exception:

            test    eax, eax
            jz      voor		;Value out of range

            mov     bufPtr, rdi
            mov     qword ptr decDigits, rdx
            mov     fill, rcx
            mov     qword ptr fWidth, rax
            

; If the width is too big, raise an exception:

            cmp     eax, maxWidth
            ja      badWidth        

; Okay, do the conversion. 
; Begin by processing the mantissa digits:
                    
            lea     rdi, digits     ; Store result here.
            call    FPDigits        ; Convert r80 to string.
            mov     exponent, eax   ; Save away exp result.
            mov     sign, cl        ; Save mantissa sign char.

; Round the string of digits to the number of significant 
; digits we want to display for this number:

            cmp     eax, 17
            jl      dontForceWidthZero

            xor     rax, rax        ; If the exp is negative, or
                                    ; too large, set width to 0.
dontForceWidthZero:
            mov     rbx, rax        ; Really just 8 bits.
            add     ebx, decDigits  ; Compute rounding position.
            cmp     ebx, 17
            jge     dontRound       ; Don't bother if a big #.


; To round the value to the number of significant digits,
; go to the digit just beyond the last one we are considering
; (eax currently contains the number of decimal positions)
; and add 5 to that digit.  Propagate any overflow into the
; remaining digit positions.
                    
                    
            inc     ebx           ; Index+1 of last sig digit.
            mov     al, digits[rbx*1] ; Get that digit.
            add     al, 5             ; Round (e.g., +0.5 ).
            cmp     al, '9'
            jbe     dontRound

            mov     digits[ rbx*1 ], '0'+10 ; Force to zero
whileDigitGT9:                              ; (see sub 10 below).
            sub     digits[ rbx*1 ], 10     ; Sub out overflow, 
            dec     ebx                     ; carry, into prev
            js      hitFirstDigit;          ; digit (until 1st
                                            ;  digit in the #).
            inc     digits[rbx*1]
            cmp     digits[rbx], '9'        ; Overflow if > '9'.
            ja      whileDigitGT9
            jmp     dontRound
            
                                    
hitFirstDigit:
                                            
; If we get to this point, then we've hit the first
; digit in the number.  So we've got to shift all
; the characters down one position in the string of
; bytes and put a "1" in the first character position.
            
            mov     ebx, 17
repeatUntilEBXeq0:
            
            mov     al, digits[rbx*1]
            mov     digits[rbx*1+1], al
            dec     ebx     
            jnz     repeatUntilEBXeq0
                    
            mov     digits, '1'
            inc     exponent    ; Because we added a digit.
                    
dontRound: 
                    
            
; Handle positive and negative exponents separately.

            mov     rdi, bufPtr ; Store the output here.
            cmp     exponent, 0
            jge     positiveExponent

; Negative exponents:
; Handle values between 0 & 1.0 here (negative exponents
; imply negative powers of ten).
;
; Compute the number's width.  Since this value is between
; 0 & 1, the width calculation is easy: it's just the
; number of decimal positions they've specified plus three
; (since we need to allow room for a leading "-0.").
                    
            
            mov     ecx, decDigits
            add     ecx, 3
            cmp     ecx, 4
            jae     minimumWidthIs4

            mov     ecx, 4  ; Minimum possible width is four.

minimumWidthIs4:
            cmp     ecx, fWidth
            ja      widthTooBig 
            
; This number will fit in the specified field width,
; so output any necessary leading pad characters.
            
            mov     al, fill
            mov     edx, fWidth
            sub     edx, ecx
            jmp     testWhileECXltWidth
            
            
whileECXltWidth:
            mov     [rdi], al
            inc     rdi
            inc     ecx
testWhileECXltWidth:
            cmp     ecx, fWidth
            jb      whileECXltWidth
                            
; Output " 0." or "-0.", depending on the sign of the number.
            
            mov     al, sign
            cmp     al, '-'
            je      isMinus
                    
            mov     al, ' '
            
isMinus:    mov     [rdi], al
            inc     rdi
            inc     edx
                    
            mov     word ptr [rdi], '.0'
            add     rdi, 2
            add     edx, 2
            
; Now output the digits after the decimal point:

            xor     ecx, ecx        ; Count the digits in ecx.
            lea     rbx, digits     ; Pointer to data to output.
                                    
; If the exponent is currently negative, or if
; we've output more than 18 significant digits,
; just output a zero character.
            
repeatUntilEDXgeWidth: 
            mov     al, '0'
            inc     exponent
            js      noMoreOutput
            
            cmp     ecx, 18
            jge     noMoreOutput
            
            mov     al, [rbx]
            inc     ebx
                    
noMoreOutput:
            mov     [rdi], al
            inc     rdi
            inc     ecx
            inc     edx
            cmp     edx, fWidth
            jb      repeatUntilEDXgeWidth
            jmp     r10BufDone


; If the number's actual width was bigger than the width
; specified by the caller, emit a sequence of '#' characters
; to denote the error.
                            
widthTooBig:
            

; The number won't fit in the specified field width,
; so fill the string with the "#" character to indicate
; an error.
                    
                    
            mov     ecx, fWidth
            mov     al, '#'
fillPound:  mov     [rdi], al
            inc     rdi
            dec     ecx
            jnz     fillPound
            jmp     r10BufDone

            
; Handle numbers with a positive exponent here.

positiveExponent:
            
; Compute # of digits to the left of the ".".
; This is given by:
;
;                   Exponent     ; # of digits to left of "."
;           +       2            ; Allow for sign and there
;                                ; is always 1 digit left of "."
;           +       decimalpts   ; Add in digits right of "."
;           +       1            ; If there is a decimal point.
            

            mov     edx, exponent   ; Digits to left of "."
            add     edx, 2          ; 1 digit + sign posn.
            cmp     decDigits, 0
            je      decPtsIs0

            add     edx, decDigits  ; Digits to right of "."
            inc     edx             ; Make room for the "."
            
decPtsIs0:
            
; Make sure the result will fit in the
; specified field width.
            
            cmp     edx, fWidth
            ja      widthTooBig
            
                    
; If the actual number of print positions
; is less than the specified field width,
; output leading pad characters here.
            
            cmp     edx, fWidth
            jae     noFillChars
            
            mov     ecx, fWidth
            sub     ecx, edx
            jz      noFillChars
            mov     al, fill
fillChars:  mov     [rdi], al
            inc     rdi
            dec     ecx
            jnz     fillChars
                    
noFillChars:
            
            
; Output the sign character.
            
            mov     al, sign
            cmp     al, '-'
            je      outputMinus;
            
            mov     al, ' '
                    
outputMinus:
            mov     [rdi], al
            inc     rdi
                    
; Okay, output the digits for the number here.
            
            
            xor     ecx, ecx        ; Counts  # of output chars.
            lea     rbx, digits     ; Ptr to digits to output.
            
            
; Calculate the number of digits to output
; before and after the decimal point.
            
            
            mov     edx, decDigits  ; Chars after "."
            add     edx, exponent   ; # chars before "."
            inc     edx             ; Always one digit before "."
            
                    
; If we've output fewer than 18 digits, go ahead
; and output the next digit.  Beyond 18 digits,
; output zeros.
            
repeatUntilEDXeq0:
            mov     al, '0'
            cmp     ecx, 18
            jnb     putChar
            
            mov     al, [rbx]
            inc     rbx

putChar:    mov     [rdi], al
            inc     rdi     
            
; If the exponent decrements down to zero,
; then output a decimal point.
            
            cmp     exponent, 0
            jne     noDecimalPt
            cmp     decDigits, 0
            je      noDecimalPt
            
            mov     al, '.'
            mov     [rdi], al
            inc     rdi
                    
noDecimalPt:
            dec     exponent      ; Count down to "." output.
            inc     ecx           ; # of digits thus far.
            dec     edx           ; Total # of digits to output.
            jnz     repeatUntilEDXeq0
                    

; Zero-terminate string and leave:
            
r10BufDone: mov     byte ptr [rdi], 0
            leave
            clc     ;No error
            jmp     popRet

badWidth:   mov     rax, -2 ;Illegal width
            jmp     ErrorExit
            
strOverflow:
            mov     rax, -3 ;String overflow
            jmp     ErrorExit

voor:       or      rax, -1 ;Range error
ErrorExit:  leave
            stc     ;Error
            mov     [rsp], rax      ;Change RAX on return
            
popRet:     pop     rax
            pop     rsi
            pop     rdx
            pop     rcx
            pop     rbx
            pop     rdi
            ret

r10ToStr    endp



