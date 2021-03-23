#include <stdio.h>
#include <windows.h> 
#include <lm.h>

#pragma comment( lib, "netapi32.lib" )   // ���������� ������� ����������

int main()
{
  wchar_t server_name[256] = L"\\\\";  // ��� �������
  wchar_t user_name[UNLEN];            // ��� ������������
  USER_INFO_1  *ui;                    // ���������� � ������������
  NET_API_STATUS  ret_status;          // ��� �������� �� �������

  printf("Input server name: ");       // ������ ��� �������
  // ��������� ��� �������
  wscanf(L"%s", server_name + wcslen(server_name));

  printf("Input user name: ");
  wscanf(L"%s", user_name);            // ������ ��� ������������

  // �������� ���������� � ������������
  ret_status = NetUserGetInfo(
    server_name,     // ��� �������
    user_name,       // ��� ������������
    1,               // ������� ���������� 1
    (LPBYTE*)&ui);   // ����� ���������� � ������������

  // ��������� �� �������� ����������
  if (ret_status != NERR_Success)
  {
    printf("Net user get info failed.\n");

    return ret_status;
  }
  
  wprintf(L"User name: %s\n", ui->usri1_name);
  wprintf(L"User commemnt: %s\n", ui->usri1_comment);

  NetApiBufferFree(ui);    // ����������� �����

  return 0;
}