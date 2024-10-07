# listing15-5.mak
#
# makefile for listing15-4

listing15-4.exe:print.obj getTitle.obj listing15-4.obj
    cl /nologo /O2 /Zi /utf-8 /EHa /Felisting15-4.exe c.cpp \
            print.obj getTitle.obj listing15-4.obj
            
listing15-4.obj: listing15-4.asm aoalib.inc
  ml64 /nologo /c listing15-4.asm

print.obj: print.asm aoalib.inc
  ml64 /nologo /c print.asm

getTitle.obj: getTitle.asm aoalib.inc
  ml64 /nologo /c getTitle.asm