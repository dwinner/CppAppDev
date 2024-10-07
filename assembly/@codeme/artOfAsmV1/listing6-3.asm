; Listing 6-3
;
; Demonstration of various forms of fmul

        option  casemap:none

nl          =       10


            .const
ttlStr      byte    "Listing 6-3", 0
fmtSt0St1   byte    "st(0):%f, st(1):%f", nl, 0
fmtMul1     byte    "fmul: st0:%f", nl, 0
fmtMul2     byte    "fmulp: st0:%f", nl, 0
fmtMul3     byte    "fmul st(1), st(0): st0:%f, st1:%f", nl, 0
fmtMul4     byte    "fmul st(0), st(1): st0:%f, st1:%f", nl, 0
fmtMul5     byte    "fmulp st(1), st(0): st0:%f", nl, 0
fmtMul6     byte    "fmul mem: st0:%f", nl, 0

zero        real8   0.0
three       real8   3.0
minusTwo    real8   -2.0
        
            .data
st0         real8   0.0
st1         real8   0.0
        
            .code
            externdef printf:proc
            
; Return program title to C++ program:

            public  getTitle
getTitle    proc
            lea     rax, ttlStr
            ret
getTitle    endp


; printFP- Prints values of st0 and (possibly) st1.
;          Caller must pass in ptr to fmtStr in RCX.

printFP     proc
            sub     rsp, 40
            
; For varargs (e.g., printf call), double
; values must appear in RDX and R8 rather
; than XMM1, XMM2.
; Note: if only one double arg in format
; string, printf call will ignore 2nd
; value in R8.

            mov     rdx, qword ptr st0
            mov     r8, qword ptr st1
            call    printf
            add     rsp, 40
            ret
printFP     endp

            
            
; Here is the "asmMain" function.

        
            public  asmMain
asmMain     proc
            push    rbp
            mov     rbp, rsp
            sub     rsp, 48   ;Shadow storage
        
; Demonstrate various fmul instructions:

            mov     rax, qword ptr three
            mov     qword ptr st1, rax
            mov     rax, qword ptr minusTwo
            mov     qword ptr st0, rax
            lea     rcx, fmtSt0St1
            call    printFP

; fmul (same as fmulp)
 
            fld     three
            fld     minusTwo
            fmul                    ;Pops st(0)!
            fstp    st0
            
            lea     rcx, fmtMul1
            call    printFP            
            
; fmulp:
 
            fld     three
            fld     minusTwo
            fmulp                   ;Pops st(0)!
            fstp    st0
            
            lea     rcx, fmtMul2
            call    printFP            
            
; fmul st(1), st(0)
 
            fld     three
            fld     minusTwo
            fmul    st(1), st(0)
            fstp    st0
            fstp    st1
            
            lea     rcx, fmtMul3
            call    printFP            
            
; fmul st(0), st(1)
 
            fld     three
            fld     minusTwo
            fmul    st(0), st(1)
            fstp    st0
            fstp    st1
            
            lea     rcx, fmtMul4
            call    printFP            
            
; fmulp st(1), st(0)
 
            fld     three
            fld     minusTwo
            fmulp   st(1), st(0)
            fstp    st0
            
            lea     rcx, fmtMul5
            call    printFP            
            
; fmulp mem64
 
            fld     three
            fmul    minusTwo
            fstp    st0
            
            lea     rcx, fmtMul6
            call    printFP            
            
            leave
            ret     ;Returns to caller
        
asmMain     endp
            end