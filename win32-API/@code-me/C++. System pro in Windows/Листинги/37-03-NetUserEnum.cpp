#include <stdio.h>
#include <windows.h> 
#include <lm.h>

#pragma comment( lib, "netapi32.lib" ) // подключаем сетевую библиотеку

int main()
{
  wchar_t server_name[256] = L"\\\\";  // имя сервера
  USER_INFO_0  *ui;        // информация о пользователе
  DWORD  entries_read;     // количество прочитанных пользователей
  DWORD  total_entries;    // общее количество пользователей

  NET_API_STATUS  ret_status;  // код возврата из функции

  printf("Input server name: ");   // читаем имя сервера
  // формируем имя сервера
  wscanf(L"%s", server_name + wcslen(server_name));

  // получаем информацию о пользователях
  ret_status = NetUserEnum(
    server_name,       // имя сервера
    0,                 // узнаем только имена пользователей
    FILTER_NORMAL_ACCOUNT,   // перечисляем пользователей, зарегистрированных на компьютере
    (LPBYTE*)&ui,      // адрес информации о пользователях
    MAX_PREFERRED_LENGTH,    // перечисляем всех пользователей
    &entries_read,     // количество прочитанных пользователей
    &total_entries,    // общее количество пользователей
    NULL);             // индексации нет

  // проверяем на успешное завершение
  if (ret_status != NERR_Success)
  {
    printf("Net user get info failed.\n");
    printf("Net API Status: %d\n", ret_status);
    NetApiBufferFree(ui);    // освобождаем буфер

    return ret_status;
  }

  for (DWORD i = 0; i < entries_read; ++i)
    wprintf(L"User name: %s\n", ui[i].usri0_name);

  NetApiBufferFree(ui);      // освобождаем буфер

  return 0;
}