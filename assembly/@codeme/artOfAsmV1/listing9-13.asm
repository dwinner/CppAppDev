; Listing 9-13
;
; Exponent output helper function
;
; Cut and pasted from Listing 9-10

;***********************************************************
;                                                           
; eToStr-                                                   
;                                                           
; Converts a REAL10 floating-point number to the       
; corresponding string of digits.  Note that this           
; function always emits the string using scientific                  
; notation, use the r10ToStr routine for decimal notation.   
;                                                           
; On Entry:                                                 
;                                                           
;    e10-           Real10 value to convert.
;                   Passed in ST(0)                     
;                                                           
;    width-         Field width for the number (note that this   
;                   is an *exact* field width, not a minimum     
;                   field width).
;                   Passed in RAX (LO 32 bits).                                
;                                                           
;    fill-          Padding character if the number is smaller   
;                   than the specified field width.
;                   Passed in RCX.                  
;                                                                            
;    buffer-        e10ToStr stores the resulting characters in  
;                   this buffer (passed in RDI).
;                                                           
;    expDigs-       Number of exponent digits (2 for real4,     
;                   3 for real8, and 4 for real10).
;                   Passed in RDX (LO 8 bits)             
;                                                                            
;
;    maxLength-     Maximum buffer size.
;                   Passed in R8.                                     
; On Exit: 
;
;    RDI-           Points at end of converted string.                                                 
;                                                           
;    Buffer contains the newly formatted string.  If the    
;    formatted value does not fit in the width specified,   
;    e10ToStr will store "#" characters into this string.
;
;    If there was an error, EAX contains -1, -2, or -3
;    denoting the error (value out of range, bad width,
;    or string overflow, respectively).   
;                                                           
;-----------------------------------------------------------
;                                                           
; Unlike the integer to string conversions, this routine    
; always right justifies the number in the specified        
; string.  Width must be a positive number, negative        
; values are illegal (actually, they are treated as         
; *really* big positive numbers which will always raise     
; a string overflow exception.                              
;                                                           
;***********************************************************

e10ToStr    proc

fWidth      equ     <[rbp-8]>       ;RAX
buffer      equ     <[rbp-16]>      ;RDI
expDigs     equ     <[rbp-24]>      ;RDX
rbxSave     equ     <[rbp-32]>
rcxSave     equ     <[rbp-40]>
rsiSave     equ     <[rbp-48]>
Exponent    equ     <dword ptr [rbp-52]>
MantSize    equ     <dword ptr [rbp-56]>
Sign        equ     <byte ptr [rbp-60]>
Digits      equ     <byte ptr [rbp-128]>

            push    rbp
            mov     rbp, rsp
            sub     rsp, 128
            
            mov     buffer, rdi
            mov     rsiSave, rsi
            mov     rcxSave, rcx
            mov     rbxSave, rbx
            mov     fWidth, rax
            mov     expDigs, rdx

            cmp     eax, r8d
            jae     strOvfl
            mov     byte ptr [rdi+rax*1], 0 ; 0-terminate str
            
            
            
; First, make sure the width isn't zero.
            
            test    eax, eax
            jz      voor

; Just to be on the safe side, don't allow widths greater 
; than 1024:

            cmp     eax, 1024
            ja      badWidth

; Okay, do the conversion.

            lea     rdi, Digits     ; Store result string here.
            call    FPDigits        ; Convert e80 to digit str.
            mov     Exponent, eax   ; Save away exponent result.
            mov     Sign, cl        ; Save mantissa sign char.

; Verify that there is sufficient room for the mantissa's sign,
; the decimal point, two mantissa digits, the "E", 
; and the exponent's sign.  Also add in the number of digits
; required by the exponent (2 for real4, 3 for real8, 4 for 
; real10).
;
; -1.2e+00    :real4
; -1.2e+000   :real8
; -1.2e+0000  :real10
            
            
            mov     ecx, 6          ; Char posns for above chars.
            add     ecx, expDigs    ; # of digits for the exp.
            cmp     ecx, fWidth
            jbe     goodWidth
            
; Output a sequence of "#...#" chars (to the specified width)
; if the width value is not large enough to hold the 
; conversion:

            mov     ecx, fWidth
            mov     al, '#'
            mov     rdi, buffer
fillPound:  mov     [rdi], al
            inc     rdi
            dec     ecx
            jnz     fillPound
            jmp     exit_eToBuf


; Okay, the width is sufficient to hold the number, do the
; conversion and output the string here:

goodWidth:
            
            mov     ebx, fWidth     ; Compute the # of mantissa
            sub     ebx, ecx        ; digits to display.
            add     ebx, 2          ; ECX allows for 2 mant digs.
            mov     MantSize,ebx
                    
            
; Round the number to the specified number of print positions.
; (Note: since there are a maximum of 18 significant digits,
;  don't bother with the rounding if the field width is greater
;  than 18 digits.)
            
            
            cmp     ebx, 18
            jae     noNeedToRound
                    
; To round the value to the number of significant digits,
; go to the digit just beyond the last one we are considering
; (ebx currently contains the number of decimal positions)
; and add 5 to that digit.  Propagate any overflow into the
; remaining digit positions.
            
            mov     al, Digits[rbx*1] ; Get least sig digit + 1.
            add     al, 5             ; Round (e.g., +0.5 ).
            cmp     al, '9'
            jbe     noNeedToRound
            mov     Digits[rbx*1], '9'+1
            jmp     whileDigitGT9Test
whileDigitGT9:                      

; Subtract out overflow and add the carry into the previous
; digit (unless we hit the first digit in the number).

            sub     Digits[ rbx*1 ], 10     
            dec     ebx                     
            cmp     ebx, 0                  
            jl      firstDigitInNumber      
                                                                    
            inc     Digits[rbx*1]
            jmp     whileDigitGT9Test

firstDigitInNumber:

; If we get to this point, then we've hit the first
; digit in the number.  So we've got to shift all
; the characters down one position in the string of
; bytes and put a "1" in the first character position.
            
            mov     ebx, 17
repeatUntilEBXeq0:
            
            mov     al, Digits[rbx*1]
            mov     Digits[rbx*1+1], al
            dec     ebx
            jnz     repeatUntilEBXeq0
                    
            mov     Digits, '1'
            inc     Exponent         ; Because we added a digit.
            jmp     noNeedToRound
            
                    
whileDigitGT9Test:
            cmp     Digits[rbx], '9' ; Overflow if char > '9'.
            ja      whileDigitGT9 
            
noNeedToRound:      
            
; Okay, emit the string at this point.  This is pretty easy
; since all we really need to do is copy data from the
; digits array and add an exponent (plus a few other simple chars).
            
            xor     ecx, ecx    ; Count output mantissa digits.
            mov     rdi, buffer
            xor     edx, edx    ; Count output chars.
            mov     al, Sign
            cmp     al, '-'
            je      noMinus
            
            mov     al, ' '
                    
noMinus:    mov     [rdi], al
            
; Output the first character and a following decimal point
; if there are more than two mantissa digits to output.
            
            mov     al, Digits
            mov     [rdi+1], al
            add     rdi, 2
            add     edx, 2
            inc     ecx
            cmp     ecx, MantSize
            je      noDecPt
            
            mov     al, '.'
            mov     [rdi], al
            inc     rdi
            inc     edx     
                                    
noDecPt:
            
; Output any remaining mantissa digits here.
; Note that if the caller requests the output of
; more than 18 digits, this routine will output zeros
; for the additional digits.
            
            jmp     whileECXltMantSizeTest
            
whileECXltMantSize:
            
            mov     al, '0'
            cmp     ecx, 18
            jae     justPut0

            mov     al, Digits[ rcx*1 ]
                    
justPut0:
            mov     [rdi], al
            inc     rdi
            inc     ecx
            inc     edx
            
whileECXltMantSizeTest:
            cmp     ecx, MantSize
            jb      whileECXltMantSize

; Output the exponent:
            
            mov     byte ptr [rdi], 'e'
            inc     rdi
            inc     edx
            mov     al, '+'
            cmp     Exponent, 0
            jge     noNegExp
            
            mov     al, '-'
            neg     Exponent
                                            
noNegExp:
            mov     [rdi], al
            inc     rdi
            inc     edx
            
            mov     eax, Exponent
            mov     ecx, expDigs
            call    expToBuf
            jc      error
                    
exit_eToBuf:
            mov     rsi, rsiSave
            mov     rcx, rcxSave
            mov     rbx, rbxSave
            mov     rax, fWidth
            mov     rdx, expDigs
            leave
            clc
            ret

strOvfl:    mov     rax, -3
            jmp     error

badWidth:   mov     rax, -2
            jmp     error
            
voor:       mov     rax, -1
error:      mov     rsi, rsiSave
            mov     rcx, rcxSave
            mov     rbx, rbxSave
            mov     rdx, expDigs
            leave
            stc
            ret

e10ToStr   endp
