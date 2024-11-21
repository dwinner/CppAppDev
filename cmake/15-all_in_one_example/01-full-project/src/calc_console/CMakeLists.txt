add_library(calc_console_static STATIC tui.cpp)
target_include_directories(calc_console_static PUBLIC include)
target_precompile_headers(calc_console_static PUBLIC <string>)

include(GetFTXUI)
target_link_libraries(calc_console_static PUBLIC calc_shared
                      ftxui::screen ftxui::dom ftxui::component)

include(BuildInfo)
BuildInfo(calc_console_static)

InstrumentForCoverage(calc_console_static)
CleanCoverage(calc_console_static)

Format(calc_console_static .)

AddCppCheck(calc_console_static)

Doxygen(calc_console src/calc_console)

add_executable(calc_console bootstrap.cpp)
target_link_libraries(calc_console calc_console_static)

# Installation
include(GNUInstallDirs)
install(TARGETS calc_console
  RUNTIME COMPONENT runtime
)
