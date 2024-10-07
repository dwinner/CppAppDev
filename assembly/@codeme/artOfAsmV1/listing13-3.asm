; Listing 13-3
;
; Equivalent program to Listing13-2

        option  casemap:none

nl          =       10

            .const
ttlStr      byte    "Listing 13-3", 0
           

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


            mov     edx, 0         ;This is a constant!
            mov     r8d, ary[ 0]   ;Index is a constant
            call    print
            byte    "array[ %d ] = %d", nl, 0 

            mov     edx, 1          ;This is a constant!
            mov     r8d, ary[ 4 ]   ;Index is a constant
            call    print
            byte    "array[ %d ] = %d", nl, 0 

            mov     edx, 2         ;This is a constant!
            mov     r8d, ary[ 8]   ;Index is a constant
            call    print
            byte    "array[ %d ] = %d", nl, 0 

            mov     edx, 3          ;This is a constant!
            mov     r8d, ary[ 12]   ;Index is a constant
            call    print
            byte    "array[ %d ] = %d", nl, 0 

            mov     edx, 4          ;This is a constant!
            mov     r8d, ary[ 16 ]   ;Index is a constant
            call    print
            byte    "array[ %d ] = %d", nl, 0 

             
allDone:    leave
            pop     rbx
            ret     ;Returns to caller
asmMain     endp
            end
