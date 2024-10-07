listing17-1.exe: strlen1.obj strlen2.obj strlen3.obj \
                 strlen4.obj strlen5.obj strlen6.obj \
                 strlen7.obj strlen8.obj maskOut0s.obj \
                 listing17-1.obj
                                                
    cl /nologo /O2 /Zi /utf-8 /EHa /Felisting17-1.exe c.cpp \
                 strlen1.obj strlen2.obj strlen3.obj \
                 strlen4.obj strlen5.obj strlen6.obj \
                 strlen7.obj strlen8.obj maskOut0s.obj \
                 listing17-1.obj            
    
strlen1.obj: strlen1.asm zstrings.inc
    ml64 /c /nologo strlen1.asm
                     
strlen2.obj: strlen2.asm zstrings.inc
    ml64 /c /nologo strlen2.asm              
                     
strlen3.obj: strlen3.asm zstrings.inc
    ml64 /c /nologo strlen3.asm              
                     
strlen4.obj: strlen4.asm zstrings.inc
    ml64 /c /nologo strlen4.asm              
                     
strlen5.obj: strlen5.asm zstrings.inc
    ml64 /c /nologo strlen5.asm              
                     
strlen6.obj: strlen6.asm zstrings.inc
    ml64 /c /nologo strlen6.asm              
                     
strlen7.obj: strlen7.asm zstrings.inc
    ml64 /c /nologo strlen7.asm              
                     
strlen8.obj: strlen8.asm zstrings.inc
    ml64 /c /nologo strlen8.asm              
                     
maskOut0s.obj: maskOut0s.asm zstrings.inc
    ml64 /c /nologo maskOut0s.asm              
                     
listing17-1.obj: listing17-1.asm zstrings.inc
    ml64 /c /nologo listing17-1.asm              
