listing18-9.exe: stringCat1.obj stringCat2.obj \
				 printString.obj stringCmp1.obj \
				 listing18-9.obj
                 
    cl /nologo /O2 /Zi /utf-8 /EHa /Felisting18-9.exe c.cpp \
                 stringCat1.obj stringCat2.obj \
				 printString.obj  stringCmp1.obj \
				 listing18-9.obj            
    
stringCat1.obj: stringCat1.asm string.inc
    ml64 /c /nologo stringCat1.asm
                     
stringCat2.obj: stringCat2.asm string.inc
    ml64 /c /nologo stringCat2.asm
                     
printString.obj: printString.asm string.inc
    ml64 /c /nologo printString.asm
                                                                                                                             
stringCmp1.obj: stringCmp1.asm string.inc
    ml64 /c /nologo stringCmp1.asm
                                                                                                                             

listing18-9.obj: listing18-9.asm string.inc
	time /t
    ml64 /c /nologo listing18-9.asm
	time /t
