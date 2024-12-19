func5: func5.o 
	gcc -g -o func5 func5.o -no-pie
func5.o: func5.asm
	nasm -f elf64 -g -F dwarf func5.asm -l func5.lst
