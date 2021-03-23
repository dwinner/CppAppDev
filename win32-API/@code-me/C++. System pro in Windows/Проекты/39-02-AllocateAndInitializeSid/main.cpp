#include <stdio.h>
#include <windows.h> 

int main()
{
  int n;   // ���������� ���������������
  // ��������� �� ������������� ������� ������
  SID_IDENTIFIER_AUTHORITY *sia;
DWORD dwSubAuthority;    // ������������� ������������� ������� ������
  PSID pSid = NULL;      // ��������� �� SID

  // ���������������� �������������� ������� ������
  SID_IDENTIFIER_AUTHORITY s0 = SECURITY_NULL_SID_AUTHORITY;
  SID_IDENTIFIER_AUTHORITY s1 = SECURITY_WORLD_SID_AUTHORITY;
  SID_IDENTIFIER_AUTHORITY s2 = SECURITY_LOCAL_SID_AUTHORITY;
  SID_IDENTIFIER_AUTHORITY s5 = SECURITY_NT_AUTHORITY;

  // ���� �������������� ������������
  printf("Choose one of the predefined SID.\n");
  printf("Null SID:\t\t0\n");
  printf("World SID:\t\t1\n");
  printf("Local SID:\t\t2\n");
  printf("Anonimous logon SID:\t5\n\n");

  printf("SID = ");

  scanf("%d", &n);     // ������ ������������� ������� ������
  switch (n)
  {
  case 0:
    sia = &s0;
    dwSubAuthority = SECURITY_NULL_RID;
    break;
  case 1:
    sia = &s1;
    dwSubAuthority = SECURITY_NULL_RID;
    break;
  case 2:
    sia = &s2;
    dwSubAuthority = SECURITY_NULL_RID;
    break;
  case 5:
    sia = &s5;
    dwSubAuthority = SECURITY_NULL_RID;
    break;
  default:
    printf("Unknown uiniversal SID.\n");
    return 1;
  }

  // ������� SID
  if(!AllocateAndInitializeSid(
      sia,     // ������������� ������� ������
      1,       // ���������� ������������� ��������������� ������� ������
      dwSubAuthority,        // ������ RID
      0, 0, 0, 0, 0, 0, 0,   // ��������� RID ����� 0
      &pSid) )
  {
    DWORD dwRetCode = GetLastError();
    printf( "Allocate and initialize sid failed %u\n", dwRetCode);

    return dwRetCode;
  }

  printf("The SID is allocated and initialized.\n");

  // ����������� SID
  FreeSid(pSid);
  
  printf("The SID is freed.\n");

  return 0;
}