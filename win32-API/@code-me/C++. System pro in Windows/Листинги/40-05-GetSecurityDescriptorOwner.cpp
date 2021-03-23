#define _WIN32_WINNT 0x0500

#include <stdio.h>
#include <windows.h> 
#include <sddl.h>

int main()
{
  char chFileName[256];    // ��� �����

  PSID pSidOwner = NULL;   // ��������� �� SID ��������� �������
  PSID pSidGroup = NULL;   // ��������� �� SID ��������� ������ �������
  PSECURITY_DESCRIPTOR pSD = NULL;  // ��������� �� SD
  BOOL bOwnerDefaulted = FALSE;   // ���� ��������� �� ���������
  BOOL bGroupDefaulted = FALSE;   // ���� ��������� ������ �� ���������

  LPTSTR lpStringSid;    // ��������� �� ������ SID

  DWORD dwLength = 0;    // ����� ����������� ������������
  DWORD dwRetCode;       // ��� ��������

  // ������ ��� �����, � �������� �� ������ ������
  printf("Input a full path to your file or directory: ");
  gets(chFileName);

  // �������� ����� ����������� ������������ �����
  if (!GetFileSecurity(
    chFileName,      // ��� �����
    GROUP_SECURITY_INFORMATION | 
    OWNER_SECURITY_INFORMATION,    // ����������, ������� ����� ��������
    pSD,             // ����� ������ ��� ����������� ������������
    dwLength,        // ����� ������
    &dwLength))      // ����������� �����

    if (dwLength != 0)
      // ����������� ������ ��� ����������� ������������
      pSD = (PSECURITY_DESCRIPTOR) new char[dwLength];
    else
    {
      printf("Get file security for length failed.\n");
      dwRetCode = GetLastError();
      printf("Error code: %u\n", dwRetCode);

      return dwRetCode;
    }

  // �������� ���������� ������������ �����
  if (!GetFileSecurity(
    chFileName,      // ��� �����
    GROUP_SECURITY_INFORMATION | 
    OWNER_SECURITY_INFORMATION,    // ����������, ������� ����� ��������
    pSD,             // ����� ������ ��� ����������� ������������
    dwLength,        // ����� ������
    &dwLength))      // ����������� �����
  {
    printf("Get file security failed.\n");
    dwRetCode = GetLastError();
    printf("Error code: %u\n", dwRetCode);

    return dwRetCode;
  }

  // �������� ������������� ������������ ��������� �������
  if (!GetSecurityDescriptorOwner(
    pSD,
    &pSidOwner,
    &bOwnerDefaulted))
  {
    printf("Get security descriptor owner failed.\n");
    dwRetCode = GetLastError();
    printf("Error code: %u\n", dwRetCode);

    return dwRetCode;
  }

  // �������� SD ��������� ������ ��������� �������
  if (!GetSecurityDescriptorGroup(
    pSD,
    &pSidGroup,
    &bGroupDefaulted))
  {
    printf("Get security descriptor group failed.\n");
    dwRetCode = GetLastError();
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
  delete[] pSD;

  return 0;
}