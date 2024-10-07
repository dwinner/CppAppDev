; listing 1-3:
; A simple MASM module that contains an empty function to be 
; called by the C++ code in listing 1-2.

        .CODE
        
; The "option casemap:none" statement tells MASM to make all 
; identifiers case sensitive (rather than mapping them to 
; upper case). This is necessary because C++ identifiers are 
; case sensitive.

        option  casemap:none

; Here is the "asmFunc" function.

        public  asmFunc
asmFunc PROC

; Empty function just returns to C++ code
        
        ret     ;Returns to caller
        
asmFunc ENDP
        END