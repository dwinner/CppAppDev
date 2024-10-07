; Listing 13-2
;
; CTL while loop demonstration program

        option  casemap:none

nl          =       10


            .const
ttlStr      byte    "Listing 13-2", 0
           

            .data
ary         dword   2, 3, 5, 8, 13


            include getTitle.inc
            include print.inc
            
            .code

            
; Here is the "asmMain" function.

        
            public  asmMain
asmMain     proc
            push    rbx
            push    rbp
            mov     rbp, rsp
            sub     rsp, 56         ;Shadow storage

i           =       0            
            while   i LT 5  

            mov     edx, i          ;This is a constant!
            mov     r8d, ary[ i*4 ] ;Index is a constant
            call    print
            byte    "array[ %d ] = %d", nl, 0
              
i           =       i + 1
            endm 

             
allDone:    leave
            pop     rbx
            ret     ;Returns to caller
asmMain     endp
            end
