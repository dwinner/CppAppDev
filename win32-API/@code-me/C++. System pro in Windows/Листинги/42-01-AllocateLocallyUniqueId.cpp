#include <windows.h>
#include <stdio.h>

int main()
{
  LUID  luId;        // локальный идентификатор

  DWORD dwRetCode;   // код возврата

  // распределяем локальный уникальный идентификатор
  if (!AllocateLocallyUniqueId(
    &luId))      // адрес локального идентификатора
  {
    dwRetCode = GetLastError();
    perror("Lookup privilege value failed.\n");
    printf("The last error code: %u\n", dwRetCode);

    return dwRetCode;
  }

  // распечатываем LUID
  printf("Locally unique identifier.\n");
  printf("\tHigh part: %x, Low part: %x\n", luId.HighPart, luId.LowPart);

  return 0;
}