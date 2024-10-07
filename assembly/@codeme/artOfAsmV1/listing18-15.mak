listing18-15.exe: stringTrim.obj incMove.obj \
                 deleteWS.obj deleteTrailingWS.obj \
				 listing18-15.obj
                 
    cl /nologo /O2 /Zi /utf-8 /EHa /Felisting18-15.exe c.cpp \
                 stringTrim.obj incMove.obj \
                 deleteWS.obj deleteTrailingWS.obj \
				 listing18-15.obj            
    
stringTrim.obj: stringTrim.asm string.inc
    ml64 /c /nologo stringTrim.asm
                     
incMove.obj: incMove.asm string.inc
    ml64 /c /nologo incMove.asm
                     
deleteWS.obj: deleteWS.asm string.inc
    ml64 /c /nologo deleteWS.asm
                     
deleteTrailingWS.obj: deleteTrailingWS.asm string.inc
    ml64 /c /nologo deleteTrailingWS.asm
                     
listing18-15.obj: listing18-15.asm string.inc
    ml64 /c /nologo listing18-15.asm
