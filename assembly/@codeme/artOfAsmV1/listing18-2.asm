; Listing 16-2
;
; Simple demonstration of strBgn/strEnd macros

            option  casemap:none
            include getTitle.inc
            include print.inc
            include string.inc

nl          =       10

            .const
ttlStr      byte    "Listing 16-2", 0

            .data
            
; Use a the strBgn/strEnd pair to surround a
; large string constant you want to treat
; as a single string:

            strBgn  longStr, 0
            
            byte    "This is a long", nl
            byte    "string split across",nl
            byte    "multiple source lines", nl
            
            strEnd  longStr 

            .code
            
; Here is the "asmMain" function.
        
            public  asmMain
asmMain     proc
            push    rbx
            push    rbp
            mov     rbp, rsp
            sub     rsp, 56         ;Shadow storage

            lea     rdx, longStr
            call    print
            byte    "%s", nl, 0
             
allDone:    leave
            pop     rbx
            ret     ;Returns to caller
asmMain     endp
            end
