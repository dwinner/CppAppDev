listing17-3.exe: strcpy1.obj strcpy2.obj strcpy3.obj \
                 copy16.obj listing17-3.obj
                 
    cl /nologo /O2 /Zi /utf-8 /EHa /Felisting17-3.exe c.cpp \
                 strcpy1.obj strcpy2.obj strcpy3.obj \
                 copy16.obj listing17-3.obj            
    
strcpy1.obj: strcpy1.asm zstrings.inc
    ml64 /c /nologo strcpy1.asm
                     
strcpy2.obj: strcpy2.asm zstrings.inc
    ml64 /c /nologo strcpy2.asm              
                     
strcpy3.obj: strcpy3.asm zstrings.inc
    ml64 /c /nologo strcpy3.asm              
                     
copy16.obj: copy16.asm zstrings.inc
    ml64 /c /nologo copy16.asm              
                     
listing17-3.obj: listing17-3.asm zstrings.inc
    ml64 /c /nologo listing17-3.asm              
