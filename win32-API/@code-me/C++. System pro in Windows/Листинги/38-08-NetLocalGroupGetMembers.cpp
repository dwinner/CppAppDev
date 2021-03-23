#include <stdio.h>
#include <windows.h> 
#include <lm.h>

#pragma comment( lib, "netapi32.lib" )  // ���������� ������� ����������

int main()
{
  wchar_t server_name[256] = L"\\\\";    // ��� �������
  wchar_t  group_name[GNLEN];            // ��� ��������� ������
  // ���������� � ������ ������
  LOCALGROUP_MEMBERS_INFO_1  *member_info = NULL;
  DWORD entries_read;            // ����������� ���������� ������ ������
  DWORD total_entries;           // ����� ���������� ������ ������

  NET_API_STATUS  ret_status;    // ��� �������� �� �������

  printf("Input server name: ");
  // ��������� ��� �������
  wscanf(L"%s", server_name + wcslen(server_name));

  printf("Input a local group name: ");
  wscanf(L"%s", group_name);         // ������ ��� ������

  // �������� ���������� � ������ ��������� ������
  ret_status = NetLocalGroupGetMembers(
    server_name,         // ��� �������
    group_name,          // ��� ������
    1,                   // ������� ����������
    (LPBYTE*)&member_info,     // ���������� � �������������
    MAX_PREFERRED_LENGTH,      // ������ ���������� � ���� ������ ������
    &entries_read,       // ����������� ���������� ������ ������
    &total_entries,      // ������ ���������� ������ ������
    NULL);               // ������ � ���� �����
  if (ret_status != NERR_Success)
  {
    printf("Net local group get members failed.\n");
    NetApiBufferFree(member_info);      // ����������� �����

    return ret_status;
  }

  // ������������� �������������
  for (DWORD i = 0; i < entries_read; ++i)
    wprintf(L"The group member: %s\n", member_info[i].lgrmi1_name);

  NetApiBufferFree(member_info);    // ����������� �����
  return 0;
}