;string.inc-
;
; Include file with useful string macros and other declarations.
;

            ifndef  string_inc
string_inc  =       0

strObject   struct
allocPtr    qword   ?
maxLength   dword   ?
strLength   dword   ?
charData    byte    ?
strObject   ends

; Size of the strObject header:

sohs        =       (size strObject) - 1

; SSE4.2 feature flags (in ECX):

SSE42       =       00180000h       ;Bits 19 & 20

; Useful pcmpXstrY IMM8 equates:

EqualAny    =       0000000b
EqualRange  =       0000100b
EqualEach   =       0001000b
EqualOrder  =       0001100b
NegPolarity =       0010000b
MSBIndex    =       1000000b
ByteMask    =       1000000b
ss1Flags    =       EqualOrder + NegPolarity + ByteMask
scFlags     =       EqualEach + NegPolarity
spnFlags    =       EqualAny+ByteMask




; txt2str-
;
; Convert a text object to a string literal

txt2str     macro   textObject
            local   strLiteral
strLiteral  textequ <"&textObject">
            exitm   strLiteral
            endm

                        
; str2txt
;
; Convert a string literal to a text object

str2txt     macro   str
            local   csLen,csetLen,chrCnt
            local   txtObject, delimiter
            local   endChar

txtObject   textequ <>      ;Init w/empty str
csLen       sizestr <str>
csetLen     textequ %csLen

            if      csLen gt 2
txtObject   substr  <&str>, 2, csLen-2
            endif   ;csLen gt 2
            
            exitm   txtObject
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
            





;**********************************************************
;
; High-performance string function definitions:

            externdef stringAlloc:proc
            externdef stringFree:proc
            externdef stringInit:proc
            
            externdef stringCpy1:proc   ;movsb          
            externdef stringCpy2:proc   ;SSE            

            externdef stringCmp1:proc   ;cmpsb          
            externdef stringCmp2:proc   ;SSE            
            externdef stringCmp3:proc   ;pcmpestri          
            externdef stringCmp4:proc   ;pcmpistri          

            externdef printString:proc  ;movsb          

            externdef substring1:proc   ;movsb          
            externdef substring2:proc   ;SSE            

            externdef prefix1:proc      ;movsb          
            externdef prefix2:proc      ;SSE            
            externdef prefix3:proc      ;pcmpistri
                        
            externdef suffix1:proc      ;movsb          
            externdef suffix2:proc      ;SSE            
            externdef suffix3:proc      ;pcmpistri          

            externdef partialCmp1:proc  ;cmpsb
            externdef partialCmp2:proc  ;SSE
            externdef partialCmp3:proc  ;pcmpistri
            
            externdef stringCat1:proc   ;movsb
            externdef stringCat2:proc   ;SSE

            externdef maskOut0s:oword   ;Used by findChar*
            externdef maskOut0s1:oword  ; and findLastChar*
            
            externdef findChar1:proc        ;movsb
            externdef findChar2:proc        ;SSE
            externdef findLastChar1:proc    ;movsb
            externdef findLastChar2:proc    ;SSE
            
            
            externdef findStr1:proc         ;SSE
            externdef findStr2:proc         ;pcmpistri
            externdef findLastStr1:proc     ;SSE
            externdef findLastStr2:proc     ;pcmpistri
            
            
            externdef get16AtRDI:proc       ;SSE
            externdef skipCharsPS:proc      ;SSE
            externdef skipToCharPS:proc     ;pcmpistri
            externdef skipChars1:proc       ;SSE
            externdef skipToChar1:proc      ;SSE
            externdef skipChars2:proc       ;pcmpistri
            externdef skipToChar2:proc      ;pcmpistri
            
            externdef incMove:proc          ;Combo movsb/SSE
            externdef decMove:proc          ;Combo movsb/SSE
            externdef stringInsert:proc     ;Combo movsb/SSE
            
            externdef stringDelete:proc     ;Combo movsb/SSE
            
            externdef stringTrim:proc
            externdef deleteWS:proc
            externdef deleteTrailingWS:proc
            
            externdef lowerMask:oword
            externdef upperMask:oword
            externdef UCa:oword
            externdef UCz:oword
            externdef lcA:oword
            externdef lcZ:oword
            
            externdef stringUpper:proc
            externdef stringLower:proc
            
            externdef stringCaseCmp:proc
            
            endif   ;string_inc
            
            
            

