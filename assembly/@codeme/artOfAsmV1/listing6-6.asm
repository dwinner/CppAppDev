; Listing 6-6
;
; Demonstration of fcomi and fcomip instructions

        option  casemap:none

nl          =       10


            .const
ttlStr      byte    "Listing 6-6", 0
fcomiFmt    byte    "fcomi %f < %f is %d", nl, 0
fcomiFmt2   byte    "fcomi(2) %f < %f is %d", nl, 0
fcomipFmt   byte    "fcomip %f < %f is %d", nl, 0
fcomipFmt2  byte    "fcomip (2) %f < %f is %d", nl, 0

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

; Test to see if 0 < 3
; Note: st(0) contains zero, st(2) contains three
        
            xor     eax, eax
            fld     three
            fld     zero
            fcomi   st(0), st(1)
            setb    al
            fstp    st0
            fstp    st1
            lea     rcx, fcomiFmt
            call    printFP
            
; Test to see if 3 < 0
; Note: st(0) contains zero, st(2) contains three
        
            xor     eax, eax
            fld     zero
            fld     three
            fcomi   st(0), st(1)
            setb    al
            fstp    st0
            fstp    st1
            lea     rcx, fcomiFmt2
            call    printFP
                        
; Test to see if 3 < 0
; Note: st(0) contains zero, st(2) contains three
        
            xor     eax, eax
            fld     zero
            fld     three
            fst     st0             ;Because this gets popped
            fcomip   st(0), st(1)
            setb    al
            fstp    st1
            lea     rcx, fcomipFmt
            call    printFP
                        
; Test to see if 0 < 3
; Note: st(0) contains zero, st(2) contains three
        
            xor     eax, eax
            fld     three
            fld     zero
            fst     st0             ;Because this gets popped
            fcomip   st(0), st(1)
            setb    al
            fstp    st1
            lea     rcx, fcomipFmt2
            call    printFP
                        
            leave
            ret     ;Returns to caller
        
asmMain     endp
            end