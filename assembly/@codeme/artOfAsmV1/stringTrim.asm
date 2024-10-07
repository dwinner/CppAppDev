; stringTrim.asm
;
; Deletes leading and trailing white space characters
; from a string.
;
; RDI-      Pointer to string.

            option  casemap:none
            include string.inc
            include aoalib.inc

            .code
stringTrim  proc
            call    deleteTrailingWS
            jmp     deleteWS
stringTrim  endp
            end
