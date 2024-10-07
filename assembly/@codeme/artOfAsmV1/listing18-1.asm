; Listing 18-1
;
; Simple demonstration of strDcl macro

            option     casemap:none
            include    aoalib.inc
            include    string.inc
	includelib aoalib.lib
        

nl          =       10


            .const
ttlStr      byte    "Listing 18-1", 0
            

            .data
            
; Allocate storage for an empty string:

            staticStr empty, 25
            
; Allocate storage for a string and initialize
; it with "Hello, World!":

            strDcl  hello, 25, "Hello, World!"

            .code
            
; Here is the "asmMain" function.
        
            public  asmMain
asmMain     proc
            push    rbx
            push    rbp
            mov     rbp, rsp
            sub     rsp, 56         ;Shadow storage

            lea     rdx, hello
            lea     r8, empty
            call    print
            byte    "hello:'%s'", nl
            byte    "empty:'%s'", nl, 0
             
allDone:    leave
            pop     rbx
            ret     ;Returns to caller
asmMain     endp
            end
