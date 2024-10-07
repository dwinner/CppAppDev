; Listing 18-5
;									
; stringCmp functions.

            option     casemap:none
            include    string.inc
            include    aoalib.inc
            includelib aoalib.lib


            .const
ttlStr      byte    "Listing 18-5", 0

            .data
startTime   dword   ?
            
            
; Macro to generate a sequence of characters
; that are largely different:

genChrs     macro   count
            local   cntr, chr
cntr        =       0
chr         =       'A'
            while   cntr lt count
            byte    chr
chr         =       chr+1
            if      chr gt 'Z'
chr         =       'A'
            endif
cntr        =       cntr + 1
            endm
            endm

; Generate a whole bunch of source strings for
; testing purposes:

            staticStr string0, 1

strLength   =       1
            while   strLength lt 256
strName     catstr  <string>, %strLength

            strBgn  %strName, %strLength+8
            byte    '@'
            genChrs %strLength-1
            strEnd  %strName
            
strLength   =       strLength + 1
            endm
            
; The following strings will be equal to the
; source strings:

; Generate a whole bunch of source strings for
; testing purposes:
;
; string0..string255 are equal to eq0..eq255
; string2..string255 are less than lt2..lt255
; string2..string255 are greater than gt2..gt255
;
; The align directive below are just to ensure
; that the eqX, ltX, and gtX strings don't wind
; up on the same byte boundary as the stringX
; strings.

            align   16
            byte    3 dup (0ffh)

            staticStr eq0, 1

strLength   =       1
            while   strLength lt 256
strName     catstr  <eq>, %strLength

            strBgn  %strName, %strLength+8
            byte    '@'
            genChrs %strLength-1
            strEnd  %strName
            
strLength   =       strLength + 1
            endm
            

; The source string will be greater than
; the following strings:

            align   16
            byte    7 dup (0ffh)

strLength   =       2
            while   strLength lt 256
strName     catstr  <gt>, %strLength

            strBgn  %strName, %strLength+8
            byte    '@'
            genChrs %strLength-2
            byte    ' '
            strEnd  %strName
            
strLength   =       strLength + 1
            endm
            

; The source string will also be greater than the
; following strings by virtue of these being shorter.


            align   16
            byte    13 dup (0ffh)

strLength   =       2
            while   strLength lt 256
strName     catstr  <gt2_>, %strLength

            strBgn  %strName, %strLength+8
            byte    '@'
            genChrs %strLength-2
            strEnd  %strName
            
strLength   =       strLength + 1
            endm
            
            
            
; The source string will be less than the
; following strings:


            align   16
            byte    13 dup (0ffh)

strLength   =       2
            while   strLength lt 256
strName     catstr  <lt>, %strLength

            strBgn  %strName, %strLength+8
            byte    '@'
            genChrs %strLength-2
            byte    'a'
            strEnd  %strName
            
strLength   =       strLength + 1
            endm
            
            
            
; The source string will also be less than the following strings 
; by virtue of these being longer strings:

            align   16
            byte    7 dup (0ffh)

strLength   =       2
            while   strLength lt 256
strName     catstr  <lt2_>, %strLength

            strBgn  %strName, %strLength+8
            byte    '@'
            genChrs %strLength-1
            byte    ' '
            strEnd  %strName
            
strLength   =       strLength + 1
            endm
	
	
	
; Here are some additional test strings that test
; specific conditions:

; Generate a whole bunch of strings for
; testing purposes:            

            strDcl tsta,   32, " !@#$ABCDEFG01234[]{}\|~"
            strDcl tstaeq, 32, " !@#$ABCDEFG01234[]{}\|~"
            strDcl tstalt, 32, " !@#$ABCDEFh01234[]{}\|~"
            strDcl tstagt, 32, " !@#$ABCDEFF01234[]{}\|~"
	
            strDcl tstb,   32, "abcdefg !@#$01234[]{}\|~"
            strDcl tstbeq, 32, "abcdefg !@#$01234[]{}\|~"
            strDcl tstblt, 32, "abcdefh !@#$01234[]{}\|~"
            strDcl tstbgt, 32, "abcdeff !@#$01234[]{}\|~"

            strDcl tstc,   32, "ABCDEFG !@#$01234[]{}\|~"
            strDcl tstceq, 32, "ABCDEFG !@#$01234[]{}\|~"
            strDcl tstclt, 32, "ABCDEFH !@#$01234[]{}\|~"
            strDcl tstcgt, 32, "ABCDEFF !@#$01234[]{}\|~"
	
            strDcl tstd,   32, " !@#$01234abcdefg"
            strDcl tstdeq, 32, " !@#$01234abcdefg"
            strDcl tstdlt, 32, " !@#$01234abcdefg "
            strDcl tstdgt, 32, " !@#$01234abcdef"

            strDcl tste,   32, " !@#$01234ABCDEFG"
            strDcl tsteeq, 32, " !@#$01234ABCDEFG"
            strDcl tstelt, 32, " !@#$01234ABCDEFH"
            strDcl tstegt, 32, " !@#$01234ABCDEFF"

            strDcl tstf,   32, " !@#$01234[]{}\|~"
            strDcl tstfeq, 32, " !@#$01234[]{}\|~"
            strDcl tstflt, 32, "!@#$01234[]{}\|~"
            strDcl tstfgt, 32, "  @#$01234[]{}\|~"

            strDcl tstg,   32, "ABCDEFGABCDEFGABCDEFGABCDEFG"
            strDcl tstgeq, 32, "ABCDEFGABCDEFGABCDEFGABCDEFG"
            strDcl tstglt, 32, "BBCDEFGABCDEFGABCDEFGABCDEFG"
            strDcl tstggt, 32, "AACDEFGABCDEFGABCDEFGABCDEFG"
	
            strDcl tsth,   32, "a"
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



	 strDcl	msg_ilt, 32, "str_ilt"
	 strDcl	msg_ieq, 32, "str_ieq"

            
            .code
	externdef time:proc
	
