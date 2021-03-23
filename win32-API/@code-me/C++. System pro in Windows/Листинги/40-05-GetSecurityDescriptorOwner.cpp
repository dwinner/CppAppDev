#define _WIN32_WINNT 0x0500

#include <stdio.h>
#include <windows.h> 
#include <sddl.h>

int main()
{
  char chFileName[256];    // имя файла

  PSID pSidOwner = NULL;   // указатель на SID владельца объекта
  PSID pSidGroup = NULL;   // указатель на SID первичной группы объекта
  PSECURITY_DESCRIPTOR pSD = NULL;  // указатель на SD
  BOOL bOwnerDefaulted = FALSE;   // флаг владельца по умолчанию
  BOOL bGroupDefaulted = FALSE;   // флаг первичной группы по умолчанию

  LPTSTR lpStringSid;    // указатель на строку SID

  DWORD dwLength = 0;    // длина дескриптора безопасности
  DWORD dwRetCode;       // код возврата

  // вводим имя файла, к которому вы имеете доступ
  printf("Input a full path to your file or directory: ");
  gets(chFileName);

  // получаем длину дескриптора безопасности файла
  if (!GetFileSecurity(
    chFileName,      // имя файла
    GROUP_SECURITY_INFORMATION | 
    OWNER_SECURITY_INFORMATION,    // информация, которую нужно получить
    pSD,             // адрес буфера для дескриптора безопасности
    dwLength,        // длина буфера
    &dwLength))      // необходимая длина

    if (dwLength != 0)
      // захватываем память для дескриптора безопасности
      pSD = (PSECURITY_DESCRIPTOR) new char[dwLength];
    else
    {
      printf("Get file security for length failed.\n");
      dwRetCode = GetLastError();
      printf("Error code: %u\n", dwRetCode);

      return dwRetCode;
    }

  // получаем дескриптор безопасности файла
  if (!GetFileSecurity(
    chFileName,      // имя файла
    GROUP_SECURITY_INFORMATION | 
    OWNER_SECURITY_INFORMATION,    // информация, которую нужно получить
    pSD,             // адрес буфера для дескриптора безопасности
    dwLength,        // длина буфера
    &dwLength))      // необходимая длина
  {
    printf("Get file security failed.\n");
    dwRetCode = GetLastError();
    printf("Error code: %u\n", dwRetCode);

    return dwRetCode;
  }

  // получаем идентификатор безопасности владельца объекта
  if (!GetSecurityDescriptorOwner(
    pSD,
    &pSidOwner,
    &bOwnerDefaulted))
  {
    printf("Get security descriptor owner failed.\n");
    dwRetCode = GetLastError();
    printf("Error code: %u\n", dwRetCode);

    return dwRetCode;
  }

  // получаем SD первичной группы владельца объекта
  if (!GetSecurityDescriptorGroup(
    pSD,
    &pSidGroup,
    &bGroupDefaulted))
  {
    printf("Get security descriptor group failed.\n");
    dwRetCode = GetLastError();
    printf("Error code: %u\n", dwRetCode);

    return dwRetCode;
  }

  // преобразуем SID владельца в строку
  if (!ConvertSidToStringSid(pSidOwner, &lpStringSid))
  {
    printf("Convert SID to string SID failed.");
    dwRetCode = GetLastError();
  
    return dwRetCode;
  }
  // печатаем SID владельца
  printf("Owner SID: %s\n", lpStringSid);
  // освобождаем память для строки
  LocalFree(lpStringSid);

  // преобразуем SID первичной группы в строку
  if (!ConvertSidToStringSid(pSidGroup, &lpStringSid))
  {
    printf("Convert SID to string SID failed.");
    dwRetCode = GetLastError();
  
    return dwRetCode;
  }
  // печатаем SID первичной группы
  printf("Group SID: %s\n", lpStringSid);
  // освобождаем память для строки
  LocalFree(lpStringSid);
  
  // освобождаем память для дескриптора
  delete[] pSD;

  return 0;
}