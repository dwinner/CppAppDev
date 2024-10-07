; Listing 4-2
;
; // Pointer constant demonstration

        option  casemap:none

nl      =       10

        .const
ttlStr  byte    "Listing 4-2", 0
fmtStr  byte    "pb's value is %ph", nl
        byte    "*pb's value is %d", nl, 0
        
        .data
b       byte    0
        byte    1, 2, 3, 4, 5, 6, 7
        
pb      textequ <offset b[2]>
        
        .code
        externdef printf:proc


; Return program title to C++ program:

         public getTitle
getTitle proc
         lea rax, ttlStr
         ret
getTitle endp

; Here is the "asmMain" function.

        
        public  asmMain
asmMain proc

; "Magic" instruction offered without
; explanation at this point:

        sub     rsp, 48

        lea     rcx, fmtStr
        mov     rdx, pb
        movzx   r8, byte ptr [rdx]
        call    printf
        
        add     rsp, 48
        ret     ;Returns to caller
        
asmMain endp
        end