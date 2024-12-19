func6: func6.o 
	gcc -g -o func6 func6.o -no-pie
func6.o: func6.asm
	nasm -f elf64 -g -F dwarf func6.asm -l func6.lst
