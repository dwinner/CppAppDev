#include <windows.h>
#include <stdio.h>

int main()
{
  LUID  luId;        // ��������� �������������

  DWORD dwRetCode;   // ��� ��������

  // ������������ ��������� ���������� �������������
  if (!AllocateLocallyUniqueId(
    &luId))      // ����� ���������� ��������������
  {
    dwRetCode = GetLastError();
    perror("Lookup privilege value failed.\n");
    printf("The last error code: %u\n", dwRetCode);

    return dwRetCode;
  }

  // ������������� LUID
  printf("Locally unique identifier.\n");
  printf("\tHigh part: %x, Low part: %x\n", luId.HighPart, luId.LowPart);

  return 0;
}