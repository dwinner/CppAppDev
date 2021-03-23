#define _WIN32_WINNT 0x0500

#include <stdio.h>
#include <windows.h>
#include <lm.h>
#include <sddl.h>

int main()
{
  int n;   // количество относительных идентификаторов учетной записи
  LPTSTR  lpStringSID = NULL;  // указатель на строку с SID
  PSID  lpSID = NULL;          // указатель на SID
  LPTSTR  lpString;            // текущий указатель на SID

  printf("Input a number of Sub Authorities: ");
  scanf("%d", &n);
  lpStringSID = (LPTSTR) new char[10 + 5 * n];

  lpStringSID[0] = 'S';        // признак строки SID
  lpStringSID[1] = '-';
  lpStringSID[2] = '1';        // версия 1
  lpStringSID[3] = '-';

  // устанавливаем указатель на идентификатор учетной записи
  lpString = lpStringSID + 4;

  printf("Input an Identifier Authority: ");
  scanf("%s", lpString);       // вводим идентификатор учетной записи
  lpString += strlen(lpString);

  *lpString++ = '-';

  for (int i = 0; i < n - 1; ++i)
  {
    printf("Input Sub Authority #%d: ", i);
    // вводим относительный идентификатор учетной записи
    scanf("%s", lpString);
    lpString += strlen(lpString);

    *lpString++ = '-';
  }
  printf("Input Sub Authority #%d: ", n - 1);
  // вводим последний относительный идентификатор учетной записи
  scanf("%s", lpString);

  // распечатываем полученный SID
  printf("SID: %s\n", lpStringSID);

  // преобразуем строку в SID
  if (!ConvertStringSidToSid(lpStringSID, &lpSID))
  {
    DWORD dwErrCode = GetLastError();
    printf("Convert string SID to SID failed.\n");
    printf("Last error code: %u\n", dwErrCode);

    return dwErrCode;
  }

  // проверяем SID на достоверность
  if(!IsValidSid(lpSID))
  {
    printf( "The SID is not valid.\n");
    return 1;
  }
  printf("The SID is valid.\n");

  // освобождаем память
  LocalFree(lpSID);

  return 0;
}