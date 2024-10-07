
; Listing 17-4
;
; strcmp functions

            include    zstrings.inc
            include    aoalib.inc
            includelib aoalib.lib

; Number of loop repetitions for timing:

repeatCnt   =       5000000

            .const
ttlStr      byte    "Listing 17-4", 0

            .data
startTime   dword   ?
hasSSE42    byte    0 ;True if CPU supports SSE4.2 instrs

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

string0     byte    0

strLength   =       1
            while   strLength lt 256
strName     catstr  <string>, %strLength
strName     byte    '@'
            genChrs %strLength-1
            byte    0
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

eq0         byte    0

strLength   =       1
            while   strLength lt 256
strName     catstr  <eq>, %strLength
strName     byte    '@'
            genChrs (%strLength-1)
            byte    0
strLength   =       strLength + 1
            endm
            

; The following strings will be greater than the
; source strings:

            align   16
            byte    7 dup (0ffh)

strLength   =       2
            while   strLength lt 256
strName     catstr  <gt>, %strLength
strName     byte    '@'
            genChrs (%strLength-2)
            byte    ' '
            byte    0
strLength   =       strLength + 1
            endm
            
            
; The following strings will be less than the
; source strings:


            align   16
            byte    13 dup (0ffh)

strLength   =       2
            while   strLength lt 256
strName     catstr  <lt>, %strLength
strName     byte    '@'
            genChrs (%strLength-2)
            byte    'a'
            byte    0
strLength   =       strLength + 1
            endm
            

            
            
            .code

;**************************************************
;
;  Macro to test the various string compare functions
;
; Arguments:
;
;  func     strcpy function to call
;  srcReg   Register holding source address
;  destReg  Register holding destination address
;  txt      Text description of function
;
;  Executes specified strcmp function 5,000,000 * 256 times
; so we can time its operation
;

tstSCmp     macro   func, srcReg, destReg, txt
            local   strCmpLp, allDone
            local   notEql, notLess, notGreater

            call    print
            byte    "Timing &func", nl, 0
            
            xor     rcx, rcx        ;NULL argument to time
            call    time
            mov     startTime, eax  ;Save starting time

; Call the string copy function over and over again:

            mov     ebx, repeatCnt
strCmpLp:

; Generate 256 calls to the string length function, one
; for each of the 256 strings created earlier (lengths
; 0..255):

lpCnt       =       0
            while   lpCnt lt 256
            
strName     catstr  <string>, %lpCnt
destStr     catstr  <eq>, %lpCnt
            lea     srcReg, strName  ;Just compare the string
            lea     destReg, destStr ; to destStr
            call    func             ;Call strcmp function.
            lea     rdx, strName
            lea     r8, destStr
            cmp     eax, 0
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
            byte    "&txt strcmp time = %d seconds", nl, 0

; Verify that the strcmp functions produce reasonable results:

lpCnt       =       2
            while   lpCnt lt 256
strName     catstr  <string>, %lpCnt
destStr     catstr  <gt>, %lpCnt


; Test for greater than

            lea     srcReg, strName  ;Just compare the string
            lea     destReg, destStr ; to destStr
            call    func             ;Call strcmp function.
            lea     rdx, strName
            lea     r8, destStr
            cmp     eax, 0
            jle     notGreater
            
; Test for less than

destStr     catstr  <lt>, %lpCnt

            lea     srcReg, strName  ;Just compare the string
            lea     destReg, destStr ; to destStr
            call    func             ;Call strcmp function.
            lea     rdx, strName
            lea     r8, destStr
            cmp     eax, 0
            jge     notLess
            
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




            
;**************************************************
;
; Here is the "asmMain" function.

        
            public  asmMain
asmMain     proc
            push    rbx
            push    rsi
            push    rdi
            push    rbp
            mov     rbp, rsp
            sub     rsp, 56         ;Shadow storage
            
; This program requires AVX features to run properly.
; Check for the presence of those features before running.
;
; Leaf function 1 is available on all CPUs that support
; CPUID, no need to test for it.  

            mov     eax, 1
            cpuid
            and     ecx, SSE42      ;Test bits 19 & 20
            cmp     ecx, SSE42      ;Both must be set
            sete    hasSSE42
            
            
            tstSCmp strcmp1, rsi, rdi, naive
            cmp     hasSSE42, 1
            je      doPCMP
            
            call    print
            byte    "CPU does not support SSE42 "
            byte    "instructions, skipping strlen6"
            byte    nl, 0
            jmp     noSSE42
            

doPCMP:     tstSCmp strcmp2, rsi, rdi, pcmpistr 

noSSE42:    tstSCmp strcmp3, rsi, rdi, SSE
            tstSCmp strcmp,  rcx, rdx, C stdlib            
       
            
allDone:    leave
            pop     rdi
            pop     rsi
            pop     rbx
            ret     ;Returns to caller
asmMain     endp
            end
