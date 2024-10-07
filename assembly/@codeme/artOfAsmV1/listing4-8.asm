; Listing 4-8
;
; Sample struct initialization example.


         option  casemap:none

nl       =       10

         .const
ttlStr   byte    "Listing 4-8", 0
fmtStr   byte    "aString: maxLen:%d, len:%d, string data:'%s'"
         byte    nl, 0

 
; Define a struct for a string descriptor:
       
strDesc  struct
maxLen   dword   ?
len      dword   ?
strPtr   qword   ?
strDesc  ends

         .data

; Here's the string data we will initialize the
; string descriptor with:

charData byte   "Initial String Data", 0
len      =      lengthof charData ;Includes zero byte

; Create a string descriptor initialized with
; the charData string value:

aString  strDesc {len, len, offset charData}   
        
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

; Display the fields of the string descriptor.

        lea     rcx, fmtStr
        mov     edx, aString.maxLen ;Zero extends!
        mov     r8d, aString.len    ;Zero extends!
        mov     r9,  aString.strPtr
        call    printf

        add     rsp, 48 ;Restore RSP
        ret     ;Returns to caller
asmMain endp
        end