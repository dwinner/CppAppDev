listing18-16.exe: stringUpper.obj stringLower.obj \
				  caseData.obj listing18-16.obj
                 
    cl /nologo /O2 /Zi /utf-8 /EHa /Felisting18-16.exe c.cpp \
                 stringUpper.obj stringLower.obj \
				 caseData.obj listing18-16.obj            
    
stringUpper.obj: stringUpper.asm string.inc
    ml64 /c /nologo stringUpper.asm
                                          
stringLower.obj: stringLower.asm string.inc
    ml64 /c /nologo stringLower.asm
                     
caseData.obj: caseData.asm string.inc
    ml64 /c /nologo caseData.asm
                     
listing18-16.obj: listing18-16.asm string.inc
    ml64 /c /nologo listing18-16.asm
