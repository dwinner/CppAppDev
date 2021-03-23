#include <stdio.h>
#include <windows.h> 
#include <lm.h>

#pragma comment( lib, "netapi32.lib" )   // ���������� ������� ����������

int main()
{
  wchar_t server_name[256] = L"\\\\";  // ��� �������
  wchar_t old_name[UNLEN];         // ������ ��� ������������
  wchar_t new_name[UNLEN];         // ����� ��� ������������
  USER_INFO_0 ui;                  // ���������� � ������������
  NET_API_STATUS  ret_status;      // ��� �������� �� �������

  printf("Input server name: ");
// ��������� ��� �������
  wscanf(L"%s", server_name + wcslen(server_name));

  printf("Input old user name: ");
  wscanf(L"%s", old_name);       // ������ ������ ��� ������������

  printf("Input new user name: ");
  wscanf(L"%s", new_name);       // ������ ����� ��� ������������
  ui.usri0_name = new_name;      // ������������� ����� ��� ������������

  // ������������� ���������� � ������������
  ret_status = NetUserSetInfo(
    server_name,     // ��� �������
    old_name,        // ��� ������������
    0,               // �������� ��� ������������
    (LPBYTE)&ui,     // ����� ���������� � ������������
    NULL);           // ��� ����������

  // ��������� �� �������� ����������
  if (ret_status != NERR_Success)
  {
    printf("Net user set info failed.\n");
    printf("Net API Status: %d\n", ret_status);

    return ret_status;
  }

  printf("User name is changed.\n");

  USER_INFO_1  *uix;         // ���������� � ������������
  // �������� ���������� � ������������
  ret_status = NetUserGetInfo(
    server_name,     // ��� �������
    new_name,        // ��� ������������
    1,               // ������� ���������� 1
    (LPBYTE*)&uix);  // ����� ���������� � ������������

  // ��������� �� �������� ����������
  if (ret_status != NERR_Success)
  {
    printf("Net user get info failed.\n");

    return ret_status;
  }
  
  wprintf(L"User name: %s\n", uix->usri1_name);
  wprintf(L"User commemnt: %s\n", uix->usri1_comment);

  return 0;
}