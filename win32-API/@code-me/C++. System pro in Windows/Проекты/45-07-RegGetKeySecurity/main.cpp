#include <windows.h>
#include <stdio.h>

int main()
{
  HKEY hKey;       // ���� �������
  
  DWORD dwLengthOfSd = 0;            // ����� SD
  SECURITY_DESCRIPTOR *lpSd = NULL;  // SD ����� �������
  
  PSID lpOwner;    // ��������� �� SID ���������
  BOOL bOwnerDefaulted = FALSE;      // ������� ��������� �� ���������
  
  DWORD  dwLengthOfUserName = 0;     // ����� ����� ������� ������ 
  DWORD  dwLengthOfDomainName = 0;   // ����� ����� ������
  
  LPTSTR  lpUserName = NULL;         // ��������� �� ��� ������
  LPTSTR  lpDomainName = NULL;       // ��������� �� ��� ������
  
  SID_NAME_USE type_of_SID;          // ��� ������� ������
  
  DWORD dwRetCode;     // ��� ��������
  
  // ��������� ���� ��������
  dwRetCode = RegOpenKeyEx(
    HKEY_LOCAL_MACHINE,    // ��������� ������
    NULL,                  // ������� ���� ��������� ������
    0,                     // ���������������
    KEY_QUERY_VALUE,       // �������� ������ �� �����
    &hKey);                // ����� ����������� �����
  if (dwRetCode != ERROR_SUCCESS)
  {
    dwRetCode = GetLastError();
    printf("RegOpenKeyEx failed.\n");
    printf("The last error code: %u\n", dwRetCode);
    
    return dwRetCode;
  }
  
  // ���������� ����� ������������� ������������ �������
  dwRetCode = RegGetKeySecurity(
    hKey,            // ���������� �������
    OWNER_SECURITY_INFORMATION,  // �������� ��������� ����� �������
    lpSd,            // ����� SD
    &dwLengthOfSd);  // ��������� ����� ������
  if (dwRetCode == ERROR_INSUFFICIENT_BUFFER)
    // ����������� ������ ��� ���������� ������������
    lpSd = (SECURITY_DESCRIPTOR*)new char[dwLengthOfSd];
  else
  {
    printf("RegGetKeySecurity failed.\n");
    printf("The last error code: %u\n", dwRetCode);
    
    return dwRetCode;
  }
  
  // ������ ������������� ������������ ����� �������
  dwRetCode = RegGetKeySecurity(
    hKey,            // ���������� �������
    OWNER_SECURITY_INFORMATION,  // �������� ��������� ����� �������
    lpSd,            // ����� SD
    &dwLengthOfSd);  // ��������� ����� ������
  if (dwRetCode != ERROR_SUCCESS)
  {
    printf("RegGetKeySecurity failed.\n");
    printf("The last error code: %u\n", dwRetCode);
    
    return dwRetCode;
  }
  
  // �������� SID ��������� ��������
  if (!GetSecurityDescriptorOwner(
    lpSd,          // ����� ����������� ������������
    &lpOwner,      // ����� ��������� �� SID ���������
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
  
  RegCloseKey(hKey);

  return 0;
}