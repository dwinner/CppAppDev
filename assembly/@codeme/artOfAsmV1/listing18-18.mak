listing18-18.exe: stringCaseCmp.obj  stringCmp2.obj \
				  caseData.obj listing18-18.obj
                 
    cl /nologo /O2 /Zi /utf-8 /EHa /Felisting18-18.exe c.cpp \
                 stringCaseCmp.obj  stringCmp2.obj  \
				 caseData.obj listing18-18.obj            
    
stringCaseCmp.obj: stringCaseCmp.asm string.inc
    ml64 /c /nologo stringCaseCmp.asm
                                          
stringCmp2.obj: stringCmp2.asm string.inc
    ml64 /c /nologo stringCmp2.asm
                                          
caseData.obj: caseData.asm string.inc
    ml64 /c /nologo caseData.asm
                     
listing18-18.obj: listing18-18.asm string.inc
    ml64 /c /nologo listing18-18.asm
