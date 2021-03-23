#define _WIN32_WINNT 0x0500

#include <stdio.h>
#include <windows.h> 
#include <aclapi.h>

int main()
{
  char chFileName[256];    // им€ файла
  HANDLE hFile;            // дескриптор файла

  PSECURITY_DESCRIPTOR pSecurityDescriptor;  // указатель на SD

  SECURITY_DESCRIPTOR_CONTROL wControl;  // управл€ющие флаги из SD
  DWORD dwRevision;      // верси€ дескриптора безопасности

  DWORD dwRetCode;       // код возврата

  // вводим полное им€ файла, например: C:\\test.txt
  printf("Input a full path to your file: ");
  gets(chFileName);

  // открываем файл
  hFile = CreateFile(
    chFileName,        // им€ файла
    READ_CONTROL,      // разрешаем доступ к дескриптору безопасности
    0,                 // не раздел€ем доступ
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
    hFile,         // дескриптор файла
    SE_FILE_OBJECT,    // объект файл
    DACL_SECURITY_INFORMATION,   // тип информации
    NULL,          // указатель на SID владельца не нужен
    NULL,          // указатель на первичную группу не нужен
    NULL,          // указатель на DACL не нужен
    NULL,          // указатель на SACL не нужен
    &pSecurityDescriptor);       // адрес указател€ на SD
  if (dwRetCode != ERROR_SUCCESS)
  {
    printf("Get named security info failed.\n");
    printf("Error code: %u\n", dwRetCode);

    return dwRetCode;
  }

  // получаем управл€ющую информацию из дескриптора безопасности
  if(!GetSecurityDescriptorControl(
    pSecurityDescriptor,
    &wControl,
    &dwRevision))
  {
    dwRetCode = GetLastError();
    printf("Get security descriptor control failed.\n");
    printf("Error code: %u\n", dwRetCode);

    return dwRetCode;
  }

  printf("The following flags are set: \n");

  // определ€ем информацию из управл€ющего слова
  if(wControl & SE_DACL_AUTO_INHERITED)
    printf("SE_DACL_AUTO_INHERITED\n");
  if(wControl & SE_DACL_DEFAULTED)
    printf("SE_DACL_DEFAULTED\n");
  if(wControl & SE_DACL_PRESENT)
    printf("SE_DACL_PRESENT\n");
  if(wControl & SE_DACL_PROTECTED)
    printf("SE_DACL_PROTECTED\n");

  // выводим на печать версию дескриптора безопасности
  printf("Descriptor revision: %u\n", dwRevision);

  // освобождаем пам€ть дл€ дескриптора
  LocalFree(pSecurityDescriptor);

  // закрываем файл
  CloseHandle(hFile);

  return 0;
}