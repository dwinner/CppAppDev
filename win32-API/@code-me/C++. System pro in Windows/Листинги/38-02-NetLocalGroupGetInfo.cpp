#include <stdio.h>
#include <windows.h> 
#include <lm.h>

#pragma comment( lib, "netapi32.lib" )   // подключаем сетевую библиотеку

int main()
{
  wchar_t server_name[256] = L"\\\\";    // имя сервера
  wchar_t  group_name[GNLEN];            // имя локальной группы
  LOCALGROUP_INFO_1  *buf_ptr = NULL;    // адрес буфера для данных
  NET_API_STATUS    ret_status;          // код возврата из функции

  printf("Input server name: ");
// формируем имя сервера
  wscanf(L"%s", server_name + wcslen(server_name));

  printf("Input a name for the local group: ");
  wscanf(L"%s", group_name);         // вводим имя группы

  // получаем информацию о локальной группе
  ret_status = NetLocalGroupGetInfo(
    server_name,           // имя сервера
    group_name,            // имя группы
    1,                     // получаем имя группы и комментарий
    (LPBYTE*)&buf_ptr);    // указатель на адрес буфера для данных
  // проверяем завершение функции
  if (ret_status != NERR_Success)
  {
    printf("Net local group get info failed.\n");
    NetApiBufferFree(buf_ptr);  // освобождаем буфер для данных 

    return ret_status;
  }

  // выводим на консоль имя локальной группы и комментарий
  wprintf(L"Local group name: %s\n", buf_ptr->lgrpi1_name);
  wprintf(L"Comment: %s\n", buf_ptr->lgrpi1_comment);

  NetApiBufferFree(buf_ptr);     // освобождаем буфер для данных

  return 0;
}