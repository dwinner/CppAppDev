listing18-10.exe: findChar1.obj findChar2.obj \
                 findLastChar1.obj findLastChar2.obj \
				 maskOut0s.obj maskOut0s1.obj \
				 listing18-10.obj
                 
    cl /nologo /O2 /Zi /utf-8 /EHa /Felisting18-10.exe c.cpp \
                 findChar1.obj findChar2.obj \
                 findLastChar1.obj findLastChar2.obj \
				 maskOut0s.obj maskOut0s1.obj \
				 listing18-10.obj            
    
findChar1.obj: findChar1.asm string.inc
    ml64 /c /nologo findChar1.asm
                     
findChar2.obj: findChar2.asm string.inc
    ml64 /c /nologo findChar2.asm
                     
findLastChar1.obj: findLastChar1.asm string.inc
    ml64 /c /nologo findLastChar1.asm
                     
findLastChar2.obj: findLastChar2.asm string.inc
    ml64 /c /nologo findLastChar2.asm
                     
maskOut0s.obj: maskOut0s.asm string.inc
    ml64 /c /nologo maskOut0s.asm
                                                                                                                             
maskOut0s1.obj: maskOut0s1.asm string.inc
    ml64 /c /nologo maskOut0s1.asm
                                                                                                                             

listing18-10.obj: listing18-10.asm string.inc
	time /t
    ml64 /c /nologo listing18-10.asm
	time /t
