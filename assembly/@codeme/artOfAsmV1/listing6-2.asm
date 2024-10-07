; Listing 6-2
;
; Demonstration of various forms of fsub/fsubrl

        option  casemap:none

nl          =       10


            .const
ttlStr      byte    "Listing 6-2", 0
fmtSt0St1   byte    "st(0):%f, st(1):%f", nl, 0
fmtSub1     byte    "fsub: st0:%f", nl, 0
fmtSub2     byte    "fsubp: st0:%f", nl, 0
fmtSub3     byte    "fsub st(1), st(0): st0:%f, st1:%f", nl, 0
fmtSub4     byte    "fsub st(0), st(1): st0:%f, st1:%f", nl, 0
fmtSub5     byte    "fsubp st(1), st(0): st0:%f", nl, 0
fmtSub6     byte    "fsub mem: st0:%f", nl, 0
fmtSub7     byte    "fsubr st(1), st(0): st0:%f, st1:%f", nl, 0
fmtSub8     byte    "fsubr st(0), st(1): st0:%f, st1:%f", nl, 0
fmtSub9     byte    "fsubrp st(1), st(0): st0:%f", nl, 0
fmtSub10    byte    "fsubr mem: st0:%f", nl, 0

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
        
; Demonstrate various fsub instructions:

            mov     rax, qword ptr three
            mov     qword ptr st1, rax
            mov     rax, qword ptr minusTwo
            mov     qword ptr st0, rax
            lea     rcx, fmtSt0St1
            call    printFP

; fsub (same as fsubp)
 
            fld     three
            fld     minusTwo
            fsub                    ;Pops st(0)!
            fstp    st0
            
            lea     rcx, fmtSub1
            call    printFP            
            
; fsubp:
 
            fld     three
            fld     minusTwo
            fsubp                   ;Pops st(0)!
            fstp    st0
            
            lea     rcx, fmtSub2
            call    printFP            
            
; fsub st(1), st(0)
 
            fld     three
            fld     minusTwo
            fsub    st(1), st(0)
            fstp    st0
            fstp    st1
            
            lea     rcx, fmtSub3
            call    printFP            
            
; fsub st(0), st(1)
 
            fld     three
            fld     minusTwo
            fsub    st(0), st(1)
            fstp    st0
            fstp    st1
            
            lea     rcx, fmtSub4
            call    printFP            
            
; fsubp st(1), st(0)
 
            fld     three
            fld     minusTwo
            fsubp   st(1), st(0)
            fstp    st0
            
            lea     rcx, fmtSub5
            call    printFP            
            
; fsub mem64
 
            fld     three
            fsub    minusTwo
            fstp    st0
            
            lea     rcx, fmtSub6
            call    printFP            
            
	
	
; fsubr st(1), st(0)
 
            fld     three
            fld     minusTwo
            fsubr   st(1), st(0)
            fstp    st0
            fstp    st1
            
            lea     rcx, fmtSub7
            call    printFP            
            
; fsubr st(0), st(1)
 
            fld     three
            fld     minusTwo
            fsubr   st(0), st(1)
            fstp    st0
            fstp    st1
            
            lea     rcx, fmtSub8
            call    printFP            
            
; fsubrp st(1), st(0)
 
            fld     three
            fld     minusTwo
            fsubrp  st(1), st(0)
            fstp    st0
            
            lea     rcx, fmtSub9
            call    printFP            
            
; fsubr mem64
 
            fld     three
            fsubr   minusTwo
            fstp    st0
            
            lea     rcx, fmtSub10
            call    printFP            
            
            leave
            ret     ;Returns to caller
        
asmMain     endp
            end