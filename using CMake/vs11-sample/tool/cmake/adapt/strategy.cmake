include(strategy_ghs)

define_property(SOURCE PROPERTY OPTIMIZATION  BRIEF_DOCS "optimization" FULL_DOCS "Optimization strategy")
define_property(SOURCE PROPERTY REGION        BRIEF_DOCS "region"       FULL_DOCS "Memoryregion strategy")
define_property(SOURCE PROPERTY FOLDER        BRIEF_DOCS "folder"       FULL_DOCS "Visual Studio folder")

# defines
set(__option_file_path "${CMAKE_SOURCE_DIR}/adapt/gen/ghs")
set(__compiler_extension "^\\.(c|i|ii|cc|cp|cxx|cpp|c\\+\\+|s|sx|850)$")


# convert OPTIMIZATION & REGION to C/C++ COMPILER_FLAGS
function(__process_property source config property)
  if(CMAKE_CROSSCOMPILING)
    string(TOUPPER ${property} property)
    
    if(COMPILE_FLAGS_${config}_${property})
      set_property(SOURCE ${source} APPEND_STRING PROPERTY COMPILE_FLAGS "${COMPILE_FLAGS_${config}_${property}} ")
    endif()
  endif()
endfunction(__process_property)

# add all files to a source group
function(__process_source_groups)
  # get group list
  get_property(source_groups GLOBAL PROPERTY source_groups)
  foreach(group_name ${source_groups})
    # get group content
    get_property(source_group_${group_name} GLOBAL PROPERTY source_group_${group_name})
    
    # add files to source group
    set(folder ${group_name})
    string(REPLACE " " "\ " folder ${folder})
    string(REPLACE "/" "\\" folder ${folder})
    source_group(${folder} FILES ${source_group_${group_name}})
  endforeach()
endfunction(__process_source_groups)

# collect files that should be grouped
function(__add_to_group group_name)
  # add group list
  get_property(source_groups GLOBAL PROPERTY source_groups)
  list(APPEND source_groups ${group_name})
  list(REMOVE_DUPLICATES source_groups)
  set_property(GLOBAL PROPERTY source_groups ${source_groups})
  
  # add files to group
  get_property(source_group_content GLOBAL PROPERTY source_group_${group_name})
  list(APPEND source_group_content ${ARGN})
  list(REMOVE_DUPLICATES source_group_content)
  set_property(GLOBAL PROPERTY source_group_${group_name} ${source_group_content})
endfunction(__add_to_group)

# generates make option files
function(__generate_compiler_option_files)
  #message(STATUS "Generating Compiler files:")
  
  foreach(source ${ARGN})
    get_property(region SOURCE ${source} PROPERTY REGION)
    get_property(optimization SOURCE ${source} PROPERTY OPTIMIZATION)
    
    set(content)
    set(content "${content} ${COMPILE_FLAGS_REGION_${region}}\n")
    set(content "${content} ${COMPILE_FLAGS_OPTIMIZATION_${optimization}}\n")
    
    #message(STATUS "  ${source}")
    file(WRITE ${source} ${content})
    set_property(SOURCE ${source} PROPERTY GENERATED TRUE)
  endforeach()
endfunction(__generate_compiler_option_files)

########################################

# set OPTIMIZATION & REGION strategy
function(cds_set_compile_strategy region optimization)
  cds_search(sources ${ARGN})
  
  # OPTIMIZATION
  if(DEFINED COMPILE_FLAGS_REGION_${region})
    set_property(SOURCE ${sources} PROPERTY REGION ${region})
  else(DEFINED COMPILE_FLAGS_REGION_${region})
    message(SEND_ERROR "ERROR: Invalid memory region ${region} specified")
  endif(DEFINED COMPILE_FLAGS_REGION_${region})
  
  # REGION
  if(DEFINED COMPILE_FLAGS_OPTIMIZATION_${optimization})
    set_property(SOURCE ${sources} PROPERTY OPTIMIZATION ${optimization})
  else(DEFINED COMPILE_FLAGS_OPTIMIZATION_${optimization})
    message(SEND_ERROR "ERROR: Unsupported speed/size compiler option ${optimization} specified")
  endif(DEFINED COMPILE_FLAGS_OPTIMIZATION_${optimization})
endfunction(cds_set_compile_strategy)

# overwrite default FOLDER location
function(cds_set_folder folder)
  cds_search(sources ${ARGN})
  set_property(SOURCE ${sources} PROPERTY FOLDER ${folder})
endfunction(cds_set_folder)

# process the source file grouping
function(cds_process_strategy generated_files)
  foreach(source ${ARGN})
  
    # get properties
    get_property(folder SOURCE ${source} PROPERTY FOLDER)
    get_property(region SOURCE ${source} PROPERTY REGION)
    get_property(optimization SOURCE ${source} PROPERTY OPTIMIZATION)
    
    # folder base
    if(folder)
      set(group ${folder})
    else()
      set(group "code")
      file(RELATIVE_PATH path ${CMAKE_SOURCE_DIR} ${source})
      get_filename_component(path ${path} DIRECTORY)
      if(path)
        set(group "${group}/${path}")
      endif()
    endif()
    
    # fitler object sources
    get_filename_component(extension ${source} EXT)
    if(extension)
      # only compilable sources
      string(TOLOWER ${extension} extension)
      string(REGEX MATCH ${__compiler_extension} compilable ${extension})
      
      if(compilable)
        # strategy defined
        if(region AND optimization)
        
          # group
          set(group_name "${group}/${region}_${optimization}")
          __add_to_group(${group_name} ${source})
          
          # cross compiler / make toolchain
          if(CMAKE_CROSSCOMPILING)
            __process_property(${source} REGION ${region})
            __process_property(${source} OPTIMIZATION ${optimization})
          else()
            string(REPLACE "/" "_" group_path ${group})
            set(option_file "${__option_file_path}/_compile_${group_path}_${region}_${optimization}_code") # workarround hack
            #set(option_file "${__option_file_path}/${group}/_compile_${region}_${optimization}_code")
            set_property(SOURCE ${option_file} PROPERTY REGION ${region})
            set_property(SOURCE ${option_file} PROPERTY OPTIMIZATION ${optimization})
            __add_to_group(${group_name} ${option_file})
            list(APPEND _option_files ${option_file})
          endif()
        elseif(folder)
          # no stategy set for source file
          __add_to_group("STRATEGY_MISSING/${group}" ${source})
        endif()
      else()
        # non compilable or headers
        __add_to_group(${group} ${source})
      endif()
    else()
      # no extension
      __add_to_group(${group} ${source})
    endif()
  endforeach()
  
  if(_option_files)
    list(REMOVE_DUPLICATES _option_files)
  endif()
  
  __generate_compiler_option_files(${_option_files})
  __process_source_groups()
  
  set(${generated_files} ${_option_files} PARENT_SCOPE)
endfunction(cds_process_strategy)
