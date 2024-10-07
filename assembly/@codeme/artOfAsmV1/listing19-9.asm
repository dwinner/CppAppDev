; Listing 19-9            
;
; stringTokenize function test code:

            include    aoalib.inc
            include    cset.inc
            includelib aoalib.lib

            .const
ttlStr      byte    "Listing 19-9", 0

            .data
startTime1  qword   0
startTime2  qword   0

skipPosn    dword   0
fcsetPosn   dword   0

            staticStr result, 256


; CSV delimiter character set:

            csetInit
            unionStr  ";,"
            unionHex  20h, 9        ;Space and Tab characters
            emitPCset csvDelimiters
            
            
; Sample source string to test function:

            strBgn  csvStr, 256
            byte    "1, 2, 3,"
            byte    tab
            byte    "4, 5, 6, 7, 8; 90"
            strEnd  csvStr
            
            
; Array, to hold the result of stringTokenize on the above
; string:

components  qword   16 dup (0)

            .code
         

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
            
; Initialize the csvDelimiters character set

            lea     rsi, csvDelimiters
            mov     rdi, rsi
            call    csetToPCset
            
; Call stringTokenize:

            lea     rsi, csvStr
            xor     eax, eax
            lea     rdi, csvDelimiters
            lea     rbx, components
            mov     rcx, length components
            call    stringTokenize
            
            mov     rdx, rax
            call    print
            byte    "%d components", nl, 0

            xor     rcx, rcx
printComps: cmp     rcx, rax
            jae     freeComps
            mov     rdx, rcx
            mov     r8, [rbx][rcx*8]
            call    print
            byte    "%2d: '%s'", nl, 0
            inc     rcx
            jmp     printComps
            
; Free all the strings allocated by call
; to stringTokenize. Technically, this isn't
; necessary as the program is about to quit
; and that will free all allocated storage.
; However, this is done here to emphasize
; the fact that the stringTokenize caller
; should free the storage that stringTokenize
; allocated on the heap.

freeComps:  xor     rcx, rcx
freeLoop:   cmp     rcx, rax
            jae     allDone
            mov     rax, [rbx][rcx*8]
            call    stringFree
            inc     rcx
            jmp     freeLoop
                         
allDone:    leave
            pop     r15
            pop     rdi
            pop     rsi
            pop     rbx
            ret     ;Returns to caller
asmMain     endp
            end
