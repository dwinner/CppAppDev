listing18-14.exe: stringCmp1.obj incMove.obj \
                 decMove.obj stringDelete.obj \
				 listing18-14.obj
                 
    cl /nologo /O2 /Zi /utf-8 /EHa /Felisting18-14.exe c.cpp \
                 stringCmp1.obj incMove.obj \
                 decMove.obj stringDelete.obj \
				 listing18-14.obj            
    
stringCmp1.obj: stringCmp1.asm string.inc
    ml64 /c /nologo stringCmp1.asm
                     
incMove.obj: incMove.asm string.inc
    ml64 /c /nologo incMove.asm
                     
decMove.obj: decMove.asm string.inc
    ml64 /c /nologo decMove.asm
                     
stringDelete.obj: stringDelete.asm string.inc
    ml64 /c /nologo stringDelete.asm
                     
listing18-14.obj: listing18-14.asm string.inc
    ml64 /c /nologo listing18-14.asm
