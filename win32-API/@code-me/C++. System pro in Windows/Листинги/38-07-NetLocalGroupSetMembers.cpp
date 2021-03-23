#include <stdio.h>
#include <windows.h> 
#include <lm.h>

#pragma comment( lib, "netapi32.lib" )   // ���������� ������� ����������

int main()
{
  wchar_t server_name[256] = L"\\\\";      // ��� �������
  wchar_t  group_name[GNLEN];              // ��� ��������� ������
  LOCALGROUP_MEMBERS_INFO_3  *member_info; // ���������� � ������ ������
  DWORD n;     // ���������� ���������� ������ ��������� ������

  NET_API_STATUS  ret_status;      // ��� �������� �� �������

  printf("Input server name: ");
// ��������� ��� �������
  wscanf(L"%s", server_name + wcslen(server_name));

  printf("Input a local group name: ");
  wscanf(L"%s", group_name);               // ������ ��� ������

  printf("Input number of members: ");
  scanf("%d", &n);

// ����������� ������ ��� ���������� � �������������
  member_info = new LOCALGROUP_MEMBERS_INFO_3[n];

  for (DWORD i = 0; i < n; ++i)
  {
    // ����������� ������ ��� ��� ������������
    member_info[i].lgrmi3_domainandname = new wchar_t[256];
    printf("Input a domain name: ");
    // ������ ��� ������
    wscanf(L"%s", member_info[i].lgrmi3_domainandname);

    // ������������ ������ '\'
    wcscat(member_info[i].lgrmi3_domainandname, L"\\");

    printf("Input a user name: ");
    // ������ ��� ������������
    wscanf(L"%s", member_info[i].lgrmi3_domainandname + 
            wcslen(member_info[i].lgrmi3_domainandname));
}

  // ������ ��� ������
  for (i = 0; i < n; ++i)
    wprintf(L"%s\n", member_info[i].lgrmi3_domainandname);

  // ������������� ������ � ��������� ������
  ret_status = NetLocalGroupSetMembers(
    server_name,           // ��� �������
    group_name,            // ��� ������
    3,                     // ������� ����������
    (LPBYTE)member_info,   // ���������� � SID
    n);                    // ���������� ���������� ������ ������
  if (ret_status != NERR_Success)
  {
    printf("Net local group set members failed.\n");

    return ret_status;
  }

  printf("The members are set.\n");

  return 0;
}