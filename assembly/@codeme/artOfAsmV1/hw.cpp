#include <windows.h>
int main(void)
{
	DWORD written = 0;
	
	WriteFile( GetStdHandle(-11), "Hello x64 World!", 16, &written, NULL );
}