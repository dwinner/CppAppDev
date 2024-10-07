echo off
time /t
ml64 /nologo /c /Zi /Cp %1.asm
time /t
cl /nologo /O2 /Zi /utf-8 /EHa /Fe%1.exe c.cpp %1.obj
time /t  