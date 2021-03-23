#include <windows.h>
#include <stdio.h>
#include <lm.h>

int main()
{
  HANDLE hProcess;     // дескриптор процесса
  HANDLE hToken;       // дескриптор маркера доступа
  HANDLE hRestrict;    // дескриптор ограничивающего маркера доступа
  
  char chUserName[UNLEN];  // имя пользователя

  DWORD  dwLengthOfUserName = UNLEN;  // длина имени учетной записи

  DWORD  dwLengthOfSID = 0;    // длина SID
  DWORD  dwLengthOfDomainName = 0;   // длина имени домена
  
  SID    *lpSid = NULL;          // указатель на SID
  LPTSTR  lpDomainName = NULL;   // указатель на имя домена
  
  SID_NAME_USE type_of_SID;      // тип учетной записи
  
  SID_AND_ATTRIBUTES RestrictingSid;   // ограничивающий SID

  DWORD dwRetCode;       // код возврата
  
  // получаем дескриптор процесса
  hProcess = GetCurrentProcess();
  
  // получаем маркер доступа процесса
  if (!OpenProcessToken(
    hProcess,          // дескриптор процесса
    TOKEN_ALL_ACCESS,  // полный доступ к маркеру доступа
    &hToken))          // дескриптор маркера
  {
    dwRetCode = GetLastError();
    printf( "Open process token failed: %u\n", dwRetCode);
    
    return dwRetCode;
  }
  printf("Input a user name: ");
  gets(chUserName);        // вводим имя пользователя

  // определяем длину SID пользователя
  if (!LookupAccountName(
    NULL,            // ищем имя на локальном компьютере
    chUserName,      // имя пользователя
    NULL,            // определяем длину SID
    &dwLengthOfSID,  // длина SID
    NULL,            // определяем имя домена
    &dwLengthOfDomainName,   // длина имени домена
    &type_of_SID))   // тип учетной записи
  {
    dwRetCode = GetLastError();

    if (dwRetCode == ERROR_INSUFFICIENT_BUFFER)
    {
      // распределяем память для SID и имени домена
      lpSid = (SID*) new char[dwLengthOfSID];
      lpDomainName = (LPTSTR) new wchar_t[dwLengthOfDomainName];
    }
    else
    {
      // выходим из программы
      printf("Lookup account name failed.\n");
      printf("Error code: %d\n", dwRetCode);

      return dwRetCode;
    }
  }

  // определяем SID и имя домена пользователя
  if(!LookupAccountName(
    NULL,            // ищем имя на локальном компьютере
    chUserName,      // имя пользователя
    lpSid,           // указатель на SID
    &dwLengthOfSID,  // длина SID
    lpDomainName,    // указатель на имя домена
    &dwLengthOfDomainName,   // длина имени домена
    &type_of_SID))   // тип учетной записи
  {
    dwRetCode = GetLastError();

    printf("Lookup account name failed.\n");
    printf("Error code: %d\n", dwRetCode);

    return dwRetCode;
  }

  // инициализируем ограничивающий SID
  RestrictingSid.Sid = lpSid;
  RestrictingSid.Attributes = 0;

  // создаем ограничивающий маркер доступа
  if (!CreateRestrictedToken(
    hToken,          // дескриптор исходного маркера доступа
    0,               // привилегии не изменяем
    0, NULL,         // флаг SE_GROUP_USE_FOR_DENY_ONLY не устанавливаем
    0, NULL,         // привилегии не удаляем
    1,               // один ограничивающий SID
    &RestrictingSid, // адрес ограничивающего SID
    &hRestrict))     // адрес ограничивающего маркера доступа
  {
    dwRetCode = GetLastError();

    printf("Create restricted token failed.\n");
    printf("Error code: %d\n", dwRetCode);

    return dwRetCode;
  }

  // проверяем замещение маркера доступа
  if (IsTokenRestricted(hRestrict))
    printf("The restricted token is created.\n");
  else
  {
    dwRetCode = GetLastError();

    printf("Is Token Restricted failed.\n");
    printf("Error code: %d\n", dwRetCode);

    return dwRetCode;
  }


  // замещаем контекст безопасности потока
  if (!ImpersonateLoggedOnUser(hRestrict))
  {
    dwRetCode = GetLastError();

    printf("Impersonate logged on user failed.\n");
    printf("Error code: %d\n", dwRetCode);

    return dwRetCode;
  }

  // здесь делаем какую-то работу
  printf("Some work is done.\n");

  // возвращаем исходный контекст
  if (!RevertToSelf())
  {
    dwRetCode = GetLastError();

    printf("Revert to self failed.\n");
    printf("Error code: %d\n", dwRetCode);

    return dwRetCode;
  }

  CloseHandle(hToken);

  return 0;
}