#include <windows.h>
#include <stdio.h>
#include <lm.h>

extern "C" BOOL WINAPI CheckTokenMembership(HANDLE, PSID, PBOOL);

DWORD WINAPI thread(LPVOID lpSid)
{
  HANDLE hImperson;  // ���������� ����������� ������
  BOOL bIsMember;    // ������� ����������� SID

  DWORD dwRetCode;   // ��� ��������

  // �������� ������ ������� ������
  if (!OpenThreadToken(
    GetCurrentThread(),
    TOKEN_QUERY,
    FALSE,
    &hImperson))
  {
    dwRetCode = GetLastError();

    printf("Open Thread Token failed.\n");
    printf("Error code: %d\n", dwRetCode);

    return dwRetCode;
  }

  // ��������� �������������� ������� �������
  if (!CheckTokenMembership(
    hImperson,
    lpSid,
    &bIsMember))
  {
    dwRetCode = GetLastError();

    printf("Check token membership failed.\n");
    printf("Error code: %d\n", dwRetCode);

    CloseHandle(hImperson);

    return dwRetCode;
  }

  if (bIsMember)
    printf("The group is enabled.\n");
  else
    printf("The group is disabled or not present.\n");

  CloseHandle(hImperson);

  return 0;
}

int main()
{
  HANDLE hThread;
  DWORD IDThread;

  HANDLE hToken;       // ���������� ������� �������
  HANDLE hDuplicate;   // ���������� ��������� ������� �������
  
  char chGroupName[GNLEN];     // ��� ������������

  DWORD dwLengthOfUserName = GNLEN;  // ����� ����� ������� ������ 

  DWORD dwLengthOfSID = 0;     // ����� SID
  DWORD dwLengthOfDomainName = 0;    // ����� ����� ������
  
  PSID lpSid = NULL;           // ��������� �� ����������� SID
  LPTSTR lpDomainName = NULL;  // ��������� �� ��� ������
  
  SID_NAME_USE typeOfSid;      // ��� ������� ������

  DWORD dwRetCode;             // ��� ��������
  
  printf("Input a group name: ");
  gets(chGroupName);           // ������ ��� ������������

  // ���������� ����� SID ������������
  if (!LookupAccountName(
    NULL,            // ���� ��� �� ��������� ����������
    chGroupName,     // ��� ������
    NULL,            // ���������� ����� SID
    &dwLengthOfSID,  // ����� SID
    NULL,            // ���������� ��� ������
    &dwLengthOfDomainName,   // ����� ����� ������
    &typeOfSid))     // ��� ������� ������
  {
    dwRetCode = GetLastError();

    if (dwRetCode == ERROR_INSUFFICIENT_BUFFER)
    {
      // ������������ ������ ��� SID � ����� ������
      lpSid = (SID*) new char[dwLengthOfSID];
      lpDomainName = (LPTSTR) new char[dwLengthOfDomainName];
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
    chGroupName,     // ��� ������������
    lpSid,           // ��������� �� SID
    &dwLengthOfSID,  // ����� SID
    lpDomainName,    // ��������� �� ��� ������
    &dwLengthOfDomainName,   // ����� ����� ������
    &typeOfSid))     // ��� ������� ������
  {
    dwRetCode = GetLastError();

    printf("Lookup account name failed.\n");
    printf("Error code: %d\n", dwRetCode);

    return dwRetCode;
  }

  // ��������� ��� �������������� ������������
  if (typeOfSid != SidTypeAlias)
  {
    printf("This is not an alias.\n");
    return 0;
  }
  
  // �������� ������ ������� ��������
  if (!OpenProcessToken(
    GetCurrentProcess(),   // ���������� ��������
    TOKEN_DUPLICATE,       // ������������ ������� �������
    &hToken))              // ���������� �������
  {
    dwRetCode = GetLastError();
    printf( "Open process token failed: %u\n", dwRetCode);
    
    return dwRetCode;
  }

  // ��������� ������ �������
  if (!DuplicateToken(
    hToken,          // ������ �������
    SecurityImpersonation,   // ������� ���������
    &hDuplicate))    // ����� ��������� ������� �������
  {
    dwRetCode = GetLastError();
    printf( "Duplicate token failed: %u\n", dwRetCode);
    
    return dwRetCode;
  }

  // ��������� �����
  hThread = CreateThread(
    NULL,            // ������ �� ���������
    0,               // ������ ����� �� ���������
    thread,          // ����� ��������� ������
    (LPVOID) lpSid,  // ����� ������������ SID
    CREATE_SUSPENDED,  // ����������� ��������� ������
    &IDThread);      // ������������� ������
  if (hThread == NULL)
  {
    printf("Create thread failed.\n");
    return GetLastError();
  }

  // ������������� ���������� ������ ������� ��� ������
  if (!SetThreadToken(
    &hThread,      // ����� ����������� ������
    hDuplicate))   // �������� ������� �������
  {
    dwRetCode = GetLastError();
    printf( "Set thread token failed: %u\n", dwRetCode);
    
    return dwRetCode;
  }

  // ������������ �����
  ResumeThread(hThread);

  // ���� ���������� ������
  WaitForSingleObject(hThread, INFINITE);

  CloseHandle(hToken);
  CloseHandle(hThread);

  return 0;
}