#define _WIN32_WINNT 0x0500

#include <stdio.h>
#include <windows.h>
#include <lm.h>
#include <sddl.h>

int main()
{
  int n;   // ���������� ������������� ��������������� ������� ������
  LPTSTR  lpStringSID = NULL;  // ��������� �� ������ � SID
  PSID  lpSID = NULL;          // ��������� �� SID
  LPTSTR  lpString;            // ������� ��������� �� SID

  printf("Input a number of Sub Authorities: ");
  scanf("%d", &n);
  lpStringSID = (LPTSTR) new char[10 + 5 * n];

  lpStringSID[0] = 'S';        // ������� ������ SID
  lpStringSID[1] = '-';
  lpStringSID[2] = '1';        // ������ 1
  lpStringSID[3] = '-';

  // ������������� ��������� �� ������������� ������� ������
  lpString = lpStringSID + 4;

  printf("Input an Identifier Authority: ");
  scanf("%s", lpString);       // ������ ������������� ������� ������
  lpString += strlen(lpString);

  *lpString++ = '-';

  for (int i = 0; i < n - 1; ++i)
  {
    printf("Input Sub Authority #%d: ", i);
    // ������ ������������� ������������� ������� ������
    scanf("%s", lpString);
    lpString += strlen(lpString);

    *lpString++ = '-';
  }
  printf("Input Sub Authority #%d: ", n - 1);
  // ������ ��������� ������������� ������������� ������� ������
  scanf("%s", lpString);

  // ������������� ���������� SID
  printf("SID: %s\n", lpStringSID);

  // ����������� ������ � SID
  if (!ConvertStringSidToSid(lpStringSID, &lpSID))
  {
    DWORD dwErrCode = GetLastError();
    printf("Convert string SID to SID failed.\n");
    printf("Last error code: %u\n", dwErrCode);

    return dwErrCode;
  }

  // ��������� SID �� �������������
  if(!IsValidSid(lpSID))
  {
    printf( "The SID is not valid.\n");
    return 1;
  }
  printf("The SID is valid.\n");

  // ����������� ������
  LocalFree(lpSID);

  return 0;
}