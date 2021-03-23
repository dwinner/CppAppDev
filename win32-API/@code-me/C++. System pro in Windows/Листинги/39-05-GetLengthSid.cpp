#ifndef UNICODE
#define UNICODE
#endif

#include <stdio.h>
#include <windows.h> 
#include <lm.h>

int main()
{
  wchar_t user_name[UNLEN];  // ��� ������������

  DWORD dwErrCode;           // ��� ��������

  DWORD  dwLengthOfSID = 0;          // ����� SID
  DWORD  dwLengthOfDomainName = 0;   // ����� ����� ������
  DWORD  dwLengthOfUserName = UNLEN; // ����� ����� ������� ������ 
  SID    *lpSID = NULL;              // ��������� �� SID
  LPTSTR  lpDomainName = NULL;       // ��������� �� ��� ������
  SID_NAME_USE type_of_SID;          // ��� ������� ������

  // ��������� �� ������������� ����������� SID
  PSID_IDENTIFIER_AUTHORITY  lpSia;
  // ��������� �� ���������� ������������� ���������������
  PUCHAR  lpSubAuthorityCount;
  // ��������� �� ������������� �������������
  DWORD  *lpSubAuthority;

  printf("Input a user name: ");
  wscanf(L"%s", user_name);      // ������ ��� ������������

  // ���������� ����� SID ������������
  LookupAccountName(
    NULL,              // ���� ��� �� ��������� ����������
    user_name,         // ��� ������������
    NULL,              // ���������� ����� SID
    &dwLengthOfSID,    // ����� SID
    NULL,              // ���������� ��� ������
    &dwLengthOfDomainName,   // ����� ����� ������
    &type_of_SID);     // ��� ������� ������

  // ���������, ������� �� ������� ����� SID
  if (dwLengthOfSID == 0)
  {
    dwErrCode = GetLastError();

    printf("Lookup account name failed.\n");
    printf("Error code: %d\n", dwErrCode);

    return dwErrCode;
  }

  // ������������ ������ ��� SID � ����� ������
  lpSID = (SID*) new char[dwLengthOfSID];
  lpDomainName = (LPTSTR) new wchar_t[dwLengthOfDomainName];

  // ���������� SID � ��� ������ ������������
  if(!LookupAccountName(
    NULL,              // ���� ��� �� ��������� ����������
    user_name,         // ��� ������������
    lpSID,             // ��������� �� SID
    &dwLengthOfSID,    // ����� SID
    lpDomainName,      // ��������� �� ��� ������
    &dwLengthOfDomainName,   // ����� ����� ������
    &type_of_SID))     // ��� ������� ������
  {
    dwErrCode = GetLastError();

    printf("Lookup account name failed.\n");
    printf("Error code: %d\n", dwErrCode);

    return dwErrCode;
  }

  // �������� �������������� SID � ������� �� �� �������
  dwLengthOfSID = GetLengthSid(lpSID);
  printf("Length of SID: %u\n", dwLengthOfSID);

  lpSia = GetSidIdentifierAuthority(lpSID);
  printf("IdentifierAuthority: ");
  for (int i = 0; i < 6; ++i)
    printf("%u ", lpSia->Value[i]);
  printf("\n");

  lpSubAuthorityCount = GetSidSubAuthorityCount(lpSID);
  printf("SubAuthorityCount: %u\n", *lpSubAuthorityCount);

  printf("SubAuthorities: ");
  for (i = 0; i < *lpSubAuthorityCount; ++i)
  {
    lpSubAuthority = GetSidSubAuthority(lpSID, i);
    printf("%u ", *lpSubAuthority);
  }
  printf("\n");

  delete[] lpDomainName;
  delete[] lpSID;

  return 0;
}