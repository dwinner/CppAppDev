; Listing 4-4
;
; Uninitialized pointer demonstration.
; Note that this program will not
; run properly

        option  casemap:none

nl      =       10

        .const
ttlStr  byte    "Listing 4-4", 0
fmtStr  byte    "Pointer value= %p", nl, 0
        
        .data
ptrVar  qword   ?
        
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
        mov     rdx, ptrVar
        mov     rdx, [rdx]      ; Will crash system
        call    printf


        add     rsp, 48
        ret     ;Returns to caller
        
asmMain endp
        end