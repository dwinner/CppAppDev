#ifndef UNICODE
#define UNICODE
#endif

#include <stdio.h>
#include <windows.h> 
#include <lm.h>

int main()
{
  wchar_t user_name[UNLEN];    // ��� ������������

  DWORD dwErrCode;             // ��� ��������

  DWORD  dwLengthOfSID = 0;          // ����� SID
  DWORD  dwLengthOfDomainName = 0;   // ����� ����� ������
  DWORD  dwLengthOfUserName = UNLEN; // ����� ����� ������� ������ 
  SID    *lpSID = NULL;              // ��������� �� SID
  LPTSTR  lpDomainName = NULL;       // ��������� �� ��� ������
  SID_NAME_USE type_of_SID;          // ��� ������� ������

  printf("Input a user name: ");
  wscanf(L"%s", user_name);    // ������ ��� ������������

  // ���������� ����� SID ������������
  if (!LookupAccountName(
    NULL,          // ���� ��� �� ��������� ����������
    user_name,     // ��� ������������
    NULL,          // ���������� ����� SID
    &dwLengthOfSID,    // ����� SID
    NULL,          // ���������� ��� ������
    &dwLengthOfDomainName,   // ����� ����� ������
    &type_of_SID)) // ��� ������� ������
  {
    dwErrCode = GetLastError();

    if (dwErrCode == ERROR_INSUFFICIENT_BUFFER)
    {
      // ������������ ������ ��� SID � ����� ������
      lpSID = (SID*) new char[dwLengthOfSID];
      lpDomainName = (LPTSTR) new wchar_t[dwLengthOfDomainName];
    }
    else
    {
      // ������� �� ���������
      printf("Lookup account name failed.\n");
      printf("Error code: %d\n", dwErrCode);

      return dwErrCode;
    }
  }

  // ���������� SID � ��� ������ ������������
  if(!LookupAccountName(
    NULL,            // ���� ��� �� ��������� ����������
    user_name,       // ��� ������������
    lpSID,           // ��������� �� SID
    &dwLengthOfSID,  // ����� SID
    lpDomainName,    // ��������� �� ��� ������
    &dwLengthOfDomainName,   // ����� ����� ������
    &type_of_SID))   // ��� ������� ������
  {
    dwErrCode = GetLastError();

    printf("Lookup account name failed.\n");
    printf("Error code: %d\n", dwErrCode);

    return dwErrCode;
  }

  // ������� SID �� �������
  printf("SID revision: %u\n", lpSID->Revision);
  printf("SubAuthorityCount: %u\n", lpSID->SubAuthorityCount);
  printf("IdentifierAuthority: ");
  for (int i = 0; i < 6; ++i)
    printf("%u ", lpSID->IdentifierAuthority.Value[i]);
  printf("\n");
  printf("SubAuthorities: ");
  for (i = 0; i < lpSID->SubAuthorityCount; ++i)
    printf("%u ", lpSID->SubAuthority[i]);
  printf("\n");

  // ������� ��� ������
  wprintf(L"Domain name: %s\n", lpDomainName);

  delete[] lpDomainName;
  delete[] lpSID;

  return 0;
}