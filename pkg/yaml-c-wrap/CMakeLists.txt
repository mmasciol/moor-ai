cmake_minimum_required(VERSION 3.5)
project(YAML_C_WRAPPER LANGUAGES CXX)

include(CheckCXXCompilerFlag)

if (CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
    set(CMAKE_YAML_WRAP_FLAGS "${CMAKE_YAML_WRAP_FLAGS} -O3 -ggdb3 -std=c++11")
    set(CMAKE_YAML_WRAP_LINKER_FLAGS "${CMAKE_YAML_WRAP_LINKER_FLAGS} -O3 -g -std=c++11")
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    set(CMAKE_YAML_WRAP_FLAGS "${CMAKE_YAML_WRAP_FLAGS} -O3 -ggdb3 -std=c++11")
    set(CMAKE_YAML_WRAP_LINKER_FLAGS "${CMAKE_YAML_WRAP_LINKER_FLAGS} -O3 -g -std=c++11")
endif()

set(CMAKE_CXX_FLAGS "${CMAKE_C_FLAGS}")
message(STATUS "Compiling yaml-c-wrapper with options ${CMAKE_C_FLAGS}")

file(GLOB _SRC "*.cpp")
file(GLOB _HDR "*.h")

set_source_files_properties(${_SRC} PROPERTIES COMPILE_FLAGS "${CMAKE_YAML_WRAP_FLAGS}")
set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_YAML_WRAP_LINKER_FLAGS}")

add_library(yaml-c-wrapper SHARED ${_SRC} ${_HDR})
target_link_libraries(yaml-c-wrapper yaml-cpp)

SET_SOURCE_FILES_PROPERTIES("*.cpp" PROPERTIES LANGUAGE CXX )
