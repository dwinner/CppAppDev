; Listing 18-12
;
; skipChars and skipToChar Functions

            option     casemap:none
            include    string.inc
            include    aoalib.inc

            includelib aoalib.lib

; Maximum length of source string expansion
; (Controls timing loop iterations, too).

maxLen      =       200

; Number of iterations in timing loop:

repeatCnt   =       20000

            .const
ttlStr      byte    "Listing 18-12", 0            
            

            .data
temp        oword   ?
startTime   dword   ?
hasSSE42    byte    0 ;True if CPU supports SSE4.2 instrs


; Macro to generate a sequence of characters
; that are largely different:

genChrs     macro   count
            local   cntr, chr
cntr        =       0
chr         =       'a'
            while   cntr lt count
            byte    chr
chr         =       chr+1
            if      chr gt 'o'
chr         =       'a'
            endif
cntr        =       cntr + 1
            endm
            endm
            
;genStr      macro   theStr
;            exitm   <"&theStr">
;            endm
            
genVal      macro   theValue
            exitm   <&theValue>
            endm


; Generate a whole bunch of strings for
; testing purposes:


strLength   =       0
            while   strLength lt maxLen
            local   theString, nameStr
theString   catstr  <string>, %strLength
            strBgn  %theString, strLength+16
            byte    'a'
            genChrs %strLength-1
            
substr1     catstr  <result>, %strLength
substr1     =       $-theString
            byte    'ABC012_'
substr1     catstr  <result2_>, %strLength
substr1     =       $-theString
            byte    '.'
            strEnd  %theString
            
nameStr     catstr  <name>, %strLength
            strBgn  %nameStr, 16            
            byte    "name"
            byte    txt2str(%strLength)
            strEnd  %nameStr

strLength   =       strLength + 1
            endm


; Character set strings the application uses
; to test the various functions:

            strDcl  cs1, 32, "abcdefghijklmno" ;15 chars

            strBgn  cs2, 40
            byte    81h,82h,83h,84h,85h
            byte    "zyxwvutsrqpomnlkjihg"
            byte    "fedcba"                ;31 chars
            strEnd  cs2
            
            strBgn  cs3, 64
            byte    "!@#$%^&*()|+-=~`"
            byte    "zyxwvutsrqpomnlk"
            byte    "jihgfedcba<,>/?"       ;47 chars
            strEnd  cs3
            
            strBgn  cs4, 96
            byte    "abcdefghijklmnopqrst"
            byte    "uvwxyzABCDEFGHIJKLMN"
            byte    "OPQRSTUVWXYZ01234567"
            byte    "89_"                   ;63 chars
            strEnd  cs4

; Note: cs5 is used to test the strcspn functions.
            
            strDcl  cs5, 32, "ABCDEFGHIJKLMNOPQRSTUVWXYZ"


            
            .code
            externdef time:proc

;**************************************************
;
;  Macro to test the various string span functions
;
; Arguments:
;
;  func     strspn/strcspn function to call
;  which    Character set string to use
;  result   Result name prefix to use
;  srcReg   Register holding source address
;  setReg   Register holding charset address
;  txt      Text description of function
;
;  Executes specified strcmp function 500,000 * 256 times
; so we can time its operation
;

tstSS       macro   func, which, result, txt
            local   strSpnLp, badSpn, badSpn2, allDone
            local   badStrstr2

            call    print
            byte    "Timing &func with character set "
            byte    txt2str(which)
            byte    nl, 0
            
            xor     rcx, rcx        ;NULL argument to time
            call    time
            mov     startTime, eax  ;Save starting time

; Call the string copy function over and over again:

            mov     ebx, repeatCnt
strSpnLp:

; Generate 256 calls to the string length function, one
; for each of the 256 strings created earlier:

lpCnt       =       0
            while   lpCnt lt maxLen
            local   offsetLp
            
            mov     r15, 0
offsetLp:   

; Test a string (less than 16 chars):

nameStr     catstr  <name>, %lpCnt
strName     catstr  <string>, %lpCnt
            lea     rsi, strName ;String to search thru
            
; Test the "abcdefghijklmnopqrstuvwxyz" character set:

spnIndex    catstr  <&result>, %lpCnt

            lea     rdi, which
            mov     rax, r15        ;Offset into string
            mov     r14, spnIndex   ;Expected index value
            call    func            ;Call str(c)spn function.
            lea     rcx, nameStr
            jc      badSpn
            cmp     rax, -1
            jz      badSpn
            cmp     rax, r14
            jne     badSpn2
            
            inc     r15
            cmp     r15, lpCnt
            jb      offsetLp
            
                                                
lpCnt       =       lpCnt + 1
            endm
            
            dec     ebx
            jnz     strSpnLp
            
            xor     rcx, rcx        ;NULL argument to time
            call    time
            sub     eax, startTime  
            
            mov     edx, eax
            call    print
            byte    "&txt "
            byte    "&which"
            byte    " time = %d seconds", nl, 0
            jmp     allDone
            
badSpn:     mov     rdx, rcx
            mov     r8, rsi
            mov     r9, rdi
            mov     r10, r15 
            call    print
            byte    "&func; "
            byte    "%s: Failed when skipping in '%s' for cset(%s) at offset %d", nl, 0
            jmp     allDone
            
badSpn2:    mov     rdx, rcx
            mov     r8, rsi
            mov     r9, rdi
            mov     r10, rax
            mov     r11, r14 
            call    print
            byte    "&func; "
            byte    "%s:Failed when skipping in '%s' for cset(%s)", nl
            byte    "Got %d, expected %d", nl, 0
            mov     rdx, r15
            call    print
            byte    "Offset: %d", nl, 0
            
allDone:
                    
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
            
; This program requires SSE4.2 features to run properly.
; Check for the presence of those features before running.
;
; Leaf function 1 is available on all CPUs that support
; CPUID, no need to test for it.  

            mov     eax, 1
            cpuid
            and     ecx, SSE42      ;Test bits 19 & 20
            cmp     ecx, SSE42      ;Both must be set
            sete    hasSSE42
            
; Time the powerset variants:
            
            tstSS skipCharsPS,  cs1, result,   bit set
            tstSS skipCharsPS,  cs2, result,   bit set
            tstSS skipCharsPS,  cs3, result,   bit set
            tstSS skipCharsPS,  cs4, result2_, bit set
            tstSS skipToCharPS, cs5, result,   bit set
            
; Time the PCMPISTRI version here:

            cmp     hasSSE42, 1
            je      doPSTR
            
            call    print
            byte    "CPU does not support SSE42 "
            byte    "instructions, skipping strstr2"
            byte    nl, 0
            jmp     noSSE42

; Test variants that are pcmpistri-based:
            
doPSTR:     
            tstSS skipChars1,  cs1, result,   pcmpistri
            tstSS skipChars1,  cs2, result,   pcmpistri
            tstSS skipChars1,  cs3, result,   pcmpistri
            tstSS skipChars1,  cs4, result2_, pcmpistri
            tstSS skipToChar1, cs5, result,   pcmpistri


; Test the SSE code:

noSSE42:
            tstSS skipChars2,  cs1, result,   SSE
            tstSS skipChars2,  cs2, result,   SSE
            tstSS skipChars2,  cs3, result,   SSE
            tstSS skipChars2,  cs4, result2_, SSE
            tstSS skipToChar2, cs5, result,   SSE



allDone:    leave
            pop     r15
            pop     r14
            pop     rdi
            pop     rsi
            pop     rbx
            ret     ;Returns to caller
asmMain     endp
            end
