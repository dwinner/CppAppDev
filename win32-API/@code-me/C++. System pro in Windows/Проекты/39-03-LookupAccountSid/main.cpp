#ifndef UNICODE
#define UNICODE
#endif

#include <stdio.h>
#include <windows.h> 
#include <lm.h>

int main()
{
  wchar_t user_name[UNLEN];    // имя пользователя

  HANDLE  hProcess;        // дескриптор процесса
  HANDLE  hTokenHandle;    // дескриптор маркера доступа

  DWORD  dwErrCode;        // код возврата

  TOKEN_OWNER  *lpTokenOwner = NULL;    // буфер для информации
  DWORD  dwLength= 0;      // длина буфера

  DWORD  dwLengthOfUserName = UNLEN;   // длина имени учетной записи 
  DWORD  dwLengthOfDomainName = 0;     // длина имени домена
  LPTSTR  lpDomainName = NULL;         // указатель на имя домена
  SID_NAME_USE type_of_SID;            // тип учетной записи

  // получаем маркер доступа процесса
  hProcess = GetCurrentProcess();
  // получить маркер доступа процесса
  if (!OpenProcessToken(
    hProcess,        // дескриптор процесса
    TOKEN_QUERY,     // запрос информации из маркера
    &hTokenHandle))  // дескриптор маркера
  {
    dwErrCode = GetLastError();
    printf( "Open process token failed: %u\n", dwErrCode);

    return dwErrCode;
  }
  // определяем длину SID
  if (!GetTokenInformation(
    hTokenHandle,  // дескриптор маркера доступа  
    TokenOwner,    // получаем SID владельца
    NULL,          // нужна длина буфера
    0,             // пока длина равна 0
    &dwLength))    // для длины буфера
  {
    dwErrCode = GetLastError();
    if (dwErrCode == ERROR_INSUFFICIENT_BUFFER)
      // захватываем память под SID
      lpTokenOwner = (TOKEN_OWNER*)new char[dwLength];
    else
    {
      // выходим из программы
      printf( "Get token information for length failed: %u\n", 
         dwErrCode);
      return dwErrCode;
    }
  }

  // определяем имя владельца
  if (!GetTokenInformation(
    hTokenHandle,  // дескриптор маркера доступа
    TokenOwner,    // нужен SID маркера доступа
    lpTokenOwner,  // адрес буфера для SID
    dwLength,      // длина буфера
    &dwLength))    // длина буфера
  {
    dwErrCode = GetLastError();
    printf( "Get token information failed: %u\n", dwErrCode);

    return dwErrCode;
  }

  // определяем длину имени домена
  if(!LookupAccountSid(
    NULL,                  // ищем на локальном компьютере
    lpTokenOwner->Owner,   // указатель на SID
    user_name,             // имя пользователя
    &dwLengthOfUserName,    // длина имени пользователя
    lpDomainName,          // определяем имя домена
    &dwLengthOfDomainName, // длина имени домена
    &type_of_SID))         // тип учетной записи
  {
    dwErrCode = GetLastError();

    if (dwErrCode == ERROR_INSUFFICIENT_BUFFER)
        // распределяем память под имя домена
        lpDomainName = (LPTSTR) new wchar_t[dwLengthOfDomainName];
    else
    {
      printf("Lookup account SID for length failed.\n");
      printf("Error code: %d\n", dwErrCode);

      return dwErrCode;
    }
  }

  // определяем имя учетной записи по SID
  if(!LookupAccountSid(
    NULL,                  // ищем на локальном компьютере
    lpTokenOwner->Owner,   // указатель на SID
    user_name,             // имя пользователя
    &dwLengthOfUserName,   // длина имени пользователя
    lpDomainName,          // определяем имя домена
    &dwLengthOfDomainName, // длина имени домена
    &type_of_SID))         // тип учетной записи
  {
    dwErrCode = GetLastError();

    printf("Lookup account SID failed.\n");
    printf("Error code: %d\n", dwErrCode);

    return dwErrCode;
  }

  wprintf(L"User name: %s\n", user_name);    
  wprintf(L"Domain name: %s\n", lpDomainName);    

  // освобождаем память
  delete[] lpDomainName;
  delete[] lpTokenOwner;

  return 0;
}