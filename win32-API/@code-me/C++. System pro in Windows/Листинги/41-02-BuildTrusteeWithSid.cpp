#define _WIN32_WINNT 0x0500

#include <stdio.h>
#include <windows.h> 
#include <aclapi.h>
#include <sddl.h>

int main()
{
  TRUSTEE Trustee;   // информация об учетной записи
  // идентификатор учетной записи
  SID_IDENTIFIER_AUTHORITY sia = SECURITY_WORLD_SID_AUTHORITY;
  // относительный идентификатор учетной записи
  DWORD dwSubAuthority = SECURITY_WORLD_RID;
  PSID lpSid = NULL;           // указатель на SID
  LPTSTR lpStringSid = NULL;   // указатель на строку с SID

  // создаем SID for Everyone
  if(!AllocateAndInitializeSid(
      &sia,  // адрес идентификатора учетной записи
      1,     // количество относительных идентификаторов учетной записи
      dwSubAuthority,        // первый RID
      0, 0, 0, 0, 0, 0, 0,   // остальные RID равны 0
      &lpSid) )
  {
    DWORD dwRetCode = GetLastError();
    printf( "Allocate and initialize sid failed %u\n", dwRetCode);

    return dwRetCode;
  }

  // строим структуру TRUSTEE по идентификатору безопасности
  BuildTrusteeWithSid(&Trustee, lpSid);

  // проверяем значения полей
  if (Trustee.pMultipleTrustee == NULL)
    printf("Server trustee: NULL\n");

  if (Trustee.MultipleTrusteeOperation == NO_MULTIPLE_TRUSTEE)
    printf("Multiple trustee: NO_MULTIPLE_TRUSTEE\n");

  if (Trustee.TrusteeForm == TRUSTEE_IS_SID)
    printf("Trustee form: TRUSTEE_IS_SID\n");

  if (Trustee.TrusteeType == TRUSTEE_IS_UNKNOWN)
    printf("Trustee type: TRUSTEE_IS_UNKNOWN\n");

  // преобразуем SID в строку
  if (!ConvertSidToStringSid(Trustee.ptstrName, &lpStringSid))
  {
    printf("Convert SID to string SID failed.");

    return GetLastError();
  }
  // распечатываем SID
  printf("SID: %s\n", lpStringSid);

  // освобождаем SID
  FreeSid(lpSid);

  return 0;
}