#include <windows.h>
#include <iostream.h>

int main(int argc, char *argv[])
{
  char c;
  char  answer[] = "This is an answer.";
  HANDLE  hWrite, hRead;   // ������� ��� �������������
  char  WriteEvent[] = "WriteEvent";
  char  ReadEvent[] = "ReadEvent";
  char  *v;      // ��� ������ ����������� ������

  // ��������� �������
  hWrite = OpenEvent(EVENT_MODIFY_STATE, FALSE, WriteEvent);
  hRead = OpenEvent(EVENT_MODIFY_STATE, FALSE, ReadEvent);

  // ����������� �������� � �����
  v = (char*)atoi(argv[1]);
  // ������� ���������
  cout <<  v << endl;

  // ���� ���������� �� ������
  WaitForSingleObject(hWrite, INFINITE);
  // ���������� �����
  strcpy(v, "This is an answer.");
  // ��������� ������
  SetEvent(hRead);

  // ��������� �����������
  CloseHandle(hWrite);
  CloseHandle(hRead);

  // ���� ������� �� ����������
  cout << "Input any char to exit: ";
  cin >> c;
  
  return 0;
}