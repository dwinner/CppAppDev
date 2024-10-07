; Listing 13-11
;
; Compile-time program testing
; register operands

        option  casemap:none

; Register values:

regNone     =       0
regAL       =       1
regBL       =       2
regCL       =       3
regDL       =       4
regAH       =       5
regBH       =       6
regCH       =       7
regDH       =       8
regSIL      =       9
regDIL      =       10
regBPL      =       11
regSPL      =       12
regR8B      =       13
regR9B      =       14
regR10B     =       15
regR11B     =       16
regR12B     =       17
regR13B     =       18
regR14B     =       19
regR15B     =       20

regAX       =       21
regBX       =       22
regCX       =       23
regDX       =       24
regSI       =       25
regDI       =       26
regBP       =       27
regSP       =       28
regR8W      =       29
regR9W      =       30
regR10W     =       31
regR11W     =       32
regR12W     =       33
regR13W     =       34
regR14W     =       35
regR15W     =       36

regEAX      =       37
regEBX      =       38
regECX      =       39
regEDX      =       40
regESI      =       41
regEDI      =       42
regEBP      =       43
regESP      =       44
regR8D      =       45
regR9D      =       46
regR10D     =       47
regR11D     =       48
regR12D     =       49
regR13D     =       50
regR14D     =       51
regR15D     =       52

regRAX      =       53
regRBX      =       54
regRCX      =       55
regRDX      =       56
regRSI      =       57
regRDI      =       58
regRBP      =       59
regRSP      =       60
regR8       =       61
regR9       =       62
regR10      =       63
regR11      =       64
regR12      =       65
regR13      =       66
regR14      =       67
regR15      =       68

regST       =       69
regST0      =       70
regST1      =       71
regST2      =       72
regST3      =       73
regST4      =       74
regST5      =       75
regST6      =       76
regST7      =       77

regMM0      =       78
regMM1      =       79
regMM2      =       80
regMM3      =       81
regMM4      =       82
regMM5      =       83
regMM6      =       84
regMM7      =       85

regXMM0     =       86
regXMM1     =       87
regXMM2     =       88
regXMM3     =       89
regXMM4     =       90
regXMM5     =       91
regXMM6     =       92
regXMM7     =       93
regXMM8     =       94
regXMM9     =       95
regXMM10    =       96
regXMM11    =       97
regXMM12    =       98
regXMM13    =       99
regXMM14    =       100
regXMM15    =       101

regYMM0     =       102
regYMM1     =       103
regYMM2     =       104
regYMM3     =       105
regYMM4     =       106
regYMM5     =       107
regYMM6     =       108
regYMM7     =       109
regYMM8     =       110
regYMM9     =       111
regYMM10    =       112
regYMM11    =       113
regYMM12    =       114
regYMM13    =       115
regYMM14    =       116
regYMM15    =       117

; Left to the reader:
; Implement ZMM registers.
; Implement system and special-purpose registers.




; The following text equates allow
; this code to turn a register
; number (the equates above)
; into a register name.

toReg       macro   regNum
            local   register
register    catstr  <reg>,%regNum
            exitm   &register
            endm    ;toReg
                            
reg0        textequ <>
reg1        textequ <al>
reg2        textequ <bl>            
reg3        textequ <cl>
reg4        textequ <dl>
reg5        textequ <ah>
reg6        textequ <bh>
reg7        textequ <ch>
reg8        textequ <dh>
reg9        textequ <sil>
reg10       textequ <dil>
reg11       textequ <bpl>
reg12       textequ <spl>
reg13       textequ <r8b>
reg14       textequ <r9b>
reg15       textequ <r10b>
reg16       textequ <r11b>
reg17       textequ <r12b>
reg18       textequ <r13b>
reg19       textequ <r14b>
reg20       textequ <r15b>

reg21       textequ <ax>  
reg22       textequ <bx>  
reg23       textequ <cx>  
reg24       textequ <dx>  
reg25       textequ <si>  
reg26       textequ <di>  
reg27       textequ <bp>  
reg28       textequ <sp>  
reg29       textequ <r8w> 
reg30       textequ <r9w> 
reg31       textequ <r10w>
reg32       textequ <r11w>
reg33       textequ <r12w>
reg34       textequ <r13w>
reg35       textequ <r14w>
reg36       textequ <r15w>

reg37       textequ <EAX> 
reg38       textequ <EBX> 
reg39       textequ <ECX> 
reg40       textequ <EDX> 
reg41       textequ <ESI> 
reg42       textequ <EDI> 
reg43       textequ <EBP> 
reg44       textequ <ESP> 
reg45       textequ <R8D> 
reg46       textequ <R9D> 
reg47       textequ <R10D>
reg48       textequ <R11D>
reg49       textequ <R12D>
reg50       textequ <R13D>
reg51       textequ <R14D>
reg52       textequ <R15D>

reg53       textequ <RAX>
reg54       textequ <RBX>
reg55       textequ <RCX>
reg56       textequ <RDX>
reg57       textequ <RSI>
reg58       textequ <RDI>
reg59       textequ <RBP>
reg60       textequ <RSP>
reg61       textequ <R8>
reg62       textequ <R9>
reg63       textequ <R10>
reg64       textequ <R11>
reg65       textequ <R12>
reg66       textequ <R13>
reg67       textequ <R14>
reg68       textequ <R15>

reg69       textequ <ST>          
reg70       textequ <ST(0)>         
reg71       textequ <ST(1)>         
reg72       textequ <ST(2)>         
reg73       textequ <ST(3)>         
reg74       textequ <ST(4)>         
reg75       textequ <ST(5)>         
reg76       textequ <ST(6)>         
reg77       textequ <ST(7)>         

reg78       textequ <MM0>         
reg79       textequ <MM1>         
reg80       textequ <MM2>         
reg81       textequ <MM3>         
reg82       textequ <MM4>         
reg83       textequ <MM5>         
reg84       textequ <MM6>         
reg85       textequ <MM7>         

reg86       textequ <XMM0>        
reg87       textequ <XMM1>        
reg88       textequ <XMM2>        
reg89       textequ <XMM3>        
reg90       textequ <XMM4>        
reg91       textequ <XMM5>        
reg92       textequ <XMM6>        
reg93       textequ <XMM7>        
reg94       textequ <XMM8>        
reg95       textequ <XMM9>        
reg96       textequ <XMM10>       
reg97       textequ <XMM11>       
reg98       textequ <XMM12>       
reg99       textequ <XMM13>       
reg100      textequ <XMM14>       
reg101      textequ <XMM15>       

reg102      textequ <YMM0>        
reg103      textequ <YMM1>        
reg104      textequ <YMM2>        
reg105      textequ <YMM3>        
reg106      textequ <YMM4>        
reg107      textequ <YMM5>        
reg108      textequ <YMM6>        
reg109      textequ <YMM7>        
reg110      textequ <YMM8>        
reg111      textequ <YMM9>        
reg112      textequ <YMM10>       
reg113      textequ <YMM11>       
reg114      textequ <YMM12>       
reg115      textequ <YMM13>       
reg116      textequ <YMM14>       
reg117      textequ <YMM15>       


; The following equates allow
; this code to map an 8-bit
; register to its corresponding
; 16-bit register:

reg8To16    macro   reg8
            local   register
register    catstr  <m8_16_>,%reg8
            exitm   &register
            endm    ;toReg

m8_16_1     textequ <ax>    ;Maps al to ax
m8_16_2     textequ <bx>    ;Maps bl to bx
m8_16_3     textequ <cx>    ;Maps cl to cx
m8_16_4     textequ <dx>    ;Maps dl to dx
m8_16_5     textequ <ax>    ;Maps ah to ax
m8_16_6     textequ <bx>    ;Maps bh to bx
m8_16_7     textequ <cx>    ;Maps ch to cx
m8_16_8     textequ <dx>    ;Maps dh to dx
m8_16_9     textequ <si>    ;Maps sil to si
m8_16_10    textequ <di>    ;Maps dil to di
m8_16_11    textequ <bp>    ;Maps bpl to bp
m8_16_12    textequ <sp>    ;Maps spl to sp
m8_16_13    textequ <r8w>   ;Maps r8b to r8w
m8_16_14    textequ <r9w>   ;Maps r9b to r9w
m8_16_15    textequ <r10w>  ;Maps r10b to r10w
m8_16_16    textequ <r11w>  ;Maps r11b to r11w
m8_16_17    textequ <r12w>  ;Maps r12b to r12w
m8_16_18    textequ <r13w>  ;Maps r13b to r13w
m8_16_19    textequ <r14w>  ;Maps r14b to r14w
m8_16_20    textequ <r15w>  ;Maps r15b to r15w

; The following equates allow
; this code to map an 8-bit
; register to its corresponding
; 32-bit register:

reg8To32    macro   reg8
            local   register
register    catstr  <m8_32_>,%reg8
            exitm   &register
            endm    ;toReg

