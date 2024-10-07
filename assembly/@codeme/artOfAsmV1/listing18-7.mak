listing18-7.exe: prefix1.obj prefix2.obj \
                 prefix3.obj suffix1.obj \
                 suffix2.obj suffix3.obj \
				 printString.obj listing18-7.obj
                 
    cl /nologo /O2 /Zi /utf-8 /EHa /Felisting18-7.exe c.cpp \
                 prefix1.obj prefix2.obj \
                 prefix3.obj suffix1.obj \
                 suffix2.obj suffix3.obj \
				 printString.obj listing18-7.obj            
    
prefix1.obj: prefix1.asm string.inc
    ml64 /c /nologo prefix1.asm
                     
prefix2.obj: prefix2.asm string.inc
    ml64 /c /nologo prefix2.asm
                     
prefix3.obj: prefix3.asm string.inc
    ml64 /c /nologo prefix3.asm
                                                                                                                             

suffix1.obj: suffix1.asm string.inc
    ml64 /c /nologo suffix1.asm
                     
suffix2.obj: suffix2.asm string.inc
    ml64 /c /nologo suffix2.asm
                     
suffix3.obj: suffix3.asm string.inc
    ml64 /c /nologo suffix3.asm
                                                                                                                             
printString.obj: printString.asm string.inc
    ml64 /c /nologo printString.asm
                                                                                                                             

listing18-7.obj: listing18-7.asm string.inc
    ml64 /c /nologo listing18-7.asm
