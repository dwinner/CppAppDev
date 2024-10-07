; Listing 18-15
;
; stringTrim, deleteWS, and deleteLeadingWS Functions

            option     casemap:none
            include    string.inc
            include    aoalib.inc

            includelib aoalib.lib

            .const
ttlStr      byte    "Listing 18-15", 0


            .data
startTime   qword   ?
endTime     qword   ?
frequency   qword   ?


            

; Generate a whole bunch of strings for
; testing purposes:            

            strDcl str1a, 32, "     abcdefg     "
            strDcl str1b, 32, "abcdefg     "
            strDcl str1c, 32, "     abcdefg"
            strDcl str1d, 32, "          "
            strDcl str1e, 32, "abcdefg"
            strBgn str1f, 32        ;Empty string
            strEnd str1f

            strDcl str2a, 32, "     abcdefg     "
            strDcl str2b, 32, "abcdefg     "
            strDcl str2c, 32, "     abcdefg"
            strDcl str2d, 32, "          "
            strDcl str2e, 32, "abcdefg"
            strBgn str2f, 32        ;Empty string
            strEnd str2f

            strDcl str3a, 32, "     abcdefg     "
            strDcl str3b, 32, "abcdefg     "
            strDcl str3c, 32, "     abcdefg"
            strDcl str3d, 32, "          "
            strDcl str3e, 32, "abcdefg"
            strBgn str3f, 32        ;Empty string
            strEnd str3f

            
            .code
            
wsFunc      macro   func, string
            lea     rdx, string
            call    print
            byte    "Original string: '%s'  --  ", 0
            lea     rdi, string
            call    func
            lea     rdi, string
            call    print
            byte    "Result: '%s'", nl, 0
            endm

;**************************************************
;
; Here is the "asmMain" function.

        
            public  asmMain
asmMain     proc
            push    rbx
            push    rsi
            push    rdi
            push    r14
            push    r15
            push    rbp
            mov     rbp, rsp
            sub     rsp, 56         ;Shadow storage

            call    print
            byte    "Testing stringTrim:", nl, nl, 0
            wsFunc  stringTrim, str1a
            wsFunc  stringTrim, str1b
            wsFunc  stringTrim, str1c
            wsFunc  stringTrim, str1d
            wsFunc  stringTrim, str1e
            wsFunc  stringTrim, str1f
            
            call    print
            byte    nl, "Testing deleteWS:", nl, nl, 0
            wsFunc  deleteWS, str2a
            wsFunc  deleteWS, str2b
            wsFunc  deleteWS, str2c
            wsFunc  deleteWS, str2d
            wsFunc  deleteWS, str2e
            wsFunc  deleteWS, str2f
            
            call    print
            byte    nl, "Testing deleteTrailingWS:", nl, nl, 0
            wsFunc  deleteTrailingWS, str3a
            wsFunc  deleteTrailingWS, str3b
            wsFunc  deleteTrailingWS, str3c
            wsFunc  deleteTrailingWS, str3d
            wsFunc  deleteTrailingWS, str3e
            wsFunc  deleteTrailingWS, str3f
            
allDone:    leave
            pop     r15
            pop     r14
            pop     rdi
            pop     rsi
            pop     rbx
            ret     ;Returns to caller
asmMain     endp
            end
