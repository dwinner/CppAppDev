; Listing 5-2
;
; A procedure without a RET instruction


               option  casemap:none

nl             =       10

              .const
ttlStr        byte    "Listing 5-2", 0
fpMsg         byte    "followingProc was called", nl, 0
        
              .code
              externdef printf:proc

; Return program title to C++ program:

              public getTitle
getTitle      proc
              lea rax, ttlStr
              ret
getTitle      endp



; noRet-
; 
;  Demonstrates what happens when a procedure
; does not have a return instruction.

noRet         proc
noRet         endp

followingProc proc
              sub  rsp, 28h
              lea  rcx, fpMsg
              call printf
              add  rsp, 28h
              ret
followingProc endp


; Here is the "asmMain" function.

              public  asmMain
asmMain       proc
              push    rbx
                
; "Magic" instruction offered without
; explanation at this point:

              sub     rsp, 40

              call    noRet
              
              add     rsp, 40
              pop     rbx
              ret     ;Returns to caller
asmMain       endp
              end