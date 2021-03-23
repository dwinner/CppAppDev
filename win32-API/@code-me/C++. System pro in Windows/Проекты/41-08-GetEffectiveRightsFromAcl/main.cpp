#define _WIN32_WINNT 0x0500

#ifndef UNICODE
#define UNICODE
#endif

#include <windows.h>
#include <stdio.h>
#include <lm.h>
#include <aclapi.h>

int main()
{
  TRUSTEE  Trustee;            // ���������� �� ������� ������
  wchar_t wchFileName[248];    // ��� ����� ��� ��������
  wchar_t wchAccountName[UNLEN + 255];   // ��� ������� ������

  PSECURITY_DESCRIPTOR lpSd;   // ��������� �� ���������� ������������
  PACL lpDacl;                 // ��������� �� ������ DACL

  ACCESS_MASK dwAccessRights = 0;  // ����� �������
  DWORD dwErrCode;      // ��� ��������

  // ������ ��� �����
  printf("Input a file name: ");
  wscanf(L"%s", wchFileName);      // ������ ��� ����� ��� ��������

  // �������� SD ����� �����
  dwErrCode = GetNamedSecurityInfo(
    wchFileName,     // ��� �����
    SE_FILE_OBJECT,  // ������ ����
    DACL_SECURITY_INFORMATION,   // �������� DACL
    NULL,        // ����� ��������� �� SID ���������
    NULL,        // ����� ��������� �� ��������� ������
    &lpDacl,     // ��������� �� DACL
    NULL,        // ��������� �� SACL �� �����
    &lpSd);      // ����� ��������� �� ���������� ������������
  if (dwErrCode != ERROR_SUCCESS)
  {
    printf("Get named security info failed.\n");
    printf("Error code: %u\n", dwErrCode);

    return dwErrCode;
  }

  // ������ ��� ������ � ������������
  printf("Input domain account (domain_name\\user_name): ");
  wscanf(L"%s", wchAccountName);       // ������ ��� ������� ������

  // ������ ��������� TRUSTEE �� �����
  BuildTrusteeWithName(&Trustee, wchAccountName);

  // �������� ����� ������� ��� ��������� �����
  dwErrCode = GetEffectiveRightsFromAcl(
    lpDacl,      // ��������� �� ������ DACL
    &Trustee,    // ����� ��������� TRUSTEE
    &dwAccessRights);  // ����� ����� � �������
  if (dwErrCode != ERROR_SUCCESS)
  {
    printf("Get effective rights from ACL failed.\n");
    printf("Error code: %u\n", dwErrCode);

    return dwErrCode;
  }

  // ������� �� ������� ����� �������
  printf("ACCESS_MASK: %x\n", dwAccessRights);

  // ���������� ����� �������
  if ((dwAccessRights & SPECIFIC_RIGHTS_ALL) == SPECIFIC_RIGHTS_ALL)
    printf("SPECIFIC_RIGHTS_ALL is set.\n");
  else
    printf("SPECIFIC_RIGHTS_ALL is not set.\n");

  if ((dwAccessRights & STANDARD_RIGHTS_ALL) == STANDARD_RIGHTS_ALL)
    printf("STANDARD_RIGHTS_ALL is set.\n");
  else
    printf("STANDARD_RIGHTS_ALL is not set.\n");

  if ((dwAccessRights & GENERIC_ALL) == GENERIC_ALL)
    printf("GENERIC_ALL is set.\n");
  else
    printf("GENERIC_ALL is not set.\n");

  // ����������� ������
  LocalFree(lpSd);

  return 0;
}