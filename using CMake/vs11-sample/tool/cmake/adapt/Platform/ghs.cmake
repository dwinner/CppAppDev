set(GHS 1)

set(CMAKE_BUILD_TYPE_INIT Debug)

# ---------- default libraries ----------
set(CMAKE_C_STANDARD_LIBRARIES_INIT)
set(CMAKE_CXX_STANDARD_LIBRARIES_INIT)

# ---------- compiler flags ----------
set(CMAKE_FLAGS_INIT)
set(CMAKE_FLAGS_INIT "${CMAKE_FLAGS_INIT} --no_misra_runtime")
set(CMAKE_FLAGS_INIT "${CMAKE_FLAGS_INIT} --misra_req=silent")  # error,warn,silent   - Controls MISRA warning level for required rules
set(CMAKE_FLAGS_INIT "${CMAKE_FLAGS_INIT} --misra_adv=silent")  # error,warn,silent   - Controls MISRA warning level for advisory rules
set(CMAKE_FLAGS_INIT "${CMAKE_FLAGS_INIT} -cpu=rh850g3m")       # Defines CPU type (JCP2016, RH850-D1x)
set(CMAKE_FLAGS_INIT "${CMAKE_FLAGS_INIT} -fhard")              # Defines FPU availability
set(CMAKE_FLAGS_INIT "${CMAKE_FLAGS_INIT} -fpu=fpu30")          # Use FPU 3.0 instructions (RH850 and later)
set(CMAKE_FLAGS_INIT "${CMAKE_FLAGS_INIT} -registermode=22")    # Defines number of registers used by the compiler

# ---------- C flags ----------
set(CMAKE_C_FLAGS_INIT)
set(CMAKE_C_FLAGS_INIT "${CMAKE_FLAGS_INIT}")
# set(CMAKE_C_FLAGS_INIT "${CMAKE_C_FLAGS_INIT} -ansi")                       # Specifies ANSI C with extensions
set(CMAKE_C_FLAGS_INIT "${CMAKE_C_FLAGS_INIT} -c99")                        # Specifies ISO C99
# set(CMAKE_C_FLAGS_INIT "${CMAKE_C_FLAGS_INIT} --no_slash_comment")          # Controls acceptance of // style comments in C
set(CMAKE_C_FLAGS_INIT "${CMAKE_C_FLAGS_INIT} --no_wrap_diagnostics")       # Controls whether diagnostic messages are wrapped when they are too long to fit on a single line
set(CMAKE_C_FLAGS_INIT "${CMAKE_C_FLAGS_INIT} --diag_warning=193")          # Controls generation of warnings for defines without explicit value set
set(CMAKE_C_FLAGS_INIT "${CMAKE_C_FLAGS_INIT} --diag_suppress=381")         # extra ";" ignored - is certainly not a serious warning
set(CMAKE_C_FLAGS_INIT "${CMAKE_C_FLAGS_INIT} --diag_suppress=550")         # "variable was set but never used"
set(CMAKE_C_FLAGS_INIT "${CMAKE_C_FLAGS_INIT} --diag_suppress=1")           # warning #1 "last line of file ends without a newline"
set(CMAKE_C_FLAGS_INIT "${CMAKE_C_FLAGS_INIT} --diag_error=47")             # warning #47 "incompatible redefinition of macro"

set(CMAKE_C_FLAGS_INIT "${CMAKE_C_FLAGS_INIT} --unsigned_chars")            # Controls interpretation of char
set(CMAKE_C_FLAGS_INIT "${CMAKE_C_FLAGS_INIT} --unsigned_fields")           # Controls interpretation of bit-fields
set(CMAKE_C_FLAGS_INIT "${CMAKE_C_FLAGS_INIT} --unsigned_pointer")          # Controls interpretation of pointers
set(CMAKE_C_FLAGS_INIT "${CMAKE_C_FLAGS_INIT} --prototype_errors")          # Controls warning indication for functions that are used without a prototype
set(CMAKE_C_FLAGS_INIT "${CMAKE_C_FLAGS_INIT} --asm_silent")                # Controls warning indication when asm constructs are used
set(CMAKE_C_FLAGS_INIT "${CMAKE_C_FLAGS_INIT} --unknown_pragma_warnings")   # Controls warning indication for unknown pragma statement
set(CMAKE_C_FLAGS_INIT "${CMAKE_C_FLAGS_INIT} --short_enum")                # Controls memory allocation for enums
set(CMAKE_C_FLAGS_INIT "${CMAKE_C_FLAGS_INIT} --struct_min_alignment=1")    # Controls minimal structure alignment
set(CMAKE_C_FLAGS_INIT "${CMAKE_C_FLAGS_INIT} -nothreshold")                # Controls usage of the SDA area

