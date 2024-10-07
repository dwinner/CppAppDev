	option	casemap:none	;Make symbols case sensitive
	extrn printf:proc

	.CODE
hwStr	byte	"Hello World!",0ah, 0

asmMain	PROC
	
; For reasons this book will get into several
; chapters from now, we have to reduce the size
; of the stack by 56 bytes.

	sub	rsp, 56
	
;	lea	ecx, hwStr
;	call	printf
		

; Restore the stack pointer to its original
; value before returning to C++ code.
			
	add	rsp, 56
	ret
asmMain	ENDP
	END