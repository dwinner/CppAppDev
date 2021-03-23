#ifndef UNICODE
#define UNICODE
#endif

#include <stdio.h>
#include <windows.h> 
#include <lm.h>

#pragma comment( lib, "netapi32.lib" )  // ���������� ������� ����������

int main()
{
  wchar_t server_name[256] = L"\\\\";    // ��� �������
  wchar_t  group_name[GNLEN];            // ��� ��������� ������
  wchar_t user_name[UNLEN];              // ��� ������������
  LOCALGROUP_MEMBERS_INFO_0  member_info;  // ���������� � ����� ������

  NET_API_STATUS  ret_status;        // ��� �������� �� �������
  DWORD  dwErrCode;

  DWORD  dwLengthOfSID = 0;          // ����� SID
  DWORD  dwLengthOfDomainName = 0;   // ����� ����� ������
  PSID  lpSID = NULL;                // ��������� �� SID
  LPTSTR  lpDomainName = NULL;       // ��������� �� ��� ������
  SID_NAME_USE type_of_SID;          // ��� ������� ������

  printf("Input server name: ");
  // ��������� ��� �������
  wscanf(L"%s", server_name + wcslen(server_name));

  printf("Input a local group name: ");
  wscanf(L"%s", group_name);         // ������ ��� ������

  printf("Input a user name: ");
  wscanf(L"%s", user_name);          // ������ ��� ������������

  // ���������� ����� SID ������������
  LookupAccountName(
    NULL,            // ���� ��� �� ��������� ����������
    user_name,       // ��� ������������
    NULL,            // ���������� ����� SID
    &dwLengthOfSID,  // ����� SID
    NULL,            // ���������� ��� ������
    &dwLengthOfDomainName,    // ����� ����� ������
    &type_of_SID);   // ��� ������� ������
  // ���������, ������� �� ������� ����� SID
  if (dwLengthOfSID == 0)
  {
    dwErrCode = GetLastError();
    printf("Lookup account name failed.\n");
    printf("Error code: %d\n", dwErrCode);

    return dwErrCode;
  }

  // ������������ ������ ��� SID � ����� ������
  lpSID = (PSID) new char[dwLengthOfSID];
  lpDomainName = (LPTSTR) new char[dwLengthOfDomainName];

  // ���������� SID � ��� ������ ������������
  if(!LookupAccountName(
    NULL,            // ���� ��� �� ��������� ����������
    user_name,       // ��� ������������
    lpSID,           // ���������� ����� SID
    &dwLengthOfSID,  // ����� SID
    lpDomainName,    // ���������� ��� ������
    &dwLengthOfDomainName,   // ����� ����� ������
    &type_of_SID))   // ��� ������� ������
  {
    dwErrCode = GetLastError();
    printf("Lookup account name failed.\n");
    printf("Error code: %d\n", dwErrCode);

    return dwErrCode;
  }

  // ������������� ��� ������
  wprintf(L"%s\n", lpDomainName);

  // ������������� SID � ���������� � ����� ������
  member_info.lgrmi0_sid = lpSID;

  // ������� ����� ��������� ������
  ret_status = NetLocalGroupDelMembers(
    server_name,     // ��� �������
    group_name,      // ��� ������
    0,               // ������� ����������
    (LPBYTE)&member_info,    // ���������� � SID
    1);              // ��������� ������ ����� ������
  if (ret_status != NERR_Success)
  {
    printf("Net local group del members failed.\n");

    return ret_status;
  }

  printf("The member is deleted.\n");

  return 0;
}