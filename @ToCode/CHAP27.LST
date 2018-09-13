listing 1
test.exe:  test.h test.obj test2.obj test3.obj
        cl test.obj test2.obj test3.obj

test.obj: test.c test.h
        cl -c test.c

test2.obj: test2.c test.h
        cl -c test2.c

test3.obj: test3.c test.h
        cl -c test3.c

listing 2
# This is an incorrect make file.
test.obj: test.c test.h
        cl -c test.c

test2.obj: test2.c test.h
        cl -c test2.c

test3.obj: test3.c test.h
        cl -c test3.c

test.exe: test.h test.obj test2.obj test3.obj
        cl test.obj test2.obj test3.obj

listing 3
LIBFIL = graphics.lib

prog.exe: prog.obj prog2.obj prog3.obj
        cl prog.obj prog2.obj prog3.obj $(LIBFIL)

