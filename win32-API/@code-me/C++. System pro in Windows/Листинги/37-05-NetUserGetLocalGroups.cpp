#include <stdio.h>
#include <windows.h> 
#include <lm.h>

#pragma comment( lib, "netapi32.lib" )   // ���������� ������� ����������

int main()
{
  wchar_t server_name[256] = L"\\\\";  // ��� �������
  wchar_t user_name[UNLEN];            // ��� ������������
  LOCALGROUP_USERS_INFO_0  *ui;        // ���������� � �������
  DWORD  entries_read;     // ���������� ����������� �����
  DWORD  total_entries;    // ����� ���������� �����

  NET_API_STATUS  ret_status;      // ��� �������� �� �������

  printf("Input server name: ");
// ��������� ��� �������
  wscanf(L"%s", server_name + wcslen(server_name));

  printf("Input user name: ");
  wscanf(L"%s", user_name);        // ������ ��� ������������

  // �������� ��������� ������, � ������� ������ ������������
  ret_status = NetUserGetLocalGroups(
    server_name,             // ��� �������
    user_name,               // ��� ������������
    0,                       // ������ ������ ����� �����
    LG_INCLUDE_INDIRECT,     // ������� ��������� ��������������
    (LPBYTE*)&ui,            // ����� ���������� � ������
    MAX_PREFERRED_LENGTH,    // ����������� ��� ������
    &entries_read,           // ���������� ����������� �����
    &total_entries);         // ����� ���������� �����

  // ��������� �� �������� ����������
  if (ret_status != NERR_Success)
  {
    printf("Net user get groups failed.\n");
    printf("Net API Status: %d\n", ret_status);
    NetApiBufferFree(ui);      // ����������� �����

    return ret_status;
  }

  for (DWORD i = 0; i < entries_read; ++i)
    wprintf(L"Local group name: %s\n", ui[i].lgrui0_name);

  NetApiBufferFree(ui);      // ����������� �����

  return 0;
}