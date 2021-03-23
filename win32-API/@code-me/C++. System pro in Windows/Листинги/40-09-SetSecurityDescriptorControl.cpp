#define _WIN32_WINNT 0x0500

#ifndef PROTECTED_DACL_SECURITY_INFORMATION
#define PROTECTED_DACL_SECURITY_INFORMATION  0x80000000L
#endif

#include <stdio.h>
#include <windows.h> 
#include <lm.h>
#include <aclapi.h>
#include <sddl.h>

int main()
{
  char chFileName[256];    // имя файла
  HANDLE hFile;            // дескриптор файла

  PSECURITY_DESCRIPTOR pSecurityDescriptor;  // указатель на SD
  PACL pDacl;          // указатель на DACL

  DWORD dwRetCode;    // код возврата

  // вводим полное имя файла, например: C:\\test.txt
  printf("Input a full path to your file: ");
  gets(chFileName);

  // открываем файл
  hFile = CreateFile(
    chFileName,      // имя файла
    READ_CONTROL | WRITE_DAC,  // доступ к дескриптору безопасности
    0,               // не разделяем доступ
    NULL,            // не наследуемый дескриптор
    OPEN_EXISTING,   // открываем существующий файл
    FILE_ATTRIBUTE_NORMAL,   // обычный файл
    NULL);           // шаблона нет
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
    SE_FILE_OBJECT,  // объект файл
    DACL_SECURITY_INFORMATION,   // тип информации
    NULL,            // указатель на SID владельца не нужен
    NULL,            // указатель на первичную группу не нужен
    &pDacl,          // указатель на DACL
    NULL,            // указатель на SACL не нужен
    &pSecurityDescriptor);   // адрес указателя на SD
  if (dwRetCode != ERROR_SUCCESS)
  {
    printf("Get named security info failed.\n");
    printf("Error code: %u\n", dwRetCode);

    return dwRetCode;
  }

  // сбрасываем флаг автоматического наследования DACL
  if(!SetSecurityDescriptorControl(
    pSecurityDescriptor,
    SE_DACL_PROTECTED,
    0))
  {
    dwRetCode = GetLastError();
    printf("Set security descriptor control failed.");
    printf("Error code: %u\n", dwRetCode);

    return dwRetCode;
  }

  // устанавливаем новые свойства DACL
  dwRetCode = SetSecurityInfo(
    hFile,         // дескриптор файла
    SE_FILE_OBJECT,    // объект файл
    DACL_SECURITY_INFORMATION | 
    PROTECTED_DACL_SECURITY_INFORMATION,   // изменяем информацию о DACL
    NULL,          // владельца не изменяем
    NULL,          // первичную группу не изменяем
    pDacl,         // DACL изменяем
    NULL);         // SACL не изменяем
  if (dwRetCode != ERROR_SUCCESS)
  {
    printf("Set named security info failed.\n");
    printf("Error code: %u\n", dwRetCode);

    return dwRetCode;
  }

  // освобождаем память для дескриптора
  LocalFree(pSecurityDescriptor);

  printf("The flag SE_DACL_PROTECTED is reset.\n");

  // закрываем файл
  CloseHandle(hFile);

  return 0;
}