#ifndef UNICODE
#define UNICODE
#endif

#include <windows.h>
#include <stdio.h>
#include <lm.h>

int main()
{
  wchar_t wchDirName[248];         // имя каталога
  wchar_t wchUserName[UNLEN];      // имя пользователя
  
  DWORD dwSdLength = 0;            // длина SD
  DWORD dwSidLength = 0;           // длина SID
  DWORD dwLengthOfDomainName = 0;  // длина имени домена
  
  PSID lpSid = NULL;               // указатель на SID нового владельца
  LPTSTR lpDomainName = NULL;      // указатель на имя домена
  
  SID_NAME_USE typeOfSid;          // тип учетной записи
  
  SECURITY_DESCRIPTOR sdAbsoluteSd;  // абсолютный формат дескриптора безопасности

  DWORD dwRetCode;     // код возврата

  // читаем имя файла или каталога
  printf("Input a file or directory name: ");
  _getws(wchDirName);

  // вводим имя пользователя, который будет новым владельцем файла
  printf("Input a user name: ");
  _getws(wchUserName);
  
  // определяем длину SID пользователя
  if (!LookupAccountName(
    NULL,            // ищем имя на локальном компьютере
    wchUserName,     // имя пользователя
    NULL,            // определяем длину SID
    &dwSidLength,    // длина SID
    NULL,            // определяем имя домена
    &dwLengthOfDomainName,   // длина имени домена
    &typeOfSid))     // тип учетной записи
  {
    dwRetCode = GetLastError();
    
    if (dwRetCode == ERROR_INSUFFICIENT_BUFFER)
    {
      // распределяем память для SID
      lpSid = (SID*) new char[dwSidLength];
      lpDomainName = (LPTSTR) new wchar_t[dwLengthOfDomainName];
    }
    else
    {
      // выходим из программы
      printf("Lookup account name length failed.\n");
      printf("Error code: %d\n", dwRetCode);
      
      return dwRetCode;
    }
  }
  
  // определяем SID
  if(!LookupAccountName(
    NULL,              // ищем имя на локальном компьютере
    wchUserName,       // имя пользователя
    lpSid,             // указатель на SID
    &dwSidLength,      // длина SID
    lpDomainName,      // указатель на имя домена
    &dwLengthOfDomainName,   // длина имени домена
    &typeOfSid))       // тип учетной записи
  {
    dwRetCode = GetLastError();
    
    printf("Lookup account name failed.\n");
    printf("Error code: %d\n", dwRetCode);
    
    return dwRetCode;
  }

  // создаем дескриптор безопасности
  if (!InitializeSecurityDescriptor(
    &sdAbsoluteSd,     // адрес структуры SD
    SECURITY_DESCRIPTOR_REVISION))
  {
    dwRetCode = GetLastError();
    perror("Initialize security descriptor failed.\n");
    printf("The last error code: %u\n", dwRetCode);
    
    return dwRetCode;
  }

  // устанавливаем нового владельца в дескриптор безопасности
  if (!SetSecurityDescriptorOwner(
    &sdAbsoluteSd,     // адрес дескриптора безопасности
    lpSid,             // указатель на SID
    FALSE))            // SID не задан по умолчанию
  {
    dwRetCode = GetLastError();
    perror("Set security descriptor owner failed.\n");
    printf("The last error code: %u\n", dwRetCode);
    
    return dwRetCode;
  }
  
  // проверяем структуру дескриптора безопасности
  if (!IsValidSecurityDescriptor(&sdAbsoluteSd))
  {
    dwRetCode = GetLastError();
    perror("Security descriptor is invalid.\n");
    printf("The last error code: %u\n", dwRetCode);
    
    return dwRetCode;
  }
  // устанавливаем новый дескриптор безопасности
  if (!SetFileSecurity(
    wchDirName,          // имя файла
    OWNER_SECURITY_INFORMATION,  // устанавливаем SID
    &sdAbsoluteSd))      // адрес дескриптора безопасности
  {
    dwRetCode = GetLastError();

    if (dwRetCode == ERROR_INVALID_OWNER)
      printf("The user can not be the owner of the file.\n");  

    printf("Set file security failed.\n");
    printf("Error code: %d\n", dwRetCode);
    
    return dwRetCode;
  }
  
  // освобождаем память
  delete[] lpSid;
  delete[] lpDomainName;

  return 0;
}