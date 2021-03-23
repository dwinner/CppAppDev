#define _WIN32_WINNT 0x0500

#include <windows.h>
#include <stdio.h>
#include <lm.h>
#include <sddl.h>

int main()
{
  HANDLE hMutex;         // ���������� ��������
  HANDLE hProcess;       // ���������� ��������
  HANDLE hTokenHandle;   // ���������� ������� �������
  
  ACL *lpDacl;           // ��������� �� ������ �������
  void *lpAce = NULL;    // ��������� �� ������� ������
  
  BOOL bDaclPresent;     // ������� ����������� ������ DACL
  BOOL bDaclDefaulted;   // ������� ������ DACL �� ���������
  
  char chUserName[UNLEN];  // ��� ������������
  
  DWORD dwLengthOfDomainName = 0;  // ����� ����� ������
  DWORD dwLengthOfSid = 0;   // ����� ������������ SID
  
  DWORD dwDaclLength = 0;    // ����� ������ �������
  DWORD dwRetLength = 0;     // ������������ ����� ������
  
  SID *lpSid = NULL;         // ��������� �� ����������� SID
  LPTSTR lpDomainName = NULL;    // ��������� �� ��� ������
  SID_NAME_USE typeOfSid;    // ��� ������� ������
  
  PSECURITY_DESCRIPTOR lpSd = NULL;  // ��������� �� SD
  DWORD dwLengthOfSd = 0;    // ����� ����������� ������������
  
  LPTSTR StringSid;    // ��������� �� ������ SID
  
  DWORD dwRetCode;     // ��� ��������
  
  // �������� ���������� ��������
  hProcess = GetCurrentProcess();
  
  // ��������� ������ ������� ��������
  if (!OpenProcessToken(
    hProcess,        // ���������� ��������
    TOKEN_QUERY |    // �������� ���������� �� ������� ������� 
    TOKEN_ADJUST_DEFAULT,  // � ���������� ������ DACL ������� �������
    &hTokenHandle))  // ���������� �������
  {
    dwRetCode = GetLastError();
    printf( "Open process token failed: %u\n", dwRetCode);
    
    return dwRetCode;
  }
  
  // ������ ��� ������������, �������� �������� ������ � ��������
  printf("Input a user name: ");
  gets(chUserName);
  
  // ���������� ����� SID ������������
  if (!LookupAccountName(
    NULL,            // ���� ��� �� ��������� ����������
    chUserName,      // ��� ������������
    NULL,            // ���������� ����� SID
    &dwLengthOfSid,  // ����� SID
    NULL,            // ���������� ��� ������
    &dwLengthOfDomainName,   // ����� ����� ������
    &typeOfSid))     // ��� ������� ������
  {
    dwRetCode = GetLastError();
    
    if (dwRetCode == ERROR_INSUFFICIENT_BUFFER)
    {
      // ������������ ������ ��� SID � ����� ������
      lpSid = (SID*) new char[dwLengthOfSid];
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
    chUserName,      // ��� ������������
    lpSid,           // ��������� �� SID
    &dwLengthOfSid,  // ����� SID
    lpDomainName,    // ��������� �� ��� ������
    &dwLengthOfDomainName,   // ����� ����� ������
    &typeOfSid))     // ��� ������� ������
  {
    dwRetCode = GetLastError();
    
    printf("Lookup account name failed.\n");
    printf("Error code: %d\n", dwRetCode);
    
    return dwRetCode;
  }
  
  // ����������� SID � ������
  if (!ConvertSidToStringSid(
    lpSid,
    &StringSid))
  {
    dwRetCode = GetLastError();
    printf("Convert sid to string sid failed.\n");
    printf("Error code: %d\n", dwRetCode);
    
    return dwRetCode;
  }
  // ������� SID
  printf("%s\n",StringSid);
  LocalFree(StringSid);
  
  // ��������� ����� ������ DACL
  dwDaclLength = sizeof(ACL)
    + sizeof(ACCESS_ALLOWED_ACE) 
    - sizeof(DWORD) + dwLengthOfSid;
  
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
  
  // ������������� ����� DACL �� ��������� � ������ �������
  if (!SetTokenInformation(
    hTokenHandle,      // ���������� ������� �������
    TokenDefaultDacl,  // ������������� ������ DACL
    &lpDacl,           // ����� ������ � ����� ������� DACL
    dwDaclLength))     // ������ ������
  {
    dwRetCode = GetLastError();
    printf( "Set token information failed: %u\n", dwRetCode);
    
    return dwRetCode;
  }

  // ������� �������
  hMutex = CreateMutex(NULL, FALSE, "DemoMutex");
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
  
  // ������ ��������� ������ DACL ��������
  
  // ���������� ��������� ����� ������
  if (!GetKernelObjectSecurity(
    hMutex,          // ���������� ��������
    DACL_SECURITY_INFORMATION,   // �������� ������ DACL ��������
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
    DACL_SECURITY_INFORMATION,   // �������� ������ DACL ��������
    lpSd,            // ����� SD
    dwLengthOfSd,    // ����� ������
    &dwLengthOfSd))  // ��������� ����� ������
  {
    dwRetCode = GetLastError();
    printf("Get kernel object security failed.\n");
    printf("The last error code: %u\n", dwRetCode);
    
    return dwRetCode;
  }
  
  // �������� ������ DACL �� ����������� ������������
  if (!GetSecurityDescriptorDacl(
    lpSd,              // ����� ����������� ������������
    &bDaclPresent,     // ������� ����������� ������ DACL
    &lpDacl,           // ����� ��������� �� DACL
    &bDaclDefaulted))  // ������� ������ DACL �� ���������
  {
    dwRetCode = GetLastError();
    printf("Get security descriptor DACL failed.\n");
    printf("Error code: %d\n", dwRetCode);
    
    return dwRetCode;
  }
  
  // ���������, ���� �� DACL
  if (!bDaclPresent)
  {
    printf("Dacl is not present.\n");
    return 0;
  }
  else
    printf("Dacl is present.\n");

  // ���������, ���������� �� DACL �������������
  if (bDaclDefaulted == SE_DACL_DEFAULTED)
    printf("Dacl is defaulted.\n");
  else
    printf("Dacl is not defaulted.\n");

  
  // �������� ���������� ���������
  printf("Ace count: %u\n", lpDacl->AceCount);
  
  // �������� �������� ������ DACL
  for (unsigned i = 0; i < lpDacl->AceCount; ++i)
  {
    if (!GetAce(
      lpDacl,    // ����� DACL
      i,         // ������ ��������
      &lpAce))   // ��������� �� ������� ������
    {
      dwRetCode = GetLastError();
      printf("Get ace failed.\n");
      printf("Error code: %d\n", dwRetCode);
      
      return dwRetCode;
    }
    // ������� �� ������ ��� �������� � SID
    if (((ACE_HEADER*)lpAce)->AceType == ACCESS_ALLOWED_ACE_TYPE)
    {
      printf("ACCESS_ALLOWED_ACE_TYPE\n");
      // ����������� SID � ������
      if (!ConvertSidToStringSid(
        &((ACCESS_ALLOWED_ACE*)lpAce)->SidStart,
        &StringSid))
      {
        dwRetCode = GetLastError();
        printf("Convert sid to string sid failed.\n");
        printf("Error code: %d\n", dwRetCode);
        
        return dwRetCode;
      }
      // �������� SID
      printf("%s\n",StringSid);
      LocalFree(StringSid);
    }
  }
  
  // ����������� ������
  delete[] lpSd;
  
  CloseHandle(hMutex);
  CloseHandle(hTokenHandle);
  
  return 0;
}