#define _WIN32_WINNT 0x0500

#include <windows.h>
#include <stdio.h>
#include <sddl.h>

int main()
{
  char chDirName[248];       // имя файла
  
  PSECURITY_DESCRIPTOR lpSd = NULL;  // указатель на SD
  
  PSID lpGroup;              // указатель на SID первичной группы
  LPTSTR StringSid;          // указатель на строку SID
  BOOL bGroupDefaulted;      // признак группы по умолчанию
  
  DWORD dwLength;            // длина дескриптора безопасности

  DWORD dwRetCode;     // код возврата
  
  // вводим имя файла
  printf("Input a directory or file name: ");
  gets(chDirName);
  
  // получаем длину дескриптора безопасности
  if (!GetFileSecurity(
    chDirName,       // имя файла
    GROUP_SECURITY_INFORMATION,  // получаем SID первичной группы
    lpSd,            // адрес дескриптора безопасности
    0,               // определяем длину буфера
    &dwLength))      // адрес для требуемой длины
  {
    dwRetCode = GetLastError();
    
    if (dwRetCode == ERROR_INSUFFICIENT_BUFFER)
      // распределяем память для буфера
      lpSd = (SECURITY_DESCRIPTOR*) new char[dwLength];
    else
    {
      // выходим из программы
      printf("Get file security failed.\n");
      printf("Error code: %d\n", dwRetCode);
      
      return dwRetCode;
    }
  }
  
  // распределяем память для дескриптора безопасности
  lpSd = (PSECURITY_DESCRIPTOR) new char[dwLength];
  
  // читаем дескриптор безопасности
  if (!GetFileSecurity(
    chDirName,       // имя файла
    GROUP_SECURITY_INFORMATION,  // получаем SID первичной группы
    lpSd,            // адрес дескриптора безопасности
    dwLength,        // длину буфера
    &dwLength))      // адрес для требуемой длины
  {
    dwRetCode = GetLastError();
    printf("Get file security failed.\n");
    printf("Error code: %d\n", dwRetCode);
    
    return dwRetCode;
  }
  
  // получаем SID первичной группы
  if (!GetSecurityDescriptorGroup(
    lpSd,                // адрес дескриптора безопасности
    &lpGroup,            // адрес указателя на SID первичной группы
    &bGroupDefaulted))   // признак первичной группы по умолчанию
  {
    dwRetCode = GetLastError();
    printf("Get security descriptor group failed.\n");
    printf("Error code: %d\n", dwRetCode);
    
    return dwRetCode;
  }

  // проверяем, есть ли первичная группа
  if (lpGroup == NULL)
  {
    printf("The primary group is not present.\n");

    return 0;
  }
  
  // преобразуем SID в строку
  if (!ConvertSidToStringSid(
    lpGroup,       // указатель на SID первичной группы
    &StringSid))   // строка с SID
  {
    dwRetCode = GetLastError();
    printf("Convert sid to string sid failed.\n");
    printf("Error code: %d\n", dwRetCode);
    
    return dwRetCode;
  }

  printf("%s\n",StringSid);
  
  // освобождаем память
  LocalFree(StringSid);
  delete[] lpSd;
  
  return 0;
}