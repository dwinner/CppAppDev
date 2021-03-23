#ifndef UNICODE
#define UNICODE
#endif

#include <windows.h>
#include <stdio.h>

int main()
{
  HANDLE hMutex;     // ���������� ��������

  DWORD dwLengthOfSd = 0;    // ����� SD
  SECURITY_DESCRIPTOR *lpSd = NULL;  // ���������� ������������ ��������

  PSID lpOwner;              // ��������� �� SID ���������
  BOOL bOwnerDefaulted = FALSE;      // ������� ��������� �� ���������

  DWORD  dwLengthOfUserName = 0;     // ����� ����� ������� ������ 
  DWORD  dwLengthOfDomainName = 0;   // ����� ����� ������

  LPTSTR  lpUserName = NULL;         // ��������� �� ��� ������
  LPTSTR  lpDomainName = NULL;       // ��������� �� ��� ������

  SID_NAME_USE type_of_SID;          // ��� ������� ������

  DWORD dwRetCode;    // ��� ��������

  // ������� �������
  hMutex = CreateMutex(NULL, FALSE, L"DemoMutex");
  if (hMutex == NULL)
  {
    dwRetCode = GetLastError();
    perror("Create mutex failed.\n");
    printf("The last error code: %u\n", dwRetCode);

    return dwRetCode;
  }

  printf("The mutex is created.\n");

  // ���������� ��������� ����� ������
  if (!GetKernelObjectSecurity(
    hMutex,          // ���������� ��������
    OWNER_SECURITY_INFORMATION,  // �������� ��������� ��������
    lpSd,            // ����� SD
    0,               // ���������� ����� ������
    &dwLengthOfSd))  // ��������� ����� ������
  {
    dwRetCode = GetLastError();

    if (dwRetCode == ERROR_INSUFFICIENT_BUFFER)
      // ������������ ������ ��� ������
      lpSd = (SECURITY_DESCRIPTOR*) new char[dwLengthOfSd];
    else
    {
      // ������� �� ���������
      printf("Get kernel object security failed.\n");
      printf("Error code: %d\n", dwRetCode);

      return dwRetCode;
    }
  }

  // ����� ������������� ������������ ��������
  if (!GetKernelObjectSecurity(
    hMutex,          // ���������� ��������
    OWNER_SECURITY_INFORMATION,  // �������� ��������� ��������
    lpSd,            // ����� SD
    dwLengthOfSd,    // ����� ������
    &dwLengthOfSd))  // ��������� ����� ������
  {
    dwRetCode = GetLastError();
    printf("Get kernel object security failed.\n");
    printf("The last error code: %u\n", dwRetCode);

    return dwRetCode;
  }

  // �������� SID ��������� ��������
  if (!GetSecurityDescriptorOwner(
    lpSd,                // ����� ����������� ������������
    &lpOwner,            // ����� ��������� �� SID ���������
    &bOwnerDefaulted))   // ������� ��������� �� ���������
  {
    dwRetCode = GetLastError();
    printf("Get security descriptor owner failed.\n");
    printf("Error code: %d\n", dwRetCode);
    
    return dwRetCode;
  }

  // ���������, ���� �� ��������
  if (lpOwner == NULL)
  {
    printf("The owner is not present.\n");

    return 0;
  }

  if (bOwnerDefaulted)
    printf("The owner is defaulted.\n");
  
  // ���������� ����� ����� ������
  if(!LookupAccountSid(
    NULL,                // ���� �� ��������� ����������
    lpOwner,             // ��������� �� SID
    lpUserName,          // ��� ������������
    &dwLengthOfUserName,     // ����� ����� ������������
    lpDomainName,        // ���������� ��� ������
    &dwLengthOfDomainName,   // ����� ����� ������
    &type_of_SID))       // ��� ������� ������
  {
    dwRetCode = GetLastError();

    if (dwRetCode == ERROR_INSUFFICIENT_BUFFER)
    {
      // ������������ ������ ��� ��� ������������ � ���������
      lpUserName = (LPTSTR) new wchar_t[dwLengthOfUserName];
      lpDomainName = (LPTSTR) new wchar_t[dwLengthOfDomainName];
    }
    else
    {
      printf("Lookup account SID for length failed.\n");
      printf("Error code: %d\n", dwRetCode);

      return dwRetCode;
    }
  }

  // ���������� ��� ������� ������ �� SID
  if(!LookupAccountSid(
    NULL,                // ���� �� ��������� ����������
    lpOwner,             // ��������� �� SID ������������
    lpUserName,          // ��� ������������
    &dwLengthOfUserName,     // ����� ����� ������������
    lpDomainName,        // ���������� ��� ������
    &dwLengthOfDomainName,   // ����� ����� ������
    &type_of_SID))       // ��� ������� ������
  {
    dwRetCode = GetLastError();

    printf("Lookup account SID failed.\n");
    printf("Error code: %d\n", dwRetCode);

    return dwRetCode;
  }

  wprintf(L"User name: %s\n", lpUserName);
  wprintf(L"Domain name: %s\n", lpDomainName);

  // ����������� ������
  delete[] lpUserName;
  delete[] lpDomainName;
  delete[] lpSd;

  CloseHandle(hMutex);
  printf("The mutex is deleted.\n");

  return 0;
}