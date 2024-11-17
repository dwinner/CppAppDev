#ifndef CPPLIB_LIBRARY_H
#define CPPLIB_LIBRARY_H

void hello();

extern "C"
{
__declspec(dllexport) int functionInDLL(const wchar_t *p);
}

#endif //CPPLIB_LIBRARY_H
