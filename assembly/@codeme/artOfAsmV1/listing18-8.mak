listing18-8.exe: partialCmp1.obj partialCmp2.obj \
                 partialCmp3.obj substring1.obj \
				 printString.obj stringAlloc.obj \
				 listing18-8.obj
                 
    cl /nologo /O2 /Zi /utf-8 /EHa /Felisting18-8.exe c.cpp \
                 partialCmp1.obj partialCmp2.obj \
                 partialCmp3.obj substring1.obj \
				 printString.obj  stringAlloc.obj \
				 listing18-8.obj            
    
partialCmp1.obj: partialCmp1.asm string.inc
    ml64 /c /nologo partialCmp1.asm
                     
partialCmp2.obj: partialCmp2.asm string.inc
    ml64 /c /nologo partialCmp2.asm
                     
partialCmp3.obj: partialCmp3.asm string.inc
    ml64 /c /nologo partialCmp3.asm
                                                                                                                             
                                                                                                                             
printString.obj: printString.asm string.inc
    ml64 /c /nologo printString.asm
                                                                                                                             
substring1.obj: substring1.asm string.inc
    ml64 /c /nologo substring1.asm
                                                                                                                             
stringAlloc.obj: stringAlloc.asm string.inc
    ml64 /c /nologo stringAlloc.asm
                                                                                                                             

listing18-8.obj: listing18-8.asm string.inc
    ml64 /c /nologo listing18-8.asm
