#include <stdio.h>
extern "C"
{
	void asmMain( void );
};

int main(void)
{
	printf( "Running asmMain:\n" );
	asmMain();
}