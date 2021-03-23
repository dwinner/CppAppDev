#ifndef UNICODE
#define UNICODE
#endif

#include <stdio.h>
#include <windows.h> 
#include <lm.h>

#pragma comment( lib, "netapi32.lib" )  // подключаем сетевую библиотеку

int main()
{
  wchar_t server_name[256] = L"\\\\";    // имя сервера
  wchar_t  group_name[GNLEN];            // имя локальной группы
  wchar_t user_name[UNLEN];              // имя пользователя
  LOCALGROUP_MEMBERS_INFO_0  member_info;  // информация о члене группы

  NET_API_STATUS  ret_status;        // код возврата из функции
  DWORD  dwErrCode;

  DWORD  dwLengthOfSID = 0;          // длина SID
  DWORD  dwLengthOfDomainName = 0;   // длина имени домена
  PSID  lpSID = NULL;                // указатель на SID
  LPTSTR  lpDomainName = NULL;       // указатель на имя домена
  SID_NAME_USE type_of_SID;          // тип учетной записи

  printf("Input server name: ");
  // формируем имя сервера
  wscanf(L"%s", server_name + wcslen(server_name));

  printf("Input a local group name: ");
  wscanf(L"%s", group_name);         // вводим имя группы

  printf("Input a user name: ");
  wscanf(L"%s", user_name);          // вводим имя пользователя

  // определяем длину SID пользователя
  LookupAccountName(
    NULL,            // ищем имя на локальном компьютере
    user_name,       // имя пользователя
    NULL,            // определяем длину SID
    &dwLengthOfSID,  // длина SID
    NULL,            // определяем имя домена
    &dwLengthOfDomainName,    // длина имени домена
    &type_of_SID);   // тип учетной записи
  // проверяем, вернула ли функция длину SID
  if (dwLengthOfSID == 0)
  {
    dwErrCode = GetLastError();
    printf("Lookup account name failed.\n");
    printf("Error code: %d\n", dwErrCode);

    return dwErrCode;
  }

  // распределяем память для SID и имени домена
  lpSID = (PSID) new char[dwLengthOfSID];
  lpDomainName = (LPTSTR) new char[dwLengthOfDomainName];

  // определяем SID и имя домена пользователя
  if(!LookupAccountName(
    NULL,            // ищем имя на локальном компьютере
    user_name,       // имя пользователя
    lpSID,           // определяем длину SID
    &dwLengthOfSID,  // длина SID
    lpDomainName,    // определяем имя домена
    &dwLengthOfDomainName,   // длина имени домена
    &type_of_SID))   // тип учетной записи
  {
    dwErrCode = GetLastError();
    printf("Lookup account name failed.\n");
    printf("Error code: %d\n", dwErrCode);

    return dwErrCode;
  }

  // распечатываем имя домена
  wprintf(L"%s\n", lpDomainName);

  // устанавливаем SID в информацию о члене группы
  member_info.lgrmi0_sid = lpSID;

  // удаляем члена локальной группы
  ret_status = NetLocalGroupDelMembers(
    server_name,     // имя сервера
    group_name,      // имя группы
    0,               // уровень информации
    (LPBYTE)&member_info,    // информация о SID
    1);              // добавляем одного члена группы
  if (ret_status != NERR_Success)
  {
    printf("Net local group del members failed.\n");

    return ret_status;
  }

  printf("The member is deleted.\n");

  return 0;
}