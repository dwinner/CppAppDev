;cset.inc-                                                                           
;
; Include file with useful cset macros and definitions.
;
                                                                  
            ifndef  cset_inc
cset_inc    =       0

            include string.inc  ;To get txt2str, etc.



; SSE4.2 feature flags (in ECX):

SSEPopCnt       =       (1 shl 23)  ;Bit 23


; pcset is an extended cset data type.
; The first 32 bytes are a standard cset value (256 bits).
; The second 32 bytes are two 16-byte SSE blocks (strings)
;
; tag_type:
;
;  This structure overlays the pstrs_type data
; in pcset. In particular, rangeTag maps to
; the first 4 bytes of pset.pcs.pstrs_type.rangeStr
; and anyTag maps to the first 4 bytes of
; pset.pcs.pstrs_type.anyStr. If rangeTag
; contains the value 0ffffffffh then
; pset.pcs.pstrs_type.rangeStr does not
; contain a valid range string for use by
; a pcmpXstrY instruction. Similarly, if
; anyTag contains 0ffffffffh, then 
; pset.pcs.pstrs_type.anyStr does not contain
; a valid pcmpXstrY string.
  
tag_type        struct
rangeTag        dword   4 dup (?)   ;3 dwords of padding
anyTag          dword   4 dup (?)   ;3 dwords of padding
tag_type        ends

; The pstrs_type data structure holds
; two 16-byte strings for use by the
; pcmpXstrY instructions: the first
; gets used with the Imm8 RANGE operand
; value (to specify up to 8 character
; ranges as the character set operand).
; The second (anyStr) holds 16 individual
; characters that comprise the character
; set to use with a pcmpXstrY instruction.
 
pstrs_type      struct
rangeStr        oword   ?
anyStr          oword   ?
pstrs_type      ends
 
; the pcs_type overlays the tag_type
; and pstrs_type types to conserve
; space. If the first four bytes of
; either pstrs.rangeStr or pstrs.anyStr
; contain 0FFFFFFFFh, then the strings
; are invalid (note that 0FFFFFFFFh
; is not an appropriate value for either
; type of pcmpXstrY set string).

pcs_type        union
tags            tag_type    {}
pstrs           pstrs_type  {}
pcs_type        ends
 

; pcset is the pcmpXstrY-based
; character set. It contains a standard
; powerset value followed by two (possibly
; invalid) character strings for use by
; pcmpXstrY instructions, using the Imm8
; EqualAny (0000000b) or  EqualRange (0000100b)
; values. As noted above, the 16-byte string
; values are marked invalid by the presence
; of a 0ffffffffh dword value at the beginning
; of the strings. Either, or both, 16-byte
; strings can be valid or invalid. If both
; 16-byte strings are invalid, the string
; scanning functions should fall back to
; using the powerset string scanning
; functions.
;
; NOTE: Any variable of type pcset must be
; aligned on a 16-byte boundary, as is
; required by all the powerset functions.

pcset           struct
                union
csetqw          qword    4 dup (?)
cset            oword    2 dup (?)
                ends
pcs             pcs_type {}
pcset           ends



;***************************************************************
;
; Character set macros
;
; staticCset-
;
;   Allocates storage for a character set variable.
; Can be used in any read/write section (e.g., .data
; or .data?):
;
; staticPCset-
;   Allocates storage for a pcset character set.

staticCset  macro   csetName
            align   16
csetName    oword   2 dup (0)
            endm
        
staticPCset macro   csetName
            align   16
csetName    pcset   {}
            endm
        
;----------         
; insCode-
;
;  Inserts a character into the cset_Dcl_cs[0..3]
; character set array.

insCode     macro   theCode
            local   ndx,bit, element
            
; ndx will be a value in the range 0..3 which is an
; index into the csetDcl_cs[0..3] compile-time array.

ndx         textequ %(theCode / 64)

; bit will be a value in the range 0..63 which is
; a bit position to set in the csetDcl_cs[ndx]
; element.

bit         textequ %(theCode mod 64)

; Generate csetDcl_cs0..csetDcl_cs3 based
; on the ndx value:

element     catstr  <csetDcl_cs>,ndx

; Set the "bit" bit position in csetDcl_cs[ndx]
; to 1:

element     =       element or (1 shl bit)

            endm    ;insCode 
            
            
                   
;----------         
; str2cset-
;
;   Converts a string constant to a set of bits.
; ORs the bits into csetDcl_cs[0..3].
;
; This macro is for internal use only (by cset.inc)!

str2cset    macro   theStr
            local   chrCnt,ndx,bit
            local   element, csLen

; Get the length of the string so we can skip
; processing the last character of the string
; argument.

csLen       sizestr <theStr>

