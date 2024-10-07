listing17-2.exe: memset1.obj memset2.obj memset3.obj \
                 memset4.obj listing17-2.obj
                 
    cl /nologo /O2 /Zi /utf-8 /EHa /Felisting17-2.exe c.cpp \
                 memset1.obj memset2.obj memset3.obj \
                 memset4.obj listing17-2.obj            
    
memset1.obj: memset1.asm zstrings.inc
    ml64 /c /nologo memset1.asm
                     
memset2.obj: memset2.asm zstrings.inc
    ml64 /c /nologo memset2.asm              
                     
memset3.obj: memset3.asm zstrings.inc
    ml64 /c /nologo memset3.asm              
                     
memset4.obj: memset4.asm zstrings.inc
    ml64 /c /nologo memset4.asm              
                     
listing17-2.obj: listing17-2.asm zstrings.inc
    ml64 /c /nologo listing17-2.asm              
