; Listing 13-12
;
; Demonstration of putInt macro

        option  casemap:none

nl          =       10

            .const
ttlStr      byte    "Listing 13-12", 0

	include	getTitle.inc
	include	print.inc


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
            .code


; putInt
;
;  This macro expects an 8-, 16-, or 32-bit
; general-purpose register argument. It will
; print the value of that register as an
; integer.

putInt      macro   theReg
            local   regVal, sz
regVal      =       isGPReg(theReg)

; Before we do anything else, make sure
; we were actually passed a register:

            if      regVal eq regNone
            .err    <Expected a register>
            endif

; Get the size of the register so we can
; determine if we need to sign extend its
; value:
            
sz          =       regSize(regVal)

; If it was a 64-bit register, report an
; error:

            if      sz gt 4
            .err    <64-bit register not allowed>
            endif

; If it's a 1- or 2-byte register, we will need
; to sign extend the value into EDX:
            
            if      (sz eq 1) or (sz eq 2)
            movsx   edx, theReg
            
; If it's a 32-bit, but is not EDX, we need
; to move it into EDX (don't bother emitting
; the instruction if the register is EDX-
; the data is already where we want it):
 
            elseif  regVal ne regEDX
            mov     edx, theReg
            endif
            
; Print the value in EDX as an integer:

            call    print
            byte    "%d", 0
            endm
                        
                    
            
; Here is the "asmMain" function.

        
            public  asmMain
asmMain     proc
            push    rbx
            push    rbp
            mov     rbp, rsp
            sub     rsp, 56         ;Shadow storage
            
            call    print
            byte    "Value 1:", 0
            mov     al, 55
            putInt  al
            
            call    print
            byte    nl, "Value 2:", 0
            mov     cx, 1234
            putInt  cx
            
            call    print
            byte    nl, "Value 3:", 0
            mov     ebx, 12345678
            putInt  ebx
            
            call    print
            byte    nl, "Value 4:", 0
            mov     edx, 1
            putInt  edx
            call    print
            byte    nl, 0
            
            
            
             
allDone:    leave
            pop     rbx
            ret     ;Returns to caller
asmMain     endp
            end

            end








                     