listing17-4.exe: strcmp1.obj strcmp2.obj strcmp3.obj \
                 listing17-4.obj
                 
    cl /nologo /O2 /Zi /utf-8 /EHa /Felisting17-4.exe c.cpp \
                 strcmp1.obj strcmp2.obj strcmp3.obj \
                 listing17-4.obj            
    
strcmp1.obj: strcmp1.asm zstrings.inc
    ml64 /c /nologo strcmp1.asm
                     
strcmp2.obj: strcmp2.asm zstrings.inc
    ml64 /c /nologo strcmp2.asm              
                     
strcmp3.obj: strcmp3.asm zstrings.inc
    ml64 /c /nologo strcmp3.asm              
                     
listing17-4.obj: listing17-4.asm zstrings.inc
    ml64 /c /nologo listing17-4.asm              
