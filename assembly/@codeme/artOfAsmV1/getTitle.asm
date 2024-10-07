; getTitle.asm (listing 15-3)
;
; The getTitle function converted to
; an assembly unit.
;
; Return program title to C++ program:

            include aoalib.inc
            
            .code
getTitle    proc
            lea     rax, ttlStr
            ret
getTitle    endp
            end

