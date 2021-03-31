if(NOT CMAKE_TOOLCHAIN_FILE)
  set(CMAKE_USER_MAKE_RULES_OVERRIDE "${CMAKE_CURRENT_LIST_DIR}/Platform/msvc.cmake")
  
  set(CMAKE_CONFIGURATION_TYPES "Debug;Release;Multi2000" CACHE STRING "this string defines the project configuration" FORCE)
  
  set(CMAKE_C_FLAGS_MULTI2000                         "/FI\"ide/adapt/intellisense/intellisense.h\"" CACHE STRING "")
  set(CMAKE_CXX_FLAGS_MULTI2000                       "/FI\"ide/adapt/intellisense/intellisense.h\"" CACHE STRING "")
  set(CMAKE_EXE_LINKER_FLAGS_MULTI2000                "" CACHE STRING "")
  set(CMAKE_SHARED_LINKER_FLAGS_MULTI2000             "" CACHE STRING "")
  set(CMAKE_MODULE_LINKER_FLAGS_MULTI2000             "" CACHE STRING "")
  set(CMAKE_STATIC_LINKER_FLAGS_MULTI2000             "" CACHE STRING "")
endif()
