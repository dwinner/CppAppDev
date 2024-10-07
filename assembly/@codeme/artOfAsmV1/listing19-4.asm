; Listing 19-4
;
; Population count benchmark.

            include    aoalib.inc
            include    cset.inc
            includelib aoalib.lib

repeatCnt   =               10000

            .const
ttlStr      byte    "Listing 19-4", 0

            .data
startTime   qword   0
endTime     qword   0
hasPopCnt   byte    0


; The empty set (should be the fastest for the
; naive population count function):

            staticCset emptySet

; Alphabetics set (52 upper and lower case characters):
            
            csetInit                    ;Initialize cset.
            unionRng <A-Z>
            unionRng <a-z>
            unionRng <0-9>
            emitCset    alphaNumerics   ;Creates actual cset.

; Alphanumerics: 62 characters (alpha plus 10 digits):
            
            csetInit
            unionRng <A-Z>
            unionRng <a-z>
            emitCset alphabetics
            
; Full set (all 256 bit positions are 1s; this is the
; worst case for the naive population count function):

            csetInit
            negCset
            emitCset fullSet


            .code
            externdef QueryPerformanceCounter:proc
            externdef QueryPerformanceFrequencyr:proc
            
; Here's a naive population count function
; so we can compare the performance of csetPopCnt
; to a naive version.

; naivePC64 does a population count on the value
; in the RBX register. It returns the count in RCX.
        
naivePC64       proc        
                xor   rcx, rcx
                jmp   enterLp
            
cntLp:          adc   rcx, 0        ;Count last bit
enterLp:        shr   rbx, 1
                jnz   cntLp
                
; The shr instruction may have shifted out a 1 bit
; when it produced zero in RBX. Add in that (possible)
; 1 bit here:

                adc   rcx, 0
                ret
naivePC64       endp

; naiveCsetPopCnt does a naive population count on
; all 256 bits of a character set variable. It returns
; the count in RAX.

naiveCsetPopCnt proc
                push  rbx
                push  rcx
                mov   rbx, [rsi]
                call  naivePC64
                mov   rax, rcx

                mov   rbx, [rsi+8]
                call  naivePC64
                add   rax, rcx

                mov   rbx, [rsi+16]
                call  naivePC64
                add   rax, rcx

                mov   rbx, [rsi+24]
                call  naivePC64
                add   rax, rcx
            
                pop   rcx
                pop   rbx
                ret
naiveCsetPopCnt endp
            

; Use the popcnt instruction.

popcntInstr     proc
                push   rbx
                popcnt rax, [rsi]
                popcnt rbx, [rsi+8]
                add   rax, rbx
                popcnt rbx, [rsi+16]
                add   rax, rbx
                popcnt rbx, [rsi+24]
                add   rax, rbx

                pop   rbx
                ret
popcntInstr     endp
            

;**********************************************************
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

; Check for the presence of those features before running.
;
; Leaf function 1 is available on all CPUs that support
; CPUID, no need to test for it.  

            mov     eax, 1
            cpuid
            and     ecx, SSEPopCnt      ;Test bit23
            setne   hasPopCnt
            jne     noPopCntMsg
            call    print
            byte    "CPU does not support POPCNT instruction."
            byte    nl
            byte    "Skipping tests that use POPCNT", nl, 0
noPopCntMsg:

; Time the SSE variant on the alphabetic character set:
            
            lea     rcx, startTime
            call    QueryPerformanceCounter

            mov     rdi, repeatCnt
aLp1a:      lea     rsi, alphaNumerics
            call    csetPopCnt
            dec     rdi
            jnz     aLp1a
            mov     rbx, rax
            lea     rcx, endTime
            call    QueryPerformanceCounter
            mov     r8, endTime
            sub     r8, startTime
            mov     rdx, rbx
            call    print
            byte    "Alphanumerics=%d, time=%d", nl, 0
            
; Time the naive variant on the alphabetic character set:
            
            lea     rcx, startTime
            call    QueryPerformanceCounter

            mov     rdi, repeatCnt
aLp1b:      lea     rsi, alphaNumerics
            call    naiveCsetPopCnt
            dec     rdi
            jnz     aLp1b
            mov     rbx, rax
            lea     rcx, endTime
            call    QueryPerformanceCounter
            mov     r8, endTime
            sub     r8, startTime
            mov     rdx, rbx
            call    print
            byte    "Alphanumerics2=%d, time=%d", nl, 0
            
; Time the popcnt variant on the alphabetic character set:
            
            cmp     hasPopCnt, 0
            je      skip1c
            
            lea     rcx, startTime
            call    QueryPerformanceCounter

            mov     rdi, repeatCnt
aLp1c:      lea     rsi, alphaNumerics
            call    popcntInstr
            dec     rdi
            jnz     aLp1c
            mov     rbx, rax
            lea     rcx, endTime
            call    QueryPerformanceCounter
            mov     r8, endTime
            sub     r8, startTime
            mov     rdx, rbx
            call    print
            byte    "Alphanumerics3=%d, time=%d", nl, nl, 0
skip1c:            
            
; Time the SSE variant on the alphanumeric character set:
            
            lea     rcx, startTime
            call    QueryPerformanceCounter

            mov     rdi, repeatCnt
