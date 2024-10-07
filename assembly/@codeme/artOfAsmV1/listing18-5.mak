listing18-5.exe: stringCmp1.obj stringCmp2.obj \
				 stringCmp3.obj stringCmp4.obj listing18-5.obj
                 
    cl /nologo /O2 /Zi /utf-8 /EHa /Felisting18-5.exe c.cpp \
                 stringCmp1.obj stringCmp2.obj \
				 stringCmp3.obj stringCmp4.obj \
				 listing18-5.obj            
    
stringCmp1.obj: stringCmp1.asm string.inc
    ml64 /c /nologo stringCmp1.asm
                     
stringCmp2.obj: stringCmp2.asm string.inc
    ml64 /c /nologo stringCmp2.asm
                     
stringCmp3.obj: stringCmp3.asm string.inc
    ml64 /c /nologo stringCmp3.asm
                     
stringCmp4.obj: stringCmp4.asm string.inc
    ml64 /c /nologo stringCmp4.asm
                                          
                     
listing18-5.obj: listing18-5.asm string.inc
    ml64 /c /nologo listing18-5.asm              
