#include <stdio.h>
#include <windows.h> 
#include <lm.h>

#pragma comment( lib, "netapi32.lib" )   // подключаем сетевую библиотеку

int main()
{
  wchar_t server_name[256] = L"\\\\";  // имя сервера
  wchar_t  group_name[GNLEN];          // имя локальной группы
  wchar_t comment[MAXCOMMENTSZ];       // комментарий о группе
  LOCALGROUP_INFO_1  group_info;       // информация о группе
  NET_API_STATUS ret_status;           // код возврата из функции

  printf("Input server name: ");
// формируем имя сервера
  wscanf(L"%s", server_name + wcslen(server_name));

  printf("Input a name for the local group: ");
  wscanf(L"%s", group_name);           // вводим имя группы
  group_info.lgrpi1_name = group_name;   // устанавливаем адрес имени в структуру

  
  printf("Input group comments: ");
  getwchar();              // очищаем поток
  _getws(comment);         // читаем комментарий о локальной группе
  group_info.lgrpi1_comment = comment;   // устанавливаем комментарий

  // создаем локальную группу
  ret_status = NetLocalGroupAdd(
    server_name,           // имя сервера
    1,                     // уровень входных данных
    (LPBYTE)&group_info,   // имя группы и комментарии
    NULL);                 // индексацию данных не используем
  if (ret_status != NERR_Success)
  {
    printf("Net local group add failed.\n");

    return ret_status;
  }

  printf("The group is created.\n");

  return 0;
}