printResult	proc
	sete	cl
	seta	al
	setb	bl
	movzx	r8d, bl
	movzx	r9d, cl
	movzx	r10d, al
	call	print
	byte	"%s: <:%d, =:%d, >:%d", nl, 0
	ret
printResult	endp 

testResult	macro	func, msg, strParm
	local	msgStr, stringLt, stringEq, stringGt
	
string	catstr	<tst>, <&strParm>
stringLt	catstr	<tst>, <&strParm>, <lt>
msgStr	catstr	str2txt(&msg), <&func>, <_>, <lt>
	.data
	strDcl 	msgStr, 64, txt2str(%msgStr)
	.code
	lea	rsi, string
	lea	rdi, stringLt
	call	func
	lea	rdx, msgStr
	call	printResult
	
string	catstr	<tst>, <&strParm>
stringEq	catstr	<tst>, <&strParm>, <eq>
msgStr	catstr	str2txt(&msg), <&func>, <_>, <eq>
	.data
	strDcl 	msgStr, 64, txt2str(%msgStr)
	.code
	lea	rsi, string
	lea	rdi, stringEq
	call	func
	lea	rdx, msgStr
	call	printResult
	
string	catstr	<tst>, <&strParm>
stringGt	catstr	<tst>, <&strParm>, <gt>
msgStr	catstr	str2txt(&msg), <&func>, <_>, <gt>
	.data
	strDcl 	msgStr, 64, txt2str(%msgStr)
	.code
	lea	rsi, string
	lea	rdi, stringGt
	call	func
	lea	rdx, msgStr
	call	printResult
	call	print
	byte	nl, 0
	endm
	
 
;**************************************************
;
;  Macro to test and time the various string compare functions
;
; Arguments:
;
;  func     strcpy function to call
;  txt      Text description of function
;
;  Executes specified stringCmp function 5,000,000 * 256 times
; so we can time its operation
;

tstSCmp     macro   func, txt
            local   strCmpLp, allDone
            local   notEql, notLess, notGreater

            call    print
            byte    "Timing &func", nl, 0
            
            xor     rcx, rcx        ;NULL argument to time
            call    time
            mov     startTime, eax  ;Save starting time

; Call the string copy function over and over again:

            mov     ebx, 5000000
strCmpLp:

; Generate 256 calls to the string length function, one
; for each of the 256 strings created earlier (lengths
; 0..255):

lpCnt       =       0
            while   lpCnt lt 256
            
strName     catstr  <string>, %lpCnt
destStr     catstr  <eq>, %lpCnt
            lea     rsi, strName     ;Just compare the string
            lea     rdi, destStr     ; to destStr
            call    func             ;Call stringCmp function.
            lea     rdx, strName
            lea     r8, destStr
            jne     notEql
lpCnt       =       lpCnt + 1
            endm
            
            dec     ebx
            jnz     strCmpLp
            
            xor     rcx, rcx        ;NULL argument to time
            call    time
            sub     eax, startTime  
            
            mov     edx, eax
            call    print
            byte    "&txt stringCmp time = %d seconds", nl, 0

; Verify that the stringCmp functions produce reasonable results:

lpCnt       =       2
            while   lpCnt lt 3;256
strName     catstr  <string>, %lpCnt
destStr     catstr  <gt>, %lpCnt


; Test for greater than

            lea     rsi, strName  ;Just compare the string
            lea     rdi, destStr ; to destStr
            call    func             ;Call stringCmp function.
            lea     rdx, strName
            lea     r8, destStr
            jbe     notGreater
            


; Also test for greater than

destStr     catstr  <gt2_>, %lpCnt
            lea     rsi, strName  ;Just compare the string
            lea     rdi, destStr ; to destStr
            call    func             ;Call stringCmp function.
            lea     rdx, strName
            lea     r8, destStr
            jbe     notGreater
            
; Test for less than

destStr     catstr  <lt>, %lpCnt
            lea     rsi, strName  ;Just compare the string
            lea     rdi, destStr ; to destStr
            call    func             ;Call stringCmp function.
            lea     rdx, strName
            lea     r8, destStr
            jae     notLess
            
; Also test for less than

