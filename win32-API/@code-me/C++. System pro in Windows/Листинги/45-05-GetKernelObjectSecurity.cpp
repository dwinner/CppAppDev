#ifndef UNICODE
#define UNICODE
#endif

#include <windows.h>
#include <stdio.h>

int main()
{
  HANDLE hMutex;     // дескриптор мьютекса

  DWORD dwLengthOfSd = 0;    // длина SD
  SECURITY_DESCRIPTOR *lpSd = NULL;  // дескриптор безопасности мьютекса

  PSID lpOwner;              // указатель на SID владельца
  BOOL bOwnerDefaulted = FALSE;      // признак владельца по умолчанию

  DWORD  dwLengthOfUserName = 0;     // длина имени учетной записи 
  DWORD  dwLengthOfDomainName = 0;   // длина имени домена

  LPTSTR  lpUserName = NULL;         // указатель на имя домена
  LPTSTR  lpDomainName = NULL;       // указатель на имя домена

  SID_NAME_USE type_of_SID;          // тип учетной записи

  DWORD dwRetCode;    // код возврата

  // создаем каталог
  hMutex = CreateMutex(NULL, FALSE, L"DemoMutex");
  if (hMutex == NULL)
  {
    dwRetCode = GetLastError();
    perror("Create mutex failed.\n");
    printf("The last error code: %u\n", dwRetCode);

    return dwRetCode;
  }

  printf("The mutex is created.\n");

  // определяем требуемую длину буфера
  if (!GetKernelObjectSecurity(
    hMutex,          // дескриптор мьютекса
    OWNER_SECURITY_INFORMATION,  // получаем владельца мьютекса
    lpSd,            // адрес SD
    0,               // определяем длину буфера
    &dwLengthOfSd))  // требуемая длина буфера
  {
    dwRetCode = GetLastError();

    if (dwRetCode == ERROR_INSUFFICIENT_BUFFER)
      // распределяем память для буфера
      lpSd = (SECURITY_DESCRIPTOR*) new char[dwLengthOfSd];
    else
    {
      // выходим из программы
      printf("Get kernel object security failed.\n");
      printf("Error code: %d\n", dwRetCode);

      return dwRetCode;
    }
  }

  // чтаем идентификатор безопасности мьютекса
  if (!GetKernelObjectSecurity(
    hMutex,          // дескриптор мьютекса
    OWNER_SECURITY_INFORMATION,  // получаем владельца мьютекса
    lpSd,            // адрес SD
    dwLengthOfSd,    // длина буфера
    &dwLengthOfSd))  // требуемая длина буфера
  {
    dwRetCode = GetLastError();
    printf("Get kernel object security failed.\n");
    printf("The last error code: %u\n", dwRetCode);

    return dwRetCode;
  }

  // получаем SID владельца мьютекса
  if (!GetSecurityDescriptorOwner(
    lpSd,                // адрес дескриптора безопасности
    &lpOwner,            // адрес указателя на SID владельца
    &bOwnerDefaulted))   // признак владельца по умолчанию
  {
    dwRetCode = GetLastError();
    printf("Get security descriptor owner failed.\n");
    printf("Error code: %d\n", dwRetCode);
    
    return dwRetCode;
  }

  // проверяем, есть ли владелец
  if (lpOwner == NULL)
  {
    printf("The owner is not present.\n");

    return 0;
  }

  if (bOwnerDefaulted)
    printf("The owner is defaulted.\n");
  
  // определяем длину имени домена
  if(!LookupAccountSid(
    NULL,                // ищем на локальном компьютере
    lpOwner,             // указатель на SID
    lpUserName,          // имя пользователя
    &dwLengthOfUserName,     // длина имени пользователя
    lpDomainName,        // определяем имя домена
    &dwLengthOfDomainName,   // длина имени домена
    &type_of_SID))       // тип учетной записи
  {
    dwRetCode = GetLastError();

    if (dwRetCode == ERROR_INSUFFICIENT_BUFFER)
    {
      // распределяем память под имя пользователя и имядомена
      lpUserName = (LPTSTR) new wchar_t[dwLengthOfUserName];
      lpDomainName = (LPTSTR) new wchar_t[dwLengthOfDomainName];
    }
    else
    {
      printf("Lookup account SID for length failed.\n");
      printf("Error code: %d\n", dwRetCode);

      return dwRetCode;
    }
  }

  // определяем имя учетной записи по SID
  if(!LookupAccountSid(
    NULL,                // ищем на локальном компьютере
    lpOwner,             // указатель на SID пользователя
    lpUserName,          // имя пользователя
    &dwLengthOfUserName,     // длина имени пользователя
    lpDomainName,        // определяем имя домена
    &dwLengthOfDomainName,   // длина имени домена
    &type_of_SID))       // тип учетной записи
  {
    dwRetCode = GetLastError();

    printf("Lookup account SID failed.\n");
    printf("Error code: %d\n", dwRetCode);

    return dwRetCode;
  }

  wprintf(L"User name: %s\n", lpUserName);
  wprintf(L"Domain name: %s\n", lpDomainName);

  // освобождаем память
  delete[] lpUserName;
  delete[] lpDomainName;
  delete[] lpSd;

  CloseHandle(hMutex);
  printf("The mutex is deleted.\n");

  return 0;
}