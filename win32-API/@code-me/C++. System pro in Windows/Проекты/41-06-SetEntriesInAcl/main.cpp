#ifndef UNICODE
#define UNICODE
#endif

#include <windows.h>
#include <stdio.h>
#include <lm.h>
#include <aclapi.h>

int main()
{
  HANDLE hProcess;         // дескриптор процесса
  HANDLE hTokenHandle;     // дескриптор маркера доступа

  TOKEN_PRIVILEGES tp;     // привилегии маркера доступа

  wchar_t wchDirName[248];   // имя каталога
  wchar_t wchAccountName[UNLEN + 255];   // имя учетной записи

  EXPLICIT_ACCESS  eaSacl;   // информация для элемента списка DACL
  EXPLICIT_ACCESS  eaDacl;   // информация для элемента списка DACL

  PACL lpOldDacl;      // указатель на старый список DACL
  PACL lpNewDacl;      // указатель на новый список DACL
  PACL lpOldSacl;      // указатель на старый список SACL
  PACL lpNewSacl;      // указатель на новый список SACL

  PSECURITY_DESCRIPTOR lpSD;   // указатель на дескриптор безопасности

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

  // читаем имя созданного каталога
  printf("Input a directory name: ");
  wscanf(L"%s", wchDirName);     // вводим имя каталога

  // получаем SD этого каталога
  dwErrCode = GetNamedSecurityInfo(
    wchDirName,      // имя каталога
    SE_FILE_OBJECT,  // объект файл
    DACL_SECURITY_INFORMATION |    // получаем DACL и SACL
    SACL_SECURITY_INFORMATION,
    NULL,            // адрес указателя на SID владельца
    NULL,            // адрес указателя на первичную группу
    &lpOldDacl,      // указатель на DACL
    &lpOldSacl,      // указатель на SACL
    &lpSD);          // адрес указателя на дескриптор безопасности
  if (dwErrCode != ERROR_SUCCESS)
  {
    printf("Get named security info failed.\n");
    printf("Error code: %u\n", dwErrCode);

    return dwErrCode;
  }

  // вводим имя домена и пользователя, для нового элемента списка DACL
  printf("The following user will be added in DACL and SACL.\n");
  printf("Input domain account (domain_name\\user_name): ");
  wscanf(L"%s", wchAccountName);     // вводим имя учетной записи
  
  // строим структуру EXPLICIT_ACCESS для DACL по имени
  BuildExplicitAccessWithName(
    &eaDacl,         // адрес структуры ExplicitAccess
    wchAccountName,  // имя учетной записи
    GENERIC_READ,    // только чтение
    SET_ACCESS,      // установить доступ
    NO_INHERITANCE   // нет наследования
    );

  // создаем список DACL
  dwErrCode = SetEntriesInAcl(
    1,             // добавляем один элемент в список DACL
    &eaDacl,       // адрес структуры ExplicitAccess
    lpOldDacl,     // адрес старого списка DACL
    &lpNewDacl);   // адрес указателя на новый список DACL
  if (dwErrCode != ERROR_SUCCESS)
  {
    perror("Set entries in DACL failed.\n");
    printf("The last error code: %u\n", dwErrCode);

    return dwErrCode;
  }

  // строим структуру EXPLICIT_ACCESS для SACL по имени
  BuildExplicitAccessWithName(
    &eaSacl,         // адрес структуры ExplicitAccess
    wchAccountName,  // имя учетной записи
    GENERIC_READ,    // только чтение
    SET_AUDIT_SUCCESS,   // аудиторское сообщение при успешном доступе
    NO_INHERITANCE   // нет наследования
    );

  // создаем список SACL
  dwErrCode = SetEntriesInAcl(
    1,             // добавляем один элемент в список DACL
    &eaSacl,       // адрес структуры ExplicitAccess
    lpOldSacl,     // адрес старого списка DACL
    &lpNewSacl);   // адрес указателя на новый список DACL
  if (dwErrCode != ERROR_SUCCESS)
  {
    perror("Set entries in SACL failed.\n");
    printf("The last error code: %u\n", dwErrCode);

    return dwErrCode;
  }

  // устанавливаем новый списки DACL и SACL
  dwErrCode = SetNamedSecurityInfo(
    wchDirName,      // имя файла
    SE_FILE_OBJECT,  // объект файл
    DACL_SECURITY_INFORMATION |  // изменяем списки DACL
    SACL_SECURITY_INFORMATION,   // и SACL
    NULL,            // владельца не изменяем
    NULL,            // первичную группу не изменяем
    lpNewDacl,       // новый DACL
    lpNewSacl);      // новый SACL
  if (dwErrCode != ERROR_SUCCESS)
  {
    printf("Set named security info failed.\n");
    printf("Error code: %u\n", dwErrCode);

    return dwErrCode;
  }

  // запрещаем привилегию аудита
  tp.Privileges[0].Attributes = 0;

  // разрешаем привилегию для установки аудита
  if (!AdjustTokenPrivileges(
    hTokenHandle,    // дескриптор маркера доступа процесса
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

  // освобождаем память
  LocalFree(lpSD);
  LocalFree(lpNewDacl);
  LocalFree(lpNewSacl);

  printf("The DACL and SACL of the directory are modified.\n");

  return 0;
}