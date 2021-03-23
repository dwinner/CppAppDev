#define _WIN32_WINNT 0x0500

#ifndef UNICODE
#define UNICODE
#endif

#include <windows.h>
#include <stdio.h>
#include <aclapi.h>
#include <sddl.h>

int main()
{
  wchar_t wchDirName[248];   // имя каталога

  PSECURITY_DESCRIPTOR lpSd; // указатель на дескриптор безопасности
  PACL lpDacl;               // указатель на список DACL
  PEXPLICIT_ACCESS lpEa;     // указатель на массив элементов типа 
                             // EXPLICIT_ACCESS
  ULONG ulCount;     // количество элементов в массиве

  LPTSTR  lpStringSid = NULL;    // указатель на строку с SID

  DWORD dwErrCode;   // код возврата

  // читаем имя файла
  printf("Input a file name: ");
  wscanf(L"%s", wchDirName);     // вводим имя файла

  // получаем SD этого файла
  dwErrCode = GetNamedSecurityInfo(
    wchDirName,      // имя файла
    SE_FILE_OBJECT,  // объект файл
    DACL_SECURITY_INFORMATION,   // получаем DACL
    NULL,          // адрес указателя на SID владельца
    NULL,          // адрес указателя на первичную группу
    &lpDacl,       // указатель на DACL
    NULL,          // указатель на SACL не нужен
    &lpSd);        // адрес указателя на дескриптор безопасности
  if (dwErrCode != ERROR_SUCCESS)
  {
    printf("Get named security info failed.\n");
    printf("Error code: %u\n", dwErrCode);

    return dwErrCode;
  }
  // читаем элементы из списка DACL
  dwErrCode = GetExplicitEntriesFromAcl(
    lpDacl,      // адрес списка DACL
    &ulCount,    // адрес для количества элементов
    &lpEa);      // адрес указателя на буфер
  if (dwErrCode != ERROR_SUCCESS)
  {
    printf("Get explicit entries from ACL failed.\n");
    printf("Error code: %u\n", dwErrCode);

    return dwErrCode;
  }

  printf("Number of elements in DACL = %u\n", ulCount);

  // получаем информацию из структур типа TRUSTEE
  for (unsigned i = 0; i < ulCount; ++i)
  {
    if (GetTrusteeForm(&(lpEa->Trustee)) == TRUSTEE_IS_NAME)
      wprintf(L"Trustee name: %s", GetTrusteeName(&(lpEa->Trustee)));
    if (GetTrusteeForm(&(lpEa->Trustee)) == TRUSTEE_IS_SID)
    {
      // преобразуем SID в строку
      if (!ConvertSidToStringSid(lpEa->Trustee.ptstrName, &lpStringSid))
      {
        printf("Convert SID to string SID failed.");

        return GetLastError();
      }
      // распечатываем SID
      wprintf(L"Trustee SID: %s\n", lpStringSid);

      // освобождаем память, занятую строкой
      LocalFree(lpStringSid);
    }

    ++lpEa;    // продвигаемся по массиву
  }

  // освобождаем память
  LocalFree(lpSd);
  LocalFree(lpEa);

  return 0;
}