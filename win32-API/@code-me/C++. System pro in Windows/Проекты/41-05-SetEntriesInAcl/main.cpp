#ifndef UNICODE
#define UNICODE
#endif

#include <windows.h>
#include <stdio.h>
#include <lm.h>
#include <aclapi.h>

int main()
{
  wchar_t wchDirName[248];     // ��� ��������
  wchar_t wchAccountName[UNLEN + 255];   // ��� ������� ������

  EXPLICIT_ACCESS  ea;     // ���������� ��� �������� ������ DACL
  PACL lpOldDacl;          // ��������� �� ������ ������ DACL
  PACL lpNewDacl;          // ��������� �� ����� ������ DACL

  PSECURITY_DESCRIPTOR lpSD;   // ��������� �� ���������� ������������

  DWORD dwErrCode;     // ��� ��������

  // ������ ��� ���������� ��������
  printf("Input a directory name: ");
  wscanf(L"%s", wchDirName);       // ������ ��� ��������

  // �������� SD ����� ��������
  dwErrCode = GetNamedSecurityInfo(
    wchDirName,        // ��� ��������
    SE_FILE_OBJECT,    // ������ ����
    DACL_SECURITY_INFORMATION,   // �������� DACL
    NULL,          // ����� ��������� �� SID ���������
    NULL,          // ����� ��������� �� ��������� ������
    &lpOldDacl,    // ��������� �� DACL
    NULL,          // ��������� �� SACL �� �����
    &lpSD);        // ����� ��������� �� ���������� ������������
  if (dwErrCode != ERROR_SUCCESS)
  {
    printf("Get named security info failed.\n");
    printf("Error code: %u\n", dwErrCode);

    return dwErrCode;
  }

  // ������ ��� ������ � ������������, ��� ������ �������� ������ DACL
  printf("The following user will be added in DACL.\n");
  printf("Input domain account (domain_name\\user_name): ");
  wscanf(L"%s", wchAccountName);       // ������ ��� ������� ������
  
  // ������ ��������� EXPLICIT_ACCESS �� �����
  BuildExplicitAccessWithName(
    &ea,       // ����� ��������� ExplicitAccess
    wchAccountName,    // ��� ������� ������
    GENERIC_ALL,       // ������ ������
    SET_ACCESS,        // ���������� ������
    NO_INHERITANCE     // ��� ������������
    );

  // ������� ������ DACL
  dwErrCode = SetEntriesInAcl(
    1,             // ��������� ���� ������� � ������ DACL
    &ea,           // ����� ��������� ExplicitAccess
    lpOldDacl,     // ����� ������� ������ DACL
    &lpNewDacl);   // ����� ��������� �� ����� ������ DACL
  if (dwErrCode != ERROR_SUCCESS)
  {
    perror("Set entries in DACL failed.\n");
    printf("The last error code: %u\n", dwErrCode);

    return dwErrCode;
  }

  // ������������� ����� ������ DACL
  dwErrCode = SetNamedSecurityInfo(
    wchDirName,      // ��� �����
    SE_FILE_OBJECT,  // ������ ����
    DACL_SECURITY_INFORMATION,   // �������� ������ DACL
    NULL,            // ��������� �� ��������
    NULL,            // ��������� ������ �� ��������
    lpNewDacl,       // ����� DACL
    NULL);           // SACL �� ��������
  if (dwErrCode != ERROR_SUCCESS)
  {
    printf("Set named security info failed.\n");
    printf("Error code: %u\n", dwErrCode);

    return dwErrCode;
  }

  // ����������� ������
  LocalFree(lpSD);
  LocalFree(lpNewDacl);

  printf("The DACL of directory is modified.\n");

  return 0;
}