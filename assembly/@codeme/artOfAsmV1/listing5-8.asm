; Listing 5-8
;
; Demonstrate obtaining the address
; of a static variable using offset
; operator.


            option  casemap:none

            .data
staticVar   dword   ?

            .code
            externdef someFunc:proc
            
getAddress  proc

            mov     rcx, offset staticVar
            call    someFunc

            ret
getAddress  endp

            end