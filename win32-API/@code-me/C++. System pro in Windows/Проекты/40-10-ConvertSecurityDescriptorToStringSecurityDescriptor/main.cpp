#define _WIN32_WINNT 0x0500

#include <stdio.h>
#include <windows.h> 
#include <lm.h>
#include <aclapi.h>
#include <sddl.h>

int main()
{
  char chFileName[256];      // имя файла

  PSECURITY_DESCRIPTOR pSecurityDescriptor;    // указатель на SD
  LPSTR StringSecurityDescriptor;              // строка с SD
  DWORD StringSecurityDescriptorLen;           // длина строки с SD

  DWORD dwRetCode;        // код возврата

  // вводим имя файла, например: C:\\test.txt
  printf("Input a full path to your file: ");
  gets(chFileName);

  // получаем дескриптор безопасности файла
  dwRetCode = GetNamedSecurityInfo(
    chFileName,        // имя файла
    SE_FILE_OBJECT,    // объект файл
    DACL_SECURITY_INFORMATION,  // читаем список DACL
    NULL,        // указатель на владельца не нужен
    NULL,        // указатель на первичную группу не нужен
    NULL,        // указатель на DACL не нужен
    NULL,        // указатель на SACL не нужен
    &pSecurityDescriptor);   // адрес указателя на SD
  if (dwRetCode != ERROR_SUCCESS)
  {
    printf("Get named security info failed.\n");
    printf("Error code: %u\n", dwRetCode);

    return dwRetCode;
  }

  // преобразуем дескриптор безопасности в строку
  if(!ConvertSecurityDescriptorToStringSecurityDescriptor(
    pSecurityDescriptor,       // адрес дескриптора безопасности
    SDDL_REVISION_1,           // версия языка описания
    OWNER_SECURITY_INFORMATION | GROUP_SECURITY_INFORMATION | 
    DACL_SECURITY_INFORMATION | SACL_SECURITY_INFORMATION,
    &StringSecurityDescriptor,       // буфер для строки
    &StringSecurityDescriptorLen))   // длина буфера
  {
    dwRetCode = GetLastError();
    printf("Convert security descriptor to string security descriptor failed.");
    printf("Error code: %u\n", dwRetCode);

    return dwRetCode;
  }

  printf("String security descriptor length: %u\n", 
  StringSecurityDescriptorLen);
  printf("String security desriptor: %s\n", StringSecurityDescriptor);
  
  // освобождаем память
  LocalFree(pSecurityDescriptor);
  LocalFree(StringSecurityDescriptor);

  return 0;
}