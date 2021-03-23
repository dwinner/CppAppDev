#include <stdio.h>
#include <windows.h> 
#include <lm.h>

#pragma comment( lib, "netapi32.lib" )   // ���������� ������� ����������

int main()
{
  wchar_t server_name[256] = L"\\\\";  // ��� �������
  wchar_t user_name[UNLEN];            // ��� ������������

  NET_API_STATUS  ret_status;  // ��� �������� �� �������

  printf("Input server name: ");
  wscanf(L"%s", server_name);    // ������ ��� ������

  printf("Input user name: ");
  wscanf(L"%s", user_name);      // ������ ��� ������������

  // ������� ������������
  ret_status = NetUserDel(
    server_name,     // ��� ������
    user_name);      // ��� ������������

  // ��������� �� �������� ����������
  if (ret_status != NERR_Success)
  {
    printf("Net user del failed.\n");
    printf("Net API Status: %d\n", ret_status);

    return ret_status;
  }

  printf("The user is deleted.\n");

  return 0;
}