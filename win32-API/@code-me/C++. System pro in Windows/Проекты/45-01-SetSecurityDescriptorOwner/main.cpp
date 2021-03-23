#ifndef UNICODE
#define UNICODE
#endif

#include <windows.h>
#include <stdio.h>
#include <lm.h>

int main()
{
  wchar_t wchDirName[248];         // ��� ��������
  wchar_t wchUserName[UNLEN];      // ��� ������������
  
  DWORD dwSdLength = 0;            // ����� SD
  DWORD dwSidLength = 0;           // ����� SID
  DWORD dwLengthOfDomainName = 0;  // ����� ����� ������
  
  PSID lpSid = NULL;               // ��������� �� SID ������ ���������
  LPTSTR lpDomainName = NULL;      // ��������� �� ��� ������
  
  SID_NAME_USE typeOfSid;          // ��� ������� ������
  
  SECURITY_DESCRIPTOR sdAbsoluteSd;  // ���������� ������ ����������� ������������

  DWORD dwRetCode;     // ��� ��������

  // ������ ��� ����� ��� ��������
  printf("Input a file or directory name: ");
  _getws(wchDirName);

  // ������ ��� ������������, ������� ����� ����� ���������� �����
  printf("Input a user name: ");
  _getws(wchUserName);
  
  // ���������� ����� SID ������������
  if (!LookupAccountName(
    NULL,            // ���� ��� �� ��������� ����������
    wchUserName,     // ��� ������������
    NULL,            // ���������� ����� SID
    &dwSidLength,    // ����� SID
    NULL,            // ���������� ��� ������
    &dwLengthOfDomainName,   // ����� ����� ������
    &typeOfSid))     // ��� ������� ������
  {
    dwRetCode = GetLastError();
    
    if (dwRetCode == ERROR_INSUFFICIENT_BUFFER)
    {
      // ������������ ������ ��� SID
      lpSid = (SID*) new char[dwSidLength];
      lpDomainName = (LPTSTR) new wchar_t[dwLengthOfDomainName];
    }
    else
    {
      // ������� �� ���������
      printf("Lookup account name length failed.\n");
      printf("Error code: %d\n", dwRetCode);
      
      return dwRetCode;
    }
  }
  
  // ���������� SID
  if(!LookupAccountName(
    NULL,              // ���� ��� �� ��������� ����������
    wchUserName,       // ��� ������������
    lpSid,             // ��������� �� SID
    &dwSidLength,      // ����� SID
    lpDomainName,      // ��������� �� ��� ������
    &dwLengthOfDomainName,   // ����� ����� ������
    &typeOfSid))       // ��� ������� ������
  {
    dwRetCode = GetLastError();
    
    printf("Lookup account name failed.\n");
    printf("Error code: %d\n", dwRetCode);
    
    return dwRetCode;
  }

  // ������� ���������� ������������
  if (!InitializeSecurityDescriptor(
    &sdAbsoluteSd,     // ����� ��������� SD
    SECURITY_DESCRIPTOR_REVISION))
  {
    dwRetCode = GetLastError();
    perror("Initialize security descriptor failed.\n");
    printf("The last error code: %u\n", dwRetCode);
    
    return dwRetCode;
  }

  // ������������� ������ ��������� � ���������� ������������
  if (!SetSecurityDescriptorOwner(
    &sdAbsoluteSd,     // ����� ����������� ������������
    lpSid,             // ��������� �� SID
    FALSE))            // SID �� ����� �� ���������
  {
    dwRetCode = GetLastError();
    perror("Set security descriptor owner failed.\n");
    printf("The last error code: %u\n", dwRetCode);
    
    return dwRetCode;
  }
  
  // ��������� ��������� ����������� ������������
  if (!IsValidSecurityDescriptor(&sdAbsoluteSd))
  {
    dwRetCode = GetLastError();
    perror("Security descriptor is invalid.\n");
    printf("The last error code: %u\n", dwRetCode);
    
    return dwRetCode;
  }
  // ������������� ����� ���������� ������������
  if (!SetFileSecurity(
    wchDirName,          // ��� �����
    OWNER_SECURITY_INFORMATION,  // ������������� SID
    &sdAbsoluteSd))      // ����� ����������� ������������
  {
    dwRetCode = GetLastError();

    if (dwRetCode == ERROR_INVALID_OWNER)
      printf("The user can not be the owner of the file.\n");  

    printf("Set file security failed.\n");
    printf("Error code: %d\n", dwRetCode);
    
    return dwRetCode;
  }
  
  // ����������� ������
  delete[] lpSid;
  delete[] lpDomainName;

  return 0;
}