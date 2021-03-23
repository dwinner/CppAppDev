#ifndef UNICODE
#define UNICODE
#endif

#include <windows.h>
#include <stdio.h>
#include <lm.h>
#include <aclapi.h>

int main()
{
  wchar_t wchDirName[248];     // имя каталога
  wchar_t wchAccountName[UNLEN + 255];   // имя учетной записи

  EXPLICIT_ACCESS  ea;     // информация для элемента списка DACL
  PACL lpOldDacl;          // указатель на старый список DACL
  PACL lpNewDacl;          // указатель на новый список DACL

  PSECURITY_DESCRIPTOR lpSD;   // указатель на дескриптор безопасности

  DWORD dwErrCode;     // код возврата

  // читаем имя созданного каталога
  printf("Input a directory name: ");
  wscanf(L"%s", wchDirName);       // вводим имя каталога

  // получаем SD этого каталога
  dwErrCode = GetNamedSecurityInfo(
    wchDirName,        // имя каталога
    SE_FILE_OBJECT,    // объект файл
    DACL_SECURITY_INFORMATION,   // получаем DACL
    NULL,          // адрес указателя на SID владельца
    NULL,          // адрес указателя на первичную группу
    &lpOldDacl,    // указатель на DACL
    NULL,          // указатель на SACL не нужен
    &lpSD);        // адрес указателя на дескриптор безопасности
  if (dwErrCode != ERROR_SUCCESS)
  {
    printf("Get named security info failed.\n");
    printf("Error code: %u\n", dwErrCode);

    return dwErrCode;
  }

  // вводим имя домена и пользователя, для нового элемента списка DACL
  printf("The following user will be added in DACL.\n");
  printf("Input domain account (domain_name\\user_name): ");
  wscanf(L"%s", wchAccountName);       // вводим имя учетной записи
  
  // строим структуру EXPLICIT_ACCESS по имени
  BuildExplicitAccessWithName(
    &ea,       // адрес структуры ExplicitAccess
    wchAccountName,    // имя учетной записи
    GENERIC_ALL,       // полный доступ
    SET_ACCESS,        // установить доступ
    NO_INHERITANCE     // нет наследования
    );

  // создаем список DACL
  dwErrCode = SetEntriesInAcl(
    1,             // добавляем один элемент в список DACL
    &ea,           // адрес структуры ExplicitAccess
    lpOldDacl,     // адрес старого списка DACL
    &lpNewDacl);   // адрес указателя на новый список DACL
  if (dwErrCode != ERROR_SUCCESS)
  {
    perror("Set entries in DACL failed.\n");
    printf("The last error code: %u\n", dwErrCode);

    return dwErrCode;
  }

  // устанавливаем новый список DACL
  dwErrCode = SetNamedSecurityInfo(
    wchDirName,      // имя файла
    SE_FILE_OBJECT,  // объект файл
    DACL_SECURITY_INFORMATION,   // изменяем список DACL
    NULL,            // владельца не изменяем
    NULL,            // первичную группу не изменяем
    lpNewDacl,       // новый DACL
    NULL);           // SACL не изменяем
  if (dwErrCode != ERROR_SUCCESS)
  {
    printf("Set named security info failed.\n");
    printf("Error code: %u\n", dwErrCode);

    return dwErrCode;
  }

  // освобождаем память
  LocalFree(lpSD);
  LocalFree(lpNewDacl);

  printf("The DACL of directory is modified.\n");

  return 0;
}