m8_32_1     textequ <eax>   ;Maps al to eax
m8_32_2     textequ <ebx>   ;Maps bl to ebx
m8_32_3     textequ <ecx>   ;Maps cl to ecx
m8_32_4     textequ <edx>   ;Maps dl to edx
m8_32_5     textequ <eax>   ;Maps ah to eax
m8_32_6     textequ <ebx>   ;Maps bh to ebx
m8_32_7     textequ <ecx>   ;Maps ch to ecx
m8_32_8     textequ <edx>   ;Maps dh to edx
m8_32_9     textequ <esi>   ;Maps sil to esi
m8_32_10    textequ <edi>   ;Maps dil to edi
m8_32_11    textequ <ebp>   ;Maps bpl to ebp
m8_32_12    textequ <esp>   ;Maps spl to esp
m8_32_13    textequ <r8d>   ;Maps r8b to r8d
m8_32_14    textequ <r9d>   ;Maps r9b to r9d
m8_32_15    textequ <r10d>  ;Maps r10b to r10d
m8_32_16    textequ <r11d>  ;Maps r11b to r11d
m8_32_17    textequ <r12d>  ;Maps r12b to r12d
m8_32_18    textequ <r13d>  ;Maps r13b to r13d
m8_32_19    textequ <r14d>  ;Maps r14b to r14d
m8_32_20    textequ <r15d>  ;Maps r15b to r15d

; The following equates allow
; this code to map an 8-bit
; register to its corresponding
; 32-bit register:

reg8To64    macro   reg8
            local   register
register    catstr  <m8_64_>,%reg8
            exitm   &register
            endm    ;toReg

m8_64_1     textequ <rax>   ;Maps al to rax
m8_64_2     textequ <rbx>   ;Maps bl to rbx
m8_64_3     textequ <rcx>   ;Maps cl to rcx
m8_64_4     textequ <rdx>   ;Maps dl to rdx
m8_64_5     textequ <rax>   ;Maps ah to rax
m8_64_6     textequ <rbx>   ;Maps bh to rbx
m8_64_7     textequ <rcx>   ;Maps ch to rcx
m8_64_8     textequ <rdx>   ;Maps dh to rdx
m8_64_9     textequ <rsi>   ;Maps sil to rsi
m8_64_10    textequ <rdi>   ;Maps dil to rdi
m8_64_11    textequ <rbp>   ;Maps bpl to rbp
m8_64_12    textequ <rsp>   ;Maps spl to rsp
m8_64_13    textequ <r8>    ;Maps r8b to r8
m8_64_14    textequ <r9>    ;Maps r9b to r9
m8_64_15    textequ <r10>   ;Maps r10b to r10
m8_64_16    textequ <r11>   ;Maps r11b to r11
m8_64_17    textequ <r12>   ;Maps r12b to r12
m8_64_18    textequ <r13>   ;Maps r13b to r13
m8_64_19    textequ <r14>   ;Maps r14b to r14
m8_64_20    textequ <r15>   ;Maps r15b to r15



; The following equates allow
; this code to map a 16-bit
; register to its corresponding
; 32-bit register:

reg16To32   macro   reg16
            local   register
register    catstr  <m16_32_>,%reg16
            exitm   &register
            endm    ;toReg

m16_32_21   textequ <eax>   ;Maps ax to eax
m16_32_22   textequ <ebx>   ;Maps bx to ebx
m16_32_23   textequ <ecx>   ;Maps cx to ecx
m16_32_24   textequ <edx>   ;Maps dx to edx
m16_32_25   textequ <esi>   ;Maps si to esi
m16_32_26   textequ <edi>   ;Maps di to edi
m16_32_27   textequ <ebp>   ;Maps bp to ebp
m16_32_28   textequ <esp>   ;Maps sp to esp
m16_32_29   textequ <r8d>   ;Maps r8w to r8d
m16_32_30   textequ <r9d>   ;Maps r9w to r9d
m16_32_31   textequ <r10d>  ;Maps r10w to r10d
m16_32_32   textequ <r11d>  ;Maps r11w to r11d
m16_32_33   textequ <r12d>  ;Maps r12w to r12d
m16_32_34   textequ <r13d>  ;Maps r13w to r13d
m16_32_35   textequ <r14d>  ;Maps r14w to r14d
m16_32_36   textequ <r15d>  ;Maps r15w to r15d



; The following equates allow
; this code to map a 16-bit
; register to its corresponding
; 64-bit register:

reg16To64   macro   reg16
            local   register
register    catstr  <m16_64_>,%reg16
            exitm   &register
            endm    ;toReg

m16_64_21   textequ <rax>   ;Maps ax to rax
m16_64_22   textequ <rbx>   ;Maps bx to rbx
m16_64_23   textequ <rcx>   ;Maps cx to rcx
m16_64_24   textequ <rdx>   ;Maps dx to rdx
m16_64_25   textequ <rsi>   ;Maps si to rsi
m16_64_26   textequ <rdi>   ;Maps di to rdi
m16_64_27   textequ <rbp>   ;Maps bp to rbp
m16_64_28   textequ <rsp>   ;Maps sp to rsp
m16_64_29   textequ <r8>    ;Maps r8w to r8
m16_64_30   textequ <r9>    ;Maps r9w to r9
m16_64_31   textequ <r10>   ;Maps r10w to r10
m16_64_32   textequ <r11>   ;Maps r11w to r11
m16_64_33   textequ <r12>   ;Maps r12w to r12
m16_64_34   textequ <r13>   ;Maps r13w to r13
m16_64_35   textequ <r14>   ;Maps r14w to r14
m16_64_36   textequ <r15>   ;Maps r15w to r15



; The following equates allow
; this code to map a 32-bit
; register to its corresponding
; 64-bit register:

reg32To64   macro   reg32
            local   register
register    catstr  <m32_64_>,%reg32
            exitm   &register
            endm    ;toReg

m32_64_37   textequ <rax>   ;Maps eax to rax
m32_64_38   textequ <rbx>   ;Maps ebx to rbx
m32_64_39   textequ <rcx>   ;Maps ecx to rcx
m32_64_40   textequ <rdx>   ;Maps edx to rdx
m32_64_41   textequ <rsi>   ;Maps esi to rsi
m32_64_42   textequ <rdi>   ;Maps edi to rdi
m32_64_43   textequ <rbp>   ;Maps ebp to rbp
m32_64_44   textequ <rsp>   ;Maps esp to rsp
m32_64_45   textequ <r8>    ;Maps r8d to r8
m32_64_46   textequ <r9>    ;Maps r9d to r9
m32_64_47   textequ <r10>   ;Maps r10d to r10
m32_64_48   textequ <r11>   ;Maps r11d to r11
m32_64_49   textequ <r12>   ;Maps r12d to r12
m32_64_50   textequ <r13>   ;Maps r13d to r13
m32_64_51   textequ <r14>   ;Maps r14d to r14
m32_64_52   textequ <r15>   ;Maps r15d to r15
                    



; mout-
;
;  Replacement for echo. Allows "%" operator
; in operand field to expand text symbols.

mout        macro   valToPrint
            local   cmd
cmd         catstr  <echo >, <valToPrint>
            cmd
            endm


            
; toUpper
;
;   Converts alphabetic characters to upper case
;   in a text string

toUpper     macro   lcStr
            local   result
            
; Build the result string in "result":

result      textequ <>

; For each character in the source string, conver it to upper case.

            forc    eachChar, <lcStr>

; See if we have a lower case character:

            if      ('&eachChar' ge 'a') and ('&eachChar' le 'z')
            
; If lower case, convert it to the symbol "lc_*" where "*"
; is the lower case character. The equates below will map
; this character to upper case:

eachChar    catstr  <lc_>,<eachChar>
result      catstr  result, &eachChar

            else
            
; If it wasn't a lower case character, just append it
; to the end of the string:

result      catstr  result, <eachChar>

            endif
            endm    ;forc
            exitm   result  ;Return result string
            endm    ;toUpper
            
lc_a        textequ <A>
lc_b        textequ <B>
lc_c        textequ <C>
lc_d        textequ <D>
lc_e        textequ <E>
lc_f        textequ <F>
lc_g        textequ <G>
lc_h        textequ <H>
lc_i        textequ <I>
lc_j        textequ <J>
lc_k        textequ <K>
lc_l        textequ <L>
lc_m        textequ <M>
lc_n        textequ <N>
lc_o        textequ <O>
lc_p        textequ <P>
lc_q        textequ <Q>
lc_r        textequ <R>
lc_s        textequ <S>
lc_t        textequ <T>
lc_u        textequ <U>
lc_v        textequ <V>
lc_w        textequ <W>
lc_x        textequ <X>
lc_y        textequ <Y>
lc_z        textequ <Z>

; isReg-
;
;   Returns true if operand is a register
;   (any register type)

isReg       macro   parm
            local   result
result      textequ %(((opattr &parm) and 10h) eq 10h)
            exitm   <&result>
            endm    ;isReg
 
;--------------------------------------------------------
; lookupReg:
;
; Given a (suspected) register and a lookup table, convert
; that register to the corresponding numeric form.

lookupReg   macro   theReg, regList, regIndex
            local   regUpper, regConst, inst, regLen, indexLen

; Convert (possible) register to upper case:

regUpper    textequ toUpper( theReg )
regLen      sizestr <&theReg>

; Does it exist in regList? If not, it's not a register.

inst        instr   1, regList, &regUpper
            if      inst ne 0

regConst    substr  &regIndex, inst, 1
            if      &regConst eq regLen
            
; It's a  register (in text form). Create an identifier of
; the form "regXX" where "XX" represents the register name:

regConst    catStr  <reg>,regUpper

            ifdef   &regConst

; Return "regXX" as function result. This is the numeric value
; for the register.

            exitm   regConst
            endif
            endif
            endif

; If the parameter string wasn't in regList, then return
; "regNone" as the function result:

            exitm   <regNone>
            endm    ;lookupReg

