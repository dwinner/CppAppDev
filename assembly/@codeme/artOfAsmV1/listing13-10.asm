; Listing 13-10
;
; This is a compile-time program.
; It does not generate any executable code.
;
; Several useful macro functions:
;
; mout-	Like echo, but allows "%" operators.
;
; testStr-	Tests an operand to see if it
;	is a string literal constant
;
; @sizestr-	Handles missing MASM function
;
; isDigit-	Tests first character of its
;	argument to see if it's a decimal
;	digit.
;
; isSign-	Tests first character of its
;	argument to see if it's a '+'
;	or a '-' character.
;
; extract1st- Removes the first character
;	from its argument (side effect)
;	and returns that character as
;	the function result.
;
; getReal-	Parses the argument and returns
;	true if it is a reasonable-
;	looking real constant.


        option  casemap:none


; mout-
;
;  Replacement for echo. Allows "%" operator
; in operand field to expand text symbols.

mout        macro   valToPrint
            local   cmd
cmd         catstr  <echo >, <valToPrint>
            cmd
            endm

; testStr is a macro function that tests its
; operand to see if it is a string literal.
            
testStr     macro   strParm
            local   firstChar
            
            ifnb    <strParm>
firstChar   substr  <strParm>, 1, 1

            ifidn   firstChar,<!">
            
; First character was '"', so assume it's
; a string.

            exitm   <1>
            endif   ;ifidn
            endif   ;ifnb
            
; If we get to this point in the macro
; we definitely do not have a string.

            exitm   <0>
            endm
            

; @sizestr-
;
;  Replacement for the MASM function
; which doesn't seem to work

@sizestr    macro   theStr
            local   theLen
theLen      sizestr <theStr>
            exitm   <&theLen>
            endm	;@sizestr


	
; isDigit-
;
;   Macro function that returns true if the
; first character of its parameter is a
; decimal digit.

isDigit     macro   parm
            local   FirstChar
            if      @sizestr(%parm) eq 0
            exitm   <0>
            endif
            
FirstChar   substr  parm, 1, 1
	ifidn	FirstChar,<0>
	exitm	<1>
	endif
	ifidn	FirstChar,<1>
	exitm	<1>
	endif
	ifidn	FirstChar,<2>
	exitm	<1>
	endif
	ifidn	FirstChar,<3>
	exitm	<1>
	endif
	ifidn	FirstChar,<4>
	exitm	<1>
	endif
	ifidn	FirstChar,<5>
	exitm	<1>
	endif
	ifidn	FirstChar,<6>
	exitm	<1>
	endif
	ifidn	FirstChar,<7>
	exitm	<1>
	endif
	ifidn	FirstChar,<8>
	exitm	<1>
	endif
	ifidn	FirstChar,<9>
	exitm	<1>
	endif
	exitm	<0>
            endm


; isSign-
;
;   Macro function that returns true if the
; first character of its parameter is a
; + or -

isSign      macro   parm
            local   FirstChar
            ifb     <parm>
            exitm   <0>
            endif
            
FirstChar   substr  parm, 1, 1
            ifidn   FirstChar, <+>
            exitm   <1>
            endif
            ifidn   FirstChar, <->
            exitm   <1>
            endif
            exitm   <0>
            endm



; isE-
;
;   Macro function that returns true if the
; first character of its parameter is a
; e or E

isE         macro   parm
            local   FirstChar
            if      @sizestr(%parm) eq 0
            exitm   <0>
            endif
            
FirstChar   substr  parm, 1, 1
            ifidni   FirstChar, <e>
            exitm   <1>
            endif
            exitm   <0>
            endm
            
; extract1st
;
;  Macro that gets passed a text variable.
; Extracts the first character (if any)
; and removes that character from the
; argument.

extract1st  macro   parm
            local   FirstChar
            ifb     <%parm>
            exitm   <>
            endif
FirstChar   substr  parm, 1, 1
            if      @sizestr(%parm) GE 2
parm        substr  parm, 2
            else
parm        textequ <>
            endif

            exitm   <FirstChar>
            endm
            
            
            
; getExp-
;
;  Given an input string that (presumably)
; holds an exponent value, this function
; returns the following:
;
; <0>:      Invalid text (error)
; <1>:      Either a valid exponent
;           is present, or no exponent
;           at all is present.
;
; Note that a blank input string is legal.
; Exponents are optional.
;
; Sign :=(+|-) 
; Digit ::= [0-9]
; Exp ::= (e|E) Sign? Digit Digit? Digit? Digit?

getExp      macro   parm
            local   curChar
            
; Return success if no exponent present

            if      @sizestr(%parm) eq 0
            exitm   <1>
            endif

; Extract the next character, return failure
; if it is not an 'e' or 'E' character:
            
curChar     textequ extract1st(parm)
            if      isE(curChar) eq 0
            exitm   <0>
            endif

; Extract the next character:
            
curChar     textequ extract1st(parm)

; If an optional sign character appears,
; remove it from the string:

            if      isSign( curChar )
curChar     textequ extract1st(parm)        ;Skip sign char
            endif   ;isSign
            
; Must have at least one digit

            if      isDigit( curChar ) eq 0
            exitm   <0>
            endif
            
; Optionally, we can have up to three additional digits

            if      @sizestr(%parm) gt 0
curChar     textequ extract1st(parm)        ;Skip 1st digit
            if      isDigit( curChar ) eq 0
            exitm   <0>
            endif
            endif

            if      @sizestr(%parm) gt 0
