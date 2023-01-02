cmake_minimum_required(VERSION 3.5)
project(moor-ai LANGUAGES CXX)

include(CheckCXXCompilerFlag)

check_cxx_compiler_flag("-m64" HAS_CXX_OSX)  # gcc/clang specific flags
check_cxx_compiler_flag("/GS" HAS_CXX_WIN)  # MSVS specific flags

if(HAS_CXX_OSX)
    set(CMAKE_MOOR_AI_FLAGS "${CMAKE_MOOR_AI_FLAGS} -O3 -g -ggdb3 -cpp -fPIC -fprofile-arcs -ftest-coverage -lgcov")
    set(CMAKE_MOOR_AI_LINKER_FLAGS "${CMAKE_MOOR_AI_LINKER_FLAGS} -O3 -dynamiclib -g -fprofile-arcs -ftest-coverage -lgcov")
elseif(HAS_CXX_WIN)
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} /O3")
endif()


set(CMAKE_CXX_FLAGS "${CMAKE_C_FLAGS}")
message(STATUS "Compiling moor-ai-api with options ${CMAKE_MOOR_AI_FLAGS}")

file(GLOB _SRC "*.c")
file(GLOB _HDR "*.h")

set_source_files_properties(${_SRC} PROPERTIES COMPILE_FLAGS "${CMAKE_MOOR_AI_FLAGS}")
set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_MOOR_AI_LINKER_FLAGS}")

add_library(moor-ai ${_SRC} ${_HDR})
target_link_libraries(yaml-cpp)