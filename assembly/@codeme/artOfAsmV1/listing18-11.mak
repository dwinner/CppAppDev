listing18-11.exe: findStr1.obj findStr2.obj \
                 findLastStr1.obj findLastStr2.obj \
				 listing18-11.obj
                 
    cl /nologo /O2 /Zi /utf-8 /EHa /Felisting18-11.exe c.cpp \
                 findStr1.obj findStr2.obj \
                 findLastStr1.obj findLastStr2.obj \
				 listing18-11.obj            
    
findStr1.obj: findStr1.asm string.inc
    ml64 /c /nologo findStr1.asm
                     
findStr2.obj: findStr2.asm string.inc
    ml64 /c /nologo findStr2.asm
                     
findLastStr1.obj: findLastStr1.asm string.inc
    ml64 /c /nologo findLastStr1.asm
                     
findLastStr2.obj: findLastStr2.asm string.inc
    ml64 /c /nologo findLastStr2.asm
                     
listing18-11.obj: listing18-11.asm string.inc
	time /t
    ml64 /c /nologo listing18-11.asm
	time /t
