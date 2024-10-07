; Listing 18-16
;
; stringUpper, and stringLower Functions

            option     casemap:none
            include    string.inc
            include    aoalib.inc

            includelib aoalib.lib

            .const
ttlStr      byte    "Listing 18-16", 0


            .data
startTime   qword   ?
endTime     qword   ?
frequency   qword   ?


; Generate a whole bunch of strings for
; testing purposes:            

            strDcl str1a, 32, " !@#$abcdefg01234[]{}\|~"
            strDcl str1b, 32, " !@#$ABCDEFG01234[]{}\|~"
            strDcl str1c, 32, "abcdefg !@#$01234[]{}\|~"
            strDcl str1d, 32, "ABCDEFG !@#$01234[]{}\|~"
            strDcl str1e, 32, " !@#$01234abcdefg"
            strDcl str1f, 32, " !@#$01234ABCDEFG"
            strDcl str1g, 32, " !@#$01234[]{}\|~"
            strDcl str1h, 32, "ABCDEFGABCDEFGABCDEFGABCDEFG"
            strDcl str1i, 32, "abcdefgabcdefgabcdefgabcdefg"
            strDcl str1j, 32, "A"
            strDcl str1k, 32, "b"
            strDcl str1l, 32, "0"
            strDcl str1m, 32, "1"
            strBgn str1n, 32        ;Empty string
            strEnd str1n

            strDcl str2a, 32, " !@#$abcdefg01234[]{}\|~"
            strDcl str2b, 32, " !@#$ABCDEFG01234[]{}\|~"
            strDcl str2c, 32, "abcdefg !@#$01234[]{}\|~"
            strDcl str2d, 32, "ABCDEFG !@#$01234[]{}\|~"
            strDcl str2e, 32, " !@#$01234abcdefg"
            strDcl str2f, 32, " !@#$01234ABCDEFG"
            strDcl str2g, 32, " !@#$01234"
            strDcl str2h, 32, "ABCDEFGABCDEFGABCDEFGABCDEFG"
            strDcl str2i, 32, "abcdefgabcdefgabcdefgabcdefg"
            strDcl str2j, 32, "A"
            strDcl str2k, 32, "b"
            strDcl str2l, 32, "0"
            strDcl str2m, 32, "1"
            strBgn str2n, 32        ;Empty string
            strEnd str2n


            
            .code
            
caseFunc    macro   func, string
            lea     rdx, string
            call    print
            byte    "Original string: '%s'  --  ", 0
            lea     rdi, string
            call    func
            lea     rdx, string
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
            byte    "Testing stringUpper:", nl, nl, 0
            caseFunc  stringUpper, str1a
            caseFunc  stringUpper, str1b
            caseFunc  stringUpper, str1c
            caseFunc  stringUpper, str1d
            caseFunc  stringUpper, str1e
            caseFunc  stringUpper, str1f
            caseFunc  stringUpper, str1g
            caseFunc  stringUpper, str1h
            caseFunc  stringUpper, str1i
            caseFunc  stringUpper, str1j
            caseFunc  stringUpper, str1k
            caseFunc  stringUpper, str1l
            caseFunc  stringUpper, str1m
            caseFunc  stringUpper, str1n
            
            call    print
            byte    nl, "Testing stringLower:", nl, nl, 0
            caseFunc  stringLower, str2a
            caseFunc  stringLower, str2b
            caseFunc  stringLower, str2c
            caseFunc  stringLower, str2d
            caseFunc  stringLower, str2e
            caseFunc  stringLower, str2f
            caseFunc  stringLower, str2g
            caseFunc  stringLower, str2h
            caseFunc  stringLower, str2i
            caseFunc  stringLower, str2j
            caseFunc  stringLower, str2k
            caseFunc  stringLower, str2l
            caseFunc  stringLower, str2m
            caseFunc  stringLower, str2n
            
            
allDone:    leave
            pop     r15
            pop     r14
            pop     rdi
            pop     rsi
            pop     rbx
            ret     ;Returns to caller
asmMain     endp
            end
