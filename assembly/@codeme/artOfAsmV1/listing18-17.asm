; Listing 18-17
;
; stringCaseCmp Function

            option     casemap:none
            include    string.inc
            include    aoalib.inc

            includelib aoalib.lib

            .const
ttlStr      byte    "Listing 18-17", 0


            .data
startTime   qword   ?
endTime     qword   ?
frequency   qword   ?


; Generate a whole bunch of strings for
; testing purposes:            

            strDcl tsta,   32, " !@#$abcdefg01234[]{}\|~"
            strDcl tstaeq, 32, " !@#$ABCDEFG01234[]{}\|~"
            strDcl tstalt, 32, " !@#$ABCDEFH01234[]{}\|~"
            strDcl tstagt, 32, " !@#$ABCDEFF01234[]{}\|~"
            
            strDcl tstb,   32, "ABCDEFG !@#$01234[]{}\|~"
            strDcl tstbeq, 32, "abcdefg !@#$01234[]{}\|~"
            strDcl tstblt, 32, "abcdefH !@#$01234[]{}\|~"
            strDcl tstbgt, 32, "abcdefF !@#$01234[]{}\|~"

            strDcl tstc,   32, "ABCDEFG !@#$01234[]{}\|~"
            strDcl tstceq, 32, "ABCDEFG !@#$01234[]{}\|~"
            strDcl tstclt, 32, "ABCDEFh !@#$01234[]{}\|~"
            strDcl tstcgt, 32, "ABCDEFf !@#$01234[]{}\|~"
            
            strDcl tstd,   32, " !@#$01234abcdefg"
            strDcl tstdeq, 32, " !@#$01234abcdefg"
            strDcl tstdlt, 32, " !@#$01234abcdefg "
            strDcl tstdgt, 32, " !@#$01234abcdef"

            strDcl tste,   32, " !@#$01234ABCDEFG"
            strDcl tsteeq, 32, " !@#$01234ABCDEFG"
            strDcl tstelt, 32, " !@#$01234abcdefh"
            strDcl tstegt, 32, " !@#$01234abcdeff"

            strDcl tstf,   32, " !@#$01234[]{}\|~"
            strDcl tstfeq, 32, " !@#$01234[]{}\|~"
            strDcl tstflt, 32, "!@#$01234[]{}\|~"
            strDcl tstfgt, 32, "  @#$01234[]{}\|~"

            strDcl tstg,   32, "ABCDEFGABCDEFGABCDEFGABCDEFG"
            strDcl tstgeq, 32, "abcdefgabcdefgabcdefgabcdefg"
            strDcl tstglt, 32, "bbcdefgabcdefgabcdefgabcdefg"
            strDcl tstggt, 32, "aacdefgabcdefgabcdefgabcdefg"
            
            strDcl tsth,   32, "A"
            strDcl tstheq, 32, "a"
            strDcl tsthlt, 32, "aa"
            strBgn tsthgt, 32        ;Empty string
            strEnd tsthgt

            strBgn tsti,  32         ;Empty string
            strEnd tsti
            strBgn tstieq, 32        ;Empty string
            strEnd tstieq
            strDcl tstilt, 32, " "
            strBgn tstigt, 32        ;gt will fail
            strEnd tstigt


             strDcl msg_ilt, 32, "str_ilt"
             strDcl msg_ieq, 32, "str_ieq"
            
            .code
          
printResult proc
            sete    cl
            seta    al
            setb    bl
            movzx   r8d, bl
            movzx   r9d, cl
            movzx   r10d, al
            call    print
            byte    "%s: <:%d, =:%d, >:%d", nl, 0
            ret
printResult endp 

testResult  macro   msg, strParm
            
string      catstr  <tst>, <&strParm>
stringLt    catstr  <tst>, <&strParm>, <lt>
msgStr      catstr  str2txt(&msg), <lt>
            .data
            strDcl  msgStr, 64, txt2str(%msgStr)
            .code
            lea     rsi, string
            lea     rdi, stringLt
            call    stringCaseCmp
            lea     rdx, msgStr
            call    printResult
            
string      catstr  <tst>, <&strParm>
stringEq    catstr  <tst>, <&strParm>, <eq>
msgStr      catstr  str2txt(&msg), <eq>
            .data
            strDcl  msgStr, 64, txt2str(%msgStr)
            .code
            lea     rsi, string
            lea     rdi, stringEq
            call    stringCaseCmp
            lea     rdx, msgStr
            call    printResult
            
string      catstr  <tst>, <&strParm>
stringGt    catstr  <tst>, <&strParm>, <gt>
msgStr      catstr  str2txt(&msg), <gt>
            .data
            strDcl  msgStr, 64, txt2str(%msgStr)
            .code
            lea     rsi, string
            lea     rdi, stringGt
            call    stringCaseCmp
            lea     rdx, msgStr
            call    printResult
            call    print
            byte    nl, 0
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
            byte    "Testing stringCaseCmp:", nl, nl, 0
            testResult "str_a", a            
            testResult "str_b", b            
            testResult "str_c", c            
            testResult "str_d", d            
            testResult "str_e", e            
            testResult "str_f", f            
            testResult "str_g", g            
            testResult "str_h", h
            
; Must handle str_i specially as there is no
; way an empty string can be greater than
; any oter string.

            lea     rsi, tsti
            lea     rdi, tstilt
            call    stringCaseCmp
            lea     rdx, msg_ilt
            call    printResult

            lea     rsi, tsti
            lea     rdi, tstieq
            call    stringCaseCmp
            lea     rdx, msg_ieq
            call    printResult
            
            call    print
            byte    "(no comparison for lt)", nl, 0
            
                        
            
allDone:    leave
            pop     r15
            pop     r14
            pop     rdi
            pop     rsi
            pop     rbx
            ret     ;Returns to caller
asmMain     endp
            end