;------------------------------------------------------------------------------           
; is8BitReg
;
;  Returns reg numeric value if an 8-bit register,
; returns 0 (regNone) if not an 8-bit register.
;
; all8BitRegs is a string with all the 8-bit registers listed (must be upper case).
; all8Lengths is an array of 1-digit register lengths. The index into the string
; matches the starting index of each register in all8BitRegs.

all8BitRegs textequ <ALBLCLDLAHBHCHDHSILDILBPLSPLR8BR9BR10BR11BR12BR13BR14BR15B>
all8Lengths textequ <2020202020202020300300300300300300400040004000400040004000>

is8BitReg   macro   parm
            exitm   lookupReg( parm, all8BitRegs, all8Lengths )
            endm    ;is8BitReg
            

;-------------------------------------------------------------------------------            
; is16BitReg
;
;  Returns reg numeric value if a 16-bit register,
; returns 0 (regNone) if not an 16-bit register.

all16Regs   textequ <AXBXCXDXSIDIBPSPR8WR9WR10WR11WR12WR13WR14WR15W>
all16Lens   textequ <2020202020202020300300400040004000400040004000>

is16BitReg  macro   parm
            exitm   lookupReg( parm, all16Regs, all16Lens )
            endm    ;is16BitReg



;-------------------------------------------------            
; is32BitReg
;
;  Returns reg numeric value if a 32-bit register,
; returns 0 (regNone) if not an 32-bit register.

all32Regs   textequ <EAXEBXECXEDXESIEDIEBPESPR8DR9DR10DR11DR12DR13DR14DR15D>
all32Lens   textequ <300300300300300300300300300300400040004000400040004000>

is32BitReg  macro   parm
            exitm   lookupReg( parm, all32Regs, all32Lens )
            endm    ;is32BitReg


            
; is64BitReg
;
;  Returns reg numeric value if a 64-bit register,
; returns 0 (regNone) if not an 64-bit register.

all64Regs   textequ <RAXRBXRCXRDXRSIRDIRBPRSPR8R9R10R11R12R13R14R15>
all64Lens   textequ <3003003003003003003003002020300300300300300300>

is64BitReg  macro   parm
            exitm   lookupReg( parm, all64Regs, all64Lens )
            endm    ;is64BitReg


; isGPReg-
;
;   Returns the register number constant if
; the register is a general-purpose (8-, 16-,
; 32-, or 64-bit) register.

isGPReg     macro   parm
            local   text

text        textequ is8BitReg(parm)
            if      &text ne regNone
            exitm   text
            endif
                        
text        textequ is16BitReg(parm)
            if      &text ne regNone
            exitm   text
            endif
                        
text        textequ is32BitReg(parm)
            if      &text ne regNone
            exitm   text
            endif
                        
text        textequ is64BitReg(parm)
            if      &text ne regNone
            exitm   text
            endif
                        
            exitm   <0>
            endm    ;isGPReg
            

; isFPReg-
;
;  True if the parameter is one of the
; FPU registers (ST, ST(0), ST(1), etc)
;
; Note that isFPReg returns regST0 for
; the text "ST". If you need to differentiate
; ST and ST(0), you will need to keep the
; original parameter text around.
;
; Because FPU registers have a funny syntax,
; we have to brute-force compare against them.


isFPReg     macro   parm
            ifidni  <&parm>, <st>
            exitm   <regST>
            endif
            ifidni  <&parm>, <ST(0)>
            exitm   <regST0>
            endif
            ifidni  <&parm>, <ST(1)>
            exitm   <regST1>
            endif
            ifidni  <&parm>, <ST(2)>
            exitm   <regST2>
            endif
            ifidni  <&parm>, <ST(3)>
            exitm   <regST3>
            endif
            ifidni  <&parm>, <ST(4)>
            exitm   <regST4>
            endif
            ifidni  <&parm>, <ST(5)>
            exitm   <regST5>
            endif
            ifidni  <&parm>, <ST(6)>
            exitm   <regST6>
            endif
            ifidni  <&parm>, <ST(7)>
            exitm   <regST7>
            endif

            endm    ;isFPReg

; isMMReg
;
;  Returns register value for one of
; the MMX registers (mm0..mm15)

allMMRegs   textequ <MM0MM1MM2MM3MM4MM5MM6MM7>
allMMLens   textequ <300300300300300300300300>

isMMReg     macro   parm
            exitm   lookupReg( parm, allMMRegs, allMMLens )
            endm    ;isMMReg        
            
; isXMMReg
;
;  Returns register value for one of
; the XMM registers (xmm0..xmm15)

isXMMReg    macro   parm
            ifidni  <&parm>, <xmm0>
            exitm   <regXMM0>
            endif
            ifidni  <&parm>, <xmm1>
            exitm   <regXMM1>
            endif
            ifidni  <&parm>, <xmm2>
            exitm   <regXMM2>
            endif
            ifidni  <&parm>, <xmm3>
            exitm   <regXMM3>
            endif
            ifidni  <&parm>, <xmm4>
            exitm   <regXMM4>
            endif
            ifidni  <&parm>, <xmm5>
            exitm   <regXMM5>
            endif
            ifidni  <&parm>, <xmm6>
            exitm   <regXMM6>
            endif
            ifidni  <&parm>, <xmm7>
            exitm   <regXMM7>
            endif
            ifidni  <&parm>, <xmm8>
            exitm   <regXMM8>
            endif
            ifidni  <&parm>, <xmm9>
            exitm   <regXMM9>
            endif
            ifidni  <&parm>, <xmm10>
            exitm   <regXMM10>
            endif
            ifidni  <&parm>, <xmm11>
            exitm   <regXMM11>
            endif
            ifidni  <&parm>, <xmm12>
            exitm   <regXMM12>
            endif
            ifidni  <&parm>, <xmm13>
            exitm   <regXMM13>
            endif
            ifidni  <&parm>, <xmm14>
            exitm   <regXMM14>
            endif
            ifidni  <&parm>, <xmm15>
            exitm   <regXMM15>
            endif
            endm    ;isXMMReg       
            
; isYMMReg
;
;  Returns register value for one of
; the YMM registers (ymm0..ymm15)

isYMMReg    macro   parm
            ifidni  <&parm>, <ymm0>
            exitm   <regYMM0>
            endif
            ifidni  <&parm>, <ymm0>
            exitm   <regYMM0>
            endif
            ifidni  <&parm>, <ymm1>
            exitm   <regYMM1>
            endif
            ifidni  <&parm>, <ymm2>
            exitm   <regYMM2>
            endif
            ifidni  <&parm>, <ymm3>
            exitm   <regYMM3>
            endif
            ifidni  <&parm>, <ymm4>
            exitm   <regYMM4>
            endif
            ifidni  <&parm>, <ymm5>
            exitm   <regYMM5>
            endif
            ifidni  <&parm>, <ymm6>
            exitm   <regYMM6>
            endif
            ifidni  <&parm>, <ymm7>
            exitm   <regYMM7>
            endif
            ifidni  <&parm>, <ymm8>
            exitm   <regYMM8>
            endif
            ifidni  <&parm>, <ymm9>
            exitm   <regYMM9>
            endif
            ifidni  <&parm>, <ymm10>
            exitm   <regYMM10>
            endif
            ifidni  <&parm>, <ymm11>
            exitm   <regYMM11>
            endif
            ifidni  <&parm>, <ymm12>
            exitm   <regYMM12>
            endif
            ifidni  <&parm>, <ymm13>
            exitm   <regYMM13>
            endif
            ifidni  <&parm>, <ymm14>
            exitm   <regYMM14>
            endif
            ifidni  <&parm>, <ymm15>
            exitm   <regYMM15>
            endif
            endm    ;isYMMReg       
            
            
; whichReg-
;
;   Translate text register to numeric
; constant.

whichReg    macro   parm
            local   result, text
text        textequ isGPReg(parm)
result      =       &text
            if      result ne regNone
            exitm   %result
            endif
            
text        textequ isFPReg(parm)
result      =       &text
            if      result ne regNone
            exitm   %result
            endif
            
text        textequ isMMReg(parm)
result      =       &text
            if      result ne regNone
            exitm   %result
            endif
            
text        textequ isXMMReg(parm)
result      =       &text
            if      result ne regNone
            exitm   %result
            endif
            
text        textequ isYMMReg(parm)
result      =       &text
            if      result ne regNone
            exitm   %result
            endif
            
            exitm   %regNone
            endm    ;whichReg
            
            
            
; regSize-
;
;   Given a register number, this macro function
; returns the size, in bytes, of that register:

regSize     macro   regNum
            local   rn
rn          =       &regNum
            if      (rn lt regAL)
            exitm   <0>
            endif
            if      (rn le regR15B)
            exitm   <1>
            endif
            if      (rn le regR15W)
            exitm   <2>
            endif
            if      (rn le regR15D)
            exitm   <4>
            endif
            if      (rn le regR15)
            exitm   <8>
            endif
            if      (rn le regST7)
            exitm   <10>
            endif
            if      (rn le regMM7)
            exitm   <8>
            endif
            if      (rn le regXMM15)
            exitm   <16>
            endif
            if      (rn le regYMM15)
            exitm   <32>
            endif
            exitm   <0>
            endm    ;regSize


;************************************************************************
;
; Test calls to all the register macros:

            .code
            mout    Converting register numbers to register text
            mout    8-bit register numbers to text conversion:
            
toAL        textequ toReg( regAL )
            mout    toAL=%toAL
            mov     toAL, 0
            
toBL        textequ toReg( regBL )
            mout    toBL=%toBL
            mov     toBL, 0
            
