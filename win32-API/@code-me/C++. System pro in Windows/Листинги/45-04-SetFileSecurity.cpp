#ifndef UNICODE
#define UNICODE
#endif

#include <windows.h>
#include <stdio.h>
#include <lm.h>

int main()
{
  wchar_t wchDirName[248];       // ��� ��������
  wchar_t wchUserName[UNLEN];    // ��� ������������
  
  ACL *lpOldDacl;    // ��������� �� ������ DACL
  ACL *lpNewDacl;    // ��������� �� ����� DACL
  LPVOID lpAce;      // ��������� �� ������� ACE
  
  DWORD dwDaclLength = 0;        // ����� DACL
  DWORD dwSdLength = 0;          // ����� SD
  DWORD dwSidLength = 0;         // ����� SID
  DWORD dwLengthOfDomainName = 0;    // ����� ����� ������
  
  PSID lpSid = NULL;             // ��������� �� ����������� SID
  LPTSTR lpDomainName = NULL;    // ��������� �� ��� ������
  
  SID_NAME_USE typeOfSid;        // ��� ������� ������
  
  SECURITY_DESCRIPTOR *lpSd = NULL;  // ����� ����������� ������������
  SECURITY_DESCRIPTOR sdAbsoluteSd;  // ���������� ������ SD
  BOOL bDaclPresent;             // ������� ����������� ������ DACL
  BOOL bDaclDefaulted;           // ������� ������ DACL �� ���������
  
  DWORD dwRetCode;   // ��� ��������

  // ������ ��� ����� ��� ��������
  printf("Input a file or directory name: ");
  _getws(wchDirName);
  
  // �������� ����� ����������� ������������
  if (!GetFileSecurity(
    wchDirName,    // ��� �����
    DACL_SECURITY_INFORMATION,   // �������� DACL
    lpSd,          // ����� ����������� ������������
    0,             // ���������� ����� ������
    &dwSdLength))  // ����� ��� ��������� �����
  {
    dwRetCode = GetLastError();
    
    if (dwRetCode == ERROR_INSUFFICIENT_BUFFER)
      // ������������ ������ ��� ������
      lpSd = (SECURITY_DESCRIPTOR*) new char[dwSdLength];
    else
    {
      // ������� �� ���������
      printf("Get file security failed.\n");
      printf("Error code: %d\n", dwRetCode);
      
      return dwRetCode;
    }
  }

  // ������ ���������� ������������
  if (!GetFileSecurity(
    wchDirName,    // ��� �����
    DACL_SECURITY_INFORMATION,   // �������� DACL
    lpSd,          // ����� ����������� ������������
    dwSdLength,    // ����� ������
    &dwSdLength))  // ����� ��� ��������� �����
  {
    dwRetCode = GetLastError();
    printf("Get file security failed.\n");
    printf("Error code: %d\n", dwRetCode);
    
    return dwRetCode;
  }
  
  // ������ ��� ������������, �������� ��������� � DACL
  printf("Input a user name: ");
  _getws(wchUserName);
  
  // ���������� ����� SID ������������
  if (!LookupAccountName(
    NULL,          // ���� ��� �� ��������� ����������
    wchUserName,   // ��� ������������
    NULL,          // ���������� ����� SID
    &dwSidLength,  // ����� SID
    NULL,          // ���������� ��� ������
    &dwLengthOfDomainName,     // ����� ����� ������
    &typeOfSid))   // ��� ������� ������
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
      printf("Lookup account name failed.\n");
      printf("Error code: %d\n", dwRetCode);
      
      return dwRetCode;
    }
  }
  
  // ���������� SID
  if(!LookupAccountName(
    NULL,          // ���� ��� �� ��������� ����������
    wchUserName,   // ��� ������������
    lpSid,         // ��������� �� SID
    &dwSidLength,  // ����� SID
    lpDomainName,  // ��������� �� ��� ������
    &dwLengthOfDomainName,   // ����� ����� ������
    &typeOfSid))   // ��� ������� ������
  {
    dwRetCode = GetLastError();
    
    printf("Lookup account name failed.\n");
    printf("Error code: %d\n", dwRetCode);
    
    return dwRetCode;
  }

  // �������� ������ DACL �� ����������� ������������
  if (!GetSecurityDescriptorDacl(
    lpSd,              // ����� ����������� ������������
    &bDaclPresent,     // ������� ����������� ������ DACL
    &lpOldDacl,        // ����� ��������� �� DACL
    &bDaclDefaulted))  // ������� ������ DACL �� ���������
  {
    dwRetCode = GetLastError();
    printf("Get security descriptor DACL failed.\n");
    printf("Error code: %d\n", dwRetCode);
    
    return dwRetCode;
  }

  // ���������� ����� ������ DACL
  dwDaclLength = lpOldDacl->AclSize + 
    sizeof(ACCESS_ALLOWED_ACE) - sizeof(DWORD) + dwSidLength;

  // ������������ ������ ��� ����� DACL
  lpNewDacl = (ACL*)new char[dwDaclLength];

  // �������������� ����� DACL
  if (!InitializeAcl(
    lpNewDacl,       // ����� DACL
    dwDaclLength,    // ����� DACL
    ACL_REVISION))   // ������ DACL
  {
    dwRetCode = GetLastError();
    
    printf("Lookup account name failed.\n");
    printf("Error code: %d\n", dwRetCode);
    
    return dwRetCode;
  }

  // ��������� ������ ������� � ����� DACL
  if (!AddAccessDeniedAce(
    lpNewDacl,       // ����� DACL
    ACL_REVISION,    // ������ DACL
    FILE_WRITE_ATTRIBUTES,  // ��������� ������ ��������
    lpSid))          // ����� SID
  {
    dwRetCode = GetLastError();
    perror("Add access allowed ace failed.\n");
    printf("The last error code: %u\n", dwRetCode);
    
    return dwRetCode;
  }

  // �������� ����� ������� ACE � ������ ������ DACL
  if (!GetAce(
    lpOldDacl,     // ����� ������� DACL
    0,             // ���� ������ �������
    &lpAce))       // ����� ������� ��������
  {
    dwRetCode = GetLastError();
    
    printf("Get ace failed.\n");
    printf("Error code: %d\n", dwRetCode);
    
    return dwRetCode;
  }

  // ������������ �������� �� ������� DACL � ����� DACL
  if (bDaclPresent)
  {
    if (!AddAce(
      lpNewDacl,       // ����� ������ DACL
      ACL_REVISION,    // ������ DACL
      MAXDWORD,        // ��������� � ����� ������
      lpAce,           // ����� ������� DACL
      lpOldDacl->AclSize - sizeof(ACL)))  // ����� ������� DACL
    {
      dwRetCode = GetLastError();
      perror("Add access allowed ace failed.\n");
      printf("The last error code: %u\n", dwRetCode);
      
      return dwRetCode;
    }
  }

  // ��������� ������������� DACL
  if (!IsValidAcl(lpNewDacl))
  {
    dwRetCode = GetLastError();
    perror("The new ACL is invalid.\n");
    printf("The last error code: %u\n", dwRetCode);
    
    return dwRetCode;
  }

  // ������� ����� ���������� ������������ � ���������� �����
  if (!InitializeSecurityDescriptor(
    &sdAbsoluteSd,       // ����� ��������� SD
    SECURITY_DESCRIPTOR_REVISION))
  {
    dwRetCode = GetLastError();
    perror("Initialize security descriptor failed.\n");
    printf("The last error code: %u\n", dwRetCode);
    
    return dwRetCode;
  }

  // ������������� DACL  � ����� ���������� ������������
  if (!SetSecurityDescriptorDacl(
    &sdAbsoluteSd,   // ����� ����������� ������������
    TRUE,            // DACL ������������
    lpNewDacl,       // ��������� �� DACL
    FALSE))          // DACL �� ����� �� ���������
  {
    dwRetCode = GetLastError();
    perror("Set security descriptor DACL failed.\n");
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
    wchDirName,        // ��� �����
    DACL_SECURITY_INFORMATION,     // ������������� DACL
    &sdAbsoluteSd))    // ����� ����������� ������������
  {
    dwRetCode = GetLastError();
    printf("Set file security failed.\n");
    printf("Error code: %d\n", dwRetCode);
    
    return dwRetCode;
  }
  
  // ����������� ������
  delete[] lpSd;
  delete[] lpSid;
  delete[] lpDomainName;
  delete[] lpNewDacl;

  return 0;
}