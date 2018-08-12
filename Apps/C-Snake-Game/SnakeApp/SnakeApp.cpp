/**
 * SnakeApp
 */
#include "stdafx.h"
#include "SnakeApp.hpp"

int _tmain(int argc, _TCHAR* argv[])
{
   return 0;
}

void change_direction()
{
   // Считываем нажатую клавишу с помощью функции getch().
   symbol = _getch();
   switch (symbol)
   {
   case 'w':   // Вверх
      if (change_x!=1||change_y!=0)
      {
         change_x = -1;
         change_y = 0;
      }
      break;
   case 'a':   // Влево
      if (change_x!=0||change_y!=1)
      {
         change_x = 0;
         change_y = -1;
      }
      break;
   case 's':   // Вниз
      if (change_x!=-1||change_y!=0)
      {
         change_x = 1;
         change_y = 0;
      }
      break;
   case 'd':   // Вправо
      if (change_x!=0||change_y!=-1)
      {
         change_x = 0;
         change_y = 1;
      }
      break;
#ifdef WINDOWS
   case 'q':
      nonblock(NB_DISABLE);
      std::exit(0);
      break;
#endif
   default:
      break;
   }
}

void show_table()
{
   // Очищаем консоль.
#ifdef WINDOWS
   system("cls");
#else
   system("clear");
#endif

   // Выводим таблицу и края.
   for (int i = 0; i <= N+1; ++i)
   {
      for (int j = 0; j <= M+1; ++j)
      {
         std::cout << (i == 0 || j == 0 || i == N + 1 || j == M + 1
            ? '#'
            : a[i][j])
            << (j <= M ? "" : "\n");
      }
   }
}

void clear_snake_on_table()
{
   for (int i = 1; i <= snake_size; ++i)
   {
      a[coords_x[i]][coords_y[i]] = ' ';
   }
}

