; Listing 18-18
;
; Benchmarking the stringCmp2 and 
; stringCaseCmp Functions

            option     casemap:none
            include    string.inc
            include    aoalib.inc

            includelib aoalib.lib

            .const
ttlStr      byte    "Listing 18-18", 0


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
            
            
            .code
          
printResult proc
	mov	r11, rax
            sete    cl
            seta    al
            setb    bl
            movzx   r8d, bl
            movzx   r9d, cl
            movzx   r10d, al
            call    print
            byte    "%s: <:%d, =:%d, >:%d, time:%I64d cycles", nl, 0
            ret
printResult endp 

testResult  macro   func, strParm
            
string      catstr  <tst>, <&strParm>
stringLt    catstr  <tst>, <&strParm>, <lt>
msgStr      catstr  <&func>, <_>, <lt>
            .data
            strDcl  msgStr, 64, txt2str(%msgStr)
            .code
	rdtsc
	mov	dword ptr startTime, eax
	mov	dword ptr startTime[4], edx
            lea     rsi, string
            lea     rdi, stringLt
            call    func
	rdtsc
	shl	rdx, 32
	or	rax, rdx
	sub	rax, startTime
            lea     rdx, msgStr
            call    printResult
            
string      catstr  <tst>, <&strParm>
stringEq    catstr  <tst>, <&strParm>, <eq>
msgStr      catstr  <&func>, <_>, <eq>
            .data
            strDcl  msgStr, 64, txt2str(%msgStr)
            .code
	rdtsc
	mov	dword ptr startTime, eax
	mov	dword ptr startTime[4], edx
            lea     rsi, string
            lea     rdi, stringEq
            call    func
	rdtsc
	shl	rdx, 32
	or	rax, rdx
	sub	rax, startTime
            lea     rdx, msgStr
            call    printResult
            
string      catstr  <tst>, <&strParm>
stringGt    catstr  <tst>, <&strParm>, <gt>
msgStr      catstr  <&func>, <_>, <gt>
            .data
            strDcl  msgStr, 64, txt2str(%msgStr)
            .code
	rdtsc
	mov	dword ptr startTime, eax
	mov	dword ptr startTime[4], edx
            lea     rsi, string
            lea     rdi, stringGt
            call    func
	rdtsc
	shl	rdx, 32
	or	rax, rdx
	sub	rax, startTime
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
            byte    "Timing stringCaseCmp:", nl, nl, 0
	
            testResult stringCaseCmp, a            
            
            call    print
            byte    "Timing stringCmp2:", nl, nl, 0
	
            testResult stringCmp2, a            
            
                        
            
allDone:    leave
            pop     r15
            pop     r14
            pop     rdi
            pop     rsi
            pop     rbx
            ret     ;Returns to caller
asmMain     endp
            end
