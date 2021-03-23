#include <stdio.h>
#include <windows.h> 

int main()
{
  DWORD dwSidLength;   // ����� ������ ��� SID
  SID *pSid = NULL;    // ��������� �� SID

  // ��������� �� ������������� ������������� ������� ������
  DWORD *pSubAuthority = NULL;
  // ������������� ������� ������
  SID_IDENTIFIER_AUTHORITY sia = SECURITY_LOCAL_SID_AUTHORITY;

  // ���������� ����� SID � ����� ������������� ��������������� ������� ������
  dwSidLength = GetSidLengthRequired(1);

  printf("SID length: %u\n", dwSidLength);

  // ����������� ������ ��� SID
  pSid = (SID*) new UCHAR[dwSidLength];

  // �������������� SID
  if(!InitializeSid(
    pSid,    // ��������� �� SID
    &sia,    // ������������� ������� ������
    1))      // ���������� ������������� ���������������
  {
    printf( "Initialized SID failed.\n");
    return 1;
  }
  printf("SID is initialized.\n");

  // ���������� ��������� �� ������������� �������������
  pSubAuthority = GetSidSubAuthority(pSid, 0);
  // ������������� �������� �������������� ��������������
  *pSubAuthority = SECURITY_LOCAL_RID;

  // ��������� ������������� SID
  if(!IsValidSid(pSid))
  {
    printf( "The SID is not valid.\n");
    return 1;
  }

  printf("The SID is valid.\n");

  // ����������� SID
  delete[] pSid;
  
  return 0;
}