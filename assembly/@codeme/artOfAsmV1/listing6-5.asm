; Listing 6-5
;
; Demonstration of fcom instructions

        option  casemap:none

nl          =       10


            .const
ttlStr      byte    "Listing 6-5", 0
fcomFmt     byte    "fcom %f < %f is %d", nl, 0
fcomFmt2    byte    "fcom(2) %f < %f is %d", nl, 0
fcomFmt3    byte    "fcom st(1) %f < %f is %d", nl, 0
fcomFmt4    byte    "fcom st(1) (2) %f < %f is %d", nl, 0
fcomFmt5    byte    "fcom mem %f < %f is %d", nl, 0
fcomFmt6    byte    "fcom mem %f (2) < %f is %d", nl, 0
fcompFmt    byte    "fcomp %f < %f is %d", nl, 0
fcompFmt2   byte    "fcomp (2) %f < %f is %d", nl, 0
fcompFmt3   byte    "fcomp st(1) %f < %f is %d", nl, 0
fcompFmt4   byte    "fcomp st(1) (2) %f < %f is %d", nl, 0
fcompFmt5   byte    "fcomp mem %f < %f is %d", nl, 0
fcompFmt6   byte    "fcomp mem (2) %f < %f is %d", nl, 0
fcomppFmt   byte    "fcompp %f < %f is %d", nl, 0
fcomppFmt2  byte    "fcompp (2) %f < %f is %d", nl, 0

three       real8   3.0
zero        real8   0.0
minusTwo    real8   -2.0
        
            .data
st0         real8   ?
st1         real8   ?
        
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
            movzx   r9, al
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

; fcom demo
        
            xor     eax, eax
            fld     three
            fld     zero
            fcom
            fstsw   ax
            sahf
            setb    al
            fstp    st0
            fstp    st1
            lea     rcx, fcomFmt
            call    printFP
            
; fcom demo 2
        
            xor     eax, eax
            fld     zero
            fld     three
            fcom
            fstsw   ax
            sahf
            setb    al
            fstp    st0
            fstp    st1
            lea     rcx, fcomFmt2
            call    printFP

; fcom st(i) demo
        
            xor     eax, eax
            fld     three
            fld     zero
            fcom    st(1)
            fstsw   ax
            sahf
            setb    al
            fstp    st0
            fstp    st1
            lea     rcx, fcomFmt3
            call    printFP
            
; fcom st(i) demo 2
        
            xor     eax, eax
            fld     zero
            fld     three
            fcom    st(1)
            fstsw   ax
            sahf
            setb    al
            fstp    st0
            fstp    st1
            lea     rcx, fcomFmt4
            call    printFP
            
; fcom mem64 demo
        
            xor     eax, eax
            fld     three           ;Never on stack so
            fstp    st1             ; copy for output
            fld     zero
            fcom    three
            fstsw   ax
            sahf
            setb    al
            fstp    st0
            lea     rcx, fcomFmt5
            call    printFP
                        
; fcom mem64 demo 2
        
            xor     eax, eax
            fld     zero            ;Never on stack so
            fstp    st1             ; copy for output
            fld     three
            fcom    zero
            fstsw   ax
            sahf
            setb    al
            fstp    st0
            lea     rcx, fcomFmt6
            call    printFP
                        
; fcomp demo
        
            xor     eax, eax
            fld     zero
            fld     three
            fst     st0             ;Because this gets popped
            fcomp
            fstsw   ax
            sahf
            setb    al
            fstp    st1
            lea     rcx, fcompFmt
            call    printFP
                        
; fcomp demo 2
        
            xor     eax, eax
            fld     three
            fld     zero
            fst     st0             ;Because this gets popped
            fcomp
            fstsw   ax
            sahf
            setb    al
            fstp    st1
            lea     rcx, fcompFmt2
            call    printFP
                        
; fcomp demo 3
        
            xor     eax, eax
            fld     zero
            fld     three
            fst     st0             ;Because this gets popped
            fcomp   st(1)
            fstsw   ax
            sahf
            setb    al
            fstp    st1
            lea     rcx, fcompFmt3
            call    printFP
                        
; fcomp demo 4
        
            xor     eax, eax
            fld     three
            fld     zero
            fst     st0             ;Because this gets popped
            fcomp   st(1)
            fstsw   ax
            sahf
            setb    al
            fstp    st1
            lea     rcx, fcompFmt4
            call    printFP
                        
; fcomp demo 5
        
            xor     eax, eax
            fld     three
            fstp    st1
            fld     zero
            fst     st0             ;Because this gets popped
            fcomp   three
            fstsw   ax
            sahf
            setb    al
            lea     rcx, fcompFmt5
            call    printFP
                        
; fcomp demo 6
        
            xor     eax, eax
            fld     zero
            fstp    st1
            fld     three
            fst     st0             ;Because this gets popped
            fcomp   zero
            fstsw   ax
            sahf
            setb    al
            lea     rcx, fcompFmt6
            call    printFP
                        
; fcompp demo
        
            xor     eax, eax
            fld     zero
            fst     st1             ;Because this gets popped
            fld     three
            fst     st0             ;Because this gets popped
            fcompp  
            fstsw   ax
            sahf
            setb    al
            lea     rcx, fcomppFmt
            call    printFP
                        
; fcompp demo 2
        
            xor     eax, eax
            fld     three
            fst     st1             ;Because this gets popped
            fld     zero
            fst     st0             ;Because this gets popped
            fcompp  
            fstsw   ax
            sahf
            setb    al
            lea     rcx, fcomppFmt2
            call    printFP
                        
            leave
            ret     ;Returns to caller
        
asmMain     endp
            end