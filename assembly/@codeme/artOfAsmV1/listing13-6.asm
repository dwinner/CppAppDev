; Listing 13-6
;
; Creating lookup tables with macros

        option  casemap:none

nl          =       10

            .const
ttlStr      byte    "Listing 13-6", 0
fmtStr1     byte    "testString converted to UC:", nl
            byte    "%s", nl, 0
            
fmtStr2     byte    "testString converted to LC:", nl
            byte    "%s", nl, 0
            

testString  byte    "This is a test string ", nl
            byte    "Containing UPPER CASE ", nl
            byte    "and lower case chars", nl, 0
           

emitChRange macro   start, last
            local   index, resultStr
index       =       start
            while   index lt last
            byte    index
index       =       index + 1
            endm
            endm

; Lookup table that will convert lowercase
; characters to uppercase. The byte at each
; index contains the value of that index,
; except for the bytes at indexes 'a'..'z'.
; Those bytes contain the values 'A'..'Z'.
; Therefore, if a program uses an ASCII
; character's numeric value as an index
; into this table and retrieves that byte,
; it will convert the character to upper
; case.

lcToUC      equ             this byte
            emitChRange     0, 'a'
            emitChRange     'A', %'Z'+1
            emitChRange     %'z'+1, 0ffh

; As above, but this table converts upper
; case to lower case characters.
            
UCTolc      equ             this byte
            emitChRange     0, 'A'
            emitChRange     'a', %'z'+1
            emitChRange     %'Z'+1, 0ffh

            
            .data

; Store the destination strings here:

toUC        byte    256 dup (0)
TOlc        byte    256 dup (0)     

            
            .code
            externdef printf:proc
            
; Return program title to C++ program:

            public  getTitle
getTitle    proc
            lea     rax, ttlStr
            ret
getTitle    endp

                    
            
; Here is the "asmMain" function.

        
            public  asmMain
asmMain     proc
            push    rbx
            push    rdi
            push    rsi
            push    rbp
            mov     rbp, rsp
            sub     rsp, 56         ;Shadow storage
            
; Convert the characters in testString to Uppercase

            lea     rbx, lcToUC
            lea     rsi, testString
            lea     rdi, toUC
            jmp     getUC
            
toUCLp:     xlat
            mov     [rdi], al
            inc     rsi
            inc     rdi
getUC:      mov     al, [rsi]
            cmp     al, 0
            jne     toUCLp
            
; Display the converted string

            lea     rcx, fmtStr1
            lea     rdx, toUC
            call    printf
            
                    
; Convert the characters in testString to lowercase

            lea     rbx, UCTolc
            lea     rsi, testString
            lea     rdi, TOlc
            jmp     getLC
            
toLCLp:     xlat
            mov     [rdi], al
            inc     rsi
            inc     rdi
getLC:      mov     al, [rsi]
            cmp     al, 0
            jne     toLCLp
            
; Display the converted string

            lea     rcx, fmtStr2
            lea     rdx, TOlc
            call    printf
            
                    
            

             
allDone:    leave
            pop     rsi
            pop     rdi
            pop     rbx
            ret     ;Returns to caller
asmMain     endp
            end