toCL        textequ toReg( regCL )
            mout    toCL=%toCL
            mov     toCL, 0
            
toDL        textequ toReg( regDL )
            mout    toDL=%toDL
            mov     toDL, 0
            
toAH        textequ toReg( regAH )
            mout    toAH=%toAH
            mov     toAH, 0
            
toBH        textequ toReg( regBH )
            mout    toBH=%toBH
            mov     toBH, 0
            
toCH        textequ toReg( regCH )
            mout    toCH=%toCH
            mov     toCH, 0
            
toDH        textequ toReg( regDH )
            mout    toDH=%toDH
            mov     toDH, 0
            
toSIL       textequ toReg( regSIL )
            mout    toSIL=%toSIL
            mov     toSIL, 0
            
toDIL       textequ toReg( regDIL )
            mout    toDIL=%toDIL
            mov     toDIL, 0
            
toBPL       textequ toReg( regBPL )
            mout    toBPL=%toBPL
            mov     toBPL, 0
            
toSPL       textequ toReg( regSPL )
            mout    toSPL=%toSPL
            mov     toSPL, 0
            
toR8B       textequ toReg( regR8B )
            mout    toR8B=%toR8B
            mov     toR8B, 0
            
toR9B       textequ toReg( regR9B )
            mout    toR9B=%toR9B
            mov     toR9B, 0
            
toR10B      textequ toReg( regR10B )
            mout    toR10B=%toR10B
            mov     toR10B, 0
            
toR11B      textequ toReg( regR11B )
            mout    toR11B=%toR11B
            mov     toR11B, 0
            
toR12B      textequ toReg( regR12B )
            mout    toR12B=%toR12B
            mov     toR12B, 0
            
toR13B      textequ toReg( regR13B )
            mout    toR13B=%toR13B
            mov     toR13B, 0
            
toR14B      textequ toReg( regR14B )
            mout    toR14B=%toR14B
            mov     toR14B, 0
            
toR15B      textequ toReg( regR15B )
            mout    toR15B=%toR15B
            mov     toR15B, 0
            
            
            
            mout    16-bit register numbers to text conversion:
            
toAX        textequ toReg( regAX )
            mout    toAX=%toAX
            mov     toAX, 0
            
toBX        textequ toReg( regBX )
            mout    toBX=%toBX
            mov     toBX, 0
            
toCX        textequ toReg( regCX )
            mout    toCX=%toCX
            mov     toCX, 0
            
toDX        textequ toReg( regDX )
            mout    toDX=%toDX
            mov     toDX, 0
            
toSI        textequ toReg( regSI )
            mout    toSI=%toSI
            mov     toSI, 0
            
toDI        textequ toReg( regDI )
            mout    toDI=%toDI
            mov     toDI, 0
            
toBP        textequ toReg( regBP )
            mout    toBP=%toBP
            mov     toBP, 0
            
toSP        textequ toReg( regSP )
            mout    toSP=%toSP
            mov     toSP, 0
            
toR8W       textequ toReg( regR8W )
            mout    toR8W=%toR8W
            mov     toR8W, 0
            
toR9W       textequ toReg( regR9W )
            mout    toR9W=%toR9W
            mov     toR9W, 0
            
toR10W      textequ toReg( regR10W )
            mout    toR10W=%toR10W
            mov     toR10W, 0
            
toR11W      textequ toReg( regR11W )
            mout    toR11W=%toR11W
            mov     toR11W, 0
            
toR12W      textequ toReg( regR12W )
            mout    toR12W=%toR12W
            mov     toR12W, 0
            
toR13W      textequ toReg( regR13W )
            mout    toR13W=%toR13W
            mov     toR13W, 0
            
toR14W      textequ toReg( regR14W )
            mout    toR14W=%toR14W
            mov     toR14W, 0
            
toR15W      textequ toReg( regR15W )
            mout    toR15W=%toR15W
            mov     toR15W, 0
            
            
            
            mout    32-bit register numbers to text conversion:
            
toEAX       textequ toReg( regEAX )
            mout    toEAX=%toEAX
            mov     toEAX, 0
            
toEBX       textequ toReg( regEBX )
            mout    toEBX=%toEBX
            mov     toEBX, 0
            
toECX       textequ toReg( regECX )
            mout    toECX=%toECX
            mov     toECX, 0
            
toEDX       textequ toReg( regEDX )
            mout    toEDX=%toEDX
            mov     toEDX, 0
            
toESI       textequ toReg( regESI )
            mout    toESI=%toESI
            mov     toESI, 0
            
toEDI       textequ toReg( regEDI )
            mout    toEDI=%toEDI
            mov     toDI, 0
            
toEBP       textequ toReg( regEBP )
            mout    toEBP=%toEBP
            mov     toEBP, 0
            
toESP       textequ toReg( regESP )
            mout    toESP=%toESP
            mov     toESP, 0
            
toR8D       textequ toReg( regR8D )
            mout    toR8D=%toR8D
            mov     toR8D, 0
            
toR9D       textequ toReg( regR9D )
            mout    toR9D=%toR9D
            mov     toR9D, 0
            
toR10D      textequ toReg( regR10D )
            mout    toR10D=%toR10D
            mov     toR10D, 0
            
toR11D      textequ toReg( regR11D )
            mout    toR11D=%toR11D
            mov     toR11D, 0
            
toR12D      textequ toReg( regR12D )
            mout    toR12D=%toR12D
            mov     toR12D, 0
            
toR13D      textequ toReg( regR13D )
            mout    toR13D=%toR13D
            mov     toR13D, 0
            
toR14D      textequ toReg( regR14D )
            mout    toR14D=%toR14D
            mov     toR14D, 0
            
toR15D      textequ toReg( regR15D )
            mout    toR15D=%toR15D
            mov     toR15D, 0
            
            
            
            mout    64-bit register numbers to text conversion:
            
toRAX       textequ toReg( regRAX )
            mout    toRAX=%toRAX
            mov     toRAX, 0
            
toRBX       textequ toReg( regRBX )
            mout    toRBX=%toRBX
            mov     toRBX, 0
            
toRCX       textequ toReg( regRCX )
            mout    toRCX=%toRCX
            mov     toRCX, 0
            
toRDX       textequ toReg( regRDX )
            mout    toRDX=%toRDX
            mov     toRDX, 0
            
toRSI       textequ toReg( regRSI )
            mout    toRSI=%toRSI
            mov     toRSI, 0
            
toRDI       textequ toReg( regRDI )
            mout    toRDI=%toRDI
            mov     toDI, 0
            
toRBP       textequ toReg( regRBP )
            mout    toRBP=%toRBP
            mov     toRBP, 0
            
toRSP       textequ toReg( regRSP )
            mout    toRSP=%toRSP
            mov     toRSP, 0
            
toR8        textequ toReg( regR8 )
            mout    toR8=%toR8
            mov     toR8, 0
            
toR9        textequ toReg( regR9 )
            mout    toR9=%toR9
            mov     toR9, 0
            
toR10       textequ toReg( regR10 )
            mout    toR10=%toR10
            mov     toR10, 0
            
toR11       textequ toReg( regR11 )
            mout    toR11=%toR11
            mov     toR11, 0
            
toR12       textequ toReg( regR12 )
            mout    toR12=%toR12
            mov     toR12, 0
            
toR13       textequ toReg( regR13 )
            mout    toR13=%toR13
            mov     toR13, 0
            
toR14       textequ toReg( regR14 )
            mout    toR14=%toR14
            mov     toR14, 0
            
toR15       textequ toReg( regR15 )
            mout    toR15=%toR15
            mov     toR15, 0


            
            
            
            mout    FPU register number to text conversion
            
toST        textequ toReg( regST )
            mout    toST=%toST
            fadd    toST, st(1)     
            
toST0       textequ toReg( regST0 )
            mout    toST0=%toST0
            fadd    toST0, st(1)    
            
toST1       textequ toReg( regST1 )
            mout    toST1=%toST1
            fadd    st, toST1       
            
toST2       textequ toReg( regST2 )
            mout    toST2=%toST2
            fadd    st, toST2       
            
toST3       textequ toReg( regST3 )
            mout    toST3=%toST3
            fadd    st, toST3       
            
toST4       textequ toReg( regST4 )
            mout    toST4=%toST4
            fadd    st, toST4       
            
toST5       textequ toReg( regST5 )
            mout    toST5=%toST5
            fadd    st, toST5       
            
toST6       textequ toReg( regST6 )
            mout    toST6=%toST6
            fadd    st, toST6       
            
toST7       textequ toReg( regST7 )
            mout    toST7=%toST7
            fadd    st, toST7       


            
            
            
            mout    MMX register number to text conversion
            
toMM0       textequ toReg( regMM0 )
            mout    toMM0=%toMM0
            pand    mm0, toMM0      
            
toMM1       textequ toReg( regMM1 )
            mout    toMM1=%toMM1
            pand    mm0, toMM1      
            
toMM2       textequ toReg( regMM2 )
            mout    toMM2=%toMM2
            pand    mm0, toMM2      
            
toMM3       textequ toReg( regMM3 )
            mout    toMM3=%toMM3
            pand    mm0, toMM3      
            
toMM4       textequ toReg( regMM4 )
            mout    toMM4=%toMM4
            pand    mm0, toMM4      
            
toMM5       textequ toReg( regMM5 )
            mout    toMM5=%toMM5
            pand    mm0, toMM5      
            
toMM6       textequ toReg( regMM6 )
            mout    toMM6=%toMM6
            pand    mm0, toMM6      
            
