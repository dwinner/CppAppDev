#include <stdio.h>
#include <windows.h> 
#include <lm.h>

#pragma comment( lib, "netapi32.lib" )   // подключаем сетевую библиотеку

int main()
{
  wchar_t server_name[256] = L"\\\\";    // имя сервера
  wchar_t  old_name[GNLEN];        // старое имя локальной группы
  wchar_t  new_name[GNLEN];        // новое имя локальной группы
  wchar_t comment[MAXCOMMENTSZ];   // новый комментарий

  LOCALGROUP_INFO_0 group_info_0;  // информация об имени группы
  LOCALGROUP_INFO_1 group_info_1;  // описание новой группы

  NET_API_STATUS    ret_status;    // код возврата из функции

  printf("Input a server name: ");
// формируем имя сервера
  wscanf(L"%s", server_name + wcslen(server_name));

  printf("Input a local group name: ");
  wscanf(L"%s", old_name);         // вводим имя группы

  printf("Input a new name for the group: ");
  wscanf(L"%s", new_name);         // вводим новое имя группы

  // устанавливаем адрес имени в структуру
  group_info_0.lgrpi0_name = new_name;

  // изменяем имя группы
  ret_status = NetLocalGroupSetInfo(
    server_name,       // имя сервера
    old_name,          // имя группы
    0,                 // новое имя группы
    (LPBYTE)&group_info_0,  // новая информация о группе
    NULL);             // индексирования информации нет
  // проверяем завершение функции
  if (ret_status != NERR_Success)
  {
    printf("Net local group set name failed.\n");

    return ret_status;
  }
  printf("Local group name was changed.\n");

  printf("Input group comments: ");
  getwchar();          // очищаем поток
  _getws(comment);     // читаем комментарии о пользователе
  // устанавливаем новый комментарий
  group_info_1.lgrpi1_comment = comment;

  // изменяем описание группы
  ret_status = NetLocalGroupSetInfo(
    server_name,       // имя сервера
    new_name,          // имя группы
    1,                 // получаем имя группы и комментарий
    (LPBYTE)&group_info_1,  // новое описание группы
    NULL);             // индексирования информации нет
  // проверяем завершение функции
  if (ret_status != NERR_Success)
  {
    printf("Net local group set info failed.\n");

    return ret_status;
  }
  printf("Local group comment was changed.\n");

  return 0;
}