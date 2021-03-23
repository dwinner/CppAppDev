#ifndef UNICODE
#define UNICODE
#endif

#include <stdio.h>
#include <windows.h> 
#include <lm.h>

int main()
{
  wchar_t user_name[UNLEN];  // имя пользователя

  DWORD dwErrCode;           // код возврата

  DWORD  dwLengthOfSID = 0;          // длина SID
  DWORD  dwLengthOfDomainName = 0;   // длина имени домена
  DWORD  dwLengthOfUserName = UNLEN; // длина имени учетной записи 
  SID    *lpSID = NULL;              // указатель на SID
  LPTSTR  lpDomainName = NULL;       // указатель на имя домена
  SID_NAME_USE type_of_SID;          // тип учетной записи

  // указатель на идентификатор авторизации SID
  PSID_IDENTIFIER_AUTHORITY  lpSia;
  // указатель на количество относительных идентификаторов
  PUCHAR  lpSubAuthorityCount;
  // указатель на относительный идентификатор
  DWORD  *lpSubAuthority;

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
  lpSID = (SID*) new char[dwLengthOfSID];
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

  // получаем характеристики SID и выводим их на консоль
  dwLengthOfSID = GetLengthSid(lpSID);
  printf("Length of SID: %u\n", dwLengthOfSID);

  lpSia = GetSidIdentifierAuthority(lpSID);
  printf("IdentifierAuthority: ");
  for (int i = 0; i < 6; ++i)
    printf("%u ", lpSia->Value[i]);
  printf("\n");

  lpSubAuthorityCount = GetSidSubAuthorityCount(lpSID);
  printf("SubAuthorityCount: %u\n", *lpSubAuthorityCount);

  printf("SubAuthorities: ");
  for (i = 0; i < *lpSubAuthorityCount; ++i)
  {
    lpSubAuthority = GetSidSubAuthority(lpSID, i);
    printf("%u ", *lpSubAuthority);
  }
  printf("\n");

  delete[] lpDomainName;
  delete[] lpSID;

  return 0;
}