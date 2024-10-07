;string.inc-
;
; Include file with useful string macros.
;

strObject   struct
allocPtr    qword   ?
maxLength   dword   ?
strLength   dword   ?
charData    byte    ?
strObject   ends

; Size of the strObject header:

sohs        =       (size strObject) - 1



; txt2str-
;
; Convert a text object to a string literal

txt2str     macro   textObject
            local   strLiteral
strLiteral  textequ <"&textObject">
            exitm   strLiteral
            endm

; mkDelim-
;	Brain-dead version of str2txt below
; so we can convert <"> and <'> to text.

mkDelim		macro	str
			local	theChar
theChar		substr	str, 2, 1
			exitm	theChar
			endm	;mkDelim
			
				
			            
; str2txt
;
; Convert a string literal to a text object

str2txt     macro   str
            local   csLen,csetLen,chrCnt
            local   txtObject, delimiter
			local	endChar

txtObject   textequ <>      ;Init w/empty str
csLen       sizestr <str>
csetLen     textequ %csLen

            if      csLen gt 2
txtObject   substr  <&str>, 2, csLen-2
			endif	;csLen gt 2

            exitm   <&txtObject>
            endm    ;str2txt    



;-----------
; staticStr-
;
;  This macro allocates static storage for a string and
; initializes the header information (strObject) with
; appropriate values (for an empty string).

staticStr   macro   strName, maxLen
            align   16
            qword   0   ;NULL allocation pointer.
            dword   maxLen
            dword   0   ;String length is 0.
strName     byte    0   ;Zero terminate empty string.
            
; Reserve storage for the character data. Round
; up to the next multiple of 16 bytes and ensure
; that there are at least 16 bytes beyond the end
; of the actual character data (so we can load 16 bytes
; starting with the very last character of the string). 
; Note: "byte" directive immediately above already 
; reserved storage for the zero byte.

            byte    ((maxLen+31) and (-16)) dup (0)
            endm
            
            
            

; strDcl macro-
;
;  Declares a static string variable. Can be used in the
; .data, .const, or .code sections.
;
; Usage:
;
;   strDcl <<String's Name>>, <<maximum alloc>>, <<string>>
;
; where:
; <<String's Name>> is a MASM identifier with which
; you will be able to refer to the string data.
;
; <<maximum alloc>> is the maximum number of characters
; this string object will be able to hold. If this is
; zero, the strDcl macro fills in the string's actual
; length as the maximum length value. If this value
; is less than the actual length, the macro will
; report an assembly-time error.
;
; <<string>> is a string constant to initialize the
; string's data. 
;
; Example:
;
;   strDcl  helloStr, 0, "Hello, World!"


strDcl      macro   strName, maxLength, strConst
            local   strLength
            align   16
            
; The allocation pointer is NULL because this is a
; statically-allocated string.

            qword   0
            
; As a convenience, if the invoker specifies 0 as the
; maximum length, this macro will fill in the actual
; string length as the maximum length.
            
            if      maxLength eq 0
            dword   strLength
            else
            dword   maxLength
            endif

; Fill in the actual length here:
            
            dword   strLength
            
; Note: this is automatically 16-byte aligned
; because we have emitted 16 bytes up to this point.

strName     byte    strConst
strLength   =       $-strName
            byte    maxLength-strLength+1 dup (0)
            
; Need to add padding to the end of the string to make
; sure the whole structure is an integral multiple of
; 16 bytes (and we have an extra 16 bytes at the end
; of the string, so we're guaranteed we can load 16
; bytes into an SSE register starting with the very
; last character of the string):

            if      ((strLength + 1) mod 16) ne 0
            byte    32-((strLength+1) mod 16) dup (0)
            else
            byte    16 dup (0)  ;Still need 16 extra bytes.
            endif
            
; If the user specified a non-zero maxLength value and
; it is less than the actual string length, report an
; error:


            if      (maxLength ne 0) and (maxLength lt strLength)
            .err    <Maximum length is too small>
            endif
            
            endm    ;End of strDcl
            


