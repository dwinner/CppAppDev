#include <stdio.h>
#include <windows.h> 
#include <lm.h>

#pragma comment( lib, "netapi32.lib" )   // подключаем сетевую библиотеку

int main()
{
  wchar_t server_name[256] = L"\\\\";  // имя сервера
  wchar_t user_name[UNLEN];            // имя пользователя

  NET_API_STATUS  ret_status;  // код возврата из функции

  printf("Input server name: ");
  wscanf(L"%s", server_name);    // читаем имя домена

  printf("Input user name: ");
  wscanf(L"%s", user_name);      // читаем имя пользователя

  // удалаем пользователя
  ret_status = NetUserDel(
    server_name,     // имя домена
    user_name);      // имя пользователя

  // проверяем на успешное завершение
  if (ret_status != NERR_Success)
  {
    printf("Net user del failed.\n");
    printf("Net API Status: %d\n", ret_status);

    return ret_status;
  }

  printf("The user is deleted.\n");

  return 0;
}