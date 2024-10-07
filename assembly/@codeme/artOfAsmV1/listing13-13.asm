; Listing 13-13
;
; This is a compile-time program.
; It does not generate any executable code.
;

        option  casemap:none

genArray    macro   arrayName, elements
            local   index, eleName, getName
            
; Loop over each element of the array:

index       =       0
            while   index lt &elements
            
; Generate a textequ statement to define a single
; element of the array, e.g.,
;
;  aryXX = 0
;
; where "XX" is the index (0..(elements-1))

eleName     catstr  <&arrayName>,%index,< = 0>

; Expand the text just created with the catstr directive

            eleName
            
; Move on to next array index:

index       =       index + 1
            endm    ;while
            
; Create a macro function to retrieve a value from
; the array:

getName     catstr  <&arrayName>,<_get>

getName     macro   theIndex
            local   element
element     catstr  <&arrayName>,%theIndex
            exitm   <element>
            endm
            
; Create a macro to assign a value to
; an array element


setName     catstr  <&arrayName>,<_set>

setName     macro   theIndex, theValue
            local   assign
assign      catstr  <&arrayName>, %theIndex, < = >, %theValue
            assign
            endm


            endm    ;genArray

; mout-
;
;  Replacement for echo. Allows "%" operator
; in operand field to expand text symbols.

mout        macro   valToPrint
            local   cmd
cmd         catstr  <echo >, <valToPrint>
            cmd
            endm
            
	
; Create an array ("ary") with ten elements:

            genArray ary, 10

            
; Initialize each element of the array to
; its index value:

index	= 0
	while	index lt 10
	ary_set	index, index
index	=	index + 1
	endm
	
; Print out the array values:

index	= 	0
	while	index lt 10
	
value	=	ary_get(index)
	mout	ary[%index] = %value
index	=	index + 1
	endm
	
            end
