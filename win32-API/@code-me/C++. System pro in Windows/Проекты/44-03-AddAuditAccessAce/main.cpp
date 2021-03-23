#ifndef UNICODE
#define UNICODE
#endif

#include <windows.h>
#include <stdio.h>
#include <lm.h>

int main()
{
  HANDLE hProcess;       // ���������� ��������
  HANDLE hTokenHandle;   // ���������� ������� �������

  TOKEN_PRIVILEGES tp;   // ���������� ������� �������

  ACL *lpDacl;           // ��������� �� ������ ������� DACL
  DWORD dwDaclLength;    // ����� ������ ������� DACL

  ACL *lpSacl;           // ��������� �� ������ ������� SACL
  DWORD dwSaclLength;    // ����� ������ ������� SACL

  wchar_t wchUserName[UNLEN];    // ��� ������������
  wchar_t wchDirName[248];       // ��� ��������

  DWORD dwLengthOfDomainName = 0;  // ����� ����� ������

  DWORD dwLengthOfSid = 0;   // ����� SID
  SID *lpSid = NULL;         // ��������� �� SID
  LPTSTR lpDomainName = NULL;    // ��������� �� ��� ������

  SID_NAME_USE typeOfSid;    // ��� ������� ������

  SECURITY_DESCRIPTOR sd;    // ���������� ������������ ��������
  SECURITY_ATTRIBUTES sa;    // �������� ������ ��������

  DWORD dwRetCode;           // ��� ��������

  // �������� ���������� ��������
  hProcess = GetCurrentProcess();

  // �������� ������ ������� ��������
  if (!OpenProcessToken(
    hProcess,            // ���������� ��������
    TOKEN_ALL_ACCESS,    // ������ ������ � ������� �������
    &hTokenHandle))      // ���������� ������� �������
  {
    dwRetCode = GetLastError();
    printf( "Open process token failed: %u\n", dwRetCode);

    return dwRetCode;
  }

  // ������������� ����� ���������� ����������
  tp.PrivilegeCount = 1;

  // ���������� ������������� ���������� ��� ��������� ������
  if (!LookupPrivilegeValue(
    NULL,      // ���� ������������� ���������� �� ��������� ����������
    SE_SECURITY_NAME,  // ���������� ��� ������
    &(tp.Privileges[0].Luid)))
  {
    dwRetCode = GetLastError();
    printf("Lookup privilege value failed.\n");
    printf("Error code: %d\n", dwRetCode);

    return dwRetCode;
  }

  // ��������� ���������� ������
  tp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;

  // ��������� ���������� ��� ��������� ������
  if (!AdjustTokenPrivileges(
    hTokenHandle,    // ���������� ������� ������� ��������
    FALSE,     // �� ��������� ��� ����������
    &tp,       // ����� ����������
    0,         // ����� ������ ���
    NULL,      // ���������� ��������� ���������� �� �����
    NULL))     // ����� ������ �� �����
  {
    dwRetCode = GetLastError();
    printf("Lookup privilege value failed.\n");
    printf("Error code: %d\n", dwRetCode);

    return dwRetCode;
  }

  // ������ ��� ������������, �������� �������� ������ � ��������
  printf("Input a user name: ");
  _getws(wchUserName);

  // ���������� ����� SID ������������
  if (!LookupAccountName(
    NULL,            // ���� ��� �� ��������� ����������
    wchUserName,     // ��� ������������
    NULL,            // ���������� ����� SID
    &dwLengthOfSid,  // ����� SID
    NULL,            // ���������� ��� ������
    &dwLengthOfDomainName,   // ����� ����� ������
    &typeOfSid))     // ��� ������� ������
  {
    dwRetCode = GetLastError();

    if (dwRetCode == ERROR_INSUFFICIENT_BUFFER)
    {
      // ������������ ������ ��� SID � ����� ������
      lpSid = (SID*) new char[dwLengthOfSid];
      lpDomainName = (LPTSTR) new wchar_t[dwLengthOfDomainName];
    }
    else
    {
      // ������� �� ���������
      printf("Lookup account name failed.\n");
      printf("Error code: %d\n", dwRetCode);

      return dwRetCode;
    }
  }

  // ���������� SID � ��� ������ ������������
  if(!LookupAccountName(
    NULL,              // ���� ��� �� ��������� ����������
    wchUserName,       // ��� ������������
    lpSid,             // ��������� �� SID
    &dwLengthOfSid,    // ����� SID
    lpDomainName,      // ��������� �� ��� ������
    &dwLengthOfDomainName,   // ����� ����� ������
    &typeOfSid))       // ��� ������� ������
  {
    dwRetCode = GetLastError();

    printf("Lookup account name failed.\n");
    printf("Error code: %d\n", dwRetCode);

    return dwRetCode;
  }

  // ��������� ����� ������ DACL
  dwDaclLength = sizeof(ACL)
    + sizeof(ACCESS_ALLOWED_ACE) - sizeof(DWORD) + dwLengthOfSid
    + sizeof(ACCESS_DENIED_ACE) - sizeof(DWORD) + dwLengthOfSid;

  // ������������ ������ ��� DACL
  lpDacl = (ACL*)new char[dwDaclLength];

  // �������������� ������ DACL
  if (!InitializeAcl(
    lpDacl,          // ����� DACL
    dwDaclLength,    // ����� DACL
    ACL_REVISION))   // ������ DACL
  {
    dwRetCode = GetLastError();

    printf("Lookup account name failed.\n");
    printf("Error code: %d\n", dwRetCode);

    return dwRetCode;
  }

  // ��������� ����������� ������� � ������ DACL
  if (!AddAccessDeniedAce(
    lpDacl,        // ����� DACL
    ACL_REVISION,  // ������ DACL
    WRITE_OWNER,   // ��������� �������� ��������� �������
    lpSid))        // ����� SID
  {
    dwRetCode = GetLastError();
    perror("Add access denied ace failed.\n");
    printf("The last error code: %u\n", dwRetCode);

    return dwRetCode;
  }

  // ��������� ����������� ������� � ������ DACL
  if (!AddAccessAllowedAce(
    lpDacl,        // ����� DACL
    ACL_REVISION,  // ������ DACL
    GENERIC_ALL,   // ��������� ��� ������� ����� �������
    lpSid))        // ����� SID
  {
    dwRetCode = GetLastError();
    perror("Add access allowed ace failed.\n");
    printf("The last error code: %u\n", dwRetCode);

    return dwRetCode;
  }

  // ��������� ����� ������ SACL
  dwSaclLength = sizeof(ACL)
    + sizeof(SYSTEM_AUDIT_ACE ) - sizeof(DWORD) + dwLengthOfSid;

  // ������������ ������ ��� SACL
  lpSacl = (ACL*)new char[dwSaclLength];

  // �������������� ������ SACL
  if (!InitializeAcl(
    lpSacl,          // ����� SACL
    dwSaclLength,    // ����� SACL
    ACL_REVISION))   // ������ SACL
  {
    dwRetCode = GetLastError();

    printf("Lookup account name failed.\n");
    printf("Error code: %d\n", dwRetCode);

    return dwRetCode;
  }

  // ��������� ������� � ������ SACL
  if (!AddAuditAccessAce(
    lpSacl,        // ����� DACL
    ACL_REVISION,  // ������ DACL
    WRITE_OWNER,   // ��������� �������� ��������� �������
    lpSid,         // ����� SID
    FALSE,         // �� ����� ����� �������� �������
    TRUE))         // ����� ����� ���������� �������
  {
    dwRetCode = GetLastError();
    perror("Add audit access ace failed.\n");
    printf("The last error code: %u\n", dwRetCode);

    return dwRetCode;
  }

  // �������������� ������ ����������� ������������
  if (!InitializeSecurityDescriptor(
    &sd,
    SECURITY_DESCRIPTOR_REVISION))
  {
    dwRetCode = GetLastError();
    printf("Initialize security descroptor failed.\n");
    printf("Error code: %d\n", dwRetCode);

    return dwRetCode;
  }

  // ������������� SID ��������� �������
  if (!SetSecurityDescriptorOwner(
    &sd,         // ����� ����������� ������������
    NULL,        // �� ������ ���������
    SE_OWNER_DEFAULTED))   // ���������� ��������� �� ���������
  {
    dwRetCode = GetLastError();
    perror("Set security descriptor owner failed.\n");
    printf("The last error code: %u\n", dwRetCode);

    return dwRetCode;
  }

  // ������������� SID ��������� ������ ���������
  if (!SetSecurityDescriptorGroup(
    &sd,         // ����� ����������� ������������
    NULL,        // �� ������ ��������� ������
    SE_GROUP_DEFAULTED))   // ���������� ��������� ������ �� ���������
  {
    dwRetCode = GetLastError();
    perror("Set security descriptor group failed.\n");
    printf("The last error code: %u\n", dwRetCode);

    return dwRetCode;
  }
  // ������������� DACL  � ���������� ������������
  if (!SetSecurityDescriptorDacl(
    &sd,       // ����� ����������� ������������
    TRUE,      // DACL ������������
    lpDacl,    // ��������� �� DACL
    FALSE))    // DACL �� ����� �� ���������
  {
    dwRetCode = GetLastError();
    perror("Set security descriptor group failed.\n");
    printf("The last error code: %u\n", dwRetCode);

    return dwRetCode;
  }
  // ������������� SACL  � ���������� ������������
  if (!SetSecurityDescriptorSacl(
    &sd,       // ����� ����������� ������������
    TRUE,      // SACL ������������
    lpSacl,    // ��������� �� SACL
    FALSE))    // SACL �� ����� �� ���������
  {
    dwRetCode = GetLastError();
    perror("Set security descriptor group failed.\n");
    printf("The last error code: %u\n", dwRetCode);

    return dwRetCode;
  }

  // ��������� ��������� ����������� ������������
  if (!IsValidSecurityDescriptor(&sd))
  {
    dwRetCode = GetLastError();
    perror("Security descriptor is invalid.\n");
    printf("The last error code: %u\n", dwRetCode);

    return dwRetCode;
  }

  // �������������� �������� ������������
  sa.nLength = sizeof(sa);     // ������������� ����� ��������� ������
  sa.lpSecurityDescriptor = &sd;     // ������������� ����� ����������� ������������
  sa.bInheritHandle = FALSE;   // ���������� �������� �� �����������
  
  // ������ ��� ������������ ��������
  printf("Input a new directory name: ");
  _getws(wchDirName);          // ������ ��� ��������

  // ������� �������
  if (!CreateDirectory(wchDirName, &sa))
  {
    dwRetCode = GetLastError();
    perror("Security descriptor is invalid.\n");
    printf("The last error code: %u\n", dwRetCode);

    return dwRetCode;
  }

  printf("The directory is created.\n");

  // ��������� ���������� ������
  tp.Privileges[0].Attributes = 0;

  // ��������� ���������� ��� ��������� ������
  if (!AdjustTokenPrivileges(
    hTokenHandle,    // ���������� ������� ������� ��������
    FALSE,           // �� ��������� ��� ����������
    &tp,             // ����� ����������
    0,               // ����� ������ ���
    NULL,            // ���������� ��������� ���������� �� �����
    NULL))           // ����� ������ �� �����
  {
    dwRetCode = GetLastError();
    printf("Lookup privilege value failed.\n");
    printf("Error code: %d\n", dwRetCode);

    return dwRetCode;
  }

  // ����������� ������
  delete[] lpSid;
  delete[] lpDomainName;
  delete[] lpDacl;

  return 0;
}