# CMAKE generated file: DO NOT EDIT!
# Generated by "NMake Makefiles" Generator, CMake Version 3.16

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


.SUFFIXES: .hpux_make_needs_suffix_list


# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE
NULL=nul
!ENDIF
SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = "C:\Program Files\JetBrains\CLion 2020.1\bin\cmake\win\bin\cmake.exe"

# The command to remove a file.
RM = "C:\Program Files\JetBrains\CLion 2020.1\bin\cmake\win\bin\cmake.exe" -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = "G:\cpp\Asm,C,C++.AppDev\appDev. C\C. Compiling with GCC\optimization\nopt-sample"

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = "G:\cpp\Asm,C,C++.AppDev\appDev. C\C. Compiling with GCC\optimization\nopt-sample\cmake-build-release"

# Include any dependencies generated for this target.
include CMakeFiles\nopt_sample.dir\depend.make

# Include the progress variables for this target.
include CMakeFiles\nopt_sample.dir\progress.make

# Include the compile flags for this target's objects.
include CMakeFiles\nopt_sample.dir\flags.make

CMakeFiles\nopt_sample.dir\main.c.obj: CMakeFiles\nopt_sample.dir\flags.make
CMakeFiles\nopt_sample.dir\main.c.obj: ..\main.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="G:\cpp\Asm,C,C++.AppDev\appDev. C\C. Compiling with GCC\optimization\nopt-sample\cmake-build-release\CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/nopt_sample.dir/main.c.obj"
	C:\PROGRA~2\MICROS~2\2019\ENTERP~1\VC\Tools\MSVC\1428~1.299\bin\Hostx86\x86\cl.exe @<<
 /nologo $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) /FoCMakeFiles\nopt_sample.dir\main.c.obj /FdCMakeFiles\nopt_sample.dir\ /FS -c "G:\cpp\Asm,C,C++.AppDev\appDev. C\C. Compiling with GCC\optimization\nopt-sample\main.c"
<<

CMakeFiles\nopt_sample.dir\main.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/nopt_sample.dir/main.c.i"
	C:\PROGRA~2\MICROS~2\2019\ENTERP~1\VC\Tools\MSVC\1428~1.299\bin\Hostx86\x86\cl.exe > CMakeFiles\nopt_sample.dir\main.c.i @<<
 /nologo $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E "G:\cpp\Asm,C,C++.AppDev\appDev. C\C. Compiling with GCC\optimization\nopt-sample\main.c"
<<

CMakeFiles\nopt_sample.dir\main.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/nopt_sample.dir/main.c.s"
	C:\PROGRA~2\MICROS~2\2019\ENTERP~1\VC\Tools\MSVC\1428~1.299\bin\Hostx86\x86\cl.exe @<<
 /nologo $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) /FoNUL /FAs /FaCMakeFiles\nopt_sample.dir\main.c.s /c "G:\cpp\Asm,C,C++.AppDev\appDev. C\C. Compiling with GCC\optimization\nopt-sample\main.c"
<<

CMakeFiles\nopt_sample.dir\eval_parser.c.obj: CMakeFiles\nopt_sample.dir\flags.make
CMakeFiles\nopt_sample.dir\eval_parser.c.obj: ..\eval_parser.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="G:\cpp\Asm,C,C++.AppDev\appDev. C\C. Compiling with GCC\optimization\nopt-sample\cmake-build-release\CMakeFiles" --progress-num=$(CMAKE_PROGRESS_2) "Building C object CMakeFiles/nopt_sample.dir/eval_parser.c.obj"
	C:\PROGRA~2\MICROS~2\2019\ENTERP~1\VC\Tools\MSVC\1428~1.299\bin\Hostx86\x86\cl.exe @<<
 /nologo $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) /FoCMakeFiles\nopt_sample.dir\eval_parser.c.obj /FdCMakeFiles\nopt_sample.dir\ /FS -c "G:\cpp\Asm,C,C++.AppDev\appDev. C\C. Compiling with GCC\optimization\nopt-sample\eval_parser.c"
<<

CMakeFiles\nopt_sample.dir\eval_parser.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/nopt_sample.dir/eval_parser.c.i"
	C:\PROGRA~2\MICROS~2\2019\ENTERP~1\VC\Tools\MSVC\1428~1.299\bin\Hostx86\x86\cl.exe > CMakeFiles\nopt_sample.dir\eval_parser.c.i @<<
 /nologo $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E "G:\cpp\Asm,C,C++.AppDev\appDev. C\C. Compiling with GCC\optimization\nopt-sample\eval_parser.c"
