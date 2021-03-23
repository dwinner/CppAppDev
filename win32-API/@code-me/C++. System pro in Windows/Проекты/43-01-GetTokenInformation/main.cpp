#include <windows.h>
#include <stdio.h>

int main()
{
  HANDLE hProcess;       // дескриптор процесса
  HANDLE hTokenHandle;   // дескриптор маркера доступа

  TOKEN_SOURCE ts;       // источник маркера доступа

  DWORD dwRetLength;     // возвращаемая длина буфера
  DWORD dwRetCode;       // код возврата

  // получаем дескриптор процесса
  hProcess = GetCurrentProcess();

  // открываем маркер доступа процесса
  if (!OpenProcessToken(
    hProcess,            // дескриптор процесса
    TOKEN_QUERY_SOURCE,  // доступ к источнику маркера
    &hTokenHandle))      // дескриптор маркера
  {
    dwRetCode = GetLastError();
    printf( "Open process token failed: %u\n", dwRetCode);

    return dwRetCode;
  }

  // получаем источник маркера доступа
  if (!GetTokenInformation(
    hTokenHandle,    // дескриптор маркера доступа
    TokenSource,     // получаем источник маркера доступа
    &ts,             // адрес буфера для источника
    sizeof(ts),      // размер буфера
    &dwRetLength))   // требуемый размер буфера в случае неудачи
  {
    dwRetCode = GetLastError();
    printf( "Get token information failed: %u\n", dwRetCode);

    return dwRetCode;
  }

  // распечатываем источник маркера доступа
  printf("Source name: ");
  for (int i = 0; i < TOKEN_SOURCE_LENGTH; ++i)
    putchar(ts.SourceName[i]);
  putchar('\n');
  printf("Source identifier: %X %X\n", ts.SourceIdentifier.HighPart,
    ts.SourceIdentifier.LowPart);

  CloseHandle(hTokenHandle);

  return 0;
}