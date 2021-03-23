#define _WIN32_WINNT 0x0500

#include <stdio.h>
#include <windows.h> 
#include <aclapi.h>
#include <sddl.h>

int main()
{
  TRUSTEE Trustee;   // ���������� �� ������� ������
  // ������������� ������� ������
  SID_IDENTIFIER_AUTHORITY sia = SECURITY_WORLD_SID_AUTHORITY;
  // ������������� ������������� ������� ������
  DWORD dwSubAuthority = SECURITY_WORLD_RID;
  PSID lpSid = NULL;           // ��������� �� SID
  LPTSTR lpStringSid = NULL;   // ��������� �� ������ � SID

  // ������� SID for Everyone
  if(!AllocateAndInitializeSid(
      &sia,  // ����� �������������� ������� ������
      1,     // ���������� ������������� ��������������� ������� ������
      dwSubAuthority,        // ������ RID
      0, 0, 0, 0, 0, 0, 0,   // ��������� RID ����� 0
      &lpSid) )
  {
    DWORD dwRetCode = GetLastError();
    printf( "Allocate and initialize sid failed %u\n", dwRetCode);

    return dwRetCode;
  }

  // ������ ��������� TRUSTEE �� �������������� ������������
  BuildTrusteeWithSid(&Trustee, lpSid);

  // ��������� �������� �����
  if (Trustee.pMultipleTrustee == NULL)
    printf("Server trustee: NULL\n");

  if (Trustee.MultipleTrusteeOperation == NO_MULTIPLE_TRUSTEE)
    printf("Multiple trustee: NO_MULTIPLE_TRUSTEE\n");

  if (Trustee.TrusteeForm == TRUSTEE_IS_SID)
    printf("Trustee form: TRUSTEE_IS_SID\n");

  if (Trustee.TrusteeType == TRUSTEE_IS_UNKNOWN)
    printf("Trustee type: TRUSTEE_IS_UNKNOWN\n");

  // ����������� SID � ������
  if (!ConvertSidToStringSid(Trustee.ptstrName, &lpStringSid))
  {
    printf("Convert SID to string SID failed.");

    return GetLastError();
  }
  // ������������� SID
  printf("SID: %s\n", lpStringSid);

  // ����������� SID
  FreeSid(lpSid);

  return 0;
}