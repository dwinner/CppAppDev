#define _WIN32_WINNT 0x0500

#include <windows.h>
#include <stdio.h>
#include <sddl.h>

int main()
{
  char chDirName[248];   // ��� �����
  
  PSECURITY_DESCRIPTOR lpSd = NULL;  // ��������� �� SD
  
  PACL lpDacl = NULL;    // ��������� �� ������ ���������� ��������
  BOOL bDaclPresent;     // ������� ����������� ������ DACL
  BOOL bDaclDefaulted;   // ������� ������ DACL �� ���������
  
  void *lpAce = NULL;    // ��������� �� ������� ������
  LPTSTR StringSid;      // ��������� �� ������ SID
  
  DWORD dwLength;        // ����� ����������� ������������
  DWORD dwRetCode;       // ��� ��������
  
  // ������ ��� �����
  printf("Input a directory or file name: ");
  gets(chDirName);
  
  // �������� ����� ����������� ������������
  if (!GetFileSecurity(
    chDirName,     // ��� �����
    DACL_SECURITY_INFORMATION,   // �������� DACL
    lpSd,          // ����� ����������� ������������
    0,             // ���������� ����� ������
    &dwLength))    // ����� ��� ��������� �����
  {
    dwRetCode = GetLastError();
    
    if (dwRetCode == ERROR_INSUFFICIENT_BUFFER)
      // ������������ ������ ��� ������
      lpSd = (SECURITY_DESCRIPTOR*) new char[dwLength];
    else
    {
      // ������� �� ���������
      printf("Get file security failed.\n");
      printf("Error code: %d\n", dwRetCode);
      
      return dwRetCode;
    }
  }
  
  // ������������ ������ ��� ����������� ������������
  lpSd = (PSECURITY_DESCRIPTOR) new char[dwLength];
  
  // ������ ���������� ������������
  if (!GetFileSecurity(
    chDirName,     // ��� �����
    DACL_SECURITY_INFORMATION,   // �������� DACL
    lpSd,          // ����� ����������� ������������
    dwLength,      // ����� ������
    &dwLength))    // ����� ��� ��������� �����
  {
    dwRetCode = GetLastError();
    printf("Get file security failed.\n");
    printf("Error code: %d\n", dwRetCode);
    
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
    printf("Dacl is not present.");

    return 0;
  }

  // �������� ���������� ���������
  printf("Ace count: %u\n", lpDacl->AceCount);
  
  // �������� �������� ������ DACL
  for (unsigned i = 0; i < lpDacl->AceCount; ++i)
  {
    if (!GetAce(
      lpDacl,  // ����� DACL
      i,       // ������ ��������
      &lpAce)) // ��������� �� ������� ������
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
      printf("%s\n", StringSid);
      LocalFree(StringSid);
    }
    if (((ACE_HEADER*)lpAce)->AceType == ACCESS_DENIED_ACE_TYPE)
    {
      printf("ACCESS_DENIED_ACE_TYPE\n");
      // ����������� SID � ������
      if (!ConvertSidToStringSid(
        &((ACCESS_DENIED_ACE*)lpAce)->SidStart,
        &StringSid))
      {
        dwRetCode = GetLastError();
        printf("Convert sid to string sid failed.\n");
        printf("Error code: %d\n", dwRetCode);
        
        return dwRetCode;
      }
      
      printf("%s\n", StringSid);
      LocalFree(StringSid);
    }
  }
  
  // ����������� ������
  delete[] lpSd;
  
  return 0;
}