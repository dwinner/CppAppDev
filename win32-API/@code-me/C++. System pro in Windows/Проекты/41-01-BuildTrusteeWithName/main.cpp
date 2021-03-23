#include <stdio.h>
#include <windows.h> 
#include <aclapi.h>

int main()
{
  TRUSTEE  Trustee;
  char  trustee_name[] = "CURRENT_USER";   // имя пользователя

  // строим структуру TRUSTEE по имени
  BuildTrusteeWithName(&Trustee, trustee_name);

  // проверяем значения полей
  if (Trustee.pMultipleTrustee == NULL)
    printf("Server trustee: NULL\n");

  if (Trustee.MultipleTrusteeOperation == NO_MULTIPLE_TRUSTEE)
    printf("Multiple trustee: NO_MULTIPLE_TRUSTEE\n");

  if (Trustee.TrusteeForm == TRUSTEE_IS_NAME)
    printf("Trustee form: TRUSTEE_IS_NAME\n");

  if (Trustee.TrusteeType == TRUSTEE_IS_UNKNOWN)
    printf("Trustee type: TRUSTEE_IS_UNKNOWN\n");

  printf("Trustee name: %s\n", Trustee.ptstrName);

  return 0;
}