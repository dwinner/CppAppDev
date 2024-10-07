; Listing 7-3
;
; Initializing qword values with the
; addresses of statement labels.

        option  casemap:none

            .data
lblsInProc  qword   globalLbl1, globalLbl2  ;From procWLabels
        
            .code


;procWLabels-
; Just a procedure containing private (lexically scoped)
; and global symbols. This really isn't an executable
; procedure.
 
procWLabels proc
privateLbl:
            nop     ;"No operation" just to consume space
            option  noscoped
globalLbl1: jmp     globalLbl2
globalLbl2: nop
            option  scoped
privateLbl2:
            ret
dataInCode  qword   privateLbl, globalLbl1
            qword   globalLbl2, privateLbl2
procWLabels endp
            
            end