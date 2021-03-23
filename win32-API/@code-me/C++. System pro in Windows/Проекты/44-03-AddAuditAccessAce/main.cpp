#ifndef UNICODE
#define UNICODE
#endif

#include <windows.h>
#include <stdio.h>
#include <lm.h>

int main()
{
  HANDLE hProcess;       // дескриптор процесса
  HANDLE hTokenHandle;   // дескриптор маркера доступа

  TOKEN_PRIVILEGES tp;   // привилегии маркера доступа

  ACL *lpDacl;           // указатель на список доступа DACL
  DWORD dwDaclLength;    // длина списка доступа DACL

  ACL *lpSacl;           // указатель на список доступа SACL
  DWORD dwSaclLength;    // длина списка доступа SACL

  wchar_t wchUserName[UNLEN];    // имя пользователя
  wchar_t wchDirName[248];       // имя каталога

  DWORD dwLengthOfDomainName = 0;  // длина имени домена

  DWORD dwLengthOfSid = 0;   // длина SID
  SID *lpSid = NULL;         // указатель на SID
  LPTSTR lpDomainName = NULL;    // указатель на имя домена

  SID_NAME_USE typeOfSid;    // тип учетной записи

  SECURITY_DESCRIPTOR sd;    // дескриптор безопасности каталога
  SECURITY_ATTRIBUTES sa;    // атрибуты защиты каталога

  DWORD dwRetCode;           // код возврата

  // получаем дескриптор процесса
  hProcess = GetCurrentProcess();

  // получаем маркер доступа процесса
  if (!OpenProcessToken(
    hProcess,            // дескриптор процесса
    TOKEN_ALL_ACCESS,    // полный доступ к маркеру доступа
    &hTokenHandle))      // дескриптор маркера доступа
  {
    dwRetCode = GetLastError();
    printf( "Open process token failed: %u\n", dwRetCode);

    return dwRetCode;
  }

  // устанавливаем общее количество привилегий
  tp.PrivilegeCount = 1;

  // определяем идентификатор привилегии для установки аудита
  if (!LookupPrivilegeValue(
    NULL,      // ищем идентификатор привилегии на локальном компьютере
    SE_SECURITY_NAME,  // привилегия для аудита
    &(tp.Privileges[0].Luid)))
  {
    dwRetCode = GetLastError();
    printf("Lookup privilege value failed.\n");
    printf("Error code: %d\n", dwRetCode);

    return dwRetCode;
  }

  // разрешаем привилегию аудита
  tp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;

  // разрешаем привилегию для установки аудита
  if (!AdjustTokenPrivileges(
    hTokenHandle,    // дескриптор маркера доступа процесса
    FALSE,     // не запрещаем все привилегии
    &tp,       // адрес привилегий
    0,         // длины буфера нет
    NULL,      // предыдущее состояние привилегий не нужно
    NULL))     // длина буфера не нужна
  {
    dwRetCode = GetLastError();
    printf("Lookup privilege value failed.\n");
    printf("Error code: %d\n", dwRetCode);

    return dwRetCode;
  }

  // вводим имя пользователя, которому разрешим доступ к каталогу
  printf("Input a user name: ");
  _getws(wchUserName);

  // определяем длину SID пользователя
  if (!LookupAccountName(
    NULL,            // ищем имя на локальном компьютере
    wchUserName,     // имя пользователя
    NULL,            // определяем длину SID
    &dwLengthOfSid,  // длина SID
    NULL,            // определяем имя домена
    &dwLengthOfDomainName,   // длина имени домена
    &typeOfSid))     // тип учетной записи
  {
    dwRetCode = GetLastError();

    if (dwRetCode == ERROR_INSUFFICIENT_BUFFER)
    {
      // распределяем память для SID и имени домена
      lpSid = (SID*) new char[dwLengthOfSid];
      lpDomainName = (LPTSTR) new wchar_t[dwLengthOfDomainName];
    }
    else
    {
      // выходим из программы
      printf("Lookup account name failed.\n");
      printf("Error code: %d\n", dwRetCode);

      return dwRetCode;
    }
  }

  // определяем SID и имя домена пользователя
  if(!LookupAccountName(
    NULL,              // ищем имя на локальном компьютере
    wchUserName,       // имя пользователя
    lpSid,             // указатель на SID
    &dwLengthOfSid,    // длина SID
    lpDomainName,      // указатель на имя домена
    &dwLengthOfDomainName,   // длина имени домена
    &typeOfSid))       // тип учетной записи
  {
    dwRetCode = GetLastError();

    printf("Lookup account name failed.\n");
    printf("Error code: %d\n", dwRetCode);

    return dwRetCode;
  }

  // определем длину списка DACL
  dwDaclLength = sizeof(ACL)
    + sizeof(ACCESS_ALLOWED_ACE) - sizeof(DWORD) + dwLengthOfSid
    + sizeof(ACCESS_DENIED_ACE) - sizeof(DWORD) + dwLengthOfSid;

  // распределяем память под DACL
  lpDacl = (ACL*)new char[dwDaclLength];

  // инициализируем список DACL
  if (!InitializeAcl(
    lpDacl,          // адрес DACL
    dwDaclLength,    // длина DACL
    ACL_REVISION))   // версия DACL
  {
    dwRetCode = GetLastError();

    printf("Lookup account name failed.\n");
    printf("Error code: %d\n", dwRetCode);

    return dwRetCode;
  }

  // добавляем запрещающий элемент в список DACL
  if (!AddAccessDeniedAce(
    lpDacl,        // адрес DACL
    ACL_REVISION,  // версия DACL
    WRITE_OWNER,   // запрещаем изменять владельца объекта
    lpSid))        // адрес SID
  {
    dwRetCode = GetLastError();
    perror("Add access denied ace failed.\n");
    printf("The last error code: %u\n", dwRetCode);

    return dwRetCode;
  }

  // добавляем разрешающий элемент в список DACL
  if (!AddAccessAllowedAce(
    lpDacl,        // адрес DACL
    ACL_REVISION,  // версия DACL
    GENERIC_ALL,   // разрешаем все родовые права доступа
    lpSid))        // адрес SID
  {
    dwRetCode = GetLastError();
    perror("Add access allowed ace failed.\n");
    printf("The last error code: %u\n", dwRetCode);

    return dwRetCode;
  }

  // определем длину списка SACL
  dwSaclLength = sizeof(ACL)
    + sizeof(SYSTEM_AUDIT_ACE ) - sizeof(DWORD) + dwLengthOfSid;

  // распределяем память под SACL
  lpSacl = (ACL*)new char[dwSaclLength];

  // инициализируем список SACL
  if (!InitializeAcl(
    lpSacl,          // адрес SACL
    dwSaclLength,    // длина SACL
    ACL_REVISION))   // версия SACL
  {
    dwRetCode = GetLastError();

    printf("Lookup account name failed.\n");
    printf("Error code: %d\n", dwRetCode);

    return dwRetCode;
  }

  // добавляем элемент в список SACL
  if (!AddAuditAccessAce(
    lpSacl,        // адрес DACL
    ACL_REVISION,  // версия DACL
    WRITE_OWNER,   // запрещаем изменять владельца объекта
    lpSid,         // адрес SID
    FALSE,         // не нужен аудит удачного доступа
    TRUE))         // нужен аудит неудачного доступа
  {
    dwRetCode = GetLastError();
    perror("Add audit access ace failed.\n");
    printf("The last error code: %u\n", dwRetCode);

    return dwRetCode;
  }

  // инициализируем версию дескриптора безопасности
  if (!InitializeSecurityDescriptor(
    &sd,
    SECURITY_DESCRIPTOR_REVISION))
  {
    dwRetCode = GetLastError();
    printf("Initialize security descroptor failed.\n");
    printf("Error code: %d\n", dwRetCode);

    return dwRetCode;
  }

  // устанавливаем SID владельца объекта
  if (!SetSecurityDescriptorOwner(
    &sd,         // адрес дескриптора безопасности
    NULL,        // не задаем владельца
    SE_OWNER_DEFAULTED))   // определить владельца по умолчанию
  {
    dwRetCode = GetLastError();
    perror("Set security descriptor owner failed.\n");
    printf("The last error code: %u\n", dwRetCode);

    return dwRetCode;
  }

  // устанавливаем SID первичной группы владельца
  if (!SetSecurityDescriptorGroup(
    &sd,         // адрес дескриптора безопасности
    NULL,        // не задаем первичную группу
    SE_GROUP_DEFAULTED))   // определить первичную группу по умолчанию
  {
    dwRetCode = GetLastError();
    perror("Set security descriptor group failed.\n");
    printf("The last error code: %u\n", dwRetCode);

    return dwRetCode;
  }
  // устанавливаем DACL  в дескриптор безопасности
  if (!SetSecurityDescriptorDacl(
    &sd,       // адрес дескриптора безопасности
    TRUE,      // DACL присутствует
    lpDacl,    // указатель на DACL
    FALSE))    // DACL не задан по умолчанию
  {
    dwRetCode = GetLastError();
    perror("Set security descriptor group failed.\n");
    printf("The last error code: %u\n", dwRetCode);

    return dwRetCode;
  }
  // устанавливаем SACL  в дескриптор безопасности
  if (!SetSecurityDescriptorSacl(
    &sd,       // адрес дескриптора безопасности
    TRUE,      // SACL присутствует
    lpSacl,    // указатель на SACL
    FALSE))    // SACL не задан по умолчанию
  {
    dwRetCode = GetLastError();
    perror("Set security descriptor group failed.\n");
    printf("The last error code: %u\n", dwRetCode);

    return dwRetCode;
  }

  // проверяем структуру дескриптора безопасности
  if (!IsValidSecurityDescriptor(&sd))
  {
    dwRetCode = GetLastError();
    perror("Security descriptor is invalid.\n");
    printf("The last error code: %u\n", dwRetCode);

    return dwRetCode;
  }

  // инициализируем атрибуты безопасности
  sa.nLength = sizeof(sa);     // устанавливаем длину атрибутов защиты
  sa.lpSecurityDescriptor = &sd;     // устанавливаем адрес дескриптора безопасности
  sa.bInheritHandle = FALSE;   // дескриптор каталога не наследуемый
  
  // читаем имя создаваемого каталога
  printf("Input a new directory name: ");
  _getws(wchDirName);          // вводим имя каталога

  // создаем каталог
  if (!CreateDirectory(wchDirName, &sa))
  {
    dwRetCode = GetLastError();
    perror("Security descriptor is invalid.\n");
    printf("The last error code: %u\n", dwRetCode);

    return dwRetCode;
  }

  printf("The directory is created.\n");

  // запрещаем привилегию аудита
  tp.Privileges[0].Attributes = 0;

  // разрешаем привилегию для установки аудита
  if (!AdjustTokenPrivileges(
    hTokenHandle,    // дескриптор маркера доступа процесса
    FALSE,           // не запрещаем все привилегии
    &tp,             // адрес привилегий
    0,               // длины буфера нет
    NULL,            // предыдущее состояние привилегий не нужно
    NULL))           // длина буфера не нужна
  {
    dwRetCode = GetLastError();
    printf("Lookup privilege value failed.\n");
    printf("Error code: %d\n", dwRetCode);

    return dwRetCode;
  }

  // освобождаем память
  delete[] lpSid;
  delete[] lpDomainName;
  delete[] lpDacl;

  return 0;
}