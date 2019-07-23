/**
 * Snake game
 */

#include <cstdlib>
#include "snake_app.hpp"

int main()
{
   // Задаем стандартные настройки
   standart_settings();

#ifndef WIN32
   std::memset(a, ' ', sizeof(a));
   nonblock(NB_ENABLE);
#endif

   // Бесконечный цикл
   while (true)
   {
      // Если нажата клавиша, обрабатываем нажатую клавишу
      if (_kbhit() != 0)
      {
         change_direction();
      }

      // Двигаем змейку
      next_step();

      // Если нет еды, то ставим её
      if (!food_check())
      {
         place_food();
      }

      // Рисуем змейку
      show_table();

      // "Усыпляем" программу на заданный интервал
      Sleep(INTERVAL);
   }

   return EXIT_SUCCESS;
}
