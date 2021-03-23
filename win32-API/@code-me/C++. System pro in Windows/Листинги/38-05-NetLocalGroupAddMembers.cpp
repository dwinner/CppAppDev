#include <stdio.h>
#include <windows.h> 
#include <lm.h>

#pragma comment( lib, "netapi32.lib" )   // подключаем сетевую библиотеку

int main()
{
  wchar_t server_name[256] = L"\\\\";      // имя сервера
  wchar_t group_name[GNLEN];               // имя локальной группы
  wchar_t user_name[UNLEN];                // имя пользователя
  LOCALGROUP_MEMBERS_INFO_3  member_info;  // информация о члене группы

  NET_API_STATUS  ret_status;      // код возврата из функции

  printf("Input server name: ");
  // формируем имя сервера
  wscanf(L"%s", server_name + wcslen(server_name));

  printf("Input a local group name: ");
  wscanf(L"%s", group_name);         // вводим имя группы

  printf("Input a domain name: ");
  wscanf(L"%s", user_name);          // вводим имя домена

  wcscat(user_name, L"\\");          // присоединяем символ '\'

  printf("Input a user name: ");
  // вводим имя пользователя
  wscanf(L"%s", user_name + wcslen(user_name));

  // устанавливаем информацию о пользователе
  member_info.lgrmi3_domainandname = user_name;

  // добавляем пользователя в локальную группу
  ret_status = NetLocalGroupAddMembers(
    server_name,           // имя сервера
    group_name,            // имя группы
    3,                     // уровень информации
    (LPBYTE)&member_info,  // имя учетной записи
    1);                    // добавляем одного члена группы
  if (ret_status != NERR_Success)
  {
    printf("Ret status: %d\n", ret_status);
    printf("Net local group add members failed.\n");

    return ret_status;
  }

  printf("The member is added.\n");

  return 0;
}