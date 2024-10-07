; Listing 6-4
;
; Demonstration of various forms of fdiv/fdivr

        option  casemap:none

nl          =       10


            .const
ttlStr      byte    "Listing 6-4", 0
fmtSt0St1   byte    "st(0):%f, st(1):%f", nl, 0
fmtDiv1     byte    "fdiv: st0:%f", nl, 0
fmtDiv2     byte    "fdivp: st0:%f", nl, 0
fmtDiv3     byte    "fdiv st(1), st(0): st0:%f, st1:%f", nl, 0
fmtDiv4     byte    "fdiv st(0), st(1): st0:%f, st1:%f", nl, 0
fmtDiv5     byte    "fdivp st(1), st(0): st0:%f", nl, 0
fmtDiv6     byte    "fdiv mem: st0:%f", nl, 0
fmtDiv7     byte    "fdivr st(1), st(0): st0:%f, st1:%f", nl, 0
fmtDiv8     byte    "fdivr st(0), st(1): st0:%f, st1:%f", nl, 0
fmtDiv9     byte    "fdivrp st(1), st(0): st0:%f", nl, 0
fmtDiv10    byte    "fdivr mem: st0:%f", nl, 0

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
        
; Demonstrate various fdiv instructions:

            mov     rax, qword ptr three
            mov     qword ptr st1, rax
            mov     rax, qword ptr minusTwo
            mov     qword ptr st0, rax
            lea     rcx, fmtSt0St1
            call    printFP

; fdiv (same as fdivp)
 
            fld     three
            fld     minusTwo
            fdiv                    ;Pops st(0)!
            fstp    st0
            
            lea     rcx, fmtDiv1
            call    printFP            
            
; fdivp:
 
            fld     three
            fld     minusTwo
            fdivp                   ;Pops st(0)!
            fstp    st0
            
            lea     rcx, fmtDiv2
            call    printFP            
            
; fdiv st(1), st(0)
 
            fld     three
            fld     minusTwo
            fdiv    st(1), st(0)
            fstp    st0
            fstp    st1
            
            lea     rcx, fmtDiv3
            call    printFP            
            
; fdiv st(0), st(1)
 
            fld     three
            fld     minusTwo
            fdiv    st(0), st(1)
            fstp    st0
            fstp    st1
            
            lea     rcx, fmtDiv4
            call    printFP            
            
; fdivp st(1), st(0)
 
            fld     three
            fld     minusTwo
            fdivp   st(1), st(0)
            fstp    st0
            
            lea     rcx, fmtDiv5
            call    printFP            
            
; fdiv mem64
 
            fld     three
            fdiv    minusTwo
            fstp    st0
            
            lea     rcx, fmtDiv6
            call    printFP            
            
            
            
; fdivr st(1), st(0)
 
            fld     three
            fld     minusTwo
            fdivr   st(1), st(0)
            fstp    st0
            fstp    st1
            
            lea     rcx, fmtDiv7
            call    printFP            
            
; fdivr st(0), st(1)
 
            fld     three
            fld     minusTwo
            fdivr   st(0), st(1)
            fstp    st0
            fstp    st1
            
            lea     rcx, fmtDiv8
            call    printFP            
            
; fdivrp st(1), st(0)
 
            fld     three
            fld     minusTwo
            fdivrp  st(1), st(0)
            fstp    st0
            
            lea     rcx, fmtDiv9
            call    printFP            
            
; fdivr mem64
 
            fld     three
            fdivr   minusTwo
            fstp    st0
            
            lea     rcx, fmtDiv10
            call    printFP            
            
            leave
            ret     ;Returns to caller
        
asmMain     endp
            end