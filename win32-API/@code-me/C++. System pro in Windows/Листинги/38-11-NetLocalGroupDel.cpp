#include <stdio.h>
#include <windows.h> 
#include <lm.h>

#pragma comment( lib, "netapi32.lib" )  // ���������� ������� ����������

int main()
{
  wchar_t server_name[256] = L"\\\\";  // ��� �������
  wchar_t group_name[GNLEN];     // ��� ��������� ��������� ������
  NET_API_STATUS ret_status;     // ��� �������� �� �������

  printf("Input server name: ");
  // ��������� ��� �������
  wscanf(L"%s", server_name + wcslen(server_name));

  printf("Input a name of the local group: ");
  wscanf(L"%s", group_name);     // ������ ��� ������

  // ������� ��������� ������
  ret_status = NetLocalGroupDel(server_name, group_name);
  // ��������� ��� ����������
  if (ret_status != NERR_Success)
  {
    printf("Net local group del failed.\n");
    printf("Error code: %d\n", ret_status);

    return ret_status;
  }

  printf("The local group is deleted.\n");

  return 0;
}