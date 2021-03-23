#define _WIN32_WINNT 0x0500

#ifndef UNICODE
#define UNICODE
#endif

#include <windows.h>
#include <stdio.h>
#include <aclapi.h>
#include <sddl.h>

int main()
{
  wchar_t wchDirName[248];   // ��� ��������

  PSECURITY_DESCRIPTOR lpSd; // ��������� �� ���������� ������������
  PACL lpDacl;               // ��������� �� ������ DACL
  PEXPLICIT_ACCESS lpEa;     // ��������� �� ������ ��������� ���� 
                             // EXPLICIT_ACCESS
  ULONG ulCount;     // ���������� ��������� � �������

  LPTSTR  lpStringSid = NULL;    // ��������� �� ������ � SID

  DWORD dwErrCode;   // ��� ��������

  // ������ ��� �����
  printf("Input a file name: ");
  wscanf(L"%s", wchDirName);     // ������ ��� �����

  // �������� SD ����� �����
  dwErrCode = GetNamedSecurityInfo(
    wchDirName,      // ��� �����
    SE_FILE_OBJECT,  // ������ ����
    DACL_SECURITY_INFORMATION,   // �������� DACL
    NULL,          // ����� ��������� �� SID ���������
    NULL,          // ����� ��������� �� ��������� ������
    &lpDacl,       // ��������� �� DACL
    NULL,          // ��������� �� SACL �� �����
    &lpSd);        // ����� ��������� �� ���������� ������������
  if (dwErrCode != ERROR_SUCCESS)
  {
    printf("Get named security info failed.\n");
    printf("Error code: %u\n", dwErrCode);

    return dwErrCode;
  }
  // ������ �������� �� ������ DACL
  dwErrCode = GetExplicitEntriesFromAcl(
    lpDacl,      // ����� ������ DACL
    &ulCount,    // ����� ��� ���������� ���������
    &lpEa);      // ����� ��������� �� �����
  if (dwErrCode != ERROR_SUCCESS)
  {
    printf("Get explicit entries from ACL failed.\n");
    printf("Error code: %u\n", dwErrCode);

    return dwErrCode;
  }

  printf("Number of elements in DACL = %u\n", ulCount);

  // �������� ���������� �� �������� ���� TRUSTEE
  for (unsigned i = 0; i < ulCount; ++i)
  {
    if (GetTrusteeForm(&(lpEa->Trustee)) == TRUSTEE_IS_NAME)
      wprintf(L"Trustee name: %s", GetTrusteeName(&(lpEa->Trustee)));
    if (GetTrusteeForm(&(lpEa->Trustee)) == TRUSTEE_IS_SID)
    {
      // ����������� SID � ������
      if (!ConvertSidToStringSid(lpEa->Trustee.ptstrName, &lpStringSid))
      {
        printf("Convert SID to string SID failed.");

        return GetLastError();
      }
      // ������������� SID
      wprintf(L"Trustee SID: %s\n", lpStringSid);

      // ����������� ������, ������� �������
      LocalFree(lpStringSid);
    }

    ++lpEa;    // ������������ �� �������
  }

  // ����������� ������
  LocalFree(lpSd);
  LocalFree(lpEa);

  return 0;
}