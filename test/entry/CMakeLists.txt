cmake_minimum_required(VERSION 3.5)
project(TEST_ENTRY LANGUAGES CXX)

include(CheckCXXCompilerFlag)

if (CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
    set(CMAKE_TEST_ENTRY_FLAGS "${CMAKE_TEST_ENTRY_FLAGS} -O3 -g -ggdb3 -cpp")
    set(CMAKE_TEST_ENTRY_LINKER_FLAGS "${CMAKE_TEST_ENTRY_LINKER_FLAGS} -O3 -g")
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    message(ERROR "GCC compiler unsupported")
endif()

set(CMAKE_CXX_FLAGS "${CMAKE_C_FLAGS}")
message(STATUS "Compiling test-entry with options ${CMAKE_C_FLAGS}")

file(GLOB _SRC "*.c")
file(GLOB _HDR "*.h")

set_source_files_properties(${_SRC} PROPERTIES COMPILE_FLAGS "${CMAKE_TEST_ENTRY_FLAGS}")
set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_TEST_ENTRY_LINKER_FLAGS}")

add_executable(test-entry ${_SRC} ${_HDR})
target_link_libraries(test-entry moor-ai)