; The following loop processes each of the
; characters in theStr EXCEPT for the first
; and last characters (which should be string
; delimiters).

chrCnt      =       1
            forc    chr, theStr

; The MASM sizestr function has an issue. It doesn't
; count "!" characters appearing in the string because
; it thinks they are escape character sequences. This
; isn't the case for strings that str2cset is processing,
; so this macro must bump up the length of the string
; by one for each "!" character it finds.

            ifidn   <!&chr>, <!!>
csLen       =   csLen + 1
            endif
            
            if      (chrCnt ne 1) and (chrCnt ne (csLen))
            insCode %("&chr")
            endif
            
; This macro uses chrCnt to determine when it
; is processing the first and last characters
; of "theStr" (which should be string delimiter
; characters):

chrCnt      =       chrCnt+1
            endm    ;forc
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

; Array[4] of qwords:
            
csetDcl_cs0 =       0
csetDcl_cs1 =       0
csetDcl_cs2 =       0
csetDcl_cs3 =       0

; Convert the string passed as an argument
; to a set of bits in csetDcl_cs[0..3]:

            str2cset theStr
                
            align   16      
csetName    equ     this oword
            qword   csetDcl_cs0, csetDcl_cs1
            qword   csetDcl_cs2, csetDcl_cs3
            
            endm    ;csetDcl

; pcsetDecl-
; Creates  pcset variable with an initialized
; set. However, disables the anyStr and rangeStr
; fields (must call csetToPCset to initialize
; those).
            
pcsetDcl    macro   csetName, theStr

; Array[4] of qwords:
            
csetDcl_cs0 =       0
csetDcl_cs1 =       0
csetDcl_cs2 =       0
csetDcl_cs3 =       0

; Convert the string passed as an argument
; to a set of bits in csetDcl_cs[0..3]:

            str2cset theStr
                
            align   16      
csetName    equ     this pcset
            qword   csetDcl_cs0, csetDcl_cs1
            qword   csetDcl_cs2, csetDcl_cs3
            qword   -1, -1
            qword   -1, -1
            endm    ;pcsetDcl
            
;-------------------------------------------
;
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
; unionHex-
;
;  Allows the inclusion of characters in a set
; by specifying their hexadecimal character
; code (actually, any numeric base will work
; fine, too).

unionHex    macro   first:req, optional:vararg

; Emit the required value:

            insCode %(&first)
            
; If there are additional arguments, emit them:

            for     code, <&optional>
            insCode %(&code)
            endm    ;for
            
            endm    ;unionHex

;----------         
; negCset-
;
;  Produce the complement of the current
; character second constant.

negCset     macro
csetDcl_cs0 =       not csetDcl_cs0
csetDcl_cs1 =       not csetDcl_cs1
csetDcl_cs2 =       not csetDcl_cs2
csetDcl_cs3 =       not csetDcl_cs3
            endm    ;negCset

            
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
            
            
;----------         
; emitPCset-
;   Outputs a pcset character set that
; has been built up in pieces since the
; last csetInit invocation. The argument
; supplies the name of the cset variable
; to create:
            
emitPCset   macro   csetName

; Emit the data built up from
; earlier calls (that have added
; their bits to csetDcl_cs[0..3]

            align   16      
csetName    equ     this pcset
            qword   csetDcl_cs0, csetDcl_cs1
            qword   csetDcl_cs2, csetDcl_cs3
            qword   -1, -1, -1, -1          ;Disable strings
            endm    ;emitPCset
            
            
;--------------------------------------------
; csetConst-
;
;  Copies the current set under construction
; to a set of 4 qword constants (based name
; is specified as macro argument).

csetConst   macro   baseName
            local   csName

csName      concat  baseName, <_cs0>
csName      =   csetDcl_cs0
csName      concat  baseName, <_cs1>
csName      =   csetDcl_cs1
csName      concat  baseName, <_cs2>
csName      =   csetDcl_cs2
csName      concat  baseName, <_cs3>
csName      =   csetDcl_cs3

            endm    ;csetConst




;**********************************************************
;
; Character set function definitions:

            externdef csetPopCnt:proc
            externdef csetToString:proc
            externdef csetToString2:proc
            externdef csetToRange:proc
            externdef csetToPCset:proc
            
            externdef skipCset:proc
            externdef skipToCset:proc
            externdef fscanCset:proc
            externdef fscanToCset:proc
            
            externdef stringTokenize:proc
            
            externdef zeroOrMoreCset:proc
            externdef oneOrMoreCset:proc
            externdef oneCset:proc
            externdef zeroOrOneCset:proc
            externdef nCset:proc
            externdef exactlyNCset:proc
            externdef nToMCset:proc
            externdef nOrLessCset:proc
                 
            endif   ;cset_inc
            
            
            

