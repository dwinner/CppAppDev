listing19-6.exe: csetToRange.obj  listing19-6.obj
                 
    cl /nologo /O2 /Zi /utf-8 /EHa /Felisting19-6.exe c.cpp \
                 csetToRange.obj  listing19-6.obj            
    
csetToRange.obj: csetToRange.asm string.inc
    ml64 /c /nologo csetToRange.asm
                                          
                     
listing19-6.obj: listing19-6.asm string.inc
    ml64 /c /nologo listing19-6.asm