; strBgn and strEnd are a pair of macros used like
; strDcl. These two macros work together to let
; you create string constants of any length.
;
; Syntax:
;
;  strBgn  <<string Name>>, <<maxLength>>
;
;  byte    "arbitrary string data that"
;  byte    "you want to initialize the"
;  byte    "string constant with; note"
;  byte    "there is no zero-terminating"
;  byte    "byte here."
;
;  strEnd  <<string Name>>
;
; <<string Name>> is a valid MASM identifier that
; the code will use to access this string constant.
; Note that whatever identifier you choose for
; strBgn, you must use the exact same identifier
; for strEnd.
;
; <<maxLength>> is either zero (to have strBgn
; fill in the string's actual length as the
; maximum length) or a maximum allocation for
; this string object. <<maxLength>> must be
; greater than or equal to the string's actual
; length or MASM will report an error.


strBgn      macro   strName, maxLength
            local   strLength, lenName, maxName
lenName     catstr  <&strName>,<$>,<length>
maxName     catstr  <&strName>,<$>,<maxLen>
maxName =   maxLength
            align   16
            
; The allocation pointer is NULL because this is a
; statically-allocated string.

            qword   0
            
; As a convenience, if the invoker specifies 0 as the
; maximum length, this macro will fill in the actual
; string length as the maximum length.
            
            if      maxLength eq 0
            dword   lenName
            else
            dword   maxLength
            endif

; Fill in the actual length here:
            
            dword   lenName
strName     equ     this byte
            
            endm    ;End of strBgn
            
            
; Note: the actual string constant gets defined
; between the strStart and strEnd macro invocations.
            
strEnd      macro   strName
            local   lenName, maxName
lenName     catstr  <&strName>,<$>,<length>
maxName     catstr  <&strName>,<$>,<maxLen>
lenName     =       $-strName

; Report an error if maxLength is too small.

            if  (maxName ne 0) and (maxName lt lenName)
            .err    <Maximum length is too small>
            endif
    
; Need to pad the string for maxLength bytes and
; add a zero terminating byte.
            
            byte    maxName-lenName+1 dup (0)
            
; Need to add padding to the end of the string to make
; sure the whole structure is an integral multiple of
; 16 bytes plus an extra 16 bytes at the end:

            if      ((lenName + 1) mod 16) ne 0
            byte    32-((lenName+1) mod 16) dup (0)
            else
            byte    16 dup (0)  ;Still need 16 extra bytes.
            endif
            
            endm    ;End of strEnd
            


;***************************************************************
;
; Character set macros
;
; staticCset-
;
;   Allocates storage for a character set variable.
; Can be used in any read/write section (e.g., .data
; or .data?):

staticCset  macro   csetName
            align   16
csetName    oword   2 dup (0)
            endm
        
        
;----------         
; str2cset-
;
;   Converts a string constant to a set of bits.
; Returns the bits in csetDcl_cs[0..3].
;
; This macro is for internal use only (by string.inc)!

str2cset    macro   cset
            local   ndx,bit,element
			local	chrNdx, csetLen
;			local	chr
			
csetLen		sizeStr	cset			
chrNdx		=		1
			while	chrNdx le csetLen

chr			substr	cset, chrNdx, 1
chr2		textequ	<"&chr">
chr3		=		chr2
chr4		textequ	%chr3

% echo c=chr, chr2, chr4

; Convert the character (ASCII) code
; to two value:
;
; ndx: an index into the csetDcl_cs compile-time
;      array (this will be a value in the range
;      0-3).
;
; bit: a bit position with a 64-bit element of
;      the csetDcl_cs compile-time array.
            
ndx         textequ %(chr3 / 64)
bit         textequ %(chr3 mod 64)

% echo n=ndx, b=bit

; Generate a string of the form
; csetDcl_csX, where "X" is a value
; in the range 0-3, which is the 
; index into the csetDcl_cs array.

element     catstr  <csetDcl_cs>,ndx

