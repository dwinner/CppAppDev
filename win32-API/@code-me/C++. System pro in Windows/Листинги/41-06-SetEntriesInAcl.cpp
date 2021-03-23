#ifndef UNICODE
#define UNICODE
#endif

#include <windows.h>
#include <stdio.h>
#include <lm.h>
#include <aclapi.h>

int main()
{
  HANDLE hProcess;         // ���������� ��������
  HANDLE hTokenHandle;     // ���������� ������� �������

  TOKEN_PRIVILEGES tp;     // ���������� ������� �������

  wchar_t wchDirName[248];   // ��� ��������
  wchar_t wchAccountName[UNLEN + 255];   // ��� ������� ������

  EXPLICIT_ACCESS  eaSacl;   // ���������� ��� �������� ������ DACL
  EXPLICIT_ACCESS  eaDacl;   // ���������� ��� �������� ������ DACL

  PACL lpOldDacl;      // ��������� �� ������ ������ DACL
  PACL lpNewDacl;      // ��������� �� ����� ������ DACL
  PACL lpOldSacl;      // ��������� �� ������ ������ SACL
  PACL lpNewSacl;      // ��������� �� ����� ������ SACL

  PSECURITY_DESCRIPTOR lpSD;   // ��������� �� ���������� ������������

  DWORD dwErrCode;     // ��� ��������

  // �������� ���������� ��������
  hProcess = GetCurrentProcess();

  // �������� ������ ������� ��������
  if (!OpenProcessToken(
    hProcess,          // ���������� ��������
    TOKEN_ALL_ACCESS,  // ������ ������ � ������� �������
    &hTokenHandle))    // ���������� �������
  {
    dwErrCode = GetLastError();
    printf( "Open process token failed: %u\n", dwErrCode);

    return dwErrCode;
  }

  // ������������� ����� ���������� ����������
  tp.PrivilegeCount = 1;

  // ���������� ������������� ���������� ��� ��������� ������
  if (!LookupPrivilegeValue(
    NULL,      // ���� ������������� ���������� �� ��������� ����������
    SE_SECURITY_NAME,  // ���������� ��� ������
    &(tp.Privileges[0].Luid)))
  {
    dwErrCode = GetLastError();
    printf("Lookup privilege value failed.\n");
    printf("Error code: %d\n", dwErrCode);

    return dwErrCode;
  }

  // ��������� ���������� ������
  tp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;

  // ��������� ���������� ��� ��������� ������
  if (!AdjustTokenPrivileges(
    hTokenHandle,  // ���������� ������� ������� ��������
    FALSE,     // �� ��������� ��� ����������
    &tp,       // ����� ����������
    0,         // ����� ������ ���
    NULL,      // ���������� ��������� ���������� �� �����
    NULL))     // ����� ������ �� �����
  {
    dwErrCode = GetLastError();
    printf("Lookup privilege value failed.\n");
    printf("Error code: %d\n", dwErrCode);

    return dwErrCode;
  }

  // ������ ��� ���������� ��������
  printf("Input a directory name: ");
  wscanf(L"%s", wchDirName);     // ������ ��� ��������

  // �������� SD ����� ��������
  dwErrCode = GetNamedSecurityInfo(
    wchDirName,      // ��� ��������
    SE_FILE_OBJECT,  // ������ ����
    DACL_SECURITY_INFORMATION |    // �������� DACL � SACL
    SACL_SECURITY_INFORMATION,
    NULL,            // ����� ��������� �� SID ���������
    NULL,            // ����� ��������� �� ��������� ������
    &lpOldDacl,      // ��������� �� DACL
    &lpOldSacl,      // ��������� �� SACL
    &lpSD);          // ����� ��������� �� ���������� ������������
  if (dwErrCode != ERROR_SUCCESS)
  {
    printf("Get named security info failed.\n");
    printf("Error code: %u\n", dwErrCode);

    return dwErrCode;
  }

  // ������ ��� ������ � ������������, ��� ������ �������� ������ DACL
  printf("The following user will be added in DACL and SACL.\n");
  printf("Input domain account (domain_name\\user_name): ");
  wscanf(L"%s", wchAccountName);     // ������ ��� ������� ������
  
  // ������ ��������� EXPLICIT_ACCESS ��� DACL �� �����
  BuildExplicitAccessWithName(
    &eaDacl,         // ����� ��������� ExplicitAccess
    wchAccountName,  // ��� ������� ������
    GENERIC_READ,    // ������ ������
    SET_ACCESS,      // ���������� ������
    NO_INHERITANCE   // ��� ������������
    );

  // ������� ������ DACL
  dwErrCode = SetEntriesInAcl(
    1,             // ��������� ���� ������� � ������ DACL
    &eaDacl,       // ����� ��������� ExplicitAccess
    lpOldDacl,     // ����� ������� ������ DACL
    &lpNewDacl);   // ����� ��������� �� ����� ������ DACL
  if (dwErrCode != ERROR_SUCCESS)
  {
    perror("Set entries in DACL failed.\n");
    printf("The last error code: %u\n", dwErrCode);

    return dwErrCode;
  }

  // ������ ��������� EXPLICIT_ACCESS ��� SACL �� �����
  BuildExplicitAccessWithName(
    &eaSacl,         // ����� ��������� ExplicitAccess
    wchAccountName,  // ��� ������� ������
    GENERIC_READ,    // ������ ������
    SET_AUDIT_SUCCESS,   // ����������� ��������� ��� �������� �������
    NO_INHERITANCE   // ��� ������������
    );

  // ������� ������ SACL
  dwErrCode = SetEntriesInAcl(
    1,             // ��������� ���� ������� � ������ DACL
    &eaSacl,       // ����� ��������� ExplicitAccess
    lpOldSacl,     // ����� ������� ������ DACL
    &lpNewSacl);   // ����� ��������� �� ����� ������ DACL
  if (dwErrCode != ERROR_SUCCESS)
  {
    perror("Set entries in SACL failed.\n");
    printf("The last error code: %u\n", dwErrCode);

    return dwErrCode;
  }

  // ������������� ����� ������ DACL � SACL
  dwErrCode = SetNamedSecurityInfo(
    wchDirName,      // ��� �����
    SE_FILE_OBJECT,  // ������ ����
    DACL_SECURITY_INFORMATION |  // �������� ������ DACL
    SACL_SECURITY_INFORMATION,   // � SACL
    NULL,            // ��������� �� ��������
    NULL,            // ��������� ������ �� ��������
    lpNewDacl,       // ����� DACL
    lpNewSacl);      // ����� SACL
  if (dwErrCode != ERROR_SUCCESS)
  {
    printf("Set named security info failed.\n");
    printf("Error code: %u\n", dwErrCode);

    return dwErrCode;
  }

  // ��������� ���������� ������
  tp.Privileges[0].Attributes = 0;

  // ��������� ���������� ��� ��������� ������
  if (!AdjustTokenPrivileges(
    hTokenHandle,    // ���������� ������� ������� ��������
    FALSE,     // �� ��������� ��� ����������
    &tp,       // ����� ����������
    0,         // ����� ������ ���
    NULL,      // ���������� ��������� ���������� �� �����
    NULL))     // ����� ������ �� �����
  {
    dwErrCode = GetLastError();
    printf("Lookup privilege value failed.\n");
    printf("Error code: %d\n", dwErrCode);

    return dwErrCode;
  }

  // ����������� ������
  LocalFree(lpSD);
  LocalFree(lpNewDacl);
  LocalFree(lpNewSacl);

  printf("The DACL and SACL of the directory are modified.\n");

  return 0;
}