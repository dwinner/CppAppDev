; Listing 7-1
;
; Demonstration of local symbols.
; Note that this program will not
; compile; it fails with an
; undefined symbol error.

        option  casemap:none

        
            .code

hasLocalLbl proc

localStmLbl:
            ret
hasLocalLbl endp


; Here is the "asmMain" function.

        
asmMain     proc

asmLocal:	jmp	asmLocal	;This is okay
	jmp	localStmtLbl	;Undefined in asmMain
asmMain     endp
            end