; The following statement sets the particular
; bit (0..63) in csetDcl_cs[ndx]:

element     =       element or (1 shl bit)

chrNdx		=		chrNdx + 1
            endm    ;while
            endm    ;str2cset   
            
            
;---------          
; csetDcl-
;
;   Given a name and a string constant,
; creates a character set object.
;
; e.g.,
;
;   csetDcl someName, "abc"         
            
csetDcl     macro   csetName, theStr
			local	strAsTxt

; Array[4] of qwords:
            
csetDcl_cs0 =       0
csetDcl_cs1 =       0
csetDcl_cs2 =       0
csetDcl_cs3 =       0

; Convert the string passed as an argument
; to a set of bits in csetDcl_cs[0..3]:

strAsTxt	textequ	 str2txt(theStr)
            str2cset &strAsTxt
                
            align   16      
csetName    equ     this oword
            qword   csetDcl_cs0, csetDcl_cs1
            qword   csetDcl_cs2, csetDcl_cs3
            
            endm    ;csetDcl
            

; The following macros build up a cset piece
; by piece. For example:
;
;   csetInit                    ;Initialize cset.
;   unionStr    "abcdefghijklmnopqrstuvwxyz"
;   unionStr    "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
;   unionStr    "0123456789"
;   emitCset    alphaNumerics   ;Creates actual cset.
;
;
;
;----------         
; csetInit-
;
;   Initializes the csetDcl_cs[0..3] array prior
; to unioning in the characters in the set:

csetInit    macro

; Create an empty set:
            
csetDcl_cs0 =       0
csetDcl_cs1 =       0
csetDcl_cs2 =       0
csetDcl_cs3 =       0

            endm    ;csetInit
            

;----------         
; unionStr-
;
; Union in a cset built from a character
; string:

unionStr    macro    theStr
            str2cset theStr
            endm     ;unionStr
            
;----------         
; unionRng-
;
;  Union in a range of characters specified
; by a TEXT constant of the form:
;
;    <x-y>
;
; where x and y are single characters and
; the ASCII code of x is less than the ASCII
; code of y.

unionRng         macro    range
                 local    rangeCnt, rangeLen
            
rangeCnt         sizestr  <&range>
rangeLen         textequ  %rangeCnt

                 if       rangeLen ne 3
                 .err     <unionRng arg must be <x-y>>
                 exitm
                 endif

midCh            substr   <&range>, 2, 1
                 ifdif    midCh,<->
                 .err     <unionRng arg must be <x-y>>
                 exitm
                 endif
            
unionRng_start   substr   <&range>, 1, 1
unionRng_end     substr   <&range>, 3, 1

chr              =        txt2str(%unionRng_start) 
chrEnd           =        txt2str(%unionRng_end)
                 while    chr le chrEnd
            
unionRng_ndx     textequ  %(chr / 64)
unionRng_bit     textequ  %(chr mod 64)

unionRng_element catstr   <csetDcl_cs>,unionRng_ndx
unionRng_b       =        (1 shl unionRng_bit)
unionRng_element =        unionRng_element or unionRng_b
chr              =        chr+1
                 endm     ;while

                 endm    ;unionRng
            
;----------         
; negCset-
;
;  Produce the complement of the current
; character second constant.

negCset		macro
csetDcl_cs0 =       not csetDcl_cs0
csetDcl_cs1 =       not csetDcl_cs1
csetDcl_cs2 =       not csetDcl_cs2
csetDcl_cs3 =       not csetDcl_cs3
			endm	;negCset

            
;----------         
; emitCset-
;   Outputs the actual character set that
; has been built up in pieces since the
; last csetInit invocation. The argument
; supplies the name of the cset variable
; to create:
            
emitCset    macro   csetName

; Emit the data built up from
; earlier calls (that have added
; their bits to csetDcl_cs[0..3]

            align   16      
csetName    equ     this oword
            qword   csetDcl_cs0, csetDcl_cs1
            qword   csetDcl_cs2, csetDcl_cs3
            
            endm    ;emitCset
            
            
            

