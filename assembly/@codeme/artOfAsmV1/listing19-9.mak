listing19-9.exe: stringAlloc.obj  csetToPCset.obj \
				stringFree.obj fscanCset.obj skipCset.obj \
				csetToRange.obj fscanToCset.obj \
				substring2.obj substring1.obj skipToCset.obj \
				stringTokenize.obj listing19-9.obj
    cl /nologo /O2 /Zi /utf-8 /EHa /Felisting19-9.exe c.cpp \
                 stringAlloc.obj  csetToPCset.obj  \
				 csetToRange.obj skipToCset.obj skipCset.obj \
				 stringTokenize.obj	substring2.obj \
				 fscanToCset.obj substring1.obj \
				 stringFree.obj fscanCset.obj listing19-9.obj            
    
stringAlloc.obj: stringAlloc.asm string.inc
    ml64 /c /nologo stringAlloc.asm
                                          
csetToPCset.obj: csetToPCset.asm string.inc
    ml64 /c /nologo csetToPCset.asm
                                          
stringFree.obj: stringFree.asm string.inc
    ml64 /c /nologo stringFree.asm
                                          
fscanCset.obj: fscanCset.asm string.inc
    ml64 /c /nologo fscanCset.asm
                                          
fscanToCset.obj: fscanToCset.asm string.inc
    ml64 /c /nologo fscanToCset.asm
                                          
skipCset.obj: skipCset.asm string.inc
    ml64 /c /nologo skipCset.asm
                                          
skipToCset.obj: skipToCset.asm string.inc
    ml64 /c /nologo skipToCset.asm
                                          
csetToRange.obj: csetToRange.asm string.inc
    ml64 /c /nologo csetToRange.asm
                                          
stringTokenize.obj: stringTokenize.asm string.inc
    ml64 /c /nologo stringTokenize.asm
                                          
substring2.obj: substring2.asm string.inc
    ml64 /c /nologo substring2.asm
                                          
substring1.obj: substring1.asm string.inc
    ml64 /c /nologo substring1.asm
                                          
                     
listing19-9.obj: listing19-9.asm string.inc
    ml64 /c /nologo listing19-9.asm
