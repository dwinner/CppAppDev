#define _WIN32_WINNT 0x0500

#ifndef UNICODE
#define UNICODE
#endif

#include <stdio.h>
#include <windows.h> 
#include <lm.h>
#include <sddl.h>

int main()
{
  wchar_t user_name[UNLEN];    // имя пользователя

  DWORD dwErrCode;             // код возврата

  DWORD  dwLengthOfSID = 0;    // длина SID
  DWORD  dwLengthOfDomainName = 0;   // длина имени домена
  PSID  lpSID = NULL;          // указатель на SID
  LPTSTR  lpDomainName = NULL; // указатель на имя домена
  SID_NAME_USE type_of_SID;    // тип учетной записи

  LPTSTR  lpStringSID = NULL;  // указатель на строку с SID

  printf("Input a user name: ");
  wscanf(L"%s", user_name);      // вводим имя пользователя

  // определяем длину SID пользователя
  LookupAccountName(
    NULL,              // ищем имя на локальном компьютере
    user_name,         // имя пользователя
    NULL,              // определяем длину SID
    &dwLengthOfSID,    // длина SID
    NULL,              // определяем имя домена
    &dwLengthOfDomainName,   // длина имени домена
    &type_of_SID);     // тип учетной записи

  // проверяем, вернула ли функция длину SID
  if (dwLengthOfSID == 0)
  {
    dwErrCode = GetLastError();

    printf("Lookup account name failed.\n");
    printf("Error code: %d\n", dwErrCode);

    return dwErrCode;
  }

  // распределяем память для SID и имени домена
  lpSID = (PSID) new wchar_t[dwLengthOfSID];
  lpDomainName = (LPTSTR) new wchar_t[dwLengthOfDomainName];


  // определяем SID и имя домена пользователя
  if(!LookupAccountName(
    NULL,              // ищем имя на локальном компьютере
    user_name,         // имя пользователя
    lpSID,             // указатель на SID
    &dwLengthOfSID,    // длина SID
    lpDomainName,      // указатель на имя домена
    &dwLengthOfDomainName,   // длина имени домена
    &type_of_SID))     // тип учетной записи
  {
    dwErrCode = GetLastError();

    printf("Lookup account name failed.\n");
    printf("Error code: %d\n", dwErrCode);

    return dwErrCode;
  }

  // преобразуем SID в строку
  if (!ConvertSidToStringSid(lpSID, &lpStringSID))
  {
    printf("Convert SID to string SID failed.");

    return GetLastError();
  }
  // распечатываем SID
  wprintf(L"SID: %s\n", lpStringSID);
  // распечатываем имя домена
  wprintf(L"Domain name: %s\n", lpDomainName);


  // освобождаем память
  LocalFree(lpStringSID);

  delete[] lpDomainName;
  delete[] lpSID;

  return 0;
}