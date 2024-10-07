# listing15-8.mak
#
# makefile for listing15-7

listing15-7.exe:listing15-7.obj
    cl /nologo /O2 /Zi /utf-8 /EHa /Felisting15-7.exe c.cpp \
            listing15-7.obj
            
listing15-7.obj: listing15-7.asm aoalib.inc
    ml64 /nologo /c listing15-7.asm
    