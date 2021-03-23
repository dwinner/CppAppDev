#include <windows.h>
#include <stdio.h>

int main()
{
  LUID  luId;                // локальный идентификатор для привилегии
  DWORD dwLength = 0;        // длина имени привилегии
  LPTSTR lpPrivName = NULL;  // адрес имени привилегии

  DWORD dwRetCode;           // код возврата

  // определяем локальный идентификатор привилегии
  if (!LookupPrivilegeValue(
    NULL,            // ищем привилегии на локальной машине
    SE_DEBUG_NAME,   // привилегия выполнять отладку процесса
    &luId))          // адрес локального идентификатора привилегии
  {
    dwRetCode = GetLastError();
    perror("Lookup privilege value failed.\n");
    printf("The last error code: %u\n", dwRetCode);

    return dwRetCode;
  }

  // распечатываем LUID
  printf("Luid of SE_DEBUG_NAME privilege. ");
  printf("High part: %x, Low part: %x\n", luId.HighPart, luId.LowPart);

  // определяем длину имени привилегии
  if (!LookupPrivilegeName(
    NULL,          // локальная машина
    &luId,         // адрес локального уникального идентификатора
    lpPrivName,    // адрес имени привилегии
    &dwLength))    // адрес длины буфера
  {
    dwRetCode = GetLastError();
    if (dwRetCode != ERROR_INSUFFICIENT_BUFFER)
    {
      perror("Lookup privilege name failed.\n");
      printf("The last error code: %u\n", dwRetCode);

      return dwRetCode;
    }

    // захватываем память для имени привилегии
    lpPrivName = new CHAR[dwLength + 1];
  }

  // определяем имя привилегии
  if (!LookupPrivilegeName(
    NULL,          // локальная машина
    &luId,         // адрес локального уникального идентификатора
    lpPrivName,    // адрес имени привилегии
    &dwLength))    // адрес длины буфера
  {
    dwRetCode = GetLastError();
    perror("Lookup privilege name failed.\n");
    printf("The last error code: %u\n", dwRetCode);

    return dwRetCode;
  }

  // распечатываем имя привилегии
  printf("Name of the Luid: %s\n", lpPrivName);

  delete[] lpPrivName;

  return 0;
}