listing19-8.exe: csetToRange.obj  csetToPCset.obj \
				skipCset.obj fscanCset.obj listing19-8.obj
    cl /nologo /O2 /Zi /utf-8 /EHa /Felisting19-8.exe c.cpp \
                 csetToRange.obj  csetToPCset.obj  \
				 skipCset.obj fscanCset.obj listing19-8.obj            
    
csetToRange.obj: csetToRange.asm string.inc
    ml64 /c /nologo csetToRange.asm
                                          
csetToPCset.obj: csetToPCset.asm string.inc
    ml64 /c /nologo csetToPCset.asm
                                          
skipCset.obj: skipCset.asm string.inc
    ml64 /c /nologo skipCset.asm
                                          
fscanCset.obj: fscanCset.asm string.inc
    ml64 /c /nologo fscanCset.asm
                                          
                     
listing19-8.obj: listing19-8.asm string.inc
    ml64 /c /nologo listing19-8.asm