toMM7       textequ toReg( regMM7 )
            mout    toMM7=%toMM7
            pand    mm0, toMM7      


            
            
            
            mout    XMM register number to text conversion
            
toXMM0      textequ toReg( regXMM0 )
            mout    toXMM0=%toXMM0
            pand    xmm0, toXMM0    
            
toXMM1      textequ toReg( regXMM1 )
            mout    toXMM1=%toXMM1
            pand    xmm0, toXMM1    
            
toXMM2      textequ toReg( regXMM2 )
            mout    toXMM2=%toXMM2
            pand    xmm0, toXMM2    
            
toXMM3      textequ toReg( regXMM3 )
            mout    toXMM3=%toXMM3
            pand    xmm0, toXMM3    
            
toXMM4      textequ toReg( regXMM4 )
            mout    toXMM4=%toXMM4
            pand    xmm0, toXMM4    
            
toXMM5      textequ toReg( regXMM5 )
            mout    toXMM5=%toXMM5
            pand    xmm0, toXMM5    
            
toXMM6      textequ toReg( regXMM6 )
            mout    toXMM6=%toXMM6
            pand    xmm0, toXMM6    
            
toXMM7      textequ toReg( regXMM7 )
            mout    toXMM7=%toXMM7
            pand    xmm0, toXMM7    
            
toXMM8      textequ toReg( regXMM8 )
            mout    toXMM8=%toXMM8
            pand    xmm0, toXMM8    
            
toXMM9      textequ toReg( regXMM9 )
            mout    toXMM9=%toXMM9
            pand    xmm0, toXMM9    
            
toXMM10     textequ toReg( regXMM10 )
            mout    toXMM10=%toXMM10
            pand    xmm0, toXMM10   
            
toXMM11     textequ toReg( regXMM11 )
            mout    toXMM11=%toXMM11
            pand    xmm0, toXMM11   
            
toXMM12     textequ toReg( regXMM12 )
            mout    toXMM12=%toXMM12
            pand    xmm0, toXMM12   
            
toXMM13     textequ toReg( regXMM13 )
            mout    toXMM13=%toXMM13
            pand    xmm0, toXMM13   
            
toXMM14     textequ toReg( regXMM14 )
            mout    toXMM14=%toXMM14
            pand    xmm0, toXMM14   
            
toXMM15     textequ toReg( regXMM15 )
            mout    toXMM15=%toXMM15
            pand    xmm0, toXMM15   


            
            
            
            mout    YMM register number to text conversion
            
toYMM0      textequ toReg( regYMM0 )
            mout    toYMM0=%toYMM0
            vpand   ymm0, ymm0, toYMM0      
            
toYMM1      textequ toReg( regYMM1 )
            mout    toYMM1=%toYMM1
            vpand   ymm0, ymm0, toYMM1      
            
toYMM2      textequ toReg( regYMM2 )
            mout    toYMM2=%toYMM2
            vpand   ymm0, ymm0, toYMM2      
            
toYMM3      textequ toReg( regYMM3 )
            mout    toYMM3=%toYMM3
            vpand   ymm0, ymm0, toYMM3      
            
toYMM4      textequ toReg( regYMM4 )
            mout    toYMM4=%toYMM4
            vpand   ymm0, ymm0, toYMM4      
            
toYMM5      textequ toReg( regYMM5 )
            mout    toYMM5=%toYMM5
            vpand   ymm0, ymm0, toYMM5      
            
toYMM6      textequ toReg( regYMM6 )
            mout    toYMM6=%toYMM6
            vpand   ymm0, ymm0, toYMM6      
            
toYMM7      textequ toReg( regYMM7 )
            mout    toYMM7=%toYMM7
            vpand   ymm0, ymm0, toYMM7      
            
toYMM8      textequ toReg( regYMM8 )
            mout    toYMM8=%toYMM8
            vpand   ymm0, ymm0, toYMM8      
            
toYMM9      textequ toReg( regYMM9 )
            mout    toYMM9=%toYMM9
            vpand   ymm0, ymm0, toYMM9      
            
toYMM10     textequ toReg( regYMM10 )
            mout    toYMM10=%toYMM10
            vpand   ymm0, ymm0, toYMM10     
            
toYMM11     textequ toReg( regYMM11 )
            mout    toYMM11=%toYMM11
            vpand   ymm0, ymm0, toYMM11     
            
toYMM12     textequ toReg( regYMM12 )
            mout    toYMM12=%toYMM12
            vpand   ymm0, ymm0, toYMM12     
            
toYMM13     textequ toReg( regYMM13 )
            mout    toYMM13=%toYMM13
            vpand   ymm0, ymm0, toYMM13     
            
toYMM14     textequ toReg( regYMM14 )
            mout    toYMM14=%toYMM14
            vpand   ymm0, ymm0, toYMM14     
            
toYMM15     textequ toReg( regYMM15 )
            mout    toYMM15=%toYMM15
            vpand   ymm0, ymm0, toYMM15     
            
            
            
            
            mout    8-bit to 16-bit register conversion
            
al2ax       textequ reg8To16( regAL )
            mout    al2ax=%al2ax
            mov     al2ax, 0
            
bl2bx       textequ reg8To16( regBL )
            mout    bl2bx=%bl2bx
            mov     bl2bx, 0
            
cl2cx       textequ reg8To16( regCL )
            mout    cl2cx=%cl2cx
            mov     cl2cx, 0
            
dl2dx       textequ reg8To16( regDL )
            mout    dl2dx=%dl2dx
            mov     dl2dx, 0
            
ah2ax       textequ reg8To16( regAH )
            mout    ah2ax=%ah2ax
            mov     ah2ax, 0
            
bh2bx       textequ reg8To16( regBH )
            mout    bh2bx=%bh2bx
            mov     bh2bx, 0
            
ch2cx       textequ reg8To16( regCH )
            mout    ch2cx=%ch2cx
            mov     ch2cx, 0
            
dh2dx       textequ reg8To16( regDH )
            mout    dh2dx=%dh2dx
            mov     dh2dx, 0
            
sil2si      textequ reg8To16( regSIL )
            mout    sil2si=%sil2si
            mov     sil2si, 0
            
dil2di      textequ reg8To16( regDIL )
            mout    dil2di=%dil2di
            mov     dil2di, 0
            
bpl2bp      textequ reg8To16( regBPL )
            mout    bpl2bp=%bpl2bp
            mov     bpl2bp, 0
            
spl2sp      textequ reg8To16( regSPL )
            mout    spl2sp=%spl2sp
            mov     spl2sp, 0
            
r8b2r8w     textequ reg8To16( regR8B )
            mout    r8b2r8w=%r8b2r8w
            mov     r8b2r8w, 0
            
r9b2r9w     textequ reg8To16( regR9B )
            mout    r9b2r9w=%r9b2r9w
            mov     r9b2r9w, 0
            
r10b2r10w   textequ reg8To16( regR10B )
            mout    r10b2r10w=%r10b2r10w
            mov     r10b2r10w, 0
            
r11b2r11w   textequ reg8To16( regR11B )
            mout    r11b2r11w=%r11b2r11w
            mov     r11b2r11w, 0
            
r12b2r12w   textequ reg8To16( regR12B )
            mout    r12b2r12w=%r12b2r12w
            mov     r12b2r12w, 0
            
r13b2r13w   textequ reg8To16( regR13B )
            mout    r13b2r13w=%r13b2r13w
            mov     r13b2r13w, 0
            
r14b2r14w   textequ reg8To16( regR14B )
            mout    r14b2r14w=%r14b2r14w
            mov     r14b2r14w, 0
            
r15b2r15w   textequ reg8To16( regR15B )
            mout    r15b2r15w=%r15b2r15w
            mov     r15b2r15w, 0
            


            
            
            
            mout    8-bit to 32-bit register conversion
            
al2eax      textequ reg8To32( regAL )
            mout    al2eax=%al2eax
            mov     al2eax, 0
            
bl2ebx      textequ reg8To32( regBL )
            mout    bl2ebx=%bl2ebx
            mov     bl2ebx, 0
            
cl2ecx      textequ reg8To32( regCL )
            mout    cl2ecx=%cl2ecx
            mov     cl2ecx, 0
            
dl2edx      textequ reg8To32( regDL )
            mout    dl2edx=%dl2edx
            mov     dl2edx, 0
            
ah2eax      textequ reg8To32( regAH )
            mout    ah2eax=%ah2eax
            mov     ah2eax, 0
            
bh2ebx      textequ reg8To32( regBH )
            mout    bh2ebx=%bh2ebx
            mov     bh2ebx, 0
            
ch2ecx      textequ reg8To32( regCH )
            mout    ch2ecx=%ch2ecx
            mov     ch2ecx, 0
            
dh2edx      textequ reg8To32( regDH )
            mout    dh2edx=%dh2edx
            mov     dh2edx, 0
            
sil2esi     textequ reg8To32( regSIL )
            mout    sil2esi=%sil2esi
            mov     sil2esi, 0
            
dil2edi     textequ reg8To32( regDIL )
            mout    dil2edi=%dil2edi
            mov     dil2edi, 0
            
bpl2ebp     textequ reg8To32( regBPL )
            mout    bpl2ebp=%bpl2ebp
            mov     bpl2ebp, 0
            
spl2esp     textequ reg8To32( regSPL )
            mout    spl2esp=%spl2esp
            mov     spl2esp, 0
            
