#include <windows.h>
#include <stdio.h>
#include <lm.h>

int main()
{
  HANDLE hProcess;     // ���������� ��������
  HANDLE hToken;       // ���������� ������� �������
  HANDLE hRestrict;    // ���������� ��������������� ������� �������
  
  char chUserName[UNLEN];  // ��� ������������

  DWORD  dwLengthOfUserName = UNLEN;  // ����� ����� ������� ������

  DWORD  dwLengthOfSID = 0;    // ����� SID
  DWORD  dwLengthOfDomainName = 0;   // ����� ����� ������
  
  SID    *lpSid = NULL;          // ��������� �� SID
  LPTSTR  lpDomainName = NULL;   // ��������� �� ��� ������
  
  SID_NAME_USE type_of_SID;      // ��� ������� ������
  
  SID_AND_ATTRIBUTES RestrictingSid;   // �������������� SID

  DWORD dwRetCode;       // ��� ��������
  
  // �������� ���������� ��������
  hProcess = GetCurrentProcess();
  
  // �������� ������ ������� ��������
  if (!OpenProcessToken(
    hProcess,          // ���������� ��������
    TOKEN_ALL_ACCESS,  // ������ ������ � ������� �������
    &hToken))          // ���������� �������
  {
    dwRetCode = GetLastError();
    printf( "Open process token failed: %u\n", dwRetCode);
    
    return dwRetCode;
  }
  printf("Input a user name: ");
  gets(chUserName);        // ������ ��� ������������

  // ���������� ����� SID ������������
  if (!LookupAccountName(
    NULL,            // ���� ��� �� ��������� ����������
    chUserName,      // ��� ������������
    NULL,            // ���������� ����� SID
    &dwLengthOfSID,  // ����� SID
    NULL,            // ���������� ��� ������
    &dwLengthOfDomainName,   // ����� ����� ������
    &type_of_SID))   // ��� ������� ������
  {
    dwRetCode = GetLastError();

    if (dwRetCode == ERROR_INSUFFICIENT_BUFFER)
    {
      // ������������ ������ ��� SID � ����� ������
      lpSid = (SID*) new char[dwLengthOfSID];
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
    NULL,            // ���� ��� �� ��������� ����������
    chUserName,      // ��� ������������
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

  // �������������� �������������� SID
  RestrictingSid.Sid = lpSid;
  RestrictingSid.Attributes = 0;

  // ������� �������������� ������ �������
  if (!CreateRestrictedToken(
    hToken,          // ���������� ��������� ������� �������
    0,               // ���������� �� ��������
    0, NULL,         // ���� SE_GROUP_USE_FOR_DENY_ONLY �� �������������
    0, NULL,         // ���������� �� �������
    1,               // ���� �������������� SID
    &RestrictingSid, // ����� ��������������� SID
    &hRestrict))     // ����� ��������������� ������� �������
  {
    dwRetCode = GetLastError();

    printf("Create restricted token failed.\n");
    printf("Error code: %d\n", dwRetCode);

    return dwRetCode;
  }

  // ��������� ��������� ������� �������
  if (IsTokenRestricted(hRestrict))
    printf("The restricted token is created.\n");
  else
  {
    dwRetCode = GetLastError();

    printf("Is Token Restricted failed.\n");
    printf("Error code: %d\n", dwRetCode);

    return dwRetCode;
  }


  // �������� �������� ������������ ������
  if (!ImpersonateLoggedOnUser(hRestrict))
  {
    dwRetCode = GetLastError();

    printf("Impersonate logged on user failed.\n");
    printf("Error code: %d\n", dwRetCode);

    return dwRetCode;
  }

  // ����� ������ �����-�� ������
  printf("Some work is done.\n");

  // ���������� �������� ��������
  if (!RevertToSelf())
  {
    dwRetCode = GetLastError();

    printf("Revert to self failed.\n");
    printf("Error code: %d\n", dwRetCode);

    return dwRetCode;
  }

  CloseHandle(hToken);

  return 0;
}