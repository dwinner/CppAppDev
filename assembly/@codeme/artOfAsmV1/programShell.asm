; Comments consist of all text from a
; semicolon character to the end of the line.

; The ".CODE" directive tells MASM that the
; statements following this directive go in
; the section of memory reserved for machine
; instructions (code).

        .CODE

; Here is the "main" function.
; (This example assumes that the
; assembly language program is a
; stand-alone program with its own
; main function.)

main    PROC

; << Machine Instructions go here >>
        
        ret	;Returns to caller
	
main    ENDP

; The END directive marks the end of
; the source file.

        END