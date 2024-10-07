; Listing 6-1
;
; Demonstration of various forms of fadd

        option  casemap:none

nl          =       10


            .const
ttlStr      byte    "Listing 6-1", 0
fmtSt0St1   byte    "st(0):%f, st(1):%f", nl, 0
fmtAdd1     byte    "fadd: st0:%f", nl, 0
fmtAdd2     byte    "faddp: st0:%f", nl, 0
fmtAdd3     byte    "fadd st(1), st(0): st0:%f, st1:%f", nl, 0
fmtAdd4     byte    "fadd st(0), st(1): st0:%f, st1:%f", nl, 0
fmtAdd5     byte    "faddp st(1), st(0): st0:%f", nl, 0
fmtAdd6     byte    "fadd mem: st0:%f", nl, 0

zero        real8   0.0
one         real8   1.0
two         real8   2.0
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
        
; Demonstrate various fadd instructions:

            mov     rax, qword ptr one
            mov     qword ptr st1, rax
            mov     rax, qword ptr minusTwo
            mov     qword ptr st0, rax
            lea     rcx, fmtSt0St1
            call    printFP

; fadd (same as faddp)
 
            fld     one
            fld     minusTwo
            fadd                    ;Pops st(0)!
            fstp    st0
            
            lea     rcx, fmtAdd1
            call    printFP            
            
; faddp:
 
            fld     one
            fld     minusTwo
            faddp                   ;Pops st(0)!
            fstp    st0
            
            lea     rcx, fmtAdd2
            call    printFP            
            
; fadd st(1), st(0)
 
            fld     one
            fld     minusTwo
            fadd    st(1), st(0)
            fstp    st0
            fstp    st1
            
            lea     rcx, fmtAdd3
            call    printFP            
            
; fadd st(0), st(1)
 
            fld     one
            fld     minusTwo
            fadd    st(0), st(1)
            fstp    st0
            fstp    st1
            
            lea     rcx, fmtAdd4
            call    printFP            
            
; faddp st(1), st(0)
 
            fld     one
            fld     minusTwo
            faddp   st(1), st(0)
            fstp    st0
            
            lea     rcx, fmtAdd5
            call    printFP            
            
; faddp mem64
 
            fld     one
            fadd    two
            fstp    st0
            
            lea     rcx, fmtAdd6
            call    printFP            
            
            leave
            ret     ;Returns to caller
        
asmMain     endp
            end