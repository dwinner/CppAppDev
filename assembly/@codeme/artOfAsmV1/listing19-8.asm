; Listing 19-8	      
;
; Fast pcmpXstrY-based string scanning

            include    aoalib.inc
            include    cset.inc
            includelib aoalib.lib

            .const
ttlStr      byte    "Listing 19-8", 0

            .data
startTime1  qword   0
startTime2  qword   0

skipPosn    dword   0
fcsetPosn   dword   0

            staticStr result, 256


; This will fill up the range string (8 characters, whose
; codes are 2 apart):

            csetInit                    ;Initialize cset.
            unionStr  "ACEGIKMO"
            emitPCset rangeOnly
            
; This will (barely) succeed, filling up both the anyStr
; and rangeStr fields (24 characters, whose ASCII codes
; are 2 apart):

            csetInit                    ;Initialize cset.
            unionStr  "ACEGIKMOQSUWYbdfhjlnprtv"
            emitPCset anyAndRange
            
; This will fill the any string (16 characters, with
; each ASCII code being 2 apart):

            csetInit                    ;Initialize cset.
            unionStr  "ACEGIKMOQSUWYbdf"
            emitPCset anyOnly
            
            
; A really large string that contains only the characters
; in rangeOnly

            strBgn  roStr, 8200
            byte    1024 dup ("ACEGIKMO")
            strEnd  roStr
            
; A short string that contains only the characters in rangeOnly:

            strBgn  roShort, 256
            byte    8 dup ("ACEGIKMO")
            strEnd  roShort

            

; A really large string that contains only the characters
; in anyAndRange. Note: the characters are arranged in
; such a way that half the time the worst-case scenario
; (from a timing poing of view) occurs.

            strBgn  aarStr, 25000
            byte    1024 dup ("AbCdEfGhIKMOQSUWYjlnprtv")
            strEnd  aarStr
            
; A short string that contains only the characters
; in anyAndRange

            strBgn  aarShort, 256
            byte    8 dup ("AbCdEfGhIKMOQSUWYjlnprtv")
            strEnd  aarShort
            
                        

; A really large string that contains only the characters
; in anyOnly

            strBgn  aoStr, 16400
            byte    1024 dup ("ACEGIKMOQSUWYbdf")
            strEnd  aoStr

; A short string that contains only the characters
; in anyOnly

            strBgn  aoShort, 256
            byte    8 dup ("ACEGIKMOQSUWYbdf")
            strEnd  aoShort


            .code
         
; run1Test-
;
;  Utility used by runTests procedure.
;
; On Entry:
;
;  RSI-     string to scan
;  RDI-     character set to use
;  R15b-    true if code must initialize pcset.
;
; On Exit-
;
;  skipPosn-  Scan position returned by skipCset
;  fcsetPosn- Scan position returned by fscanCset
;  R8-        Timing (cycles) required by skipCset
;  r1-        Timing (cycles) required by fscanCset 

run1Test    proc
            rdtsc
            mov     dword ptr startTime1, eax
            mov     dword ptr startTime1[4], edx
            xor     eax, eax
            call    skipCset
            mov     skipPosn, eax   ;Save for later output
            
            rdtsc
            mov     dword ptr startTime2, eax
            mov     dword ptr startTime2[4], edx

; See if must include pcset creation in timing:

            cmp     r15b, 0
            je      justTime
            
            push    rsi
            mov     rsi, rdi
            call    csetToPCset
            pop     rsi            
                    
justTime:   xor     eax, eax
            call    fscanCset
            mov     fcsetPosn, eax  ;Save for later
            
            rdtsc
            shl     rdx, 32
            or      rax, rdx
            sub     rax, startTime2
            mov     r10, rax
            mov     r8, startTime2
            sub     r8, startTime1
            ret
run1Test    endp

   
; runTests-
;
; Times the running of the skipCset and fscanCset
; functions. Displays their outputs and running
; times.
;
; Input:
;
;  R15b-    true (1) if this function should also
;           initialize the pcset character set
;           strings as part of the timing operation.
            
runTests    proc
            
; Test/time fscanCset using the rangeOnly cset and string:

            lea     rsi, roStr
            lea     rdi, rangeOnly
            call    run1Test
            
            mov     edx, skipPosn
            mov     r9d, fcsetPosn
            call    print
            byte    "Range Only:    "
            byte    "skipCset= %5d, cycles=%7d", nl
            byte    "Range Only:    "
            byte    "fscanCset=%5d, cycles=%7d", nl, 0

            lea     rsi, roShort
            lea     rdi, rangeOnly
            call    run1Test
            
            mov     edx, skipPosn
            mov     r9d, fcsetPosn
            call    print
            byte    "Short RO:      "
            byte    "skipCset= %5d, cycles=%7d", nl
            byte    "Short RO:      "
            byte    "fscanCset=%5d, cycles=%7d", nl, 0



