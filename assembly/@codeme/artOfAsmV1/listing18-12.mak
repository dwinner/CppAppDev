listing18-12.exe: skipToChar1.obj skipToChar2.obj \
                 skipChars1.obj skipChars2.obj \
				 skipCharsPS.obj skiptoCharPS.obj \
				 sGet16AtRDI.obj maskOut0s.obj \
				 listing18-12.obj
                 
    cl /nologo /O2 /Zi /utf-8 /EHa /Felisting18-12.exe c.cpp \
                 skipToChar1.obj skipToChar2.obj \
                 skipChars1.obj skipChars2.obj \
				 skipCharsPS.obj skiptoCharPS.obj \
				 sGet16AtRDI.obj maskOut0s.obj \
				 listing18-12.obj
    
skipToChar1.obj: skipToChar1.asm string.inc
    ml64 /c /nologo skipToChar1.asm
                     
skipToCharPS.obj: skipToCharPS.asm string.inc
    ml64 /c /nologo skipToCharPS.asm
                     
skipToChar2.obj: skipToChar2.asm string.inc
    ml64 /c /nologo skipToChar2.asm
                     
skipChars1.obj: skipChars1.asm string.inc
    ml64 /c /nologo skipChars1.asm
                     
skipCharsPS.obj: skipCharsPS.asm string.inc
    ml64 /c /nologo skipCharsPS.asm
                     
skipChars2.obj: skipChars2.asm string.inc
    ml64 /c /nologo skipChars2.asm
                     
sGet16AtRDI.obj: sGet16AtRDI.asm string.inc
    ml64 /c /nologo sGet16AtRDI.asm
                     
maskOut0s.obj: maskOut0s.asm string.inc
    ml64 /c /nologo maskOut0s.asm
                     
listing18-12.obj: listing18-12.asm string.inc
	time /t
    ml64 /c /nologo listing18-12.asm
	time /t
