;12.6.2 - 9

include Irvine32.inc
INCLUDE macros.inc

; .386
; .model flat, stdcall
;.stack 4096
; ExitProcess PROTO, dwExitCode:DWORD

.data 

val1 real8 7.8
val2 real8 3.6
val3 real8 7.1
val4 real8 0.0

.code
main PROC

finit

fld val1
call ShowFPUStack
call Crlf

fadd val3
call ShowFPUStack
call Crlf

fmul val2
call ShowFPUStack
call Crlf

fchs
call ShowFPUStack
call Crlf

fst val4

exit
main ENDP
END main