<<

CMakeFiles\nopt_sample.dir\eval_parser.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/nopt_sample.dir/eval_parser.c.s"
	C:\PROGRA~2\MICROS~2\2019\ENTERP~1\VC\Tools\MSVC\1428~1.299\bin\Hostx86\x86\cl.exe @<<
 /nologo $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) /FoNUL /FAs /FaCMakeFiles\nopt_sample.dir\eval_parser.c.s /c "G:\cpp\Asm,C,C++.AppDev\appDev. C\C. Compiling with GCC\optimization\nopt-sample\eval_parser.c"
<<

# Object files for target nopt_sample
nopt_sample_OBJECTS = \
"CMakeFiles\nopt_sample.dir\main.c.obj" \
"CMakeFiles\nopt_sample.dir\eval_parser.c.obj"

# External object files for target nopt_sample
nopt_sample_EXTERNAL_OBJECTS =

nopt_sample.exe: CMakeFiles\nopt_sample.dir\main.c.obj
nopt_sample.exe: CMakeFiles\nopt_sample.dir\eval_parser.c.obj
nopt_sample.exe: CMakeFiles\nopt_sample.dir\build.make
nopt_sample.exe: CMakeFiles\nopt_sample.dir\objects1.rsp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir="G:\cpp\Asm,C,C++.AppDev\appDev. C\C. Compiling with GCC\optimization\nopt-sample\cmake-build-release\CMakeFiles" --progress-num=$(CMAKE_PROGRESS_3) "Linking C executable nopt_sample.exe"
	"C:\Program Files\JetBrains\CLion 2020.1\bin\cmake\win\bin\cmake.exe" -E vs_link_exe --intdir=CMakeFiles\nopt_sample.dir --rc=C:\PROGRA~2\WI3CF2~1\10\bin\100190~1.0\x86\rc.exe --mt=C:\PROGRA~2\WI3CF2~1\10\bin\100190~1.0\x86\mt.exe --manifests  -- C:\PROGRA~2\MICROS~2\2019\ENTERP~1\VC\Tools\MSVC\1428~1.299\bin\Hostx86\x86\link.exe /nologo @CMakeFiles\nopt_sample.dir\objects1.rsp @<<
 /out:nopt_sample.exe /implib:nopt_sample.lib /pdb:"G:\cpp\Asm,C,C++.AppDev\appDev. C\C. Compiling with GCC\optimization\nopt-sample\cmake-build-release\nopt_sample.pdb" /version:0.0  /machine:X86 /INCREMENTAL:NO /subsystem:console  kernel32.lib user32.lib gdi32.lib winspool.lib shell32.lib ole32.lib oleaut32.lib uuid.lib comdlg32.lib advapi32.lib 
<<

# Rule to build all files generated by this target.
CMakeFiles\nopt_sample.dir\build: nopt_sample.exe

.PHONY : CMakeFiles\nopt_sample.dir\build

CMakeFiles\nopt_sample.dir\clean:
	$(CMAKE_COMMAND) -P CMakeFiles\nopt_sample.dir\cmake_clean.cmake
.PHONY : CMakeFiles\nopt_sample.dir\clean

CMakeFiles\nopt_sample.dir\depend:
	$(CMAKE_COMMAND) -E cmake_depends "NMake Makefiles" "G:\cpp\Asm,C,C++.AppDev\appDev. C\C. Compiling with GCC\optimization\nopt-sample" "G:\cpp\Asm,C,C++.AppDev\appDev. C\C. Compiling with GCC\optimization\nopt-sample" "G:\cpp\Asm,C,C++.AppDev\appDev. C\C. Compiling with GCC\optimization\nopt-sample\cmake-build-release" "G:\cpp\Asm,C,C++.AppDev\appDev. C\C. Compiling with GCC\optimization\nopt-sample\cmake-build-release" "G:\cpp\Asm,C,C++.AppDev\appDev. C\C. Compiling with GCC\optimization\nopt-sample\cmake-build-release\CMakeFiles\nopt_sample.dir\DependInfo.cmake" --color=$(COLOR)
.PHONY : CMakeFiles\nopt_sample.dir\depend

