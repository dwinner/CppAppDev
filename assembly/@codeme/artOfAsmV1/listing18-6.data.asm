; Generate a set of strings that will hold the
; expected results for each of the substring
; operations. Assuming maxSubstrs = 256, 
; this generates the strings:
;
;   sub_<start index>_<length>
;
; I.e.,
;
;   sub_0_1    = 01h
;   sub_0_2    = 01h 02h
;    .
;    .
;    .
;   sub_0_255  = 01h 02h 03h ... 0FFh
;
;   sub_1_1    = 02h
;   sub_1_2    = 02h 03h
;    .
;    .
;    .
;   sub_1_254  = 02h 03h ... 0FFh
;
; WARNING: Because of the massive number of
; variable declarations this creates, this
; file takes a long time to assemble
; by MASM (remember the DUP bug).
;
; Note that the following compile-time loops
; only generate the strings to hold the values.
; The initial string values are actually created
; byte the program at run-time because generating
; this many different values at compile time is
; just too slow.

            include    string.inc
	include	   listing18-6.inc

 
 	.data           
startNdx    =       0
            while   startNdx lt maxSubstrs
len         =       1
            while   len lt (maxSubstrs-startNdx)
strName     catstr  <sub_>, %startNdx, <_>, %len
            
            staticStr %strName, len+8
            
len         =       len + 1
            endm
startNdx    =       startNdx + 1
            endm
	end
