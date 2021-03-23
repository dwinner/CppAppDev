#ifndef UNICODE
#define UNICODE
#endif

#include <windows.h>
#include <stdio.h>
#include <lm.h>
#include <aclapi.h>

int main()
{
  HANDLE hProcess;       // ���������� ��������
  HANDLE hTokenHandle;   // ���������� ������� �������

  TOKEN_PRIVILEGES tp;   // ���������� ������� �������
  
  wchar_t wchDirName[248];   // ��� ��������
  wchar_t wchAccountName[UNLEN + 255];   // ��� ������� ������

  SECURITY_DESCRIPTOR sd;    // ���������� ������������ ��������
  SECURITY_ATTRIBUTES sa;    // �������� ������ ��������

  EXPLICIT_ACCESS  eaDacl;   // ���������� ��� �������� ������ DACL
  PACL lpNewDacl;            // ��������� �� ������ DACL

  EXPLICIT_ACCESS  eaSacl;   // ���������� ��� �������� ������ SACL
  PACL lpNewSacl;            // ��������� �� ������ DACL

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
    FALSE,   // �� ��������� ��� ����������
    &tp,     // ����� ����������
    0,       // ����� ������ ���
    NULL,    // ���������� ��������� ���������� �� �����
    NULL))   // ����� ������ �� �����
  {
    dwErrCode = GetLastError();
    printf("Lookup privilege value failed.\n");
    printf("Error code: %d\n", dwErrCode);

    return dwErrCode;
  }

  // �������������� ������ ����������� ������������
  if (!InitializeSecurityDescriptor(
    &sd,
    SECURITY_DESCRIPTOR_REVISION))
  {
    dwErrCode = GetLastError();
    printf("Initialize security descroptor failed.\n");
    printf("Error code: %d\n", dwErrCode);

    return dwErrCode;
  }

  // ������������� SID ��������� �������
  if (!SetSecurityDescriptorOwner(
    &sd,       // ����� ����������� ������������
    NULL,      // �� ������ ���������
    SE_OWNER_DEFAULTED))   // ���������� ��������� �� ���������
  {
    dwErrCode = GetLastError();
    perror("Set security descriptor owner failed.\n");
    printf("The last error code: %u\n", dwErrCode);

    return dwErrCode;
  }

  // ������������� SID ��������� ������ ���������
  if (!SetSecurityDescriptorGroup(
    &sd,       // ����� ����������� ������������
    NULL,      // �� ������ ��������� ������
    SE_GROUP_DEFAULTED))   // ���������� ��������� ������ �� ���������
  {
    dwErrCode = GetLastError();
    perror("Set security descriptor group failed.\n");
    printf("The last error code: %u\n", dwErrCode);

    return dwErrCode;
  }

  // ������ ��� ������ � ������������
  printf("The following user will have full access to directory.\n");
  printf("Input domain account (domain_name\\user_name): ");
  wscanf(L"%s", wchAccountName);       // ������ ��� ������� ������
  
  // ������ ��������� EXPLICIT_ACCESS �� ����� ��� ������ DACL
  BuildExplicitAccessWithName(
    &eaDacl,         // ����� ��������� ExplicitAccess
    wchAccountName,  // ��� ������� ������
    GENERIC_ALL,     // ������ ������ � �������
    SET_ACCESS,      // ���������� ������
    NO_INHERITANCE   // ��� ������������
    );

  // ������� ������ DACL
  dwErrCode = SetEntriesInAcl(
    1,         // ���� �������
    &eaDacl,   // ����� ��������� ExplicitAccess
    NULL,      // ������� DACL ���
    &lpNewDacl);   // ����� ������ DACL
  if (dwErrCode != ERROR_SUCCESS)
  {
    perror("Set entries in DACL failed.\n");
    printf("The last error code: %u\n", dwErrCode);

    return dwErrCode;
  }

  // ������������� DACL � ���������� ������������
  if (!SetSecurityDescriptorDacl(
    &sd,       // ����� ����������� ������������
    TRUE,      // DACL ������������
    lpNewDacl, // ��������� �� DACL
    FALSE))    // DACL �� ����� �� ���������
  {
    dwErrCode = GetLastError();
    perror("Set security descriptor group failed.\n");
    printf("The last error code: %u\n", dwErrCode);

    return dwErrCode;
  }

  // ������ ��������� EXPLICIT_ACCESS �� ����� ��� ������ SACL
  BuildExplicitAccessWithName(
    &eaSacl,           // ����� ��������� ExplicitAccess
    wchAccountName,    // ��� ������� ������
    GENERIC_ALL,       // ������ ������ � �������
    SET_AUDIT_SUCCESS, // ���������� ������
    NO_INHERITANCE     // ��� ������������
    );

  // ������� ������ SACL
  dwErrCode = SetEntriesInAcl(
    1,         // ���� �������
    &eaSacl,   // ����� ��������� ExplicitAccess
    NULL,      // ������� SACL ���
    &lpNewSacl);   // ����� ������ SACL
  if (dwErrCode != ERROR_SUCCESS)
  {
    perror("Set entries in DACL failed.\n");
    printf("The last error code: %u\n", dwErrCode);

    return dwErrCode;
  }

  // ������������� SACL  � ���������� ������������
  if (!SetSecurityDescriptorSacl(
    &sd,         // ����� ����������� ������������
    TRUE,        // SACL ������������
    lpNewSacl,   // ��������� �� SACL
    FALSE))      // SACL �� ����� �� ���������
  {
    dwErrCode = GetLastError();
    perror("Set security descriptor group failed.\n");
    printf("The last error code: %u\n", dwErrCode);

    return dwErrCode;
  }

  // ��������� ��������� ����������� ������������
  if (!IsValidSecurityDescriptor(&sd))
  {
    dwErrCode = GetLastError();
    perror("Security descriptor is invalid.\n");
    printf("The last error code: %u\n", dwErrCode);

    return dwErrCode;
  }

  // �������������� �������� ������������
  sa.nLength = sizeof(sa);     // ������������� ����� ��������� ������
  // ������������� ����� ����������� ������������
  sa.lpSecurityDescriptor = &sd; 
  // ���������� �������� �� �����������
  sa.bInheritHandle = FALSE; 

  // ������ ��� ������������ ��������
  printf("Input a directory name: ");
  wscanf(L"%s", wchDirName);     // ������ ��� ��������

  // ������� �������
  if (!CreateDirectory(wchDirName, &sa))
  {
    dwErrCode = GetLastError();
    perror("Security descriptor is invalid.\n");
    printf("The last error code: %u\n", dwErrCode);

    return dwErrCode;
  }

  // ��������� ���������� ������
  tp.Privileges[0].Attributes = 0;

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

  // ����������� ������, ����������� ��� ������ DACL � SACL
  LocalFree(lpNewDacl);
  LocalFree(lpNewSacl);

  printf("The directory is created.\n");

  return 0;
}