; Test/time fscanCset using the anyOnly cset and aoStr string:

            lea     rsi, aoStr
            lea     rdi, anyOnly
            call    run1Test        
            
            mov     edx, skipPosn
            mov     r9d, fcsetPosn
            call    print
            byte    "Any Only:      "
            byte    "skipCset= %5d, cycles=%7d", nl
            byte    "Any Only:      "
            byte    "fscanCset=%5d, cycles=%7d", nl, 0

            lea     rsi, aoShort
            lea     rdi, anyOnly
            call    run1Test        
            
            mov     edx, skipPosn
            mov     r9d, fcsetPosn
            call    print
            byte    "Any Short:     "
            byte    "skipCset= %5d, cycles=%7d", nl
            byte    "Any Short:     "
            byte    "fscanCset=%5d, cycles=%7d", nl, 0

; Test/time fscanCset using the anyAndRange cset and 
; aarStr string:

            lea     rsi, aarStr
            lea     rdi, anyAndRange
            call    run1Test        
            
            mov     edx, skipPosn
            mov     r9d, fcsetPosn
            call    print
            byte    "Any and Range: "
            byte    "skipCset= %5d, cycles=%7d", nl
            byte    "Any and Range: "
            byte    "fscanCset=%5d, cycles=%7d", nl, 0

            lea     rsi, aarShort
            lea     rdi, anyAndRange
            call    run1Test        
            
            mov     edx, skipPosn
            mov     r9d, fcsetPosn
            call    print
            byte    "AAR Short:     "
            byte    "skipCset= %5d, cycles=%7d", nl
            byte    "AAR Short:     "
            byte    "fscanCset=%5d, cycles=%7d", nl, 0
            
            ret
runTests    endp

;**********************************************************
;
; Here is the "asmMain" function.
        
            public  asmMain
asmMain     proc
            push    rbx
            push    rsi
            push    rdi
            push    r15
            push    rbp
            mov     rbp, rsp
            sub     rsp, 56         ;Shadow storage
            
; Before timing anything, "touch" the pages
; containing the data this program uses
; in order to ensure the data is sitting in
; real (not virtual) memory:
 
            lea     rdi, rangeOnly
            lea     rsi, rangeOnly
            call    csetToPCset
            lea     rdi, anyOnly
            lea     rsi, anyOnly
            call    csetToPCset
            lea     rdi, anyAndRange
            lea     rsi, anyAndRange
            call    csetToPCset
            
; Just for comparison, time the creation of the three
; pcset character sets:

            rdtsc
            mov     dword ptr startTime1, eax
            mov     dword ptr startTime1[4], edx
            lea     rdi, rangeOnly
            lea     rsi, rangeOnly
            call    csetToPCset
            rdtsc
            shl     rdx, 32
            or      rdx, rax
            sub     rdx, startTime1
            call    print
            byte    "Generate rangeOnly: %d", nl, 0

            rdtsc
            mov     dword ptr startTime1, eax
            mov     dword ptr startTime1[4], edx
            lea     rdi, anyOnly
            lea     rsi, anyOnly
            call    csetToPCset
            rdtsc
            shl     rdx, 32
            or      rdx, rax
            sub     rdx, startTime1
            call    print
            byte    "Generate anyOnly: %d", nl, 0

            rdtsc
            mov     dword ptr startTime1, eax
            mov     dword ptr startTime1[4], edx
            lea     rdi, anyAndRange
            lea     rsi, anyAndRange
            call    csetToPCset
            rdtsc
            shl     rdx, 32
            or      rdx, rax
            sub     rdx, startTime1
            call    print
            byte    "Generate anyAndRange: %d", nl, nl, 0
            
            
; Quick tests of fscanCset:

            call    print
            byte    "Timing comparison including "
            byte    "pcset construction", nl, nl, 0
            
            mov     r15b, 1         ;Construct the sets
            call    runTests
              

; Now that the pcset sets have already been created, repeat
; the code    

            call    print
            byte    nl, nl
            byte    "Timing comparison without "
            byte    "pcset construction", nl, nl, 0
            
            mov     r15b, 0
            call    runTests
            
                         
allDone:    leave
            pop     r15
            pop     rdi
            pop     rsi
            pop     rbx
            ret     ;Returns to caller
asmMain     endp
            end
