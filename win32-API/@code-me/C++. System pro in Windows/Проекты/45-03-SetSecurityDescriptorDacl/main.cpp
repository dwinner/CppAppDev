#ifndef UNICODE
#define UNICODE
#endif

#include <windows.h>
#include <stdio.h>
#include <lm.h>

int main()
{
  HANDLE hMutex;         // ���������� ��������

  ACL *lpDacl;           // ��������� �� ������ �������
  DWORD dwDaclLength;    // ����� ������ �������

  wchar_t wchUserName[UNLEN];      // ��� ������������

  DWORD dwLengthOfDomainName = 0;  // ����� ����� ������

  DWORD dwLengthOfSid = 0;         // ����� SID
  SID *lpSid = NULL;               // ��������� �� SID
  LPTSTR lpDomainName = NULL;      // ��������� �� ��� ������

  SID_NAME_USE typeOfSid;    // ��� ������� ������

  SECURITY_DESCRIPTOR sd;    // ���������� ������������ ��������
  SECURITY_ATTRIBUTES sa;    // �������� ������ ��������

  DWORD dwRetCode;   // ��� ��������

  // ������ ��� ������������, �������� �������� ������ � ��������
  printf("Input a user name: ");
  _getws(wchUserName);

  // ���������� ����� SID ������������
  if (!LookupAccountName(
    NULL,              // ���� ��� �� ��������� ����������
    wchUserName,       // ��� ������������
    NULL,              // ���������� ����� SID
    &dwLengthOfSid,    // ����� SID
    NULL,              // ���������� ��� ������
    &dwLengthOfDomainName,  // ����� ����� ������
    &typeOfSid))       // ��� ������� ������
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
    &dwLengthOfDomainName,  // ����� ����� ������
    &typeOfSid))       // ��� ������� ������
  {
    dwRetCode = GetLastError();

    printf("Lookup account name failed.\n");
    printf("Error code: %d\n", dwRetCode);

    return dwRetCode;
  }

  // ��������� ��� SID
  if (typeOfSid != SidTypeUser)
  {
    printf("This is not a user name.\n");
    return 1;
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
    lpDacl,          // ����� DACL
    ACL_REVISION,    // ������ DACL
    WRITE_OWNER,     // ��������� �������� ��������� �������
    lpSid))          // ����� SID
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
    SE_OWNER_DEFAULTED))    // ���������� ��������� �� ���������
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
    SE_GROUP_DEFAULTED))    // ���������� ��������� ������ �� ���������
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

  // ��������� ��������� ����������� ������������
  if (!IsValidSecurityDescriptor(&sd))
  {
    dwRetCode = GetLastError();
    perror("Security descriptor is invalid.\n");
    printf("The last error code: %u\n", dwRetCode);

    return dwRetCode;
  }

  // �������������� �������� ������������
  sa.nLength = sizeof(sa);       // ������������� ����� ��������� ������
  sa.lpSecurityDescriptor = &sd;   // ������������� ����� SD
  sa.bInheritHandle = FALSE;     // ���������� �������� �� �����������
  

  // ������� �������
  hMutex = CreateMutex(&sa, FALSE, L"DemoMutex");
  if (hMutex == NULL)
  {
    dwRetCode = GetLastError();
    perror("Create mutex failed.\n");
    printf("The last error code: %u\n", dwRetCode);

    return dwRetCode;
  }

  printf("The mutex is created.\n");

  // ����������� ������
  delete[] lpSid;
  delete[] lpDomainName;
  delete[] lpDacl;

  CloseHandle(hMutex);

  return 0;
}