listing18-13.exe: stringCmp1.obj incMove.obj \
                 decMove.obj stringInsert.obj \
				 stringAlloc.obj  stringInit.obj \
				 listing18-13.obj
                 
    cl /nologo /O2 /Zi /utf-8 /EHa /Felisting18-13.exe c.cpp \
                 stringCmp1.obj incMove.obj \
                 decMove.obj stringInsert.obj \
				 stringAlloc.obj stringInit.obj	\
				 listing18-13.obj            
    
stringCmp1.obj: stringCmp1.asm string.inc
    ml64 /c /nologo stringCmp1.asm
                     
incMove.obj: incMove.asm string.inc
    ml64 /c /nologo incMove.asm
                     
decMove.obj: decMove.asm string.inc
    ml64 /c /nologo decMove.asm
                     
stringInsert.obj: stringInsert.asm string.inc
    ml64 /c /nologo stringInsert.asm
                     
stringAlloc.obj: stringAlloc.asm string.inc
    ml64 /c /nologo stringAlloc.asm
                     
stringInit.obj: stringInit.asm string.inc
    ml64 /c /nologo stringInit.asm
                     
listing18-13.obj: listing18-13.asm string.inc
    ml64 /c /nologo listing18-13.asm
