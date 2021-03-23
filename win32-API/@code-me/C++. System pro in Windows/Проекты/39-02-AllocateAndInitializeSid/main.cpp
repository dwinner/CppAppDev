#include <stdio.h>
#include <windows.h> 

int main()
{
  int n;   // количество идентификаторов
  // указатель на идентификатор учетной записи
  SID_IDENTIFIER_AUTHORITY *sia;
DWORD dwSubAuthority;    // относительный идентификатор учетной записи
  PSID pSid = NULL;      // указатель на SID

  // предопределенные идентификаторы учетной записи
  SID_IDENTIFIER_AUTHORITY s0 = SECURITY_NULL_SID_AUTHORITY;
  SID_IDENTIFIER_AUTHORITY s1 = SECURITY_WORLD_SID_AUTHORITY;
  SID_IDENTIFIER_AUTHORITY s2 = SECURITY_LOCAL_SID_AUTHORITY;
  SID_IDENTIFIER_AUTHORITY s5 = SECURITY_NT_AUTHORITY;

  // ввод идентификатора безопасности
  printf("Choose one of the predefined SID.\n");
  printf("Null SID:\t\t0\n");
  printf("World SID:\t\t1\n");
  printf("Local SID:\t\t2\n");
  printf("Anonimous logon SID:\t5\n\n");

  printf("SID = ");

  scanf("%d", &n);     // читаем идентификатор учетной записи
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

  // создаем SID
  if(!AllocateAndInitializeSid(
      sia,     // идентификатор учетной записи
      1,       // количество относительных идентификаторов учетной записи
      dwSubAuthority,        // первый RID
      0, 0, 0, 0, 0, 0, 0,   // остальные RID равны 0
      &pSid) )
  {
    DWORD dwRetCode = GetLastError();
    printf( "Allocate and initialize sid failed %u\n", dwRetCode);

    return dwRetCode;
  }

  printf("The SID is allocated and initialized.\n");

  // освобождаем SID
  FreeSid(pSid);
  
  printf("The SID is freed.\n");

  return 0;
}