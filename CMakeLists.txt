cmake_minimum_required(VERSION 3.10)

project(jMetalCpp)

# for emacs completion
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# for grouping into folders
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

# cpp standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# threads
set(THREADS_PREFER_PTHREAD_FLAG OFF)
find_package(Threads REQUIRED)

# project files
file(GLOB_RECURSE header_files src/*.h)
file(GLOB_RECURSE source_files src/*.cpp)
file(GLOB_RECURSE main_files src/*_main.cpp src/experiments/main/*.cpp)
list(REMOVE_ITEM source_files ${main_files})

# get header directories based on location of headers
macro(get_header_directories return_list)
  file(GLOB_RECURSE new_list src/*.h)
  set(dir_list "")
  foreach(file_path ${new_list})
    get_filename_component(dir_path ${file_path} PATH)
    set(dir_list ${dir_list} ${dir_path})
  endforeach()
  list(REMOVE_DUPLICATES dir_list)
  set(${return_list} ${dir_list})
endmacro()

# include header directories
get_header_directories(include_dirs)
include_directories(${include_dirs})
# foreach(dir IN LISTS include_dirs)
#   message("${dir}")
# endforeach()

# static library
set(library_target jmetal)
add_library(${library_target} STATIC ${source_files} ${header_files})
target_link_libraries(${library_target} PRIVATE Threads::Threads)
target_compile_options(${library_target} PRIVATE -fPIC)
if(MSVC) # ignore function must return a value on MSCV
  target_compile_options(${library_target} PRIVATE /w34716)
endif()
install(TARGETS ${library_target} DESTINATION lib)
install(FILES ${header_files} DESTINATION include)

# build main files
foreach(main_program ${main_files})
  # NAME_WE stands for "name without extension"
  get_filename_component(main_target ${main_program} NAME_WE)
  add_executable(${main_target} ${main_program})
  target_link_libraries(${main_target} ${library_target})
  set_target_properties(${main_target}
    PROPERTIES
    PROJECT_LABEL "${main_target}"
    FOLDER "main")
  install(TARGETS ${main_target} DESTINATION bin)
endforeach()