r8b2r8d     textequ reg8To32( regR8B )
            mout    r8b2r8d=%r8b2r8d
            mov     r8b2r8d, 0
            
r9b2r9d     textequ reg8To32( regR9B )
            mout    r9b2r9d=%r9b2r9d
            mov     r9b2r9d, 0
            
r10b2r10d   textequ reg8To32( regR10B )
            mout    r10b2r10d=%r10b2r10d
            mov     r10b2r10d, 0
            
r11b2r11d   textequ reg8To32( regR11B )
            mout    r11b2r11d=%r11b2r11d
            mov     r11b2r11d, 0
            
r12b2r12d   textequ reg8To32( regR12B )
            mout    r12b2r12d=%r12b2r12d
            mov     r12b2r12d, 0
            
r13b2r13d   textequ reg8To32( regR13B )
            mout    r13b2r13d=%r13b2r13d
            mov     r13b2r13d, 0
            
r14b2r14d   textequ reg8To32( regR14B )
            mout    r14b2r14d=%r14b2r14d
            mov     r14b2r14d, 0
            
r15b2r15d   textequ reg8To32( regR15B )
            mout    r15b2r15d=%r15b2r15d
            mov     r15b2r15d, 0
            


            
            
            
            mout    8-bit to 64-bit register conversion
            
al2rax      textequ reg8To64( regAL )
            mout    al2rax=%al2rax
            mov     al2rax, 0
            
bl2rbx      textequ reg8To64( regBL )
            mout    bl2rbx=%bl2rbx
            mov     bl2rbx, 0
            
cl2rcx      textequ reg8To64( regCL )
            mout    cl2rcx=%cl2rcx
            mov     cl2rcx, 0
            
dl2rdx      textequ reg8To64( regDL )
            mout    dl2rdx=%dl2rdx
            mov     dl2rdx, 0
            
ah2rax      textequ reg8To64( regAH )
            mout    ah2rax=%ah2rax
            mov     ah2rax, 0
            
bh2rbx      textequ reg8To64( regBH )
            mout    bh2rbx=%bh2rbx
            mov     bh2rbx, 0
            
ch2rcx      textequ reg8To64( regCH )
            mout    ch2rcx=%ch2rcx
            mov     ch2rcx, 0
            
dh2rdx      textequ reg8To64( regDH )
            mout    dh2rdx=%dh2rdx
            mov     dh2rdx, 0
            
sil2rsi     textequ reg8To64( regSIL )
            mout    sil2rsi=%sil2rsi
            mov     sil2rsi, 0
            
dil2rdi     textequ reg8To64( regDIL )
            mout    dil2rdi=%dil2rdi
            mov     dil2rdi, 0
            
bpl2rbp     textequ reg8To64( regBPL )
            mout    bpl2rbp=%bpl2rbp
            mov     bpl2rbp, 0
            
spl2rsp     textequ reg8To64( regSPL )
            mout    spl2rsp=%spl2rsp
            mov     spl2rsp, 0
            
r8b2r8      textequ reg8To64( regR8B )
            mout    r8b2r8=%r8b2r8
            mov     r8b2r8, 0
            
r9b2r9      textequ reg8To64( regR9B )
            mout    r9b2r9=%r9b2r9
            mov     r9b2r9, 0
            
r10b2r10    textequ reg8To64( regR10B )
            mout    r10b2r10=%r10b2r10
            mov     r10b2r10, 0
            
r11b2r11    textequ reg8To64( regR11B )
            mout    r11b2r11=%r11b2r11
            mov     r11b2r11, 0
            
r12b2r12    textequ reg8To64( regR12B )
            mout    r12b2r12=%r12b2r12
            mov     r12b2r12, 0
            
r13b2r13    textequ reg8To64( regR13B )
            mout    r13b2r13=%r13b2r13
            mov     r13b2r13, 0
            
r14b2r14    textequ reg8To64( regR14B )
            mout    r14b2r14=%r14b2r14
            mov     r14b2r14, 0
            
r15b2r15    textequ reg8To64( regR15B )
            mout    r15b2r15=%r15b2r15
            mov     r15b2r15, 0
            


            
            
            
            mout    16-bit to 32-bit register conversion
            
ax2eax      textequ reg16To32( regAX )
            mout    ax2eax=%ax2eax
            mov     ax2eax, 0
            
bx2ebx      textequ reg16To32( regBX )
            mout    bx2ebx=%bx2ebx
            mov     bx2ebx, 0
            
cx2ecx      textequ reg16To32( regCX )
            mout    cx2ecx=%cx2ecx
            mov     cx2ecx, 0
            
dx2edx      textequ reg16To32( regDX )
            mout    dx2edx=%dx2edx
            mov     dx2edx, 0
                    
si2esi      textequ reg16To32( regSI )
            mout    si2esi=%si2esi
            mov     si2esi, 0
            
di2edi      textequ reg16To32( regDI )
            mout    di2edi=%di2edi
            mov     di2edi, 0
            
bp2ebp      textequ reg16To32( regBP )
            mout    bp2ebp=%bp2ebp
            mov     bp2ebp, 0
            
sp2esp      textequ reg16To32( regSP )
            mout    sp2esp=%sp2esp
            mov     sp2esp, 0
            
r8w2r8d     textequ reg16To32( regR8W )
            mout    r8w2r8d=%r8w2r8d
            mov     r8w2r8d, 0
            
r9w2r9d     textequ reg16To32( regR9W )
            mout    r9w2r9d=%r9w2r9d
            mov     r9w2r9d, 0
            
r10w2r10d   textequ reg16To32( regR10W )
            mout    r10w2r10d=%r10w2r10d
            mov     r10w2r10d, 0
            
r11w2r11d   textequ reg16To32( regR11W )
            mout    r11w2r11d=%r11w2r11d
            mov     r11w2r11d, 0
            
r12w2r12d   textequ reg16To32( regR12W )
            mout    r12w2r12d=%r12w2r12d
            mov     r12w2r12d, 0
            
r13w2r13d   textequ reg16To32( regR13W )
            mout    r13w2r13d=%r13w2r13d
            mov     r13w2r13d, 0
            
r14w2r14d   textequ reg16To32( regR14W )
            mout    r14w2r14d=%r14w2r14d
            mov     r14w2r14d, 0
            
r15w2r15d   textequ reg16To32( regR15W )
            mout    r15w2r15d=%r15w2r15d
            mov     r15w2r15d, 0


            
            
            
            mout    16-bit to 64-bit register conversion
            
ax2rax      textequ reg16To64( regAX )
            mout    ax2rax=%ax2rax
            mov     ax2rax, 0
            
bx2rbx      textequ reg16To64( regBX )
            mout    bx2rbx=%bx2rbx
            mov     bx2rbx, 0
            
cx2rcx      textequ reg16To64( regCX )
            mout    cx2rcx=%cx2rcx
            mov     cx2rcx, 0
            
dx2rdx      textequ reg16To64( regDX )
            mout    dx2rdx=%dx2rdx
            mov     dx2rdx, 0
                    
si2rsi      textequ reg16To64( regSI )
            mout    si2rsi=%si2rsi
            mov     si2rsi, 0
            
di2rdi      textequ reg16To64( regDI )
            mout    di2rdi=%di2rdi
            mov     di2rdi, 0
            
bp2rbp      textequ reg16To64( regBP )
            mout    bp2rbp=%bp2rbp
            mov     bp2rbp, 0
            
sp2rsp      textequ reg16To64( regSP )
            mout    sp2rsp=%sp2rsp
            mov     sp2rsp, 0
            
r8w2r8      textequ reg16To64( regR8W )
            mout    r8w2r8=%r8w2r8
            mov     r8w2r8, 0
            
r9w2r9      textequ reg16To64( regR9W )
            mout    r9w2r9=%r9w2r9
            mov     r9w2r9, 0
            
r10w2r10    textequ reg16To64( regR10W )
            mout    r10w2r10=%r10w2r10
            mov     r10w2r10, 0
            
r11w2r11    textequ reg16To64( regR11W )
            mout    r11w2r11=%r11w2r11
            mov     r11w2r11, 0
            
r12w2r12    textequ reg16To64( regR12W )
            mout    r12w2r12=%r12w2r12
            mov     r12w2r12, 0
            
r13w2r13    textequ reg16To64( regR13W )
            mout    r13w2r13=%r13w2r13
            mov     r13w2r13, 0
            
r14w2r14    textequ reg16To64( regR14W )
            mout    r14w2r14=%r14w2r14
            mov     r14w2r14, 0
            
r15w2r15    textequ reg16To64( regR15W )
            mout    r15w2r15=%r15w2r15
            mov     r15w2r15, 0


            
            
            
            mout    32-bit to 64-bit register conversion
            
eax2rax     textequ reg32To64( regEAX )
            mout    eax2rax=%eax2rax
            mov     eax2rax, 0
            
ebx2rbx     textequ reg32To64( regEBX )
            mout    ebx2rbx=%ebx2rbx
            mov     ebx2rbx, 0
            
ecx2rcx     textequ reg32To64( regECX )
            mout    ecx2rcx=%ecx2rcx
            mov     ecx2rcx, 0
            
edx2rdx     textequ reg32To64( regEDX )
            mout    edx2rdx=%edx2rdx
            mov     edx2rdx, 0
                    
esi2rsi     textequ reg32To64( regESI )
            mout    esi2rsi=%esi2rsi
            mov     esi2rsi, 0
            
edi2rdi     textequ reg32To64( regEDI )
            mout    edi2rdi=%edi2rdi
            mov     edi2rdi, 0
            
