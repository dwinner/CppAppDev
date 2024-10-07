listing17-5.exe: strchr1.obj strchr2.obj strchr3.obj \
                 strchr4.obj strrchr1.obj strrchr2.obj \
				 strrchr3.obj strrchr4.obj strchr2Data.obj \
				 maskOut0s.obj maskOut0s1.obj listing17-5.obj
                 
    cl /nologo /O2 /Zi /utf-8 /EHa /Felisting17-5.exe c.cpp \
                 strchr1.obj strchr2.obj strchr3.obj \
                 strchr4.obj strrchr1.obj strrchr2.obj \
				 strrchr3.obj strrchr4.obj strchr2Data.obj \
				 maskOut0s.obj maskOut0s1.obj listing17-5.obj            
    
strchr1.obj: strchr1.asm zstrings.inc
    ml64 /c /nologo strchr1.asm
                     
strchr2.obj: strchr2.asm zstrings.inc
    ml64 /c /nologo strchr2.asm              
                     
strchr2Data.obj: strchr2Data.asm zstrings.inc
    ml64 /c /nologo strchr2Data.asm              
                     
strchr3.obj: strchr3.asm zstrings.inc
    ml64 /c /nologo strchr3.asm              
                     
maskOut0s.obj: maskOut0s.asm zstrings.inc
    ml64 /c /nologo maskOut0s.asm              
                     
maskOut0s1.obj: maskOut0s1.asm zstrings.inc
    ml64 /c /nologo maskOut0s1.asm              
                     
strchr4.obj: strchr4.asm zstrings.inc
    ml64 /c /nologo strchr4.asm              
                     
strrchr1.obj: strrchr1.asm zstrings.inc
    ml64 /c /nologo strrchr1.asm
                     
strrchr2.obj: strrchr2.asm zstrings.inc
    ml64 /c /nologo strrchr2.asm              
                     
strrchr3.obj: strrchr3.asm zstrings.inc
    ml64 /c /nologo strrchr3.asm              
                     
strrchr4.obj: strrchr4.asm zstrings.inc
    ml64 /c /nologo strrchr4.asm              
                     
listing17-5.obj: listing17-5.asm zstrings.inc
    ml64 /c /nologo listing17-5.asm              
