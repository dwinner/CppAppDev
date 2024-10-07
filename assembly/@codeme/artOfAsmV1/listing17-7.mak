listing17-7.exe: strspn1.obj strspnPS.obj strspn3.obj \
                 strspn4.obj strcspn1.obj strlen6.obj \
				 strcspn3.obj strchr4.obj strlen7.obj \
				 maskOut0s.obj strcspnPS.obj strcspn4.obj \
				 matchset.obj noMatchset.obj get16AtRDI.obj \
				 listing17-7.obj
                 
    cl /nologo /O2 /Zi /utf-8 /EHa /Felisting17-7.exe c.cpp \
                 strspn1.obj strspnPS.obj strspn3.obj \
                 strspn4.obj strcspn1.obj strlen6.obj \
				 strcspn3.obj strchr4.obj strlen7.obj \
				 maskOut0s.obj strcspnPS.obj strcspn4.obj \
				 matchset.obj noMatchset.obj get16AtRDI.obj \
				 listing17-7.obj            
    
strspn1.obj: strspn1.asm zstrings.inc
    ml64 /c /nologo strspn1.asm
                     
strspnPS.obj: strspnPS.asm zstrings.inc
    ml64 /c /nologo strspnPS.asm              
                     
strcspnPS.obj: strcspnPS.asm zstrings.inc
    ml64 /c /nologo strcspnPS.asm              
                     
strspn3.obj: strspn3.asm zstrings.inc
    ml64 /c /nologo strspn3.asm              
                     
strspn4.obj: strspn4.asm zstrings.inc
    ml64 /c /nologo strspn4.asm              
                     
strcspn4.obj: strcspn4.asm zstrings.inc
    ml64 /c /nologo strcspn4.asm              
                     
strcspn1.obj: strcspn1.asm zstrings.inc
    ml64 /c /nologo strcspn1.asm
                     
strcspn3.obj: strcspn3.asm zstrings.inc
    ml64 /c /nologo strcspn3.asm              
                     
strlen7.obj: strlen7.asm zstrings.inc
    ml64 /c /nologo strlen7.asm              
                     
strlen6.obj: strlen6.asm zstrings.inc
    ml64 /c /nologo strlen6.asm              
                     
strchr4.obj: strchr4.asm zstrings.inc
    ml64 /c /nologo strchr4.asm              
                     
maskOut0s.obj: maskOut0s.asm zstrings.inc
    ml64 /c /nologo maskOut0s.asm              
                     
matchset.obj: matchset.asm zstrings.inc
    ml64 /c /nologo matchset.asm              
                     
noMatchset.obj: noMatchset.asm zstrings.inc
    ml64 /c /nologo noMatchset.asm              
                     
get16AtRDI.obj: get16AtRDI.asm zstrings.inc
    ml64 /c /nologo get16AtRDI.asm              
                     
listing17-7.obj: listing17-7.asm zstrings.inc
    ml64 /c /nologo listing17-7.asm              
