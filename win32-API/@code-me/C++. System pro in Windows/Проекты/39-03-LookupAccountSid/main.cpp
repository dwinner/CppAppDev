#ifndef UNICODE
#define UNICODE
#endif

#include <stdio.h>
#include <windows.h> 
#include <lm.h>

int main()
{
  wchar_t user_name[UNLEN];    // ��� ������������

  HANDLE  hProcess;        // ���������� ��������
  HANDLE  hTokenHandle;    // ���������� ������� �������

  DWORD  dwErrCode;        // ��� ��������

  TOKEN_OWNER  *lpTokenOwner = NULL;    // ����� ��� ����������
  DWORD  dwLength= 0;      // ����� ������

  DWORD  dwLengthOfUserName = UNLEN;   // ����� ����� ������� ������ 
  DWORD  dwLengthOfDomainName = 0;     // ����� ����� ������
  LPTSTR  lpDomainName = NULL;         // ��������� �� ��� ������
  SID_NAME_USE type_of_SID;            // ��� ������� ������

  // �������� ������ ������� ��������
  hProcess = GetCurrentProcess();
  // �������� ������ ������� ��������
  if (!OpenProcessToken(
    hProcess,        // ���������� ��������
    TOKEN_QUERY,     // ������ ���������� �� �������
    &hTokenHandle))  // ���������� �������
  {
    dwErrCode = GetLastError();
    printf( "Open process token failed: %u\n", dwErrCode);

    return dwErrCode;
  }
  // ���������� ����� SID
  if (!GetTokenInformation(
    hTokenHandle,  // ���������� ������� �������  
    TokenOwner,    // �������� SID ���������
    NULL,          // ����� ����� ������
    0,             // ���� ����� ����� 0
    &dwLength))    // ��� ����� ������
  {
    dwErrCode = GetLastError();
    if (dwErrCode == ERROR_INSUFFICIENT_BUFFER)
      // ����������� ������ ��� SID
      lpTokenOwner = (TOKEN_OWNER*)new char[dwLength];
    else
    {
      // ������� �� ���������
      printf( "Get token information for length failed: %u\n", 
         dwErrCode);
      return dwErrCode;
    }
  }

  // ���������� ��� ���������
  if (!GetTokenInformation(
    hTokenHandle,  // ���������� ������� �������
    TokenOwner,    // ����� SID ������� �������
    lpTokenOwner,  // ����� ������ ��� SID
    dwLength,      // ����� ������
    &dwLength))    // ����� ������
  {
    dwErrCode = GetLastError();
    printf( "Get token information failed: %u\n", dwErrCode);

    return dwErrCode;
  }

  // ���������� ����� ����� ������
  if(!LookupAccountSid(
    NULL,                  // ���� �� ��������� ����������
    lpTokenOwner->Owner,   // ��������� �� SID
    user_name,             // ��� ������������
    &dwLengthOfUserName,    // ����� ����� ������������
    lpDomainName,          // ���������� ��� ������
    &dwLengthOfDomainName, // ����� ����� ������
    &type_of_SID))         // ��� ������� ������
  {
    dwErrCode = GetLastError();

    if (dwErrCode == ERROR_INSUFFICIENT_BUFFER)
        // ������������ ������ ��� ��� ������
        lpDomainName = (LPTSTR) new wchar_t[dwLengthOfDomainName];
    else
    {
      printf("Lookup account SID for length failed.\n");
      printf("Error code: %d\n", dwErrCode);

      return dwErrCode;
    }
  }

  // ���������� ��� ������� ������ �� SID
  if(!LookupAccountSid(
    NULL,                  // ���� �� ��������� ����������
    lpTokenOwner->Owner,   // ��������� �� SID
    user_name,             // ��� ������������
    &dwLengthOfUserName,   // ����� ����� ������������
    lpDomainName,          // ���������� ��� ������
    &dwLengthOfDomainName, // ����� ����� ������
    &type_of_SID))         // ��� ������� ������
  {
    dwErrCode = GetLastError();

    printf("Lookup account SID failed.\n");
    printf("Error code: %d\n", dwErrCode);

    return dwErrCode;
  }

  wprintf(L"User name: %s\n", user_name);    
  wprintf(L"Domain name: %s\n", lpDomainName);    

  // ����������� ������
  delete[] lpDomainName;
  delete[] lpTokenOwner;

  return 0;
}