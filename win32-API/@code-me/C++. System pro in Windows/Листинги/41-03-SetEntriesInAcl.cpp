#ifndef UNICODE
#define UNICODE
#endif

#include <windows.h>
#include <stdio.h>
#include <lm.h>
#include <aclapi.h>
#include <accctrl.h>

int main()
{
  wchar_t wchDirName[248];   // ��� ��������
  wchar_t wchAccountName[UNLEN + 255];   // ��� ������� ������

  SECURITY_DESCRIPTOR sd;    // ���������� ������������ ��������
  SECURITY_ATTRIBUTES sa;    // �������� ������ ��������

  EXPLICIT_ACCESS  ea;       // ���������� ��� �������� ������ DACL
  PACL lpNewDacl;            // ��������� �� ������ DACL

  DWORD dwErrCode;           // ��� ��������

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
    SE_GROUP_DEFAULTED))  // ���������� ��������� ������ �� ���������
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
  
  // ������ ��������� EXPLICIT_ACCESS �� �����
  BuildExplicitAccessWithName(
    &ea,             // ����� ��������� ExplicitAccess
    wchAccountName,  // ��� ������� ������
    GENERIC_ALL,     // ������ ������ � �������
    SET_ACCESS,      // ���������� ������
    NO_INHERITANCE   // ��� ������������
    );

  // ������� ������ DACL
  dwErrCode = SetEntriesInAcl(
    1,           // ���� �������
    &ea,         // ����� ��������� ExplicitAccess
    NULL,        // ������� DACL ���
    &lpNewDacl); // ����� ������ DACL
  if (dwErrCode != ERROR_SUCCESS)
  {
    perror("Set entries in DACL failed.\n");
    printf("The last error code: %u\n", dwErrCode);

    return dwErrCode;
  }

  // ������������� DACL � ���������� ������������
  if (!SetSecurityDescriptorDacl(
    &sd,         // ����� ����������� ������������
    TRUE,        // DACL ������������
    lpNewDacl,   // ��������� �� DACL
    FALSE))      // DACL �� ����� �� ���������
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
  sa.lpSecurityDescriptor = &sd;   // ������������� ����� ����������� 
                                   // ������������
  sa.bInheritHandle = FALSE;   // ���������� �������� �� �����������
  
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

  // ����������� ������, ����������� ��� DACL
  LocalFree(lpNewDacl);

  printf("The directory is created.\n");

  return 0;
}