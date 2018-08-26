#ifndef SNAKEAPP_HPP_H
#define SNAKEAPP_HPP_H

#if !defined(WIN32)
#define WIN32
#endif

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

/**
* \brief размер змейки
*/
int snake_size;

/**
* В какую сторону движется змейка
*/
int change_x, change_y;

/**
* Массивы, хранящие координаты частей тела змейки.
* Координаты головы змейки хранятся в coordinates_x[1], coordinates_y[1]
*/
int coords_x[1000], coords_y[1000];

/**
 * Координаты еды
 */
int food_x = -1, food_y = -1;

/**
 * \brief Хранит в себе ASCII-код нажатой клавиши.
 */
char symbol;

/**
 * \brief Наша таблица, в которой происходит игра
 */
char a[1000][1000];

/**
 * \brief Размер таблицы, а именно высота
 */
const int N = 13;

/**
 * \brief Ширина таблицы
 */
const int M = 17;

/**
 * \brief Интервал в миллисекундах
 * \details через каждый этот промежуток времени змейка будет передвигаться
 */
const int INTERVAL = 200;

/**
 * \brief Функция, считывающая нажатую клавишу.
 */
void change_direction();

/**
 * \brief Функция для вывода таблицы
 */
void show_table();

/**
 * \brief Очищаем координаты, в которых располагалась змейка
 */
void clear_snake_on_table();

void show_snake_on_table();

bool game_over();

void check_coordinates();

void next_step();

bool food_check();

void place_food();

void standart_settings();

#endif // SNAKEAPP_HPP_H
