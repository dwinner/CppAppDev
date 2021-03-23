#include <stdio.h>
#include <windows.h> 
#include <lm.h>

#pragma comment( lib, "netapi32.lib" ) // подключаем сетевую библиотеку

int main()
{
  wchar_t server_name[256] = L"\\\\";  // имя сервера
  wchar_t user_name[UNLEN];    // имя пользователя
  GROUP_USERS_INFO_0  *ui;     // информация о группах
  DWORD  entries_read;         // количество прочитанных групп
  DWORD  total_entries;        // общее количество групп

  NET_API_STATUS  ret_status;      // код возврата из функции

  printf("Input server name: ");
  // формируем имя сервера
  wscanf(L"%s", server_name + wcslen(server_name));

  printf("Input user name: ");
  wscanf(L"%s", user_name);        // читаем имя пользователя

  // получаем информацию о группах, в которые входит пользователь
  ret_status = NetUserGetGroups(
    server_name,       // имя сервера
    user_name,         // имя пользователя
    0,                 // узнаем имена групп
    (LPBYTE*)&ui,      // адрес информации о группах
    MAX_PREFERRED_LENGTH,    // перечисляем все группы
    &entries_read,     // количество прочитанных групп
    &total_entries);   // общеее количество групп

  // проверяем на успешное завершение
  if (ret_status != NERR_Success)
  {
    printf("Net user get groups failed.\n");
    printf("Net API Status: %d\n", ret_status);
    NetApiBufferFree(ui);      // освобождаем буфер

    return ret_status;
  }

  for (DWORD i = 0; i < entries_read; ++i)
    wprintf(L"Global group name: %s\n", ui[i].grui0_name);

  NetApiBufferFree(ui);      // освобождаем буфер

  return 0;
}