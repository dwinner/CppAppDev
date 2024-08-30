gcc -Wall -o web_get_normal web_get.c chap06.h
gcc -Wall -O3 -o web_get_opt web_get.c chap06.h
gcc -Wall -Os -o web_get_minsize web_get.c chap06.h
pause