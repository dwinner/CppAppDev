#define _WIN32_WINNT 0x0500

#include <stdio.h>
#include <windows.h> 
#include <lm.h>
#include <aclapi.h>
#include <sddl.h>

int main()
{
  char chFileName[256];  // ��� �����

  PSID  pSidOwner;       // ��������� �� SID ��������� �������
  PSID  pSidGroup;       // ��������� �� SID ��������� ������ �������

  PSECURITY_DESCRIPTOR  pSecurityDescriptor;  // ��������� �� SD

  LPTSTR lpStringSid;    // ��������� �� ������ SID

  DWORD dwRetCode;       // ��� ��������

  // ������ ��� �����, ��������: C:\\test.txt
  printf("Input a full path to your file: ");
  gets(chFileName);

  // �������� ���������� ������������ �����
  dwRetCode = GetNamedSecurityInfo(
    chFileName,          // ��� �����
    SE_FILE_OBJECT,      // ������ ����
    GROUP_SECURITY_INFORMATION | OWNER_SECURITY_INFORMATION,
    &pSidOwner,          // ����� ��������� �� SID ���������
    &pSidGroup,          // ����� ��������� �� ��������� ������
    NULL,                // ��������� �� DACL �� �����
    NULL,                // ��������� �� SACL �� �����
    &pSecurityDescriptor);  // ����� ��������� �� SD
  if (dwRetCode != ERROR_SUCCESS)
  {
    printf("Get named security info failed.\n");
    printf("Error code: %u\n", dwRetCode);

    return dwRetCode;
  }

  // ����������� SID ��������� � ������
  if (!ConvertSidToStringSid(pSidOwner, &lpStringSid))
  {
    printf("Convert SID to string SID failed.");
    dwRetCode = GetLastError();
  
    return dwRetCode;
  }
  // �������� SID ���������
  printf("Owner SID: %s\n", lpStringSid);
  // ����������� ������ ��� ������
  LocalFree(lpStringSid);

  // ����������� SID ��������� ������ � ������
  if (!ConvertSidToStringSid(pSidGroup, &lpStringSid))
  {
    printf("Convert SID to string SID failed.");
    dwRetCode = GetLastError();
  
    return dwRetCode;
  }
  // �������� SID ��������� ������
  printf("Group SID: %s\n", lpStringSid);
  // ����������� ������ ��� ������
  LocalFree(lpStringSid);
  
  // ����������� ������ ��� �����������
  LocalFree(pSecurityDescriptor);

  return 0;
}