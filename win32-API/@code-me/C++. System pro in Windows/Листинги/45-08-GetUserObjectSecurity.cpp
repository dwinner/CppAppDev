#include <windows.h>
#include <stdio.h>

int main()
{
  HWINSTA hWindow = NULL;      // ���������� ����
  
  DWORD dwLengthOfSd = 0;      // ����� SD
  SECURITY_DESCRIPTOR *lpSd = NULL;  // ���������� ������������ ��������

  // �������� ���������� � ��������� ����
  SECURITY_INFORMATION si = OWNER_SECURITY_INFORMATION;
  
  PSID lpOwner;    // ��������� �� SID ���������
  BOOL bOwnerDefaulted = FALSE;      // ������� ��������� �� ���������
  
  DWORD  dwLengthOfUserName = 0;     // ����� ����� ������� ������ 
  DWORD  dwLengthOfDomainName = 0;   // ����� ����� ������
  
  LPTSTR  lpUserName = NULL;         // ��������� �� ��� ������
  LPTSTR  lpDomainName = NULL;       // ��������� �� ��� ������
  
  SID_NAME_USE type_of_SID;          // ��� ������� ������
  
  DWORD dwRetCode;   // ��� ��������

  // �������� ���������� ������� ����
  hWindow = GetProcessWindowStation();
  
  // ���������� ����� ������������� ������������ ����
  if (!GetUserObjectSecurity(
    hWindow,         // ���������� ������� ����
    &si,             // �������� ��������� ����
    lpSd,            // ����� SD
    dwLengthOfSd,    // ���������� �����
    &dwLengthOfSd))  // ��������� ����� ������
  {
    dwRetCode = GetLastError();

    if (dwRetCode == ERROR_INSUFFICIENT_BUFFER)
      // ����������� ������ ��� ���������� ������������
      lpSd = (SECURITY_DESCRIPTOR*)new char[dwLengthOfSd];
    else
    {
      printf("GetUserObjectSecurity for length failed.\n");
      printf("The last error code: %u\n", dwRetCode);

      return dwRetCode;
    }
  }
  
  // ������ ������������� ������������ ����
  if (!GetUserObjectSecurity(
    hWindow,         // ���������� ������� ����
    &si,             // �������� ��������� ����
    lpSd,            // ����� SD
    dwLengthOfSd,    // ���������� �����
    &dwLengthOfSd))  // ��������� ����� ������
  {
    dwRetCode = GetLastError();

    printf("GetUserObjectSecurity failed.\n");
    printf("The last error code: %u\n", dwRetCode);
    
    return dwRetCode;
  }
  
  // �������� SID ��������� ����
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
    NULL,              // ���� �� ��������� ����������
    lpOwner,           // ��������� �� SID
    lpUserName,        // ��� ������������
    &dwLengthOfUserName,     // ����� ����� ������������
    lpDomainName,      // ���������� ��� ������
    &dwLengthOfDomainName,   // ����� ����� ������
    &type_of_SID))     // ��� ������� ������
  {
    dwRetCode = GetLastError();
    
    if (dwRetCode == ERROR_INSUFFICIENT_BUFFER)
    {
      // ������������ ������ ��� ��� ������������ � ��� ������
      lpUserName = (LPTSTR) new char[dwLengthOfUserName];
      lpDomainName = (LPTSTR) new char[dwLengthOfDomainName];
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
    NULL,              // ���� �� ��������� ����������
    lpOwner,           // ��������� �� SID ������������
    lpUserName,        // ��� ������������
    &dwLengthOfUserName,     // ����� ����� ������������
    lpDomainName,      // ���������� ��� ������
    &dwLengthOfDomainName,   // ����� ����� ������
    &type_of_SID))     // ��� ������� ������
  {
    dwRetCode = GetLastError();
    
    printf("Lookup account SID failed.\n");
    printf("Error code: %d\n", dwRetCode);
    
    return dwRetCode;
  }
  
  printf("Key owner name: %s\n", lpUserName);
  printf("Key owner domain name: %s\n", lpDomainName);
  
  // ����������� ������
  delete[] lpUserName;
  delete[] lpDomainName;
  delete[] lpSd;
  
  return 0;
}