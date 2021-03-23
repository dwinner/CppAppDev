#ifndef UNICODE
#define UNICODE
#endif

#include <stdio.h>
#include <windows.h> 
#include <lm.h>

int main()
{
  wchar_t group_name[GNLEN];   // имя группы

  DWORD dwErrCode;             // код возврата

  DWORD  dwLengthOfSID = 0;          // длина SID
  DWORD  dwLengthOfDomainName = 0;   // длина имени домена
  DWORD  dwLengthOfUserName = UNLEN; // длина имени учетной записи 
  SID    *lpSID_1 = NULL;            // указатель на SID первой группы
  SID    *lpSID_2 = NULL;            // указатель на SID второй группы
  LPTSTR  lpDomainName_1 = NULL;     // указатель на имя домена
  LPTSTR  lpDomainName_2 = NULL;     // указатель на имя домена
  SID_NAME_USE type_of_SID;          // тип учетной записи

  printf("Input a name of the first group: ");
  wscanf(L"%s", group_name);       // вводим имя группы

  // определяем длину SID группы
  LookupAccountName(
    NULL,              // ищем имя на локальном компьютере
    group_name,        // имя пользователя
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
  lpSID_1 = (SID*) new char[dwLengthOfSID];
  lpDomainName_1 = (LPTSTR) new wchar_t[dwLengthOfDomainName];

  // определяем SID и имя домена группы
  if(!LookupAccountName(
    NULL,              // ищем имя на локальном компьютере
    group_name,        // имя группы
    lpSID_1,           // указатель на SID
    &dwLengthOfSID,    // длина SID
    lpDomainName_1,    // указатель на имя домена
    &dwLengthOfDomainName,   // длина имени домена
    &type_of_SID))     // тип учетной записи
  {
    dwErrCode = GetLastError();

    printf("Lookup account name failed.\n");
    printf("Error code: %d\n", dwErrCode);

    return dwErrCode;
  }

  // проверяем тип учетной записи
  if (type_of_SID != SidTypeAlias)
  {
    printf("This is not a group.\n");
    return 1;
  }

  printf("Input a name of the second group: ");
  wscanf(L"%s", group_name);       // вводим имя группы

  // определяем длину SID группы
  LookupAccountName(
    NULL,              // ищем имя на локальном компьютере
    group_name,        // имя пользователя
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
  lpSID_2 = (SID*) new char[dwLengthOfSID];
  lpDomainName_2 = (LPTSTR) new wchar_t[dwLengthOfDomainName];

  // определяем SID и имя домена группы
  if(!LookupAccountName(
    NULL,              // ищем имя на локальном компьютере
    group_name,        // имя группы
    lpSID_2,           // указатель на SID
    &dwLengthOfSID,    // длина SID
    lpDomainName_2,    // указатель на имя домена
    &dwLengthOfDomainName,   // длина имени домена
    &type_of_SID))     // тип учетной записи
  {
    dwErrCode = GetLastError();

    printf("Lookup account name failed.\n");
    printf("Error code: %d\n", dwErrCode);

    return dwErrCode;
  }

  // проверяем тип учетной записи
  if (type_of_SID != SidTypeAlias)
  {
    printf("This is not a group.\n");
    return 1;
  }

  // сравниваем префиксы SID групп
  if (EqualPrefixSid(lpSID_1, lpSID_2))
    printf("SID prefixes are equal\n");
  else
    printf("SID prefixes are not equal\n");

  delete[] lpDomainName_1;
  delete[] lpDomainName_2;
  delete[] lpSID_1;
  delete[] lpSID_2;

  return 0;
}