listing19-7.exe: csetToRange.obj  csetToPCset.obj \
				csetToString2.obj listing19-7.obj
    cl /nologo /O2 /Zi /utf-8 /EHa /Felisting19-7.exe c.cpp \
                 csetToRange.obj  csetToPCset.obj  \
				 csetToString2.obj listing19-7.obj            
    
csetToRange.obj: csetToRange.asm string.inc
    ml64 /c /nologo csetToRange.asm
                                          
csetToPCset.obj: csetToPCset.asm string.inc
    ml64 /c /nologo csetToPCset.asm
                                          
csetToString2.obj: csetToString2.asm string.inc
    ml64 /c /nologo csetToString2.asm
                                          
                     
listing19-7.obj: listing19-7.asm string.inc
    ml64 /c /nologo listing19-7.asm
