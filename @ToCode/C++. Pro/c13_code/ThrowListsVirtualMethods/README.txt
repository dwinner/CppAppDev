Compile each of the source files in this directory separately.

Visual C++ 2013 does not yet support noexcept used in CorrectOne.cpp.

Note:
Broken.cpp does not compile on compilers that implement throw lists.
Some compilers (such as Microsoft Visual Studio) do not implement throw
lists.

Note:
These source code files demonstrate throw lists
because you might encounter throw lists in existing code bases.
However, don't use throw lists in new code because since C++11,
any throw list is deprecated, except for noexcept.