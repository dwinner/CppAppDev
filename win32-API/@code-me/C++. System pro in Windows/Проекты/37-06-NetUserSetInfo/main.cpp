#include <stdio.h>
#include <windows.h> 
#include <lm.h>

#pragma comment( lib, "netapi32.lib" )   // подключаем сетевую библиотеку

int main()
{
  wchar_t server_name[256] = L"\\\\";  // имя сервера
  wchar_t old_name[UNLEN];         // старое имя пользователя
  wchar_t new_name[UNLEN];         // новое имя пользователя
  USER_INFO_0 ui;                  // информация о пользователе
  NET_API_STATUS  ret_status;      // код возврата из функции

  printf("Input server name: ");
// формируем имя сервера
  wscanf(L"%s", server_name + wcslen(server_name));

  printf("Input old user name: ");
  wscanf(L"%s", old_name);       // читаем старое имя пользователя

  printf("Input new user name: ");
  wscanf(L"%s", new_name);       // читаем новое имя пользователя
  ui.usri0_name = new_name;      // устанавливаем новое имя пользователя

  // устанавливаем информацию о пользователе
  ret_status = NetUserSetInfo(
    server_name,     // имя сервера
    old_name,        // имя пользователя
    0,               // изменяем имя пользователя
    (LPBYTE)&ui,     // адрес информации о пользователе
    NULL);           // нет индексации

  // проверяем на успешное завершение
  if (ret_status != NERR_Success)
  {
    printf("Net user set info failed.\n");
    printf("Net API Status: %d\n", ret_status);

    return ret_status;
  }

  printf("User name is changed.\n");

  USER_INFO_1  *uix;         // информация о пользователе
  // получаем информацию о пользователе
  ret_status = NetUserGetInfo(
    server_name,     // имя сервера
    new_name,        // имя пользователя
    1,               // уровень информации 1
    (LPBYTE*)&uix);  // адрес информации о пользователе

  // проверяем на успешное завершение
  if (ret_status != NERR_Success)
  {
    printf("Net user get info failed.\n");

    return ret_status;
  }
  
  wprintf(L"User name: %s\n", uix->usri1_name);
  wprintf(L"User commemnt: %s\n", uix->usri1_comment);

  return 0;
}