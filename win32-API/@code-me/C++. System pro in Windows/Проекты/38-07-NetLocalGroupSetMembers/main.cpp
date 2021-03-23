#include <stdio.h>
#include <windows.h> 
#include <lm.h>

#pragma comment( lib, "netapi32.lib" )   // подключаем сетевую библиотеку

int main()
{
  wchar_t server_name[256] = L"\\\\";      // имя сервера
  wchar_t  group_name[GNLEN];              // имя локальной группы
  LOCALGROUP_MEMBERS_INFO_3  *member_info; // информация о членах группы
  DWORD n;     // количество остающихся членов локальной группы

  NET_API_STATUS  ret_status;      // код возврата из функции

  printf("Input server name: ");
// формируем имя сервера
  wscanf(L"%s", server_name + wcslen(server_name));

  printf("Input a local group name: ");
  wscanf(L"%s", group_name);               // вводим имя группы

  printf("Input number of members: ");
  scanf("%d", &n);

// захватываем память для информации о пользователях
  member_info = new LOCALGROUP_MEMBERS_INFO_3[n];

  for (DWORD i = 0; i < n; ++i)
  {
    // захватываем память под имя пользователя
    member_info[i].lgrmi3_domainandname = new wchar_t[256];
    printf("Input a domain name: ");
    // вводим имя домена
    wscanf(L"%s", member_info[i].lgrmi3_domainandname);

    // присоединяем символ '\'
    wcscat(member_info[i].lgrmi3_domainandname, L"\\");

    printf("Input a user name: ");
    // вводим имя пользователя
    wscanf(L"%s", member_info[i].lgrmi3_domainandname + 
            wcslen(member_info[i].lgrmi3_domainandname));
}

  // вводим имя домена
  for (i = 0; i < n; ++i)
    wprintf(L"%s\n", member_info[i].lgrmi3_domainandname);

  // устанавливаем членов в локальной группе
  ret_status = NetLocalGroupSetMembers(
    server_name,           // имя сервера
    group_name,            // имя группы
    3,                     // уровень информации
    (LPBYTE)member_info,   // информация о SID
    n);                    // количество остающихся членов группы
  if (ret_status != NERR_Success)
  {
    printf("Net local group set members failed.\n");

    return ret_status;
  }

  printf("The members are set.\n");

  return 0;
}