# ---------- C++ flags ----------
set(CMAKE_CXX_FLAGS_INIT)
set(CMAKE_CXX_FLAGS_INIT "${CMAKE_FLAGS_INIT}")
# set(CMAKE_CXX_FLAGS_INIT "${CMAKE_CXX_FLAGS_INIT} --ee")                                # Specifies Extended Embedded C++, which adds templates, namespaces, mutable new-style casts, and the Standard Template Library (STL) to Embedded C++.
# set(CMAKE_CXX_FLAGS_INIT "${CMAKE_CXX_FLAGS_INIT} -eel")                                # Controls inclusion of system library variant
set(CMAKE_CXX_FLAGS_INIT "${CMAKE_CXX_FLAGS_INIT} --no_exceptions")                     # Controls support for exception handling
set(CMAKE_CXX_FLAGS_INIT "${CMAKE_CXX_FLAGS_INIT} --max_inlining")                      # Controls treatment of all appropriate functions for inlining
set(CMAKE_CXX_FLAGS_INIT "${CMAKE_CXX_FLAGS_INIT} --link_once_templates")               # Controls the link-once method of non-export template instantiation
set(CMAKE_CXX_FLAGS_INIT "${CMAKE_CXX_FLAGS_INIT} --no_implicit_include")               # Controls Implicit Source File Inclusion for templates
# set(CMAKE_CXX_FLAGS_INIT "${CMAKE_CXX_FLAGS_INIT} --no_instantiate_extern_inline")      # Revert changed default behaviour in compiler >= 2014.1 see release notes

# ---------- Linker flags ----------
set(LINKER_FLAGS)
set(LINKER_FLAGS "${LINKER_FLAGS} -map")                            # Controls generation of link map file
set(LINKER_FLAGS "${LINKER_FLAGS} -keepmap")                        # Controls deletion of mapfile if project cannot be linked
set(LINKER_FLAGS "${LINKER_FLAGS} -Mn")                             # Controls sorting method of mapfile
set(LINKER_FLAGS "${LINKER_FLAGS} -Mu")                             # Controls marking unreferenced symbols in the map file
set(LINKER_FLAGS "${LINKER_FLAGS} -strict_overlap_check")           # Controls error message indication for overlapping sections
set(LINKER_FLAGS "${LINKER_FLAGS} -nostartfiles")                   # Controls inclusion of default startup files from system libs
set(LINKER_FLAGS "${LINKER_FLAGS} -delete")                         # Controls deletion of unused functions
set(LINKER_FLAGS "${LINKER_FLAGS} --no_commons")                    # Controls handling of multiple global symbol declarations
set(LINKER_FLAGS "${LINKER_FLAGS} -e IVJMP_vROM_ResetHandler")      # Entry point the boot ROM jumps to

set(CMAKE_EXE_LINKER_FLAGS_INIT)
set(CMAKE_EXE_LINKER_FLAGS_INIT "${LINKER_FLAGS}")

set(CMAKE_SHARED_LINKER_FLAGS_INIT)
set(CMAKE_SHARED_LINKER_FLAGS_INIT "${LINKER_FLAGS}")

set(CMAKE_MODULE_LINKER_FLAGS_INIT)
set(CMAKE_MODULE_LINKER_FLAGS_INIT "${LINKER_FLAGS}")

set(CMAKE_STATIC_LINKER_FLAGS_INIT)
set(CMAKE_STATIC_LINKER_FLAGS_INIT "${LINKER_FLAGS}")

# ---------- debug configuration ----------
set(CMAKE_C_FLAGS_DEBUG_INIT)
set(CMAKE_C_FLAGS_DEBUG_INIT "${CMAKE_C_FLAGS_DEBUG_INIT} -G")                      # Controls generation of debug information level
set(CMAKE_C_FLAGS_DEBUG_INIT "${CMAKE_C_FLAGS_DEBUG_INIT} -check=nobounds")         # bounds        - Controls error message indicating array indexes against array bounds
set(CMAKE_C_FLAGS_DEBUG_INIT "${CMAKE_C_FLAGS_DEBUG_INIT} -check=nozerodivide")     # zerodivide    - Controls error message indicating a divide by zero
set(CMAKE_C_FLAGS_DEBUG_INIT "${CMAKE_C_FLAGS_DEBUG_INIT} -check=noassignbound")    # assignbounds  - Controls error message indicating value out of the type range
set(CMAKE_C_FLAGS_DEBUG_INIT "${CMAKE_C_FLAGS_DEBUG_INIT} -check=nonilderef")       # nilderef      - Controls error message indicating all dereferences of NULL pointers
set(CMAKE_C_FLAGS_DEBUG_INIT "${CMAKE_C_FLAGS_DEBUG_INIT} -check=noswitch")         # switch        - Controls error message indicating the case/switch expression not matching any of the c/s labels
set(CMAKE_C_FLAGS_DEBUG_INIT "${CMAKE_C_FLAGS_DEBUG_INIT} -check=nowatch")          # watch         - Controls error message indicating creation of the watchpoint without using an assertion
set(CMAKE_C_FLAGS_DEBUG_INIT "${CMAKE_C_FLAGS_DEBUG_INIT} -check=nomemory")         # alloc,memory  - Controls error message indicating Memory or Allocation setting sensible for dynamic memory management

