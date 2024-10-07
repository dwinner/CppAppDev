; Listing 5-9
;
; Demonstrate obtaining the address
; of a variable using the lea instruction

            option  casemap:none

            .data
staticVar   dword   ?

            .code
            externdef someFunc:proc
            
getAddress  proc

            lea     rcx, staticVar
            call    someFunc

            ret
getAddress  endp

            end