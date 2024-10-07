listing17-6.exe: strstr1.obj strstr2.obj strstr3.obj \
                 strstr4.obj strrstr1.obj strlen6.obj \
				 strrstr3.obj strchr4.obj strlen7.obj \
				 maskOut0s.obj listing17-6.obj
                 
    cl /nologo /O2 /Zi /utf-8 /EHa /Felisting17-6.exe c.cpp \
                 strstr1.obj strstr2.obj strstr3.obj \
                 strstr4.obj strrstr1.obj strlen6.obj \
				 strrstr3.obj strchr4.obj strlen7.obj \
				 maskOut0s.obj listing17-6.obj            
    
strstr1.obj: strstr1.asm zstrings.inc
    ml64 /c /nologo strstr1.asm
                     
strstr2.obj: strstr2.asm zstrings.inc
    ml64 /c /nologo strstr2.asm              
                     
strstr3.obj: strstr3.asm zstrings.inc
    ml64 /c /nologo strstr3.asm              
                     
strstr4.obj: strstr4.asm zstrings.inc
    ml64 /c /nologo strstr4.asm              
                     
strrstr1.obj: strrstr1.asm zstrings.inc
    ml64 /c /nologo strrstr1.asm
                     
strrstr3.obj: strrstr3.asm zstrings.inc
    ml64 /c /nologo strrstr3.asm              
                     
strlen7.obj: strlen7.asm zstrings.inc
    ml64 /c /nologo strlen7.asm              
                     
strlen6.obj: strlen6.asm zstrings.inc
    ml64 /c /nologo strlen6.asm              
                     
strchr4.obj: strchr4.asm zstrings.inc
    ml64 /c /nologo strchr4.asm              
                     
maskOut0s.obj: maskOut0s.asm zstrings.inc
    ml64 /c /nologo maskOut0s.asm              
                     
listing17-6.obj: listing17-6.asm zstrings.inc
    ml64 /c /nologo listing17-6.asm              
