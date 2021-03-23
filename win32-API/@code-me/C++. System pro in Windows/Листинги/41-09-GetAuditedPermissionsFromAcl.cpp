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
  HANDLE hProcess;       // ���������� ��������
  HANDLE hTokenHandle;   // ���������� ������� �������

  TOKEN_PRIVILEGES tp;   // ���������� ������� �������

  DWORD  dwLengthOfSID = 0;          // ����� SID
  DWORD  dwLengthOfDomainName = 0;   // ����� ����� ������
  DWORD  dwLengthOfUserName = UNLEN; // ����� ����� ������� ������ 
  SID    *lpSid = NULL;              // ��������� �� SID

  LPTSTR  lpDomainName = NULL;   // ��������� �� ��� ������
  SID_NAME_USE type_of_SID;      // ��� ������� ������

  wchar_t wchFileName[248];      // ��� ��������
  wchar_t wchUserName[UNLEN];    // ��� ������� ������

  TRUSTEE  Trustee;      // ���������� �� ������� ������
  PACL pSacl = NULL;     // ��������� �� ������ SACL
  PSECURITY_DESCRIPTOR pSd = NULL;   // ��������� �� ���������� ������������

  ACCESS_MASK amSuccess = 0;     // ����� ��� ������ ��������� �������
  ACCESS_MASK amFailed = 0;      // ����� ��� ������ ���������� �������

  DWORD dwRetCode;       // ��� ��������

  // �������� ���������� ��������
  hProcess = GetCurrentProcess();

  // �������� ������ ������� ��������
  if (!OpenProcessToken(
    hProcess,          // ���������� ��������
    TOKEN_ALL_ACCESS,  // ������ ������ � ������� �������
    &hTokenHandle))    // ���������� �������
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
    hTokenHandle,  // ���������� ������� ������� ��������
    FALSE,   // �� ��������� ��� ����������
    &tp,     // ����� ����������
    0,       // ����� ������ ���
    NULL,    // ���������� ��������� ���������� �� �����
    NULL))   // ����� ������ �� �����
  {
    dwRetCode = GetLastError();
    printf("Lookup privilege value failed.\n");
    printf("Error code: %d\n", dwRetCode);

    return dwRetCode;
  }

  // ������ ��� ����� ��� ��������, ��������: C:\\test.txt
  printf("Input a full path to your file: ");
  _getws(wchFileName);

  // �������� ���������� ������������ �����
  dwRetCode = GetNamedSecurityInfo(
    wchFileName,     // ��� �����
    SE_FILE_OBJECT,  // ������ ����
    SACL_SECURITY_INFORMATION,   // �������� �������� �� ������
    NULL,      // SID ��������� �� �����
    NULL,      // SID ��������� ������ �� �����
    NULL,      // DACL �� �����
    &pSacl,    // ��������� �� SACL
    &pSd);     // ����� ��������� �� ���������� ������������
  if (dwRetCode != ERROR_SUCCESS)
  {
    printf("Get named security info failed.\n");
    printf("Error code: %u\n", dwRetCode);

    return dwRetCode;
  }

  // ������ ��� ������������
  printf("Input user_name: ");
  _getws(wchUserName);       // ������ ��� ������� ������

  // �������� SID ������� ������
  // ���������� ����� SID ������������
  LookupAccountName(
    NULL,            // ���� ��� �� ��������� ����������
    wchUserName,     // ��� ������������
    NULL,            // ���������� ����� SID
    &dwLengthOfSID,  // ����� SID
    NULL,            // ���������� ��� ������
    &dwLengthOfDomainName,   // ����� ����� ������
    &type_of_SID);   // ��� ������� ������

  // ���������, ������� �� ������� ����� SID
  if (dwLengthOfSID == 0)
  {
    dwRetCode = GetLastError();

    printf("Lookup account name failed.\n");
    printf("Error code: %d\n", dwRetCode);

    return dwRetCode;
  }

  // ������������ ������ ��� SID � ����� ������
  lpSid = (SID*) new char[dwLengthOfSID];
  lpDomainName = (LPTSTR) new wchar_t[dwLengthOfDomainName];

  // ���������� SID � ��� ������ ������������
  if(!LookupAccountName(
    NULL,            // ���� ��� �� ��������� ����������
    wchUserName,     // ��� ������������
    lpSid,           // ��������� �� SID
    &dwLengthOfSID,  // ����� SID
    lpDomainName,    // ��������� �� ��� ������
    &dwLengthOfDomainName,   // ����� ����� ������
    &type_of_SID))   // ��� ������� ������
  {
    dwRetCode = GetLastError();

    printf("Lookup account name failed.\n");
    printf("Error code: %d\n", dwRetCode);

    return dwRetCode;
  }

  // ������ ��������� TRUSTEE �� �������������� ������������
  BuildTrusteeWithSid(&Trustee, lpSid);

  // �������� ����������� ����� ������������
  dwRetCode = GetAuditedPermissionsFromAcl(
    pSacl,       // ����� ������ SACL
    &Trustee,    // ���������� �� ������� ������
    &amSuccess,  // ����� ����� ���� ��������� �������
    &amFailed);  // ����� ����� ���� ���������� �������
  if (dwRetCode != ERROR_SUCCESS)
  {
    printf("Get audited permissions from ACL failed.\n");
    printf("Error code: %u\n", dwRetCode);

    return dwRetCode;
  }

  // ������������� ����� �������
  printf("Success audit rights: %x\n", amSuccess);
  printf("Failed audit rights: %x\n", amFailed);
  
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
    dwRetCode = GetLastError();
    printf("Lookup privilege value failed.\n");
    printf("Error code: %d\n", dwRetCode);

    return dwRetCode;
  }

  // ����������� ������ ��� �����������
  LocalFree(pSd);
  delete[] lpDomainName;
  delete[] lpSid;

  return 0;
}