set(CMAKE_CXX_FLAGS_DEBUG_INIT)
set(CMAKE_CXX_FLAGS_DEBUG_INIT "${CMAKE_C_FLAGS_DEBUG_INIT}")

set(CMAKE_EXE_LINKER_FLAGS_DEBUG_INIT)
set(CMAKE_SHARED_LINKER_FLAGS_DEBUG_INIT)
set(CMAKE_MODULE_LINKER_FLAGS_DEBUG_INIT)
set(CMAKE_STATIC_LINKER_FLAGS_DEBUG_INIT)

# ---------- release configuration ----------
set(CMAKE_C_FLAGS_RELEASE_INIT)
set(CMAKE_C_FLAGS_RELEASE_INIT "${CMAKE_C_FLAGS_RELEASE_INIT} -nofloatio")  # Controls support for %f%g%e in printf, use of libnoflt.a, a library containing special versions of printf which is smaller than standard

set(CMAKE_CXX_FLAGS_RELEASE_INIT)
set(CMAKE_CXX_FLAGS_RELEASE_INIT "${CMAKE_C_FLAGS_RELEASE_INIT}")

set(CMAKE_EXE_LINKER_FLAGS_RELEASE_INIT)
set(CMAKE_SHARED_LINKER_FLAGS_RELEASE_INIT)
set(CMAKE_MODULE_LINKER_FLAGS_RELEASE_INIT)
set(CMAKE_STATIC_LINKER_FLAGS_RELEASE_INIT)

# set(CMAKE_STATIC_LINKER_FLAGS_MINSIZEREL_INIT)

# set(CMAKE_C_CREATE_SHARED_LIBRARY "<CMAKE_C_COMPILER> <CMAKE_SHARED_LIBRARY_C_FLAGS> <LANGUAGE_COMPILE_FLAGS> <LINK_FLAGS> <CMAKE_SHARED_LIBRARY_CREATE_C_FLAGS> <SONAME_FLAG><TARGET_SONAME> -o <TARGET> <OBJECTS> <LINK_LIBRARIES>")
# set(CMAKE_C_CREATE_SHARED_MODULE ${CMAKE_C_CREATE_SHARED_LIBRARY})
# set(CMAKE_C_ARCHIVE_CREATE "<CMAKE_AR> cr <TARGET> <LINK_FLAGS> <OBJECTS>")
# set(CMAKE_C_ARCHIVE_APPEND "<CMAKE_AR> r  <TARGET> <LINK_FLAGS> <OBJECTS>")
# set(CMAKE_C_ARCHIVE_FINISH "<CMAKE_RANLIB> <TARGET>")
# set(CMAKE_C_COMPILE_OBJECT "<CMAKE_C_COMPILER> <DEFINES> <FLAGS> -o <OBJECT>   -c <SOURCE>")
# set(CMAKE_C_LINK_EXECUTABLE "<CMAKE_C_COMPILER> <FLAGS> <CMAKE_C_LINK_FLAGS> <LINK_FLAGS> <OBJECTS>  -o <TARGET> <LINK_LIBRARIES>")

# set(CMAKE_CXX_CREATE_SHARED_LIBRARY "<CMAKE_CXX_COMPILER> <CMAKE_SHARED_LIBRARY_CXX_FLAGS> <LANGUAGE_COMPILE_FLAGS> <LINK_FLAGS> <CMAKE_SHARED_LIBRARY_CREATE_CXX_FLAGS> <SONAME_FLAG><TARGET_SONAME> -o <TARGET> <OBJECTS> <LINK_LIBRARIES>")
# set(CMAKE_CXX_CREATE_SHARED_MODULE ${CMAKE_CXX_CREATE_SHARED_LIBRARY})
# set(CMAKE_CXX_ARCHIVE_CREATE "<CMAKE_AR> cr <TARGET> <LINK_FLAGS> <OBJECTS>")
# set(CMAKE_CXX_ARCHIVE_APPEND "<CMAKE_AR> r  <TARGET> <LINK_FLAGS> <OBJECTS>")
# set(CMAKE_CXX_ARCHIVE_FINISH "<CMAKE_RANLIB> <TARGET>")
# set(CMAKE_CXX_COMPILE_OBJECT "<CMAKE_CXX_COMPILER>  <DEFINES> <FLAGS> -o <OBJECT> -c <SOURCE>")
# set(CMAKE_CXX_LINK_EXECUTABLE "<CMAKE_CXX_COMPILER>  <FLAGS> <CMAKE_CXX_LINK_FLAGS> <LINK_FLAGS> <OBJECTS>  -o <TARGET> <LINK_LIBRARIES>")
