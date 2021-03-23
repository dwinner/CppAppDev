#ifndef UNICODE
#define UNICODE
#endif

#define _WIN32_WINNT 0x0500

#include <stdio.h>
#include <windows.h> 
#include <lm.h>
#include <aclapi.h>
#include <sddl.h>

int main()
{
  HANDLE hProcess;       // дескриптор процесса
  HANDLE hTokenHandle;   // дескриптор маркера доступа

  TOKEN_PRIVILEGES tp;   // привилегии маркера доступа

  DWORD  dwLengthOfSID = 0;          // длина SID
  DWORD  dwLengthOfDomainName = 0;   // длина имени домена
  DWORD  dwLengthOfUserName = UNLEN; // длина имени учетной записи 
  SID    *lpSid = NULL;              // указатель на SID

  LPTSTR  lpDomainName = NULL;   // указатель на имя домена
  SID_NAME_USE type_of_SID;      // тип учетной записи

  wchar_t wchFileName[248];      // имя каталога
  wchar_t wchUserName[UNLEN];    // имя учетной записи

  TRUSTEE  Trustee;      // информация об учетной записи
  PACL pSacl = NULL;     // указатель на список SACL
  PSECURITY_DESCRIPTOR pSd = NULL;   // указатель на дескриптор безопасности

  ACCESS_MASK amSuccess = 0;     // маска для аудита успешного доступа
  ACCESS_MASK amFailed = 0;      // маска для аудита неудачного доступа

  DWORD dwRetCode;       // код возврата

  // получаем дескриптор процесса
  hProcess = GetCurrentProcess();

  // получаем маркер доступа процесса
  if (!OpenProcessToken(
    hProcess,          // дескриптор процесса
    TOKEN_ALL_ACCESS,  // полный доступ к маркеру доступа
    &hTokenHandle))    // дескриптор маркера
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
    hTokenHandle,  // дескриптор маркера доступа процесса
    FALSE,   // не запрещаем все привилегии
    &tp,     // адрес привилегий
    0,       // длины буфера нет
    NULL,    // предыдущее состояние привилегий не нужно
    NULL))   // длина буфера не нужна
  {
    dwRetCode = GetLastError();
    printf("Lookup privilege value failed.\n");
    printf("Error code: %d\n", dwRetCode);

    return dwRetCode;
  }

  // вводим имя файла или каталога, например: C:\\test.txt
  printf("Input a full path to your file: ");
  _getws(wchFileName);

  // получаем дескриптор безопасности файла
  dwRetCode = GetNamedSecurityInfo(
    wchFileName,     // имя файла
    SE_FILE_OBJECT,  // объект файл
    SACL_SECURITY_INFORMATION,   // получаем сведения об аудите
    NULL,      // SID владельца не нужен
    NULL,      // SID первичной группы не нужен
    NULL,      // DACL не нужен
    &pSacl,    // указатель на SACL
    &pSd);     // адрес указателя на дескриптор безопасности
  if (dwRetCode != ERROR_SUCCESS)
  {
    printf("Get named security info failed.\n");
    printf("Error code: %u\n", dwRetCode);

    return dwRetCode;
  }

  // вводим имя пользователя
  printf("Input user_name: ");
  _getws(wchUserName);       // вводим имя учетной записи

  // получаем SID учетной записи
  // определяем длину SID пользователя
  LookupAccountName(
    NULL,            // ищем имя на локальном компьютере
    wchUserName,     // имя пользователя
    NULL,            // определяем длину SID
    &dwLengthOfSID,  // длина SID
    NULL,            // определяем имя домена
    &dwLengthOfDomainName,   // длина имени домена
    &type_of_SID);   // тип учетной записи

  // проверяем, вернула ли функция длину SID
  if (dwLengthOfSID == 0)
  {
    dwRetCode = GetLastError();

    printf("Lookup account name failed.\n");
    printf("Error code: %d\n", dwRetCode);

    return dwRetCode;
  }

  // распределяем память для SID и имени домена
  lpSid = (SID*) new char[dwLengthOfSID];
  lpDomainName = (LPTSTR) new wchar_t[dwLengthOfDomainName];

  // определяем SID и имя домена пользователя
  if(!LookupAccountName(
    NULL,            // ищем имя на локальном компьютере
    wchUserName,     // имя пользователя
    lpSid,           // указатель на SID
    &dwLengthOfSID,  // длина SID
    lpDomainName,    // указатель на имя домена
    &dwLengthOfDomainName,   // длина имени домена
    &type_of_SID))   // тип учетной записи
  {
    dwRetCode = GetLastError();

    printf("Lookup account name failed.\n");
    printf("Error code: %d\n", dwRetCode);

    return dwRetCode;
  }

  // строим структуру TRUSTEE по идентификатору безопасности
  BuildTrusteeWithSid(&Trustee, lpSid);

  // получаем аудиторские права пользователя
  dwRetCode = GetAuditedPermissionsFromAcl(
    pSacl,       // адрес списка SACL
    &Trustee,    // информация об учетной записи
    &amSuccess,  // адрес маски прав успешного доступа
    &amFailed);  // адрес маски прав неудачного доступа
  if (dwRetCode != ERROR_SUCCESS)
  {
    printf("Get audited permissions from ACL failed.\n");
    printf("Error code: %u\n", dwRetCode);

    return dwRetCode;
  }

  // распечатываем права доступа
  printf("Success audit rights: %x\n", amSuccess);
  printf("Failed audit rights: %x\n", amFailed);
  
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
    dwRetCode = GetLastError();
    printf("Lookup privilege value failed.\n");
    printf("Error code: %d\n", dwRetCode);

    return dwRetCode;
  }

  // освобождаем память для дескриптора
  LocalFree(pSd);
  delete[] lpDomainName;
  delete[] lpSid;

  return 0;
}