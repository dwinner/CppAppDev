#ifndef UNICODE
#define UNICODE
#endif

#include <stdio.h>
#include <windows.h> 
#include <lm.h>
#include <aclapi.h>

int main()
{
  wchar_t wchFileName[256];      // имя файла
  wchar_t wchUserName[UNLEN];    // имя нового владельца файла

  PSID  lpSID = NULL;            // указатель на SID
  LPTSTR  lpDomainName = NULL;   // указатель на имя домена

  DWORD  dwLengthOfSID = 0;      // длина SID
  DWORD  dwLengthOfDomainName = 0;   // длина имени домена

  DWORD dwRetCode;               // код возврата

  SID_NAME_USE typeOfSID;        // тип учетной записи

  // вводим имя файла, например: C:\\test.txt
  printf("Input a full path to your file: ");
  _getws(wchFileName);

  // вводим имя нового владельца объекта
  printf("Input a user name: ");
  wscanf(L"%s", wchUserName);

  // определяем длину SID нового владельца файла
  LookupAccountName(
    NULL,              // ищем имя на локальном компьютере
    wchUserName,       // имя нового владельца файла
    NULL,              // определяем длину SID
    &dwLengthOfSID,    // длина SID
    NULL,              // определяем имя домена
    &dwLengthOfDomainName,   // длина имени домена
    &typeOfSID);       // тип учетной записи

  // проверяем, вернула ли функция длину SID
  if (dwLengthOfSID == 0)
  {
    dwRetCode = GetLastError();

    printf("Lookup account name failed.\n");
    printf("Error code: %d\n", dwRetCode);

    return dwRetCode;
  }

  // распределяем память для SID и имени домена
  lpSID = (PSID) new wchar_t[dwLengthOfSID];
  lpDomainName = (LPTSTR) new wchar_t[dwLengthOfDomainName];

  // определяем SID и имя домена пользователя
  if(!LookupAccountName(
    NULL,              // ищем имя на локальном компьютере
    wchUserName,       // имя пользователя
    lpSID,             // указатель на SID
    &dwLengthOfSID,    // длина SID
    lpDomainName,      // указатель на имя домена
    &dwLengthOfDomainName,   // длина имени домена
    &typeOfSID))       // тип учетной записи
  {
    dwRetCode = GetLastError();

    printf("Lookup account name failed.\n");
    printf("Error code: %d\n", dwRetCode);

    return dwRetCode;
  }
 
  // устанавливаем нового владельца файла
  dwRetCode = SetNamedSecurityInfo(
    wchFileName,       // имя файла
    SE_FILE_OBJECT,     // объект файл
    OWNER_SECURITY_INFORMATION,  // изменяем только имя владельца файла
    lpSID,         // адрес на SID нового владельца
    NULL,          // первичную группу не изменяем
    NULL,          // DACL не изменяем
    NULL);         // SACL не изменяем
  if (dwRetCode != ERROR_SUCCESS)
  {
    printf("Set named security info failed.\n");
    printf("Error code: %u\n", dwRetCode);

    return dwRetCode;
  }

  printf("The new owner of the file is set.\n");
  
  // освобождаенм память
  delete[] lpSID;
  delete[] lpDomainName;

  return 0;
}