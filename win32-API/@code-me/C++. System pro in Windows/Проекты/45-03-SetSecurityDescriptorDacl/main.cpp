#ifndef UNICODE
#define UNICODE
#endif

#include <windows.h>
#include <stdio.h>
#include <lm.h>

int main()
{
  HANDLE hMutex;         // дескриптор мьютекса

  ACL *lpDacl;           // указатель на список доступа
  DWORD dwDaclLength;    // длина списка доступа

  wchar_t wchUserName[UNLEN];      // имя пользователя

  DWORD dwLengthOfDomainName = 0;  // длина имени домена

  DWORD dwLengthOfSid = 0;         // длина SID
  SID *lpSid = NULL;               // указатель на SID
  LPTSTR lpDomainName = NULL;      // указатель на имя домена

  SID_NAME_USE typeOfSid;    // тип учетной записи

  SECURITY_DESCRIPTOR sd;    // дескриптор безопасности мьютекса
  SECURITY_ATTRIBUTES sa;    // атрибуты защиты мьютекса

  DWORD dwRetCode;   // код возврата

  // вводим имя пользователя, которому разрешим доступ к мьютексу
  printf("Input a user name: ");
  _getws(wchUserName);

  // определяем длину SID пользователя
  if (!LookupAccountName(
    NULL,              // ищем имя на локальном компьютере
    wchUserName,       // имя пользователя
    NULL,              // определяем длину SID
    &dwLengthOfSid,    // длина SID
    NULL,              // определяем имя домена
    &dwLengthOfDomainName,  // длина имени домена
    &typeOfSid))       // тип учетной записи
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
    &dwLengthOfDomainName,  // длина имени домена
    &typeOfSid))       // тип учетной записи
  {
    dwRetCode = GetLastError();

    printf("Lookup account name failed.\n");
    printf("Error code: %d\n", dwRetCode);

    return dwRetCode;
  }

  // проверяем тип SID
  if (typeOfSid != SidTypeUser)
  {
    printf("This is not a user name.\n");
    return 1;
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
    lpDacl,          // адрес DACL
    ACL_REVISION,    // версия DACL
    WRITE_OWNER,     // запрещаем изменять владельца объекта
    lpSid))          // адрес SID
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
    SE_OWNER_DEFAULTED))    // определить владельца по умолчанию
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
    SE_GROUP_DEFAULTED))    // определить первичную группу по умолчанию
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

  // проверяем структуру дескриптора безопасности
  if (!IsValidSecurityDescriptor(&sd))
  {
    dwRetCode = GetLastError();
    perror("Security descriptor is invalid.\n");
    printf("The last error code: %u\n", dwRetCode);

    return dwRetCode;
  }

  // инициализируем атрибуты безопасности
  sa.nLength = sizeof(sa);       // устанавливаем длину атрибутов защиты
  sa.lpSecurityDescriptor = &sd;   // устанавливаем адрес SD
  sa.bInheritHandle = FALSE;     // дескриптор мьютекса не наследуемый
  

  // создаем мьютекс
  hMutex = CreateMutex(&sa, FALSE, L"DemoMutex");
  if (hMutex == NULL)
  {
    dwRetCode = GetLastError();
    perror("Create mutex failed.\n");
    printf("The last error code: %u\n", dwRetCode);

    return dwRetCode;
  }

  printf("The mutex is created.\n");

  // освобождаем память
  delete[] lpSid;
  delete[] lpDomainName;
  delete[] lpDacl;

  CloseHandle(hMutex);

  return 0;
}