aLp2a:      lea     rsi, alphabetics
            call    csetPopCnt
            dec     rdi
            jnz     aLp2a
            mov     rbx, rax
            lea     rcx, endTime
            call    QueryPerformanceCounter
            mov     r8, endTime
            sub     r8, startTime
            mov     rdx, rbx
            call    print
            byte    "Alphabetics=%d, time=%d", nl, 0
            
; Time the naive variant on the alphanumeric character set:
            
            lea     rcx, startTime
            call    QueryPerformanceCounter

            mov     rdi, repeatCnt
aLp2b:      lea     rsi, alphabetics
            call    naiveCsetPopCnt
            dec     rdi
            jnz     aLp2b
            mov     rbx, rax
            lea     rcx, endTime
            call    QueryPerformanceCounter
            mov     r8, endTime
            sub     r8, startTime
            mov     rdx, rbx
            call    print
            byte    "Alphabetics2=%d, time=%d", nl, 0
            
; Time the popcnt variant on the alphanumeric character set:
            
            cmp     hasPopCnt, 0
            je      skip2c
            
            lea     rcx, startTime
            call    QueryPerformanceCounter

            mov     rdi, repeatCnt
aLp2c:      lea     rsi, alphabetics
            call    popcntInstr
            dec     rdi
            jnz     aLp2c
            mov     rbx, rax
            lea     rcx, endTime
            call    QueryPerformanceCounter
            mov     r8, endTime
            sub     r8, startTime
            mov     rdx, rbx
            call    print
            byte    "Alphabetics3=%d, time=%d", nl, nl, 0
skip2c:            
            
; Time the SSE variant on the full character set:
            
            lea     rcx, startTime
            call    QueryPerformanceCounter

            mov     rdi, repeatCnt
aLp3a:      lea     rsi, fullSet
            call    csetPopCnt
            dec     rdi
            jnz     aLp3a
            mov     rbx, rax
            lea     rcx, endTime
            call    QueryPerformanceCounter
            mov     r8, endTime
            sub     r8, startTime
            mov     rdx, rbx
            call    print
            byte    "FullSet=%d, time=%d", nl, 0
            
; Time the naive variant on the full character set:
            
            lea     rcx, startTime
            call    QueryPerformanceCounter

            mov     rdi, repeatCnt
aLp3b:      lea     rsi, fullSet
            call    naiveCsetPopCnt
            dec     rdi
            jnz     aLp3b
            mov     rbx, rax
            lea     rcx, endTime
            call    QueryPerformanceCounter
            mov     r8, endTime
            sub     r8, startTime
            mov     rdx, rbx
            call    print
            byte    "FullSet2=%d, time=%d", nl, 0
            
; Time the popcnt variant on the full character set:
            
            cmp     hasPopCnt, 0
            je      skip3c
            
            lea     rcx, startTime
            call    QueryPerformanceCounter

            mov     rdi, repeatCnt
aLp3c:      lea     rsi, fullSet
            call    popcntInstr
            dec     rdi
            jnz     aLp3c
            mov     rbx, rax
            lea     rcx, endTime
            call    QueryPerformanceCounter
            mov     r8, endTime
            sub     r8, startTime
            mov     rdx, rbx
            call    print
            byte    "FullSet3=%d, time=%d", nl, nl, 0
skip3c:            
            
; Time the SSE variant on the empty character set:
            
            lea     rcx, startTime
            call    QueryPerformanceCounter

            mov     rdi, repeatCnt
aLp4a:      lea     rsi, emptySet
            call    csetPopCnt
            dec     rdi
            jnz     aLp4a
            mov     rbx, rax
            lea     rcx, endTime
            call    QueryPerformanceCounter
            mov     r8, endTime
            sub     r8, startTime
            mov     rdx, rbx
            call    print
            byte    "Empty set=%d, time=%d", nl, 0
            
; Time the naive variant on the empty character set:
            
            lea     rcx, startTime
            call    QueryPerformanceCounter

            mov     rdi, repeatCnt
aLp4b:      lea     rsi, emptySet
            call    naiveCsetPopCnt
            dec     rdi
            jnz     aLp4b
            mov     rbx, rax
            lea     rcx, endTime
            call    QueryPerformanceCounter
            mov     r8, endTime
            sub     r8, startTime
            mov     rdx, rbx
            call    print
            byte    "Empty set2=%d, time=%d", nl, 0
            
; Time the popcnt variant on the empty character set:
            
            cmp     hasPopCnt, 0
            je      skip4c
            
            lea     rcx, startTime
            call    QueryPerformanceCounter

            mov     rdi, repeatCnt
aLp4c:      lea     rsi, emptySet
            call    popcntInstr
            dec     rdi
            jnz     aLp4c
            mov     rbx, rax
            lea     rcx, endTime
            call    QueryPerformanceCounter
            mov     r8, endTime
            sub     r8, startTime
            mov     rdx, rbx
            call    print
            byte    "Empty set2=%d, time=%d", nl, 0
skip4c:                        
                         
allDone:    leave
            pop     rdi
            pop     rsi
            pop     rbx
            ret     ;Returns to caller
asmMain     endp
            end