destStr     catstr  <lt2_>, %lpCnt

            lea     rsi, strName  ;Just compare the string
            lea     rdi, destStr ; to destStr
            call    func             ;Call stringCmp function.
            lea     rdx, strName
            lea     r8, destStr
            jae     notLess
            
lpCnt       =       lpCnt + 1
            endm

            jmp     allDone
       
notEql:     call    print
            byte    "String:", nl
            byte    "'%s'", nl
            byte    "does not equal", nl 
            byte    "'%s'", nl, 0
            jmp     allDone
                    
notLess:    call    print
            byte    "String:", nl
            byte    "'%s'", nl
            byte    "is not less than", nl 
            byte    "'%s'", nl, 0
            jmp     allDone
                    
notGreater: call    print
            byte    "String:", nl
            byte    "'%s'", nl
            byte    "is not greater than", nl 
            byte    "'%s'", nl, 0
                    
allDone:
            endm
            

;**********************************************************
;
; Here is the "asmMain" function.
        
            public  asmMain
asmMain     proc
            push    rbx
            push    rbp
            mov     rbp, rsp
            sub     rsp, 56         ;Shadow storage

            tstSCmp stringCmp1, cmpsb 
            tstSCmp stringCmp2, SSE 
            tstSCmp stringCmp3, pcmpestri 
            tstSCmp stringCmp4, pcmpistri 


; Additional tests (no timing on these):

            call    print
            byte    "Testing stringCmp1:", nl, nl, 0
            testResult stringCmp1, "str_a", a            
            testResult stringCmp1, "str_b", b            
            testResult stringCmp1, "str_c", c            
            testResult stringCmp1, "str_d", d            
            testResult stringCmp1, "str_e", e            
            testResult stringCmp1, "str_f", f            
            testResult stringCmp1, "str_g", g            
            testResult stringCmp1, "str_h", h
	
; Must handle str_i specially as there is no
; way an empty string can be greater than
; any oter string.

	lea	rsi, tsti
	lea	rdi, tstilt
	call	stringCmp1
	lea	rdx, msg_ilt
	call	printResult

	lea	rsi, tsti
	lea	rdi, tstieq
	call	stringCmp1
	lea	rdx, msg_ieq
	call	printResult
	
	call	print
	byte	"(no comparison for lt)", nl, 0


; Additional tests (no timing on these):

            call    print
            byte    "Testing stringCmp2:", nl, nl, 0
            testResult stringCmp2, "str_a", a            
            testResult stringCmp2, "str_b", b            
            testResult stringCmp2, "str_c", c            
            testResult stringCmp2, "str_d", d            
            testResult stringCmp2, "str_e", e            
            testResult stringCmp2, "str_f", f            
            testResult stringCmp2, "str_g", g            
            testResult stringCmp2, "str_h", h
	
; Must handle str_i specially as there is no
; way an empty string can be greater than
; any oter string.

	lea	rsi, tsti
	lea	rdi, tstilt
	call	stringCmp2
	lea	rdx, msg_ilt
	call	printResult

	lea	rsi, tsti
	lea	rdi, tstieq
	call	stringCmp2
	lea	rdx, msg_ieq
	call	printResult
	
	call	print
	byte	"(no comparison for lt)", nl, 0

                         
; Additional tests (no timing on these):

            call    print
            byte    "Testing stringCmp3:", nl, nl, 0
            testResult stringCmp3, "str_a", a            
            testResult stringCmp3, "str_b", b            
            testResult stringCmp3, "str_c", c            
            testResult stringCmp3, "str_d", d            
            testResult stringCmp3, "str_e", e            
            testResult stringCmp3, "str_f", f            
            testResult stringCmp3, "str_g", g            
            testResult stringCmp3, "str_h", h
	
; Must handle str_i specially as there is no
; way an empty string can be greater than
; any oter string.

	lea	rsi, tsti
	lea	rdi, tstilt
	call	stringCmp3
	lea	rdx, msg_ilt
	call	printResult

	lea	rsi, tsti
	lea	rdi, tstieq
	call	stringCmp3
	lea	rdx, msg_ieq
	call	printResult
	
	call	print
	byte	"(no comparison for lt)", nl, 0
	
	
; Additional tests (no timing on these):

            call    print
            byte    "Testing stringCmp4:", nl, nl, 0
            testResult stringCmp4, "str_a", a            
            testResult stringCmp4, "str_b", b            
            testResult stringCmp4, "str_c", c            
            testResult stringCmp4, "str_d", d            
            testResult stringCmp4, "str_e", e            
            testResult stringCmp4, "str_f", f            
            testResult stringCmp4, "str_g", g            
            testResult stringCmp4, "str_h", h
	
; Must handle str_i specially as there is no
; way an empty string can be greater than
; any oter string.

	lea	rsi, tsti
	lea	rdi, tstilt
	call	stringCmp4
	lea	rdx, msg_ilt
	call	printResult

	lea	rsi, tsti
	lea	rdi, tstieq
	call	stringCmp4
	lea	rdx, msg_ieq
	call	printResult
	
	call	print
	byte	"(no comparison for lt)", nl, 0

                         
allDone:
            leave
            pop     rbx
            ret     ;Returns to caller
asmMain     endp
            end
