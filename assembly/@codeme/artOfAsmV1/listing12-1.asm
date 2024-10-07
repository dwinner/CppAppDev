
; Listing 12-1
;
; Demonstrate inserting bit strings into a register.
;
; Note that this program must be assembled and linked
; with the "LARGEADDRESSAWARE:NO" option.

        option  casemap:none

nl          =       10

            .const
ttlStr      byte    "Listing 12-1", 0

; The index into the following table specifies the length 
; of the bit string at each position. There are 65 entries
; in this table (for for each bit length from 0-64. 

            .const
MaskByLen   equ     this qword
    qword   0
    qword   1,           3,           7,           0fh
    qword   1fh,         3fh,         7fh,         0ffh
    qword   1ffh,        3ffh,        7ffh,        0fffh
    qword   1fffh,       3fffh,       7fffh,       0ffffh
    qword   1ffffh,      3ffffh,      7ffffh,      0fffffh
    qword   1fffffh,     3fffffh,     7fffffh,     0ffffffh 
    qword   1ffffffh,    3ffffffh,    7ffffffh,    0fffffffh 
    qword   1fffffffh,   3fffffffh,   7fffffffh,   0ffffffffh
    
    qword   1ffffffffh,         03ffffffffh
    qword   7ffffffffh,         0fffffffffh
    
    qword   1fffffffffh,        03fffffffffh
    qword   7fffffffffh,        0ffffffffffh
    
    qword   1ffffffffffh,       03ffffffffffh
    qword   7ffffffffffh,       0fffffffffffh
    
    qword   1fffffffffffh,      03fffffffffffh
    qword   7fffffffffffh,      0ffffffffffffh
    
    qword   1ffffffffffffh,     03ffffffffffffh
    qword   7ffffffffffffh,     0fffffffffffffh
    
    qword   1fffffffffffffh,    03fffffffffffffh
    qword   7fffffffffffffh,    0ffffffffffffffh
    
    qword   1ffffffffffffffh,   03ffffffffffffffh
    qword   7ffffffffffffffh,   0fffffffffffffffh
    
    qword   1fffffffffffffffh,  03fffffffffffffffh
    qword   7fffffffffffffffh,  0ffffffffffffffffh
    
           
Value2Merge qword   12h, 1eh, 5555h, 1200h, 120h
LenInBits   byte    5,     9,    16,    16,   12
StartPosn   byte    7,     4,     4,    12,   18

MergeInto   qword   0ffffffffh, 0, 12345678h
            qword   11111111h, 0f0f0f0fh
            

            include getTitle.inc
            include print.inc

            
            .code


; MergeBits( Val2Merge, MergeWith, Start, Length )
; Length (LenInBits[i]) value is passed in dl
; Start (StartPosn[i]) is passed in cl
; Val2Merge (Value2Merge[i]) and MergeWith (MergeInto[i])
; are passed in rbx and rax
;
; mergeBits result is returned in rax

mergeBits   proc
            push    rbx
            push    rcx
            push    rdx
            push    r8
            movzx   edx, dl         ;Zero-extends to rdx!
            mov     rdx, MaskByLen[ rdx*8 ]
            shl     rdx, cl
            not     rdx
            shl     rbx, cl
            and     rax, rdx
            or      rax, rbx
            pop     r8
            pop     rdx
            pop     rcx
            pop     rbx
            ret
mergeBits   endp 


            
; Here is the "asmMain" function.

        
            public  asmMain
asmMain     proc
            push    rbx
            push    rsi
            push    rdi
            push    rbp
            mov     rbp, rsp
            sub     rsp, 56         ;Shadow storage

; The following loop calls mergeBits as
; follows:
;
;  mergeBits( Value2Merg[i], MergeInto[i], 
;                   StartPosn[i], LenInBits[i] );
;
; Where "i" runs from 4 down to 0.
;
; Index of the last element in the arrays:

            mov     r10, (sizeof LenInBits) - 1
testLoop:   

; Fetch the Value2Merge element, and write
; its value to the display while it is handy.

            mov     rdx, Value2Merge[r10*8]
            call    print
            byte    "merge( %x, ", 0
            mov     rbx, rdx
            
; Fetch the MergeInto element, and write
; its value to the display.

            mov     rdx, MergeInto[r10*8]
            call    print
            byte    "%x, ", 0
            mov     rax, rdx
            
; Fetch the StartPosn element, and write
; its value to the display.

            movzx   edx, StartPosn[r10*1] ;Zero extends to rdx
            call    print
            byte    "%d, ", 0
            mov     rcx, rdx
            
; Fetch the LenInBits element, and write
; its value to the display.

            movzx   edx, LenInBits[r10*1] ;Zero extends to rdx
            call    print
            byte    "%d ) = ", 0

; Call MergeBits( Value2Merge, MergeInto,
;                   StartPosn, LenInBits )
            
            call    mergeBits
            
; Display the function result (returned
; in rax, for this program the results
; are always 32 bits, so it only prints
; the LO 32 bits of rax):

            mov     edx, eax
            call    print
            byte    "%x", nl, 0

; Repeat for each element of the array.

            dec     r10
            jns     testLoop
             
allDone:    leave
            pop     rdi
            pop     rsi
            pop     rbx
            ret     ;Returns to caller
asmMain     endp
            end
