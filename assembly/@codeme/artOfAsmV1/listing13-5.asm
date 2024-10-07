; Listing 13-5
;
; CTL while loop demonstration program

        option  casemap:none

nl          =       10

            .const
ttlStr      byte    "Listing 13-5", 0
           


; upperCase macro function.
;
; Converts text argument to a string, converting
; all lower-case characters to uppercase.

upperCase   macro   theString
            local   resultString, thisChar, sep
resultStr   equ     <> ;Initialize function result with ""
sep         textequ <> ;Initialize separator char with ""

            forc    curChar, theString
            
; Check to see if the character is lower case.
; Convert it to upper case if it is, otherwise
; output it to resultStr as-is. Concatenate the
; current character to the end of the result string
; (with a ", " separator, if this isn’t the first
; character appended to resultStr).

            if      ('&curChar' GE 'a') and ('&curChar' LE 'z')
resultStr   catstr  resultStr, sep, %'&curChar'-32
            else
resultStr   catstr  resultStr, sep, %'&curChar'
            endif
            
; First time through, sep is the empty string, for all
; other iterations, sep is the comma separator between
; values.

sep         textequ <, >    
            endm    ;End for
            
            exitm   <resultStr>
            endm    ;End macro
            


; Demonstratoin of the upperCase macro function
            
            .data
chars       byte    "Demonstration of upperCase "
            byte    "macro function:"
            byte    upperCase( <abcdEFG123> ), nl, 0



            
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
            push    rbp
            mov     rbp, rsp
            sub     rsp, 56         ;Shadow storage

            lea     rcx, chars
            call    printf
             
allDone:    leave
            pop     rbx
            ret     ;Returns to caller
asmMain     endp
            end
