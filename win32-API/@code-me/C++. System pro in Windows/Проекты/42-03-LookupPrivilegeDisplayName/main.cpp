#include <windows.h>
#include <stdio.h>

int main()
{
  LPTSTR lpPrivDisplayName = NULL;   // адрес имени привилегии для отображения

  DWORD dwLength = 0;  // длина имени привилегии
  DWORD dwLangId;      // идентификатор языка

  DWORD dwRetCode;     // код возврата


  // определяем длину имени привилегии для отображения
  if (!LookupPrivilegeDisplayName (
    NULL,              // локальная машина
    SE_SHUTDOWN_NAME,  // имя привилегии
    lpPrivDisplayName,     // адрес для имени привилегии
    &dwLength,         // адрес длины буфера
    &dwLangId))        // адрес идентификатора языка
  {
    dwRetCode = GetLastError();
    if (dwRetCode != ERROR_INSUFFICIENT_BUFFER)
    {
      perror("Lookup privilege display name failed.\n");
      printf("The last error code: %u\n", dwRetCode);

      return dwRetCode;
    }

    // захватываем память для имени привилегии
    lpPrivDisplayName = new char[dwLength + 1];
  }

  // определяем имя привилегии для отображения
  if (!LookupPrivilegeDisplayName (
    NULL,              // локальная машина
    SE_SHUTDOWN_NAME,  // имя привилегии
    lpPrivDisplayName,     // адрес для имени привилегии
    &dwLength,         // адрес длины буфера
    &dwLangId))        // адрес идентификатора языка
  {
    dwRetCode = GetLastError();
    perror("Lookup privilege display name failed.\n");
    printf("The last error code: %u\n", dwRetCode);

    return dwRetCode;
  }

  // распечатываем имя привилегии и идентификатор языка
  printf("Display name of the privilege SE_SHUTDOWN_NAME:\n\t%s\n", lpPrivDisplayName);
  printf("Language identifier: %x\n", dwLangId);

  delete[] lpPrivDisplayName;

  return 0;
}