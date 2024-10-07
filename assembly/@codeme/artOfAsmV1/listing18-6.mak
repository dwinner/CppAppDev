listing18-6.exe: substring1.obj substring2.obj \
                 stringCmp1.obj printString.obj \
				 listing18-6.obj
                 
    cl /nologo /O2 /Zi /utf-8 /EHa /Felisting18-6.exe c.cpp \
                 substring1.obj substring2.obj \
                 stringCmp1.obj printString.obj	\
				 listing18-6.obj            
    
substring1.obj: substring1.asm string.inc
    ml64 /c /nologo substring1.asm
                     
substring2.obj: substring2.asm string.inc
    ml64 /c /nologo substring2.asm
                     
stringCmp1.obj: stringCmp1.asm string.inc
    ml64 /c /nologo stringCmp1.asm
                                                                                                                             
printString.obj: printString.asm string.inc
    ml64 /c /nologo printString.asm
                                                                                                                             

listing18-6.obj: listing18-6.asm string.inc
    time /t
    ml64 /c /nologo listing18-6.asm
    time /t              
