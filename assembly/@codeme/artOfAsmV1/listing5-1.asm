; Listing 5-1
;
; Simple procedure call example.


         option  casemap:none

nl       =       10

         .const
ttlStr   byte    "Listing 5-1", 0

 
        .data
dwArray dword   256 dup (1)

        
        .code

; Return program title to C++ program:

         public getTitle
getTitle proc
         lea rax, ttlStr
         ret
getTitle endp



; Here is the user-written procedure
; that zeros out a buffer.

zeroBytes proc
          mov eax, 0
          mov edx, 256
repeatlp: mov [rcx+rdx*4-4], eax
          dec rdx
          jnz repeatlp
          ret
zeroBytes endp


; Here is the "asmMain" function.

        public  asmMain
asmMain proc

; "Magic" instruction offered without
; explanation at this point:

        sub     rsp, 48

        lea     rcx, dwArray
        call    zeroBytes 

        add     rsp, 48 ;Restore RSP
        ret     ;Returns to caller
asmMain endp
        end