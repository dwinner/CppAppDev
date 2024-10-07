; Listing 18-9
;
; stringCat function.

            option     casemap:none
            include    string.inc
            include    aoalib.inc

            includelib aoalib.lib

; Controls the maximum prefix length size.
; Maximum is 256. Can use smaller values
; to speed up assembly during development
; and test (of this code, not the algorithms).
; Must be greater than 2.  32 is a good "small"
; number for testing purposes.
;
; WARNING: when set to a large number, such 
; as 256, MASM can take a couple minutes to
; assemble this file.

maxpLen     =       256

; Controls the maximum suffix size. A good
; maximum is 26 that generates suffix strings
; with the characters A-Z. Under no circumstances
; should this value exceed 32. Must be greater than
; 1; can be less than 26 for testing purposes.
 
maxsLen     =       26


; Number of times to repeat the main benchmarking
; loop at run time:

repeatCnt   =       500000


            .const
ttlStr      byte    "Listing 18-9", 0

            .data
startTime   dword   ?
            
            
; genChrs, genSufx-
;
;   Generate a sequence of characters for a string.

genPrfx     macro   numChrs
            local   chr, cntr
cntr        =       1 
chr         =       'a'
            while   cntr le numChrs
            byte    chr
chr         =       chr+1
cntr        =       cntr+1
            if      chr gt 'z'
chr         =       'a'
            endif
            endm
            endm
            
                        
genSufx     macro   numChrs
            local   chr, cntr
cntr        =       1 
chr         =       'A'
            while   cntr le numChrs
            byte    chr
chr         =       chr+1
cntr        =       cntr+1
            if      chr gt 'Z'
chr         =       'A'
            endif
            endm
            endm
            
                                
; Generate a whole bunch of strings for
; testing purposes.
;
; This pair of nested loop generates maxpLen-1
; strings, with lengths from 1..maxpLen.
; Generate string0..string<maxpLen>:

strLength   =       0
            while   strLength lt maxpLen
            local   nameStr, lenStr, strName
strName     catstr  <string>, %strLength


; Output the string data. At least one
; byte of data.

            strBgn  %strName, %(strLength+maxsLen+32)
            genPrfx %strLength
            strEnd  %strName

                        
; Move on to the next string we're generating
; in the compile-time while loop.

strLength   =       strLength + 1
            endm  



; Generate the strings to concatente to the above strings.
; This will generate the strings:
;
; cat0, cat1, cat2, ..., cat26

strLength   =       0
            while   strLength le maxsLen
catName     catstr  <cat>, %strLength

            strBgn  %catName, 36
            genSufx %strLength
            strEnd  %catName
strLength   =       strLength + 1
            endm  
                        


; Here are the result strings:

pLen        =       0
            while   pLen lt maxpLen
sLen        =       0
            while   sLen le maxsLen
resultName  catstr  <cat_>, %pLen, <_>, %sLen

            strBgn  %resultName, %sLen+pLen+16
            
; 1st, emit the data for the 
; cat_<pLen>_<sLen> strings:

            genPrfx %pLen
            genSufx %sLen
            strEnd  %resultName
            
sLen        =       sLen + 1
            endm    ;while sLen
            
pLen        =       pLen + 1
            endm    ;while pLen
            
            
            

            .code
            externdef time:proc
            
;**********************************************************
;
; testCat-
;
;  Macro to test the various string concatenation functions
;
; Arguments:
;
;  func     stringCat function to call
;  txt      Text description of function
;
;  Executes specified strcpy function 
; repeatCnt * maxpLen times so we can time 
; its operation
;

testCat     macro   func, txt
            local   strCatLp, allDone, badCat, strOvfl 

            call    print
            byte    "Timing &func", nl, 0
            
            xor     rcx, rcx        ;NULL argument to time
            call    time
            mov     startTime, eax  ;Save starting time



; Call the string copy function over and over again:

            mov     ebx, repeatCnt
strCatLp:

              
; Okay, generate code to time the concatenation operations:       
       
pLen        =       0
            while   pLen lt maxpLen 

strName     catstr  <string>, %pLen
sLen        =       0
            while   sLen le maxsLen
            
catName     catstr  <cat>, %sLen
resultName  catstr  <cat_>, %pLen, <_>, %sLen

; First thing, convert stringX back to
; original string before concatenation
; operation.


            lea     rsi, strName
            mov     rax, pLen
            mov     byte ptr [rsi][rax*1], 0
            mov     [rsi-sohs].strObject.strLength, eax
            
; Okay, do the string concatenation operation:
            
            mov     rdx, pLen
            mov     r8, sLen
            lea     rsi, catName    ;Just concatenate cat<sLen>
            lea     rdi, strName    ; to the end of string<pLen>.
            call    func            ;Call stringCat function.
            jc      strOvfl
            
; Right now, we're just timing the concatenation, do
; the comparison opertion later:

sLen        =       sLen+1
            endm
                                    
pLen        =       pLen + 1
            endm
            
            

; Repeat the run-time loop <repeatCnt> times
             
            dec     ebx
            jnz     strCatLp
            
            xor     rcx, rcx        ;NULL argument to time
            call    time
            sub     eax, startTime  
            
            mov     edx, eax
            call    print
            byte    "&txt concatenation time = %d seconds"
            byte    nl, 0
       
;--------------------------------------------------------
;       
; Down here, test the results of the string concatenation
; operations:
       
pLen        =       0
            while   pLen lt maxpLen

strName     catstr  <string>, %pLen
sLen        =       0

            while   sLen le maxsLen
            
catName     catstr  <cat>, %sLen
resultName  catstr  <cat_>, %pLen, <_>, %sLen

; First thing, convert stringX back to
; original string before concatenation
; operation.

            lea     rsi, strName
            mov     eax, pLen
            mov     byte ptr [rsi][rax*1], 0
            mov     [rsi-sohs].strObject.strLength, eax

; Okay, do the string concatenation operation:

            mov     rdx, pLen
            mov     rcx, sLen
            lea     rsi, catName    ;Just concatenate cat<sLen>
            lea     rdi, strName    ; to the end of string<pLen>.
            call    func            ;Call stringCat function.

            lea     rsi, strName
            lea     rdi, resultName
            call    stringCmp1
            jne     badCat
            
sLen        =       sLen+1
            endm
                                    
pLen        =       pLen + 1
            endm
            jmp     allDone
            
badCat:     mov     r8, rsi
            mov     r9, rdi
            call    print
            byte    "Bad stringCat on String%d, got='%s'"
            byte    nl
            byte    "expected '%s'" 
            byte    nl, 0
            jmp     allDone
            
strOvfl:    call    print
            byte    "String overflow on string(%d, %d)", nl, 0

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

            testCat  stringCat1, movsb
            testCat  stringCat2, SSE

                         
allDone:    leave
            pop     rbx
            ret     ;Returns to caller
asmMain     endp
            end
