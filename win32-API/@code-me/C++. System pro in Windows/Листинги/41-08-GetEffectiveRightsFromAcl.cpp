#define _WIN32_WINNT 0x0500

#ifndef UNICODE
#define UNICODE
#endif

#include <windows.h>
#include <stdio.h>
#include <lm.h>
#include <aclapi.h>

int main()
{
  TRUSTEE  Trustee;            // информация об учетной записи
  wchar_t wchFileName[248];    // имя файла или каталога
  wchar_t wchAccountName[UNLEN + 255];   // имя учетной записи

  PSECURITY_DESCRIPTOR lpSd;   // указатель на дескриптор безопасности
  PACL lpDacl;                 // указатель на список DACL

  ACCESS_MASK dwAccessRights = 0;  // права доступа
  DWORD dwErrCode;      // код возврата

  // читаем имя файла
  printf("Input a file name: ");
  wscanf(L"%s", wchFileName);      // вводим имя файла или каталога

  // получаем SD этого файла
  dwErrCode = GetNamedSecurityInfo(
    wchFileName,     // имя файла
    SE_FILE_OBJECT,  // объект файл
    DACL_SECURITY_INFORMATION,   // получаем DACL
    NULL,        // адрес указателя на SID владельца
    NULL,        // адрес указателя на первичную группу
    &lpDacl,     // указатель на DACL
    NULL,        // указатель на SACL не нужен
    &lpSd);      // адрес указателя на дескриптор безопасности
  if (dwErrCode != ERROR_SUCCESS)
  {
    printf("Get named security info failed.\n");
    printf("Error code: %u\n", dwErrCode);

    return dwErrCode;
  }

  // вводим имя домена и пользователя
  printf("Input domain account (domain_name\\user_name): ");
  wscanf(L"%s", wchAccountName);       // вводим имя учетной записи

  // строим структуру TRUSTEE по имени
  BuildTrusteeWithName(&Trustee, wchAccountName);

  // получаем права доступа для заданного имени
  dwErrCode = GetEffectiveRightsFromAcl(
    lpDacl,      // указатель на список DACL
    &Trustee,    // адрес структуры TRUSTEE
    &dwAccessRights);  // адрес маски с флагами
  if (dwErrCode != ERROR_SUCCESS)
  {
    printf("Get effective rights from ACL failed.\n");
    printf("Error code: %u\n", dwErrCode);

    return dwErrCode;
  }

  // выводим на консоль права доступа
  printf("ACCESS_MASK: %x\n", dwAccessRights);

  // отображаем права доступа
  if ((dwAccessRights & SPECIFIC_RIGHTS_ALL) == SPECIFIC_RIGHTS_ALL)
    printf("SPECIFIC_RIGHTS_ALL is set.\n");
  else
    printf("SPECIFIC_RIGHTS_ALL is not set.\n");

  if ((dwAccessRights & STANDARD_RIGHTS_ALL) == STANDARD_RIGHTS_ALL)
    printf("STANDARD_RIGHTS_ALL is set.\n");
  else
    printf("STANDARD_RIGHTS_ALL is not set.\n");

  if ((dwAccessRights & GENERIC_ALL) == GENERIC_ALL)
    printf("GENERIC_ALL is set.\n");
  else
    printf("GENERIC_ALL is not set.\n");

  // освобождаем память
  LocalFree(lpSd);

  return 0;
}