curChar     textequ extract1st(parm)        ;Skip 2nd digit
            if      isDigit( curChar ) eq 0
            exitm   <0>
            endif
            endif

            if      @sizestr(%parm) gt 0
curChar     textequ extract1st(parm)        ;Skip 3rd digit
            if      isDigit( curChar ) eq 0
            exitm   <0>
            endif
            endif

; If we get to this point, we have a valid exponent.

            exitm   <1>     
            endm    ;getExp
            
; getMant
;
;
;  Given an input string that (presumably)
; holds a mantissa value, this function
; returns the following:
;
; <0>:      Invalid text (error)
; <1>:      A valid mantissa
;
; Note that processing stops on the first
; illegal character (or the second decimal
; point, if it finds 2 of them). 
; As long as the string contains at least 1 digit, 
; this function returns true. 
;
; Digit ::= [0-9]
; Mantissa ::= (Digit)+ | '.' Digit)+ | (Digit)+ '.' Digit*

getMant     macro   parm
            local   curChar, sawDecPt, rpt
sawDecPt    =       0
curChar     textequ extract1st(parm)        ;get 1st char
            ifidn   curChar, <.>            ;Check for dec pt
sawDecPt    =       1
curChar     textequ extract1st(parm)        ;get 2nd char
            endif
            
; Must have at least one digit:

            if      isDigit( curChar ) eq 0
            exitm   <0>                     ;Bad mantissa
            endif

            
; Process zero or more digits. If we haven't already
; seen a decimal point, allow exactly one of those.
;
; Do loop at least once if there is at least one
; character left in parm:

rpt         =       @sizestr(%parm)
            while   rpt
            
; Get the 1st char from parm and see if
; it is a decimal point or a digit:

curChar     substr  parm, 1, 1
            ifidn   curChar, <.>
rpt         =       sawDecPt eq 0
sawDecPt    =       1
            else
rpt         =       isDigit(curChar)
            endif

; If char was legal, then extract it from parm:

            if      rpt
curChar     textequ extract1st(parm)        ;get next char
            endif
            
; Repeat as long as we have more chars and the
; current character is legal:

rpt         =       rpt and (@sizestr(%parm) gt 0)
            endm    ;while
            
; If we've seen at least one digit, we've got a valid
; mantissa. We've stopped processing on the first 
; character that is not a digit or the 2nd '.' char.

            exitm   <1>
            endm    ;getMant
            

; getReal-
;
;   Parses a real constant.
;
; Returns:
;    true:  If the parameter contains a syntactically
;           correct real number (and no extra characters).
;    false: If there are any illegal characters or
;           other syntax errors in the numeric string.
;
; Sign :=(+|-) 
; Digit ::= [0-9]
; Mantissa ::= (Digit)+ | '.' Digit)+ | (Digit)+ '.' Digit*
; Exp ::= (e|E) Sign? Digit Digit? Digit? Digit?
; Real ::= Sign? Mantissa Exp?

getReal     macro   origParm
            local   parm, curChar, result
            
; Make a copy of the parameter so we don't
; delete the characters in the original string

parm        textequ &origParm

; Must have at least one character:

            ifb     parm
            exitm   <0>
            endif
            
; Extract the optional sign:

            if      isSign(parm)
curChar     textequ extract1st(parm)        ;skip sign char
            endif
            
; Get the required mantissa:

            if      getMant(parm) eq 0
            exitm   <0>                     ;Bad mantissa
            endif

; Extract the optional exponent:

result      textequ getExp(parm)    
            exitm   <&result>       
            
            endm    ;getReal
	
	
; Test strings and invocations for the
; getReal macro;

            
mant1       textequ <1>
mant2       textequ <.2>
mant3       textequ <3.4>
rv4         textequ <1e1>
rv5         textequ <1.e1>
rv6         textequ <1.0e1>
rv7         textequ <1.0e+1>
rv8         textequ <1.0e-1>
rv9         textequ <1.0e12>
rva         textequ <1.0e1234>
rvb         textequ <1.0E123>
rvc         textequ <1.0E+1234>
rvd         textequ <1.0E-1234>
rve         textequ <-1.0E-1234>
rvf         textequ <+1.0E-1234>
badr1       textequ <>
badr2       textequ <a>
badr3       textequ <1.1.0>
badr4       textequ <e1>
badr5       textequ <1ea1>
badr6       textequ <1e1a>

% echo get_Real(mant1) = getReal(mant1) 
% echo get_Real(mant2) = getReal(mant2)
% echo get_Real(mant3) = getReal(mant3)
% echo get_Real(rv4)   = getReal(rv4)
% echo get_Real(rv5)   = getReal(rv5)
% echo get_Real(rv6)   = getReal(rv6)
% echo get_Real(rv7)   = getReal(rv7)
% echo get_Real(rv8)   = getReal(rv8)
% echo get_Real(rv9)   = getReal(rv9)
% echo get_Real(rva)   = getReal(rva)
% echo get_Real(rvb)   = getReal(rvb)
% echo get_Real(rvc)   = getReal(rvc)
% echo get_Real(rvd)   = getReal(rvd)
% echo get_Real(rve)   = getReal(rve)
% echo get_Real(rvf)   = getReal(rvf)
% echo get_Real(badr1) = getReal(badr1)
% echo get_Real(badr2) = getReal(badr2)
% echo get_Real(badr3) = getReal(badr3)
% echo get_Real(badr4) = getReal(badr4)
% echo get_Real(badr5) = getReal(badr5)
% echo get_Real(badr5) = getReal(badr5)
            
; Here is the "asmMain" function.

        
            end
