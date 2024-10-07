; Listing 5-5
;
; Popping a return address by mistake


               option  casemap:none

nl             =       10

              .const
ttlStr        byte    "Listing 5-5", 0
calling       byte    "Calling proc2", nl, 0
call1         byte    "Called proc1", nl, 0
rtn1          byte    "Returned from proc 1", nl, 0
rtn2          byte    "Returned from proc 2", nl, 0
        
              .code
              externdef printf:proc

; Return program title to C++ program:

              public getTitle
getTitle      proc
              lea rax, ttlStr
              ret
getTitle      endp


; proc1 - Gets called by proc2, but returns
;         back to the main program.

proc1         proc
              pop   rcx     ;Pops return address off stack
              ret
proc1         endp

proc2         proc
              call  proc1   ;Will never return

; This code never executes because the call to proc1
; pops the return address off the stack and returns
; directly to asmMain.
            
              sub   rsp, 40
              lea   rcx, rtn1
              call  printf
              add   rsp, 40
              ret
proc2         endp

; Here is the "asmMain" function.

              public asmMain
asmMain       proc

              sub   rsp, 40

              lea   rcx, calling
              call  printf
              
              call  proc2
              lea   rcx, rtn2
              call  printf 
              
              add   rsp, 40
              ret           ;Returns to caller
asmMain       endp
              end