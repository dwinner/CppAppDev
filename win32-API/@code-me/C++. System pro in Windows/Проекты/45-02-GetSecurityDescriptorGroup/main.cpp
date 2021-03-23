#define _WIN32_WINNT 0x0500

#include <windows.h>
#include <stdio.h>
#include <sddl.h>

int main()
{
  char chDirName[248];       // ��� �����
  
  PSECURITY_DESCRIPTOR lpSd = NULL;  // ��������� �� SD
  
  PSID lpGroup;              // ��������� �� SID ��������� ������
  LPTSTR StringSid;          // ��������� �� ������ SID
  BOOL bGroupDefaulted;      // ������� ������ �� ���������
  
  DWORD dwLength;            // ����� ����������� ������������

  DWORD dwRetCode;     // ��� ��������
  
  // ������ ��� �����
  printf("Input a directory or file name: ");
  gets(chDirName);
  
  // �������� ����� ����������� ������������
  if (!GetFileSecurity(
    chDirName,       // ��� �����
    GROUP_SECURITY_INFORMATION,  // �������� SID ��������� ������
    lpSd,            // ����� ����������� ������������
    0,               // ���������� ����� ������
    &dwLength))      // ����� ��� ��������� �����
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
    chDirName,       // ��� �����
    GROUP_SECURITY_INFORMATION,  // �������� SID ��������� ������
    lpSd,            // ����� ����������� ������������
    dwLength,        // ����� ������
    &dwLength))      // ����� ��� ��������� �����
  {
    dwRetCode = GetLastError();
    printf("Get file security failed.\n");
    printf("Error code: %d\n", dwRetCode);
    
    return dwRetCode;
  }
  
  // �������� SID ��������� ������
  if (!GetSecurityDescriptorGroup(
    lpSd,                // ����� ����������� ������������
    &lpGroup,            // ����� ��������� �� SID ��������� ������
    &bGroupDefaulted))   // ������� ��������� ������ �� ���������
  {
    dwRetCode = GetLastError();
    printf("Get security descriptor group failed.\n");
    printf("Error code: %d\n", dwRetCode);
    
    return dwRetCode;
  }

  // ���������, ���� �� ��������� ������
  if (lpGroup == NULL)
  {
    printf("The primary group is not present.\n");

    return 0;
  }
  
  // ����������� SID � ������
  if (!ConvertSidToStringSid(
    lpGroup,       // ��������� �� SID ��������� ������
    &StringSid))   // ������ � SID
  {
    dwRetCode = GetLastError();
    printf("Convert sid to string sid failed.\n");
    printf("Error code: %d\n", dwRetCode);
    
    return dwRetCode;
  }

  printf("%s\n",StringSid);
  
  // ����������� ������
  LocalFree(StringSid);
  delete[] lpSd;
  
  return 0;
}