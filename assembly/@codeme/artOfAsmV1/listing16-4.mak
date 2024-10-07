listing16-4.exe: listing16-4.obj listing16-4.asm
	ml64 /nologo listing16-4.asm \
		/link /subsystem:console /entry:asmMain 