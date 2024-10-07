listing18-17.exe: stringCaseCmp.obj  \
				  caseData.obj listing18-17.obj
                 
    cl /nologo /O2 /Zi /utf-8 /EHa /Felisting18-17.exe c.cpp \
                 stringCaseCmp.obj  \
				 caseData.obj listing18-17.obj            
    
stringCaseCmp.obj: stringCaseCmp.asm string.inc
    ml64 /c /nologo stringCaseCmp.asm
                                          
caseData.obj: caseData.asm string.inc
    ml64 /c /nologo caseData.asm
                     
listing18-17.obj: listing18-17.asm string.inc
    ml64 /c /nologo listing18-17.asm
