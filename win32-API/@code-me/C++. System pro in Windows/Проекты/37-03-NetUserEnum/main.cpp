#include <stdio.h>
#include <windows.h> 
#include <lm.h>

#pragma comment( lib, "netapi32.lib" ) // ���������� ������� ����������

int main()
{
  wchar_t server_name[256] = L"\\\\";  // ��� �������
  USER_INFO_0  *ui;        // ���������� � ������������
  DWORD  entries_read;     // ���������� ����������� �������������
  DWORD  total_entries;    // ����� ���������� �������������

  NET_API_STATUS  ret_status;  // ��� �������� �� �������

  printf("Input server name: ");   // ������ ��� �������
  // ��������� ��� �������
  wscanf(L"%s", server_name + wcslen(server_name));

  // �������� ���������� � �������������
  ret_status = NetUserEnum(
    server_name,       // ��� �������
    0,                 // ������ ������ ����� �������������
    FILTER_NORMAL_ACCOUNT,   // ����������� �������������, ������������������ �� ����������
    (LPBYTE*)&ui,      // ����� ���������� � �������������
    MAX_PREFERRED_LENGTH,    // ����������� ���� �������������
    &entries_read,     // ���������� ����������� �������������
    &total_entries,    // ����� ���������� �������������
    NULL);             // ���������� ���

  // ��������� �� �������� ����������
  if (ret_status != NERR_Success)
  {
    printf("Net user get info failed.\n");
    printf("Net API Status: %d\n", ret_status);
    NetApiBufferFree(ui);    // ����������� �����

    return ret_status;
  }

  for (DWORD i = 0; i < entries_read; ++i)
    wprintf(L"User name: %s\n", ui[i].usri0_name);

  NetApiBufferFree(ui);      // ����������� �����

  return 0;
}