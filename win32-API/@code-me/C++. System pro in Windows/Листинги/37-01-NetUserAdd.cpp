#include <stdio.h>
#include <windows.h> 
#include <lm.h>

#pragma comment( lib, "netapi32.lib" ) // ���������� ������� ����������

int main()
{
  wchar_t server_name[256] = L"\\\\";    // ��� �������
  wchar_t user_name[UNLEN];              // ��� ������������
  wchar_t user_password[PWLEN];          // ������ ������������
  wchar_t user_comment[256];             // ����������� � ������������
  USER_INFO_1    ui;                     // ���������� � ������������
  NET_API_STATUS  ret_status;            // ��� �������� �� �������

  printf("Input server name: ");
// ��������� ��� �������
  wscanf(L"%s", server_name + wcslen(server_name));

  printf("Input user name: ");   // ������ ��� ������������
  wscanf(L"%s", user_name);      // ������ ��� ������������
  ui.usri1_name = user_name;     // ������������� ��� ������������

  printf("Input user password: ");
  wscanf(L"%s", user_password);      // ������ ������ ������������
  ui.usri1_password = user_password; // ������������� ������ ������������

  ui.usri1_priv = USER_PRIV_USER;  // ������� ������������
  ui.usri1_home_dir = NULL;        // ��������� �������� ���

  printf("Input user comment: ");
  getwchar();                      // ������� �����
  _getws(user_comment);            // ������ ����������� � ������������
  ui.usri1_comment = user_comment; // ������������� �����������

  ui.usri1_flags = UF_SCRIPT;    // ��������� ������ ��� ����� ������������ � �������
  ui.usri1_script_path = NULL;   // ���� ���� �� �������� �� ����������

  // ��������� ������������
  ret_status = NetUserAdd(
    server_name,     // ��� �������
    1,               // ������� ���������� 1
    (LPBYTE)&ui,     // ����� ���������� � ������������
    NULL);           // �������������� � ��������� ������ ���

  // ��������� �� �������� ����������
  if (ret_status != NERR_Success)
  {
    printf("Net user add failed.\n");
    printf("Error code: %u\n", ret_status);

    return ret_status;
  }
  printf("The user is added.\n");

  return 0;
}