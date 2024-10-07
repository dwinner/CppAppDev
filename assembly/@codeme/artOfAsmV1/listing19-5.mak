listing19-5.exe: csetToString.obj  listing19-5.obj
                 
    cl /nologo /O2 /Zi /utf-8 /EHa /Felisting19-5.exe c.cpp \
                 csetToString.obj  listing19-5.obj            
    
csetToString.obj: csetToString.asm string.inc
    ml64 /c /nologo csetToString.asm
                                          
                     
listing19-5.obj: listing19-5.asm string.inc
    ml64 /c /nologo listing19-5.asm
