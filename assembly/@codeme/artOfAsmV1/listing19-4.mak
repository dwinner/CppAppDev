listing19-4.exe: csetPopCnt.obj  listing19-4.obj
                 
    cl /nologo /O2 /Zi /utf-8 /EHa /Felisting19-4.exe c.cpp \
                 csetPopCnt.obj  listing19-4.obj            
    
csetPopCnt.obj: csetPopCnt.asm string.inc
    ml64 /c /nologo csetPopCnt.asm
                                          
                     
listing19-4.obj: listing19-4.asm string.inc
    ml64 /c /nologo listing19-4.asm
