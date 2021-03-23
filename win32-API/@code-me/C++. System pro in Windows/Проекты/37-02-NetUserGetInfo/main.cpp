#include <stdio.h>
#include <windows.h> 
#include <lm.h>

#pragma comment( lib, "netapi32.lib" )   // подключаем сетевую библиотеку

int main()
{
  wchar_t server_name[256] = L"\\\\";  // имя сервера
  wchar_t user_name[UNLEN];            // имя пользователя
  USER_INFO_1  *ui;                    // информация о пользователе
  NET_API_STATUS  ret_status;          // код возврата из функции

  printf("Input server name: ");       // вводим имя сервера
  // формируем имя сервера
  wscanf(L"%s", server_name + wcslen(server_name));

  printf("Input user name: ");
  wscanf(L"%s", user_name);            // читаем имя пользователя

  // получаем информацию о пользователе
  ret_status = NetUserGetInfo(
    server_name,     // имя сервера
    user_name,       // имя пользователя
    1,               // уровень информации 1
    (LPBYTE*)&ui);   // адрес информации о пользователе

  // проверяем на успешное завершение
  if (ret_status != NERR_Success)
  {
    printf("Net user get info failed.\n");

    return ret_status;
  }
  
  wprintf(L"User name: %s\n", ui->usri1_name);
  wprintf(L"User commemnt: %s\n", ui->usri1_comment);

  NetApiBufferFree(ui);    // освобождаем буфер

  return 0;
}