#ifndef UNICODE
#define UNICODE
#endif

#include <stdio.h>
#include <windows.h> 
#include <lm.h>

int main()
{
  wchar_t group_name[GNLEN];   // ��� ������

  DWORD dwErrCode;             // ��� ��������

  DWORD  dwLengthOfSID = 0;          // ����� SID
  DWORD  dwLengthOfDomainName = 0;   // ����� ����� ������
  DWORD  dwLengthOfUserName = UNLEN; // ����� ����� ������� ������ 
  SID    *lpSID_1 = NULL;            // ��������� �� SID ������ ������
  SID    *lpSID_2 = NULL;            // ��������� �� SID ������ ������
  LPTSTR  lpDomainName_1 = NULL;     // ��������� �� ��� ������
  LPTSTR  lpDomainName_2 = NULL;     // ��������� �� ��� ������
  SID_NAME_USE type_of_SID;          // ��� ������� ������

  printf("Input a name of the first group: ");
  wscanf(L"%s", group_name);       // ������ ��� ������

  // ���������� ����� SID ������
  LookupAccountName(
    NULL,              // ���� ��� �� ��������� ����������
    group_name,        // ��� ������������
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
  lpSID_1 = (SID*) new char[dwLengthOfSID];
  lpDomainName_1 = (LPTSTR) new wchar_t[dwLengthOfDomainName];

  // ���������� SID � ��� ������ ������
  if(!LookupAccountName(
    NULL,              // ���� ��� �� ��������� ����������
    group_name,        // ��� ������
    lpSID_1,           // ��������� �� SID
    &dwLengthOfSID,    // ����� SID
    lpDomainName_1,    // ��������� �� ��� ������
    &dwLengthOfDomainName,   // ����� ����� ������
    &type_of_SID))     // ��� ������� ������
  {
    dwErrCode = GetLastError();

    printf("Lookup account name failed.\n");
    printf("Error code: %d\n", dwErrCode);

    return dwErrCode;
  }

  // ��������� ��� ������� ������
  if (type_of_SID != SidTypeAlias)
  {
    printf("This is not a group.\n");
    return 1;
  }

  printf("Input a name of the second group: ");
  wscanf(L"%s", group_name);       // ������ ��� ������

  // ���������� ����� SID ������
  LookupAccountName(
    NULL,              // ���� ��� �� ��������� ����������
    group_name,        // ��� ������������
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
  lpSID_2 = (SID*) new char[dwLengthOfSID];
  lpDomainName_2 = (LPTSTR) new wchar_t[dwLengthOfDomainName];

  // ���������� SID � ��� ������ ������
  if(!LookupAccountName(
    NULL,              // ���� ��� �� ��������� ����������
    group_name,        // ��� ������
    lpSID_2,           // ��������� �� SID
    &dwLengthOfSID,    // ����� SID
    lpDomainName_2,    // ��������� �� ��� ������
    &dwLengthOfDomainName,   // ����� ����� ������
    &type_of_SID))     // ��� ������� ������
  {
    dwErrCode = GetLastError();

    printf("Lookup account name failed.\n");
    printf("Error code: %d\n", dwErrCode);

    return dwErrCode;
  }

  // ��������� ��� ������� ������
  if (type_of_SID != SidTypeAlias)
  {
    printf("This is not a group.\n");
    return 1;
  }

  // ���������� �������� SID �����
  if (EqualPrefixSid(lpSID_1, lpSID_2))
    printf("SID prefixes are equal\n");
  else
    printf("SID prefixes are not equal\n");

  delete[] lpDomainName_1;
  delete[] lpDomainName_2;
  delete[] lpSID_1;
  delete[] lpSID_2;

  return 0;
}