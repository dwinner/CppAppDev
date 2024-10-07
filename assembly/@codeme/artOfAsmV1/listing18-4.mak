listing18-4.exe: stringCpy1.obj stringCpy2.obj \
				 stringInit.obj listing18-4.obj
                 
    cl /nologo /O2 /Zi /utf-8 /EHa /Felisting18-4.exe c.cpp \
                 stringCpy1.obj stringCpy2.obj \
				 stringInit.obj listing18-4.obj            
    
stringCpy1.obj: stringCpy1.asm string.inc
    ml64 /c /nologo stringCpy1.asm
                     
stringCpy2.obj: stringCpy2.asm string.inc
    ml64 /c /nologo stringCpy2.asm
                     
stringInit.obj: stringInit.asm string.inc
    ml64 /c /nologo stringInit.asm
                     
                     
listing18-4.obj: listing18-4.asm string.inc
    ml64 /c /nologo listing18-4.asm              
