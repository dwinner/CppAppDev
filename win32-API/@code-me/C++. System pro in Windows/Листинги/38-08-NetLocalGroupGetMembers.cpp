#include <stdio.h>
#include <windows.h> 
#include <lm.h>

#pragma comment( lib, "netapi32.lib" )  // подключаем сетевую библиотеку

int main()
{
  wchar_t server_name[256] = L"\\\\";    // имя сервера
  wchar_t  group_name[GNLEN];            // имя локальной группы
  // информация о членах группы
  LOCALGROUP_MEMBERS_INFO_1  *member_info = NULL;
  DWORD entries_read;            // прочитанное количество членов группы
  DWORD total_entries;           // общее количество членов группы

  NET_API_STATUS  ret_status;    // код возврата из функции

  printf("Input server name: ");
  // формируем имя сервера
  wscanf(L"%s", server_name + wcslen(server_name));

  printf("Input a local group name: ");
  wscanf(L"%s", group_name);         // вводим имя группы

  // получаем информацию о членах локальной группы
  ret_status = NetLocalGroupGetMembers(
    server_name,         // имя сервера
    group_name,          // имя группы
    1,                   // уровень информации
    (LPBYTE*)&member_info,     // информация о пользователях
    MAX_PREFERRED_LENGTH,      // читаем информацию о всех членах группы
    &entries_read,       // прочитанное количество членов группы
    &total_entries,      // полное количество членов группы
    NULL);               // читаем в один прием
  if (ret_status != NERR_Success)
  {
    printf("Net local group get members failed.\n");
    NetApiBufferFree(member_info);      // освобождаем буфер

    return ret_status;
  }

  // распечатываем пользователей
  for (DWORD i = 0; i < entries_read; ++i)
    wprintf(L"The group member: %s\n", member_info[i].lgrmi1_name);

  NetApiBufferFree(member_info);    // освобождаем буфер
  return 0;
}