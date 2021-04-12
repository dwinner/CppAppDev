;13.7 - 5 - LastIndexOf Procedure

========================= ASM =========================
; IndexOf function (IndexOf.asm)

.586
.model flat,C

IndexOf PROTO,
srchVal:DWORD, arrayPtr:PTR DWORD, count:DWORD

.code

IndexOf PROC USES ecx esi edi,
srchVal:DWORD, arrayPtr:PTR DWORD, count:DWORD

NOT_FOUND = -1

mov eax,srchVal 
mov ecx,count 
mov esi,arrayPtr 
mov edi, ecx
sub edi, 4

L1:
cmp [esi+edi*4],eax
je found
dec edi
loop L1

notFound:
mov al,NOT_FOUND
jmp short exit

found:
mov eax,edi

exit:
ret
IndexOf ENDP
END

==========================C++ ========================

#include <iostream>
#include <time.h>

extern "C" int IndexOf(long searchVal, long * array, unsigned ARRAY_SIZE);

using namespace std;

int main() {
// Fill an array with pseudorandom integers.
const unsigned ARRAY_SIZE = 100000;
const unsigned LOOP_SIZE = 100000;
char* boolstr[] = { "false","true" };

long array[ARRAY_SIZE];
for (unsigned i = 0; i < ARRAY_SIZE; i++)
	array[i] = rand();

long searchVal;
time_t startTime, endTime;
cout << "Enter an integer value to find: ";
cin >> searchVal;
cout << "Please wait...\n";

// Test the Assembly language function.
time(&startTime);
int count = 0;

for (unsigned n = 0; n < LOOP_SIZE; n++)
	count = IndexOf(searchVal, array, ARRAY_SIZE);

bool found = count != -1;

time(&endTime);
cout << "Elapsed ASM time: " << long(endTime - startTime)
<< " seconds. Found = " << boolstr[found] << endl;

return 0;
}