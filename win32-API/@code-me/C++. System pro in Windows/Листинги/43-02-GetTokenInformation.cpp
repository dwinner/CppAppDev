#include <windows.h>
#include <stdio.h>

int main()
{
  HANDLE hProcessToken;      // дескриптор маркера доступа
  PTOKEN_PRIVILEGES lpTokenPrivileges = NULL;
  
  LPTSTR lpPrivName = NULL;          // адрес имени привилегии
  LPTSTR lpPrivDisplayName = NULL;   // адрес имени привилегии для 
                                     // отображения

  DWORD dwLangId;
  DWORD dwLength;
  
  DWORD dwRetCode;      // код возврата
  
  if (!OpenProcessToken(
    GetCurrentProcess(),     // дескриптор процесса
    TOKEN_QUERY,             // чтение информации из маркера доступа
    &hProcessToken ))        // дескриптор маркера доступа
  {
    dwRetCode = GetLastError();
    perror("Set security descriptor owner failed.\n");
    printf("The last error code: %u\n", dwRetCode);
    
    return dwRetCode;
  }
  
  // получаем длину буфера для привилегий
  if (!GetTokenInformation(
    hProcessToken,       // дескриптор маркера доступа
    TokenPrivileges,     // получаем привилегии
    lpTokenPrivileges,   // адрес буфера
    0,                   // длина буфера
    &dwLength))          // требуемая длина
  {
    dwRetCode = GetLastError();
    if (dwRetCode != ERROR_INSUFFICIENT_BUFFER)
    {
      perror("Get token information for length failed.\n");
      printf("The last error code: %u\n", dwRetCode);
      
      return dwRetCode;
    }
    
    // захватываем память для имени привилегии
    lpTokenPrivileges = (TOKEN_PRIVILEGES*)new char[dwLength];
  }
  
  // получаем привилегии маркера доступа
  if (!GetTokenInformation(
    hProcessToken,       // дескриптор маркера доступа
    TokenPrivileges,     // получаем привилегии
    lpTokenPrivileges,   // адрес буфера
    dwLength,            // длина буфера
    &dwLength))          // требуемая длина
  {
    dwRetCode = GetLastError();
    perror("Get token information failed.\n");
    printf("The last error code: %u\n", dwRetCode);
    
    return dwRetCode;
  }
  
  // распечатываем привилегии
  printf( "User privileges: \n" );
  for( unsigned i = 0; i < lpTokenPrivileges->PrivilegeCount; ++i)
  {
    // печатаем состояние привилегии
    if ((lpTokenPrivileges->Privileges[i].Attributes & 
        SE_PRIVILEGE_ENABLED) == SE_PRIVILEGE_ENABLED)
      printf("SE_PRIVILEGE_ENABLED:\n");
    if ((lpTokenPrivileges->Privileges[i].Attributes & 
        SE_PRIVILEGE_ENABLED_BY_DEFAULT) == 
        SE_PRIVILEGE_ENABLED_BY_DEFAULT)
      printf("SE_PRIVILEGE_ENABLED_BY_DEFAULT:\n");
    if ((lpTokenPrivileges->Privileges[i].Attributes & 
        SE_PRIVILEGE_USED_FOR_ACCESS) == SE_PRIVILEGE_USED_FOR_ACCESS)
      printf("SE_PRIVILEGE_USED_FOR_ACCESS:\n");
    if (!lpTokenPrivileges->Privileges[i].Attributes)
      printf("The privilege is disabled:\n");

    // определяем длину имени привилегии
    dwLength = 0;
    if (!LookupPrivilegeName(
      NULL,        // локальная машина
      &(lpTokenPrivileges->Privileges[i].Luid),  // адрес LUID
      lpPrivName,  // адрес имени привилегии
      &dwLength))  // адрес длины буфера
    {
      dwRetCode = GetLastError();
      if (dwRetCode != ERROR_INSUFFICIENT_BUFFER)
      {
        perror("Lookup privilege name for length failed.\n");
        printf("The last error code: %u\n", dwRetCode);
        
        return dwRetCode;
      }
      
      // захватываем память для имени привилегии
      lpPrivName = new char[dwLength + 1];
    }
    
    // определяем имя привилегии
    if (!LookupPrivilegeName(
      NULL,        // локальная машина
      &(lpTokenPrivileges->Privileges[i].Luid),  // адрес LUID
      lpPrivName,  // адрес имени привилегии
      &dwLength))  // адрес длины буфера
    {
      dwRetCode = GetLastError();
      perror("Lookup privilege name failed.\n");
      printf("The last error code: %u\n", dwRetCode);
      
      return dwRetCode;
    }
    // определяем длину имени привилегии для отображения
    dwLength = 0;
    if (!LookupPrivilegeDisplayName (
      NULL,          // локальная машина
      lpPrivName,    // имя привилегии
      lpPrivDisplayName,   // адрес для имени привилегии
      &dwLength,     // адрес длины буфера
      &dwLangId))    // адрес идентификатора языка
    {
      dwRetCode = GetLastError();
      if (dwRetCode != ERROR_INSUFFICIENT_BUFFER)
      {
        perror("Lookup privilege display name for length failed.\n");
        printf("The last error code: %u\n", dwRetCode);
        
        return dwRetCode;
      }
      
      // захватываем память для имени привилегии
      lpPrivDisplayName = new char[dwLength + 1];
    }
    
    // определяем имя привилегии для отображения
    if (!LookupPrivilegeDisplayName (
      NULL,          // локальная машина
      lpPrivName,    // имя привилегии
      lpPrivDisplayName,   // адрес для имени привилегии
      &dwLength,     // адрес длины буфера
      &dwLangId))    // адрес идентификатора языка
    {
      dwRetCode = GetLastError();
      perror("Lookup privilege display name failed.\n");
      printf("The last error code: %u\n", dwRetCode);
      
      return dwRetCode;
    }
    
    // распечатываем имя привилегии и идентификатор языка
    printf("\t%s\n", lpPrivDisplayName);

    // освобождаем память
    delete[] lpPrivName;
    delete[] lpPrivDisplayName;

    lpPrivName = NULL;
    lpPrivDisplayName = NULL;
  }

  CloseHandle(hProcessToken);

  return 0;
}