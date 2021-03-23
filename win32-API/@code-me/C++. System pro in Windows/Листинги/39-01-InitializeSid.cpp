#include <stdio.h>
#include <windows.h> 

int main()
{
  DWORD dwSidLength;   // длина памяти для SID
  SID *pSid = NULL;    // указатель на SID

  // указатель на относительный идентификатор учетной записи
  DWORD *pSubAuthority = NULL;
  // идентификатор учетной записи
  SID_IDENTIFIER_AUTHORITY sia = SECURITY_LOCAL_SID_AUTHORITY;

  // определеем длину SID с одним относительным идентификатором учетной записи
  dwSidLength = GetSidLengthRequired(1);

  printf("SID length: %u\n", dwSidLength);

  // захватываем память под SID
  pSid = (SID*) new UCHAR[dwSidLength];

  // инициализируем SID
  if(!InitializeSid(
    pSid,    // указатель на SID
    &sia,    // идентификатор учетной записи
    1))      // количество относительных идентификаторов
  {
    printf( "Initialized SID failed.\n");
    return 1;
  }
  printf("SID is initialized.\n");

  // определяем указатель на относительный идентификатор
  pSubAuthority = GetSidSubAuthority(pSid, 0);
  // устанавливаем значение относительного идентификатора
  *pSubAuthority = SECURITY_LOCAL_RID;

  // проверяем достоверность SID
  if(!IsValidSid(pSid))
  {
    printf( "The SID is not valid.\n");
    return 1;
  }

  printf("The SID is valid.\n");

  // освобождаем SID
  delete[] pSid;
  
  return 0;
}