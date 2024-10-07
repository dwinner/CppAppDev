listing19-testScanning.exe: skipToCset.obj skipCset.obj \
				 listing19-testScanning.obj
                 
    cl /nologo /O2 /Zi /utf-8 /EHa /Felisting19-testScanning.exe c.cpp \
                 skipToCset.obj skipCset.obj \
				 listing19-testScanning.obj
    
skipToCset.obj: skipToCset.asm string.inc
    ml64 /c /nologo skipToCset.asm
                     
skipCset.obj: skipCset.asm string.inc
    ml64 /c /nologo skipCset.asm
                     
listing19-testScanning.obj: listing19-testScanning.asm string.inc
    ml64 /c /nologo listing19-testScanning.asm
