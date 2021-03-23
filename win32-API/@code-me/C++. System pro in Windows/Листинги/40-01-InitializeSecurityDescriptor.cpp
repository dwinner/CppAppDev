#include <windows.h>
#include <stdio.h>
#include <lm.h>

int main()
{

  char chDirName[248];       // имя каталога
  SECURITY_DESCRIPTOR sd;    // дескриптор безопасности каталога
  SECURITY_ATTRIBUTES sa;    // атрибуты защиты каталога
  DWORD dwErrCode;           // код возврата

  // инициализируем версию дескриптора безопасности
  if (!InitializeSecurityDescriptor(
    &sd,
    SECURITY_DESCRIPTOR_REVISION))
  {
    dwErrCode = GetLastError();
    printf("Initialize security descroptor failed.\n");
    printf("Error code: %d\n", dwErrCode);

    return dwErrCode;
  }

  // устанавливаем SID владельца объекта
  if (!SetSecurityDescriptorOwner(
    &sd,         // адрес дескриптора безопасности
    NULL,        // не задаем владельца
    SE_OWNER_DEFAULTED))  // определить владельца по умолчанию
  {
    dwErrCode = GetLastError();
    perror("Set security descriptor owner failed.\n");
    printf("The last error code: %u\n", dwErrCode);

    return dwErrCode;
  }

  // устанавливаем SID первичной группы владельца
  if (!SetSecurityDescriptorGroup(
    &sd,         // адрес дескриптора безопасности
    NULL,        // не задаем первичную группу
    SE_GROUP_DEFAULTED))  // определить первичную группу по умолчанию
  {
    dwErrCode = GetLastError();
    perror("Set security descriptor group failed.\n");
    printf("The last error code: %u\n", dwErrCode);

    return dwErrCode;
  }

  // проверяем структуру дескриптора безопасности
  if (!IsValidSecurityDescriptor(&sd))
  {
    dwErrCode = GetLastError();
    perror("Security descriptor is invalid.\n");
    printf("The last error code: %u\n", dwErrCode);

    return dwErrCode;
  }

  // инициализируем атрибуты безопасности
  sa.nLength = sizeof(sa);   // устанавливаем длину атрибутов защиты
  sa.lpSecurityDescriptor = &sd;   // устанавливаем адрес SD
  sa.bInheritHandle = FALSE;       // дескриптор каталога не наследуемый
  
  printf("Input a directory name: ");
  scanf("%s", chDirName);          // вводим имя каталога

  // создаем каталог
  if (!CreateDirectory(chDirName, &sa))
  {
    dwErrCode = GetLastError();
    perror("Security descriptor is invalid.\n");
    printf("The last error code: %u\n", dwErrCode);

    return dwErrCode;
  }

  printf("The directory is created.\n");

  return 0;
}