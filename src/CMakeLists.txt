cmake_minimum_required(VERSION 3.5)
project(moor-ai LANGUAGES CXX)

include(CheckCXXCompilerFlag)

if (CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
    set(CMAKE_MOOR_AI_FLAGS "${CMAKE_MOOR_AI_FLAGS} -O3 -g -ggdb3 -fPIC -cpp")
    set(CMAKE_MOOR_AI_LINKER_FLAGS "${CMAKE_MOOR_AI_LINKER_FLAGS} -O3 -shared -g")
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    set(CMAKE_MOOR_AI_FLAGS "${CMAKE_MOOR_AI_FLAGS} -O3 -g -ggdb3 -fPIC -cpp")
    set(CMAKE_MOOR_AI_LINKER_FLAGS "${CMAKE_MOOR_AI_LINKER_FLAGS} -O3 -shared -g")
endif()

if (MOOR_AI_DOUBLE_PRECISION)
    set(CMAKE_MOOR_AI_FLAGS "${CMAKE_MOOR_AI_FLAGS} -DDOUBLE_PRECISION")
endif()

if (MOOR_AI_DEBUG)
    set(CMAKE_MOOR_AI_FLAGS "${CMAKE_MOOR_AI_FLAGS} -DDEBUG")
endif()

set(CMAKE_CXX_FLAGS "${CMAKE_C_FLAGS}")
message(STATUS "Compiling moor-ai-api with options ${CMAKE_MOOR_AI_FLAGS}")

file(GLOB _SRC "*.c")
file(GLOB _HDR "*.h")

set_source_files_properties(${_SRC} PROPERTIES COMPILE_FLAGS "${CMAKE_MOOR_AI_FLAGS}")
set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_MOOR_AI_LINKER_FLAGS}")

add_library(moor-ai SHARED ${_SRC} ${_HDR})
target_link_libraries(moor-ai bstring yaml simclist)