ebp2rbp     textequ reg32To64( regEBP )
            mout    ebp2rbp=%ebp2rbp
            mov     ebp2rbp, 0
            
esp2rsp     textequ reg32To64( regESP )
            mout    esp2rsp=%esp2rsp
            mov     esp2rsp, 0
            
r8d2r8      textequ reg32To64( regR8D )
            mout    r8d2r8=%r8d2r8
            mov     r8d2r8, 0
            
r9d2r9      textequ reg32To64( regR9D )
            mout    r9d2r9=%r9d2r9
            mov     r9d2r9, 0
            
r10d2r10    textequ reg32To64( regR10D )
            mout    r10d2r10=%r10d2r10
            mov     r10d2r10, 0
            
r11d2r11    textequ reg32To64( regR11D )
            mout    r11d2r11=%r11d2r11
            mov     r11d2r11, 0
            
r12d2r12    textequ reg32To64( regR12D )
            mout    r12d2r12=%r12d2r12
            mov     r12d2r12, 0
            
r13d2r13    textequ reg32To64( regR13D )
            mout    r13d2r13=%r13d2r13
            mov     r13d2r13, 0
            
r14d2r14    textequ reg32To64( regR14D )
            mout    r14d2r14=%r14d2r14
            mov     r14d2r14, 0
            
r15d2r15    textequ reg32To64( regR15D )
            mout    r15d2r15=%r15d2r15
            mov     r15d2r15, 0



            mout    toUpper demonstrations

HelloWorld  textequ toUpper( <Hello, World> )
            mout    HelloWorld=%HelloWorld

LCAlphas    textequ toUpper( abcdefghijklmnopqrstuvwxyz )
            mout    LCAlphas=%LCAlphas

UCAlphas    textequ toUpper( ABCDEFGHIJKLMNOPQRSTUVWXYZ )
            mout    UCAlphas=%UCAlphas

digits      textequ toUpper( 0123456789 )
            mout    digits=%digits



            mout    8-bit isReg tests

isAL        =       isReg( al )
            mout    isAL=%(isAL and 1)
isBL        =       isReg( bl )
            mout    isBL=%(isBL and 1)
isCL        =       isReg( cl )
            mout    isCL=%(isCL and 1)
isDL        =       isReg( dl )
            mout    isDL=%(isDL and 1)
            
isAH        =       isReg( ah )
            mout    isAH=%(isAH and 1)
isBH        =       isReg( bh )
            mout    isBH=%(isBH and 1)
isCH        =       isReg( ch )
            mout    isCH=%(isCH and 1)
isDH        =       isReg( dh )
            mout    isDH=%(isDH and 1)
            
isSIL       =       isReg( sil )
            mout    isSIL=%(isSIL and 1)
isDIL       =       isReg( dil )
            mout    isDIL=%(isDIL and 1)
isBPL       =       isReg( bpl )
            mout    isBPL=%(isBPL and 1)
isSPL       =       isReg( spl )
            mout    isSPL=%(isSPL and 1)
            
isR8B       =       isReg( r8b )
            mout    isR8B=%(isR8B and 1)
isR9B       =       isReg( r9b )
            mout    isR9B=%(isR9B and 1)
isR10B      =       isReg( r10b )
            mout    isR10B=%(isR10B and 1)
isR11B      =       isReg( r11b )
            mout    isR11B=%(isR11B and 1)
isR12B      =       isReg( r12b )
            mout    isR12B=%(isR12B and 1)
isR13B      =       isReg( r13b )
            mout    isR13B=%(isR13B and 1)
isR14B      =       isReg( r14b )
            mout    isR14B=%(isR14B and 1)
isR15B      =       isReg( r15b )
            mout    isR15B=%(isR15B and 1)





            mout    16-bit isReg tests

isAX        =       isReg( ax )
            mout    isAX=%(isAX and 1)
isBX        =       isReg( bx )
            mout    isBX=%(isBX and 1)
isCX        =       isReg( cx )
            mout    isCX=%(isCX and 1)
isDX        =       isReg( dx )
            mout    isDX=%(isDX and 1)
                    
isSI        =       isReg( si )
            mout    isSI=%(isSI and 1)
isDI        =       isReg( di )
            mout    isDI=%(isDI and 1)
isBP        =       isReg( bp )
            mout    isBP=%(isBP and 1)
isSP        =       isReg( sp )
            mout    isSP=%(isSP and 1)
            
isR8W       =       isReg( r8w )
            mout    isR8W=%(isR8W and 1)
isR9W       =       isReg( r9w )
            mout    isR9W=%(isR9W and 1)
isR10W      =       isReg( r10w )
            mout    isR10W=%(isR10W and 1)
isR11W      =       isReg( r11w )
            mout    isR11W=%(isR11W and 1)
isR12W      =       isReg( r12w )
            mout    isR12W=%(isR12W and 1)
isR13W      =       isReg( r13w )
            mout    isR13W=%(isR13W and 1)
isR14W      =       isReg( r14w )
            mout    isR14W=%(isR14W and 1)
isR15W      =       isReg( r15w )
            mout    isR15W=%(isR15W and 1)
            


            mout    8-bit register values
            
alReg       =       is8BitReg( al )
            mout    alReg  = %alReg
blReg       =       is8BitReg( bl )
            mout    blReg  = %blReg
clReg       =       is8BitReg( cl )
            mout    clReg  = %clReg
dlReg       =       is8BitReg( dl )
            mout    dlReg  = %dlReg

ahReg       =       is8BitReg( ah )
            mout    ahReg  = %ahReg
bhReg       =       is8BitReg( bl )
            mout    bhReg  = %bhReg
chReg       =       is8BitReg( ch )
            mout    chReg  = %chReg
dhReg       =       is8BitReg( dh )
            mout    dhReg  = %dhReg

silReg      =       is8BitReg( sil )
            mout    silReg  = %silReg
dilReg      =       is8BitReg( dil )
            mout    dilReg  = %dilReg
bplReg      =       is8BitReg( bpl )
            mout    bplReg  = %bplReg
splReg      =       is8BitReg( spl )
            mout    splReg  = %splReg

r8bReg      =       is8BitReg( r8b )
            mout    r8bReg  = %r8bReg
r9bReg      =       is8BitReg( r9b )
            mout    r9bReg  = %r9bReg
r10bReg     =       is8BitReg( r10b )
            mout    r10bReg  = %r10bReg
r11bReg     =       is8BitReg( r11b )
            mout    r11bReg  = %r11bReg
r12bReg     =       is8BitReg( r12b )
            mout    r12bReg  = %r12bReg
r13bReg     =       is8BitReg( r13b )
            mout    r13bReg  = %r13bReg
r14bReg     =       is8BitReg( r14b )
            mout    r14bReg  = %r14bReg
r15bReg     =       is8BitReg( r15b )
            mout    r15bReg  = %r15bReg


            mout    16-bit Register Values
            
axReg       =       is16BitReg( ax )
            mout    axReg  = %axReg
bxReg       =       is16BitReg( bx )
            mout    bxReg  = %bxReg
cxReg       =       is16BitReg( cx )
            mout    cxReg  = %cxReg
dxReg       =       is16BitReg( dx )
            mout    dxReg  = %dxReg

siReg       =       is16BitReg( si )
            mout    siReg  = %siReg
diReg       =       is16BitReg( di )
            mout    diReg  = %diReg
bpReg       =       is16BitReg( bp )
            mout    bpReg  = %bpReg
spReg       =       is16BitReg( sp )
            mout    spReg  = %spReg

r8wReg      =       is16BitReg( r8w )
            mout    r8wReg  = %r8wReg
r9wReg      =       is16BitReg( r9w )
            mout    r9wReg  = %r9wReg
r10wReg     =       is16BitReg( r10w )
            mout    r10wReg  = %r10wReg
r11wReg     =       is16BitReg( r11w )
            mout    r11wReg  = %r11wReg
r12wReg     =       is16BitReg( r12w )
            mout    r12wReg  = %r12wReg
r13wReg     =       is16BitReg( r13w )
            mout    r13wReg  = %r13wReg
r14wReg     =       is16BitReg( r14w )
            mout    r14wReg  = %r14wReg
r15wReg     =       is16BitReg( r15w )
            mout    r15wReg  = %r15wReg

            mout    32-bit Register Values
            
eaxReg      =       is32BitReg( eax )
            mout    eaxReg  = %eaxReg
ebxReg      =       is32BitReg( ebx )
            mout    ebxReg  = %ebxReg
ecxReg      =       is32BitReg( ecx )
            mout    ecxReg  = %ecxReg
edxReg      =       is32BitReg( edx )
            mout    edxReg  = %edxReg

esiReg      =       is32BitReg( esi )
            mout    esiReg  = %esiReg
ediReg      =       is32BitReg( edi )
            mout    ediReg  = %ediReg
ebpReg      =       is32BitReg( ebp )
            mout    ebpReg  = %ebpReg
espReg      =       is32BitReg( esp )
            mout    espReg  = %espReg

r8dReg      =       is32BitReg( r8d )
            mout    r8dReg  = %r8dReg
r9dReg      =       is32BitReg( r9d )
            mout    r9dReg  = %r9dReg
r10dReg     =       is32BitReg( r10d )
            mout    r10dReg  = %r10dReg
r11dReg     =       is32BitReg( r11d )
            mout    r11dReg  = %r11dReg
r12dReg     =       is32BitReg( r12d )
            mout    r12dReg  = %r12dReg
