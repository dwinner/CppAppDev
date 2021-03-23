#define _WIN32_WINNT 0x0500

#include <stdio.h>
#include <windows.h> 
#include <lm.h>
#include <aclapi.h>
#include <sddl.h>

int main()
{
  char chFileName[256];      // ��� �����

  PSECURITY_DESCRIPTOR pSecurityDescriptor;    // ��������� �� SD
  LPSTR StringSecurityDescriptor;              // ������ � SD
  DWORD StringSecurityDescriptorLen;           // ����� ������ � SD

  DWORD dwRetCode;        // ��� ��������

  // ������ ��� �����, ��������: C:\\test.txt
  printf("Input a full path to your file: ");
  gets(chFileName);

  // �������� ���������� ������������ �����
  dwRetCode = GetNamedSecurityInfo(
    chFileName,        // ��� �����
    SE_FILE_OBJECT,    // ������ ����
    DACL_SECURITY_INFORMATION,  // ������ ������ DACL
    NULL,        // ��������� �� ��������� �� �����
    NULL,        // ��������� �� ��������� ������ �� �����
    NULL,        // ��������� �� DACL �� �����
    NULL,        // ��������� �� SACL �� �����
    &pSecurityDescriptor);   // ����� ��������� �� SD
  if (dwRetCode != ERROR_SUCCESS)
  {
    printf("Get named security info failed.\n");
    printf("Error code: %u\n", dwRetCode);

    return dwRetCode;
  }

  // ����������� ���������� ������������ � ������
  if(!ConvertSecurityDescriptorToStringSecurityDescriptor(
    pSecurityDescriptor,       // ����� ����������� ������������
    SDDL_REVISION_1,           // ������ ����� ��������
    OWNER_SECURITY_INFORMATION | GROUP_SECURITY_INFORMATION | 
    DACL_SECURITY_INFORMATION | SACL_SECURITY_INFORMATION,
    &StringSecurityDescriptor,       // ����� ��� ������
    &StringSecurityDescriptorLen))   // ����� ������
  {
    dwRetCode = GetLastError();
    printf("Convert security descriptor to string security descriptor failed.");
    printf("Error code: %u\n", dwRetCode);

    return dwRetCode;
  }

  printf("String security descriptor length: %u\n", 
  StringSecurityDescriptorLen);
  printf("String security desriptor: %s\n", StringSecurityDescriptor);
  
  // ����������� ������
  LocalFree(pSecurityDescriptor);
  LocalFree(StringSecurityDescriptor);

  return 0;
}