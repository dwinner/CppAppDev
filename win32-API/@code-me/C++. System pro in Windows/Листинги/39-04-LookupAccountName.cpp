#ifndef UNICODE
#define UNICODE
#endif

#include <stdio.h>
#include <windows.h> 
#include <lm.h>

int main()
{
  wchar_t user_name[UNLEN];    // имя пользователя

  DWORD dwErrCode;             // код возврата

  DWORD  dwLengthOfSID = 0;          // длина SID
  DWORD  dwLengthOfDomainName = 0;   // длина имени домена
  DWORD  dwLengthOfUserName = UNLEN; // длина имени учетной записи 
  SID    *lpSID = NULL;              // указатель на SID
  LPTSTR  lpDomainName = NULL;       // указатель на имя домена
  SID_NAME_USE type_of_SID;          // тип учетной записи

  printf("Input a user name: ");
  wscanf(L"%s", user_name);    // вводим имя пользователя

  // определяем длину SID пользователя
  if (!LookupAccountName(
    NULL,          // ищем имя на локальном компьютере
    user_name,     // имя пользователя
    NULL,          // определяем длину SID
    &dwLengthOfSID,    // длина SID
    NULL,          // определяем имя домена
    &dwLengthOfDomainName,   // длина имени домена
    &type_of_SID)) // тип учетной записи
  {
    dwErrCode = GetLastError();

    if (dwErrCode == ERROR_INSUFFICIENT_BUFFER)
    {
      // распределяем память для SID и имени домена
      lpSID = (SID*) new char[dwLengthOfSID];
      lpDomainName = (LPTSTR) new wchar_t[dwLengthOfDomainName];
    }
    else
    {
      // выходим из программы
      printf("Lookup account name failed.\n");
      printf("Error code: %d\n", dwErrCode);

      return dwErrCode;
    }
  }

  // определяем SID и имя домена пользователя
  if(!LookupAccountName(
    NULL,            // ищем имя на локальном компьютере
    user_name,       // имя пользователя
    lpSID,           // указатель на SID
    &dwLengthOfSID,  // длина SID
    lpDomainName,    // указатель на имя домена
    &dwLengthOfDomainName,   // длина имени домена
    &type_of_SID))   // тип учетной записи
  {
    dwErrCode = GetLastError();

    printf("Lookup account name failed.\n");
    printf("Error code: %d\n", dwErrCode);

    return dwErrCode;
  }

  // выводим SID на консоль
  printf("SID revision: %u\n", lpSID->Revision);
  printf("SubAuthorityCount: %u\n", lpSID->SubAuthorityCount);
  printf("IdentifierAuthority: ");
  for (int i = 0; i < 6; ++i)
    printf("%u ", lpSID->IdentifierAuthority.Value[i]);
  printf("\n");
  printf("SubAuthorities: ");
  for (i = 0; i < lpSID->SubAuthorityCount; ++i)
    printf("%u ", lpSID->SubAuthority[i]);
  printf("\n");

  // выводим имя домена
  wprintf(L"Domain name: %s\n", lpDomainName);

  delete[] lpDomainName;
  delete[] lpSID;

  return 0;
}