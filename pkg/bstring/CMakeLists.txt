cmake_minimum_required(VERSION 3.5)
project(bstring LANGUAGES CXX)

include(CheckCXXCompilerFlag)

if (CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
    set(CMAKE_BSTRING_FLAGS "${CMAKE_BSTRING_FLAGS} -O3 -g -fPIC -cpp")
    set(CMAKE_BSTRING_LINKER_FLAGS "${CMAKE_BSTRING_LINKER_FLAGS} -O3 -shared -g")
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    message(ERROR "GCC compiler unsupported")
endif()

set(CMAKE_CXX_FLAGS "${CMAKE_C_FLAGS}")
message(STATUS "Compiling bstring with options ${CMAKE_BSTRING_FLAGS}")

file(GLOB _SRC "*.c")
file(GLOB _HDR "*.h")

set_source_files_properties(${_SRC} PROPERTIES COMPILE_FLAGS "${CMAKE_BSTRING_FLAGS}")
set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_BSTRING_LINKER_FLAGS}")

add_library(bstring SHARED ${_SRC} ${_HDR})
