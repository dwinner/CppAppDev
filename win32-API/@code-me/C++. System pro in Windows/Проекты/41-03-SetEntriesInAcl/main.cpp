#ifndef UNICODE
#define UNICODE
#endif

#include <windows.h>
#include <stdio.h>
#include <lm.h>
#include <aclapi.h>
#include <accctrl.h>

int main()
{
  wchar_t wchDirName[248];   // имя каталога
  wchar_t wchAccountName[UNLEN + 255];   // имя учетной записи

  SECURITY_DESCRIPTOR sd;    // дескриптор безопасности каталога
  SECURITY_ATTRIBUTES sa;    // атрибуты защиты каталога

  EXPLICIT_ACCESS  ea;       // информация для элемента списка DACL
  PACL lpNewDacl;            // указатель на список DACL

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
    &sd,       // адрес дескриптора безопасности
    NULL,      // не задаем владельца
    SE_OWNER_DEFAULTED))   // определить владельца по умолчанию
  {
    dwErrCode = GetLastError();
    perror("Set security descriptor owner failed.\n");
    printf("The last error code: %u\n", dwErrCode);

    return dwErrCode;
  }

  // устанавливаем SID первичной группы владельца
  if (!SetSecurityDescriptorGroup(
    &sd,       // адрес дескриптора безопасности
    NULL,      // не задаем первичную группу
    SE_GROUP_DEFAULTED))  // определить первичную группу по умолчанию
  {
    dwErrCode = GetLastError();
    perror("Set security descriptor group failed.\n");
    printf("The last error code: %u\n", dwErrCode);

    return dwErrCode;
  }

  // вводим имя домена и пользователя
  printf("The following user will have full access to directory.\n");
  printf("Input domain account (domain_name\\user_name): ");
  wscanf(L"%s", wchAccountName);       // вводим имя учетной записи
  
  // строим структуру EXPLICIT_ACCESS по имени
  BuildExplicitAccessWithName(
    &ea,             // адрес структуры ExplicitAccess
    wchAccountName,  // имя учетной записи
    GENERIC_ALL,     // полный доступ к объекту
    SET_ACCESS,      // установить доступ
    NO_INHERITANCE   // нет наследования
    );

  // создаем список DACL
  dwErrCode = SetEntriesInAcl(
    1,           // один элемент
    &ea,         // адрес структуры ExplicitAccess
    NULL,        // старого DACL нет
    &lpNewDacl); // адрес нового DACL
  if (dwErrCode != ERROR_SUCCESS)
  {
    perror("Set entries in DACL failed.\n");
    printf("The last error code: %u\n", dwErrCode);

    return dwErrCode;
  }

  // устанавливаем DACL в дескриптор безопасности
  if (!SetSecurityDescriptorDacl(
    &sd,         // адрес дескриптора безопасности
    TRUE,        // DACL присутствует
    lpNewDacl,   // указатель на DACL
    FALSE))      // DACL не задан по умолчанию
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
  sa.nLength = sizeof(sa);     // устанавливаем длину атрибутов защиты
  sa.lpSecurityDescriptor = &sd;   // устанавливаем адрес дескриптора 
                                   // безопасности
  sa.bInheritHandle = FALSE;   // дескриптор каталога не наследуемый
  
  // читаем имя создаваемого каталога
  printf("Input a directory name: ");
  wscanf(L"%s", wchDirName);     // вводим имя каталога

  // создаем каталог
  if (!CreateDirectory(wchDirName, &sa))
  {
    dwErrCode = GetLastError();
    perror("Security descriptor is invalid.\n");
    printf("The last error code: %u\n", dwErrCode);

    return dwErrCode;
  }

  // освобождаем память, захваченную под DACL
  LocalFree(lpNewDacl);

  printf("The directory is created.\n");

  return 0;
}