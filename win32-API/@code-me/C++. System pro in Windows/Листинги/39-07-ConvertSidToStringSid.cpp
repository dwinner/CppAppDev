#define _WIN32_WINNT 0x0500

#ifndef UNICODE
#define UNICODE
#endif

#include <stdio.h>
#include <windows.h> 
#include <lm.h>
#include <sddl.h>

int main()
{
  wchar_t user_name[UNLEN];    // ��� ������������

  DWORD dwErrCode;             // ��� ��������

  DWORD  dwLengthOfSID = 0;    // ����� SID
  DWORD  dwLengthOfDomainName = 0;   // ����� ����� ������
  PSID  lpSID = NULL;          // ��������� �� SID
  LPTSTR  lpDomainName = NULL; // ��������� �� ��� ������
  SID_NAME_USE type_of_SID;    // ��� ������� ������

  LPTSTR  lpStringSID = NULL;  // ��������� �� ������ � SID

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
  lpSID = (PSID) new wchar_t[dwLengthOfSID];
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

  // ����������� SID � ������
  if (!ConvertSidToStringSid(lpSID, &lpStringSID))
  {
    printf("Convert SID to string SID failed.");

    return GetLastError();
  }
  // ������������� SID
  wprintf(L"SID: %s\n", lpStringSID);
  // ������������� ��� ������
  wprintf(L"Domain name: %s\n", lpDomainName);


  // ����������� ������
  LocalFree(lpStringSID);

  delete[] lpDomainName;
  delete[] lpSID;

  return 0;
}