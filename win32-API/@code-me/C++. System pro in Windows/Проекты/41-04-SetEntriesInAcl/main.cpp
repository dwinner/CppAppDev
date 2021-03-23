#ifndef UNICODE
#define UNICODE
#endif

#include <windows.h>
#include <stdio.h>
#include <lm.h>
#include <aclapi.h>

int main()
{
  HANDLE hProcess;       // дескриптор процесса
  HANDLE hTokenHandle;   // дескриптор маркера доступа

  TOKEN_PRIVILEGES tp;   // привилегии маркера доступа
  
  wchar_t wchDirName[248];   // имя каталога
  wchar_t wchAccountName[UNLEN + 255];   // имя учетной записи

  SECURITY_DESCRIPTOR sd;    // дескриптор безопасности каталога
  SECURITY_ATTRIBUTES sa;    // атрибуты защиты каталога

  EXPLICIT_ACCESS  eaDacl;   // информация для элемента списка DACL
  PACL lpNewDacl;            // указатель на список DACL

  EXPLICIT_ACCESS  eaSacl;   // информация для элемента списка SACL
  PACL lpNewSacl;            // указатель на список DACL

  DWORD dwErrCode;     // код возврата

  // получаем дескриптор процесса
  hProcess = GetCurrentProcess();

  // получаем маркер доступа процесса
  if (!OpenProcessToken(
    hProcess,          // дескриптор процесса
    TOKEN_ALL_ACCESS,  // полный доступ к маркеру доступа
    &hTokenHandle))    // дескриптор маркера
  {
    dwErrCode = GetLastError();
    printf( "Open process token failed: %u\n", dwErrCode);

    return dwErrCode;
  }

  // устанавливаем общее количество привилегий
  tp.PrivilegeCount = 1;

  // определяем идентификатор привилегии для установки аудита
  if (!LookupPrivilegeValue(
    NULL,      // ищем идентификатор привилегии на локальном компьютере
    SE_SECURITY_NAME,  // привилегия для аудита
    &(tp.Privileges[0].Luid)))
  {
    dwErrCode = GetLastError();
    printf("Lookup privilege value failed.\n");
    printf("Error code: %d\n", dwErrCode);

    return dwErrCode;
  }

  // разрешаем привилегию аудита
  tp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;

  // разрешаем привилегию для установки аудита
  if (!AdjustTokenPrivileges(
    hTokenHandle,  // дескриптор маркера доступа процесса
    FALSE,   // не запрещаем все привилегии
    &tp,     // адрес привилегий
    0,       // длины буфера нет
    NULL,    // предыдущее состояние привилегий не нужно
    NULL))   // длина буфера не нужна
  {
    dwErrCode = GetLastError();
    printf("Lookup privilege value failed.\n");
    printf("Error code: %d\n", dwErrCode);

    return dwErrCode;
  }

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
    SE_GROUP_DEFAULTED))   // определить первичную группу по умолчанию
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
  
  // строим структуру EXPLICIT_ACCESS по имени для списка DACL
  BuildExplicitAccessWithName(
    &eaDacl,         // адрес структуры ExplicitAccess
    wchAccountName,  // имя учетной записи
    GENERIC_ALL,     // полный доступ к объекту
    SET_ACCESS,      // установить доступ
    NO_INHERITANCE   // нет наследования
    );

  // создаем список DACL
  dwErrCode = SetEntriesInAcl(
    1,         // один элемент
    &eaDacl,   // адрес структуры ExplicitAccess
    NULL,      // старого DACL нет
    &lpNewDacl);   // адрес нового DACL
  if (dwErrCode != ERROR_SUCCESS)
  {
    perror("Set entries in DACL failed.\n");
    printf("The last error code: %u\n", dwErrCode);

    return dwErrCode;
  }

  // устанавливаем DACL в дескриптор безопасности
  if (!SetSecurityDescriptorDacl(
    &sd,       // адрес дескриптора безопасности
    TRUE,      // DACL присутствует
    lpNewDacl, // указатель на DACL
    FALSE))    // DACL не задан по умолчанию
  {
    dwErrCode = GetLastError();
    perror("Set security descriptor group failed.\n");
    printf("The last error code: %u\n", dwErrCode);

    return dwErrCode;
  }

  // строим структуру EXPLICIT_ACCESS по имени для списка SACL
  BuildExplicitAccessWithName(
    &eaSacl,           // адрес структуры ExplicitAccess
    wchAccountName,    // имя учетной записи
    GENERIC_ALL,       // полный доступ к объекту
    SET_AUDIT_SUCCESS, // установить доступ
    NO_INHERITANCE     // нет наследования
    );

  // создаем список SACL
  dwErrCode = SetEntriesInAcl(
    1,         // один элемент
    &eaSacl,   // адрес структуры ExplicitAccess
    NULL,      // старого SACL нет
    &lpNewSacl);   // адрес нового SACL
  if (dwErrCode != ERROR_SUCCESS)
  {
    perror("Set entries in DACL failed.\n");
    printf("The last error code: %u\n", dwErrCode);

    return dwErrCode;
  }

  // устанавливаем SACL  в дескриптор безопасности
  if (!SetSecurityDescriptorSacl(
    &sd,         // адрес дескриптора безопасности
    TRUE,        // SACL присутствует
    lpNewSacl,   // указатель на SACL
    FALSE))      // SACL не задан по умолчанию
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
  // устанавливаем адрес дескриптора безопасности
  sa.lpSecurityDescriptor = &sd; 
  // дескриптор каталога не наследуемый
  sa.bInheritHandle = FALSE; 

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

  // запрещаем привилегию аудита
  tp.Privileges[0].Attributes = 0;

  // запрещаем привилегию для установки аудита
  if (!AdjustTokenPrivileges(
    hTokenHandle,  // дескриптор маркера доступа процесса
    FALSE,     // не запрещаем все привилегии
    &tp,       // адрес привилегий
    0,         // длины буфера нет
    NULL,      // предыдущее состояние привилегий не нужно
    NULL))     // длина буфера не нужна
  {
    dwErrCode = GetLastError();
    printf("Lookup privilege value failed.\n");
    printf("Error code: %d\n", dwErrCode);

    return dwErrCode;
  }

  // освобождаем память, захваченную под списки DACL и SACL
  LocalFree(lpNewDacl);
  LocalFree(lpNewSacl);

  printf("The directory is created.\n");

  return 0;
}