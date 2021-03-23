#define _WIN32_WINNT 0x0500

#include <stdio.h>
#include <windows.h> 
#include <lm.h>
#include <aclapi.h>
#include <sddl.h>

int main()
{
  char  chFileName[256];   // имя файла
  HANDLE  hFile;       // дескриптор файла

  PSID  pSidOwner;     // указатель на SID владельца объекта
  PSID  pSidGroup;     // указатель на SID первичной группы объекта
  PSECURITY_DESCRIPTOR  pSecurityDescriptor;  // указатель на SD

  LPTSTR  lpStringSid;   // указатель на строку SID

  DWORD  dwRetCode;      // код возврата

  // вводим полное имя файла, например: C:\\test.txt
  printf("Input a full path to your file: ");
  gets(chFileName);

  // открываем файл
  hFile = CreateFile(
    chFileName,        // имя файла
    READ_CONTROL,      // разрешаем доступ к дескриптору безопасности
    0,                 // не разделяем доступ
    NULL,              // не наследуемый дескриптор
    OPEN_EXISTING,     // открываем существующий файл
    FILE_ATTRIBUTE_NORMAL,   // обычный файл
    NULL);             // шаблона нет
  if(hFile == INVALID_HANDLE_VALUE)
  {
    dwRetCode = GetLastError();
    printf("Create file failed.\n");
    printf("Error code: %u\n", dwRetCode);

    return dwRetCode;
  }

  // получаем дескриптор безопасности файла
  dwRetCode = GetSecurityInfo(
    hFile,           // дескриптор файла
    SE_FILE_OBJECT,      // объект файл      
    GROUP_SECURITY_INFORMATION | 
    OWNER_SECURITY_INFORMATION,  // тип информации
    &pSidOwner,      // адрес указателя на SID владельца
    &pSidGroup,      // адрес указателя на первичную группу
    NULL,            // указатель на DACL не нужен
    NULL,            // указатель на SACL не нужен
    &pSecurityDescriptor);   // адрес указателя на SD
  if (dwRetCode != ERROR_SUCCESS)
  {
    printf("Get named security info failed.\n");
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
  LocalFree(pSecurityDescriptor);

  // закрываем файл
  CloseHandle(hFile);

  return 0;
}