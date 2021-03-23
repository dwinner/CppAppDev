#include <windows.h>
#include <stdio.h>

int main()
{
  SC_HANDLE hManager;            // дескриптор менеджера сервисов
  SC_HANDLE hService;            // дескриптор сервиса

  DWORD dwLengthOfSd = 0;        // длина SD
  SECURITY_DESCRIPTOR *lpSd;     // дескриптор безопасности сервиса

  PSID lpOwner;                  // указатель на SID владельца
  BOOL bOwnerDefaulted = FALSE;  // признак владельца по умолчанию

  DWORD  dwLengthOfUserName = 0;     // длина имени учетной записи 
  DWORD  dwLengthOfDomainName = 0;   // длина имени домена

  LPTSTR  lpUserName = NULL;     // указатель на имя домена
  LPTSTR  lpDomainName = NULL;   // указатель на имя домена

  SID_NAME_USE type_of_SID;      // тип учетной записи

  DWORD dwRetCode;   // код возврата

  // инициализируем, так как NULL выдаст ошибку
  lpSd = (SECURITY_DESCRIPTOR*) new char[0];

  // связываемся с менеджероом сервисов
  hManager = OpenSCManager(
    NULL,            // локальная машина
    NULL,            // активная база данных сервисов
    GENERIC_READ);   // читаем управляющую информацию
  if (hManager == NULL)
  {
    dwRetCode = GetLastError();
    printf("Open SC manager failed.\n");
    printf("The last error code: %u\n", dwRetCode);

    return dwRetCode;
  }

  // открывае сервис
  hService = OpenService(
    hManager,        // дескриптор менеджера сервисов
    "PlugPlay",      // имя сервиса
    READ_CONTROL);   // режим доступа
  if (hService == NULL)
  {
    dwRetCode = GetLastError();
    printf("Open service failed.\n");
    printf("The last error code: %u\n", dwRetCode);

    return dwRetCode;
  }

  // определяем длину идентификатор безопасности сервиса
  if (!QueryServiceObjectSecurity(
    hService,        // дескриптор сервиса
    OWNER_SECURITY_INFORMATION,  // получаем владельца сервиса
    lpSd,            // адрес SD
    dwLengthOfSd,    // длина буфера
    &dwLengthOfSd))  // требуемая длина буфера
  {
    dwRetCode = GetLastError();

    if (dwRetCode == ERROR_INSUFFICIENT_BUFFER)
      // захватываем память под дескриптор безопасности
      lpSd = (SECURITY_DESCRIPTOR*)new char[dwLengthOfSd];
    else
    {
      printf("Query Service Object Security failed.\n");
      printf("The last error code: %u\n", dwRetCode);

      return dwRetCode;
    }
  }

  // читаем идентификатор безопасности сервиса
  if (!QueryServiceObjectSecurity(
    hService,        // дескриптор сервиса
    OWNER_SECURITY_INFORMATION,  // получаем владельца мьютекса
    lpSd,            // адрес SD
    dwLengthOfSd,    // длина буфера
    &dwLengthOfSd))  // требуемая длина буфера
  {
    dwRetCode = GetLastError();
    printf("Query Service Object Security failed.\n");
    printf("The last error code: %u\n", dwRetCode);

    return dwRetCode;
  }

  // получаем SID владельца сервиса
  if (!GetSecurityDescriptorOwner(
    lpSd,          // адрес дескриптора безопасности
    &lpOwner,      // адрес указателя на SID владельца
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
  else
    printf("The owner is not defaulted.\n");

  // определяем длину имени домена
  if(!LookupAccountSid(
    NULL,              // ищем на локальном компьютере
    lpOwner,           // указатель на SID
    lpUserName,        // имя пользователя
    &dwLengthOfUserName,     // длина имени пользователя
    lpDomainName,      // определяем имя домена
    &dwLengthOfDomainName,   // длина имени домена
    &type_of_SID))     // тип учетной записи
  {
    dwRetCode = GetLastError();

    if (dwRetCode == ERROR_INSUFFICIENT_BUFFER)
    {
      // распределяем память под имя пользователя и имя домена
      lpUserName = (LPTSTR) new char[dwLengthOfUserName];
      lpDomainName = (LPTSTR) new char[dwLengthOfDomainName];
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
    NULL,              // ищем на локальном компьютере
    lpOwner,           // указатель на SID пользователя
    lpUserName,        // имя пользователя
    &dwLengthOfUserName,     // длина имени пользователя
    lpDomainName,      // определяем имя домена
    &dwLengthOfDomainName,   // длина имени домена
    &type_of_SID))     // тип учетной записи
  {
    dwRetCode = GetLastError();

    printf("Lookup account SID failed.\n");
    printf("Error code: %d\n", dwRetCode);

    return dwRetCode;
  }

  printf("The owner name: %s\n", lpUserName);
  printf("The owner domain name: %s\n", lpDomainName);

  // освобождаем память
  delete[] lpUserName;
  delete[] lpDomainName;
  delete[] lpSd;

  CloseServiceHandle(hService);
  CloseServiceHandle(hManager);

  return 0;
}