r13dReg     =       is32BitReg( r13d )
            mout    r13dReg  = %r13dReg
r14dReg     =       is32BitReg( r14d )
            mout    r14dReg  = %r14dReg
r15dReg     =       is32BitReg( r15d )
            mout    r15dReg  = %r15dReg
            
            mout    64-bit Register Values
            
raxReg      =       is64BitReg( rax )
            mout    raxReg  = %raxReg
rbxReg      =       is64BitReg( rbx )
            mout    rbxReg  = %rbxReg
rcxReg      =       is64BitReg( rcx )
            mout    rcxReg  = %rcxReg
rdxReg      =       is64BitReg( rdx )
            mout    rdxReg  = %rdxReg

rsiReg      =       is64BitReg( rsi )
            mout    rsiReg  = %rsiReg
rdiReg      =       is64BitReg( rdi )
            mout    rdiReg  = %rdiReg
rbpReg      =       is64BitReg( rbp )
            mout    rbpReg  = %rbpReg
rspReg      =       is64BitReg( rsp )
            mout    rspReg  = %rspReg

r8Reg       =       is64BitReg( r8 )
            mout    r8Reg  = %r8Reg
r9Reg       =       is64BitReg( r9 )
            mout    r9Reg  = %r9Reg
r10Reg      =       is64BitReg( r10 )
            mout    r10Reg  = %r10Reg
r11Reg      =       is64BitReg( r11 )
            mout    r11Reg  = %r11Reg
r12Reg      =       is64BitReg( r12 )
            mout    r12Reg  = %r12Reg
r13Reg      =       is64BitReg( r13 )
            mout    r13Reg  = %r13Reg
r14Reg      =       is64BitReg( r14 )
            mout    r14Reg  = %r14Reg
r15Reg      =       is64BitReg( r15 )
            mout    r15Reg  = %r15Reg
            
            
            mout    General-Purpose Register Tests
            
gpAL        =       isGPReg( al )
            mout    gpAL  = %gpAL

gpAX        =       isGPReg( ax )
            mout    gpAX  = %gpAX

gpEAX       =       isGPReg( eax )
            mout    gpEAX  = %gpEAX

gpRAX       =       isGPReg( rax )
            mout    gpRAX  = %gpRAX

gpST        =       isGPReg( st )
            mout    gpST  = %gpST
            

            mout    FPU Register Values
            
stReg       =       isFPReg( st )
            mout    stReg  = %stReg
st0Reg      =       isFPReg( st(0) )
            mout    st0Reg  = %st0Reg
st1Reg      =       isFPReg( st(1) )
            mout    st1Reg  = %st1Reg
st2Reg      =       isFPReg( st(2) )
            mout    st2Reg  = %st2Reg
st3Reg      =       isFPReg( st(3) )
            mout    st3Reg  = %st3Reg
st4Reg      =       isFPReg( st(4) )
            mout    st4Reg  = %st4Reg
st5Reg      =       isFPReg( st(5) )
            mout    st5Reg  = %st5Reg
st6Reg      =       isFPReg( st(6) )
            mout    st6Reg  = %st6Reg
st7Reg      =       isFPReg( st(7) )
            mout    st7Reg  = %st7Reg
            

            mout    MMX Register Values
            
mm0Reg      =       isMMReg( mm0 )
            mout    mm0Reg  = %mm0Reg
mm1Reg      =       isMMReg( mm1 )
            mout    mm1Reg  = %mm1Reg
mm2Reg      =       isMMReg( mm2 )
            mout    mm2Reg  = %mm2Reg
mm3Reg      =       isMMReg( mm3 )
            mout    mm3Reg  = %mm3Reg
mm4Reg      =       isMMReg( mm4 )
            mout    mm4Reg  = %mm4Reg
mm5Reg      =       isMMReg( mm5 )
            mout    mm5Reg  = %mm5Reg
mm6Reg      =       isMMReg( mm6 )
            mout    mm6Reg  = %mm6Reg
mm7Reg      =       isMMReg( mm7 )
            mout    mm7Reg  = %mm7Reg
            

            mout    XMM Register Values
            
xmm0Reg     =       isXMMReg( xmm0 )
            mout    xmm0Reg  = %xmm0Reg
xmm1Reg     =       isXMMReg( xmm1 )
            mout    xmm1Reg  = %xmm1Reg
xmm2Reg     =       isXMMReg( xmm2 )
            mout    xmm2Reg  = %xmm2Reg
xmm3Reg     =       isXMMReg( xmm3 )
            mout    xmm3Reg  = %xmm3Reg
xmm4Reg     =       isXMMReg( xmm4 )
            mout    xmm4Reg  = %xmm4Reg
xmm5Reg     =       isXMMReg( xmm5 )
            mout    xmm5Reg  = %xmm5Reg
xmm6Reg     =       isXMMReg( xmm6 )
            mout    xmm6Reg  = %xmm6Reg
xmm7Reg     =       isXMMReg( xmm7 )
            mout    xmm7Reg  = %xmm7Reg
xmm8Reg     =       isXMMReg( xmm8 )
            mout    xmm8Reg  = %xmm8Reg
xmm9Reg     =       isXMMReg( xmm9 )
            mout    xmm9Reg  = %xmm9Reg
xmm10Reg    =       isXMMReg( xmm10 )
            mout    xmm10Reg  = %xmm10Reg
xmm11Reg    =       isXMMReg( xmm11 )
            mout    xmm11Reg  = %xmm11Reg
xmm12Reg    =       isXMMReg( xmm12 )
            mout    xmm12Reg  = %xmm12Reg
xmm13Reg    =       isXMMReg( xmm13 )
            mout    xmm13Reg  = %xmm13Reg
xmm14Reg    =       isXMMReg( xmm14 )
            mout    xmm14Reg  = %xmm14Reg
xmm15Reg    =       isXMMReg( xmm15 )
            mout    xmm15Reg  = %xmm15Reg
            

            mout    YMM Register Values
            
ymm0Reg     =       isYMMReg( ymm0 )
            mout    ymm0Reg  = %ymm0Reg
ymm1Reg     =       isYMMReg( ymm1 )
            mout    ymm1Reg  = %ymm1Reg
ymm2Reg     =       isYMMReg( ymm2 )
            mout    ymm2Reg  = %ymm2Reg
ymm3Reg     =       isYMMReg( ymm3 )
            mout    ymm3Reg  = %ymm3Reg
ymm4Reg     =       isYMMReg( ymm4 )
            mout    ymm4Reg  = %ymm4Reg
ymm5Reg     =       isYMMReg( ymm5 )
            mout    ymm5Reg  = %ymm5Reg
ymm6Reg     =       isYMMReg( ymm6 )
            mout    ymm6Reg  = %ymm6Reg
ymm7Reg     =       isYMMReg( ymm7 )
            mout    ymm7Reg  = %ymm7Reg
ymm8Reg     =       isYMMReg( ymm8 )
            mout    ymm8Reg  = %ymm8Reg
ymm9Reg     =       isYMMReg( ymm9 )
            mout    ymm9Reg  = %ymm9Reg
ymm10Reg    =       isYMMReg( ymm10 )
            mout    ymm10Reg  = %ymm10Reg
ymm11Reg    =       isYMMReg( ymm11 )
            mout    ymm11Reg  = %ymm11Reg
ymm12Reg    =       isYMMReg( ymm12 )
            mout    ymm12Reg  = %ymm12Reg
ymm13Reg    =       isYMMReg( ymm13 )
            mout    ymm13Reg  = %ymm13Reg
ymm14Reg    =       isYMMReg( ymm14 )
            mout    ymm14Reg  = %ymm14Reg
ymm15Reg    =       isYMMReg( ymm15 )
            mout    ymm15Reg  = %ymm15Reg


            mout    whichReg- generic register encoding
            
whAL        textequ whichReg( al )
            mout    whAL  = %whAL
            
wAX         textequ whichReg( ax )
            mout    wAX  = %wAX
            
wEAX        textequ whichReg( eax )
            mout    wEAX  = %wEAX
            
wRAX        textequ whichReg( rax )
            mout    wRAX  = %wRAX
            
wST         textequ whichReg( st )
            mout    wST  = %wST
            
wMM0        textequ whichReg( mm0 )
            mout    wMM0  = %wMM0
            
wXMM0       textequ whichReg( xmm0 )
            mout    wXMM0  = %wXMM0
            
wYMM0       textequ whichReg( ymm0 )
            mout    wYMM0  = %wYMM0
            
wNotReg     textequ whichReg( notAReg )
            mout    wNotReg  = %wNotReg
            


            mout    regSize- Computing register size in bytes
            
rsAL        =       regSize( regAL )
            mout    rsAL  = %rsAL
            
rsAX        =       regSize( regAX )
            mout    rsAX  = %rsAX
            
rsEAX       =       regSize( regEAX )
            mout    rsEAX  = %rsEAX
            
rsRAX       =       regSize( regRAX )
            mout    rsRAX  = %rsRAX
            
rsST        =       regSize( regST )
            mout    rsST  = %rsST
            
rsMM0       =       regSize( regMM0 )
            mout    rsMM0  = %rsMM0
            
rsXMM0      =       regSize( regXMM0 )
            mout    rsXMM0  = %rsXMM0
            
rsYMM0      =       regSize( regYMM0 )
            mout    rsYMM0  = %rsYMM0
            
rsNotReg    =       regSize( regNone )
            mout    rsNotReg  = %rsNotReg
            end








                     