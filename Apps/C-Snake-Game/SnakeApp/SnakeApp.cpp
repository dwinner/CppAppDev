/**
 * SnakeApp
 */

#include "stdafx.h"
#include <iostream>
#include <cstdio>
#include <ctime>

#ifdef WIN32
#include <Windows.h>
#include <conio.h>
#else
#include <unistd.h>
#include <termios.h>
#include <sys/select.h>

#define STDIN_FILENO 0
#define NB_DISABLE   0
#define NB_ENABLE    1
#define SLEEP(x)     usleep(x*1000)

int kbhit()
{
   struct timeval tv;
   fd_set fds;
   tv.tv_sec = 0;
   tv.tv_usec = 0;
   FD_ZERO(&fds);
   FD_SET(STDIN_FILENO, &fds);
   select(STDIN_FILENO + 1, &fds, NULL, NULL, &tv);

   return FD_ISSET(STDIN_FILENO, &fds);
}

void nonblock(int state)
{
   struct termios ttystate;

   // Получаем состояние терминала
   tcgetattr(STDIN_FILENO, &ttystate);

   if (state == NB_ENABLE)
   {
      // Выключаем ICANON-режим
      ttystate.c_lflag &= ~ICANON;
      ttystate.c_cc[VMIN] = 1;
   }
   else if (state == NB_DISABLE)
   {
      // Включаем ICANON-режим
      ttystate.c_lflag |= ICANON;
   }

   // Устанавливаем атрибуты терминала
   tcsetattr(STDIN_FILENO, TCSANOW, &ttystate);
}

int getch()
{
   return fgets(stdin);
}

#endif

int _tmain(int argc, _TCHAR* argv[])
{
   return 0;
}
