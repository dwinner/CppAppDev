#include <windows.h>
#include <iostream.h>

int main() 
{
  HANDLE  hConsoleOutput;        // ��� ����������� ������ ������
  CHAR   lpBuffer[] = "abcd";    // ����� � ��������� ��� ������
  COORD  dwWriteCoord = {10, 10};// ���������� ������� �������� � ������
  DWORD  nNumberOfCharsWritten;  // ���������� ���������� ��������

  // �������� ���������� ������ ������
  hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
  if (hConsoleOutput == INVALID_HANDLE_VALUE)
  {
    cout << "Get standard handle failed." << endl;
    return GetLastError();
  }
  // ���������� ������� � ����� ������
  if (!WriteConsoleOutputCharacter(
      hConsoleOutput,      // ���������� ������ ������ 
      lpBuffer,      // ����� ��� ����� ��������
      sizeof(lpBuffer),      // ���������� ������������ ��������
      dwWriteCoord,      // ���������� ������� �������
      &nNumberOfCharsWritten))  // ���������� ���������� ��������
  {
    cout << "Read console output character failed." << endl;
    return GetLastError();
  }
  // ������� ���������� ���������� ��������
  cout << "Number of chars written: " << nNumberOfCharsWritten << endl;

  return 0; 
}