; Listing 16-3            
;
; Dialog box demonstration:

            include \masm32\include64\masm64rt.inc

            .data

msg         byte    "Dialog Box Demonstration",0
DBTitle     byte    "Dialog Box Title", 0
            
            .code
         
;**********************************************************
;
; Here is the "asmMain" function.
        
            public  asmMain
asmMain     proc
            push    rbp
            mov     rbp, rsp
            sub     rsp, 56         ;Shadow storage
            
            xor     rcx, rcx        ;HWin=NULL
            lea     rdx, msg        ;Message to display
            lea     r8, DBTitle     ;Dialog box title
            mov     r9d, MB_OK      ;Has an "OK" button
            call    MessageBox
                         
allDone:    leave
            ret     ;Returns to caller
asmMain     endp
            end
