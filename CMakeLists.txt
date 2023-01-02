cmake_minimum_required(VERSION 3.0.0)
project(moor-ai VERSION 0.1.0)

include(CheckCXXCompilerFlag)

add_subdirectory("./pkg/yaml-cpp")
add_subdirectory("./src")

set_target_properties(yaml-cpp
    PROPERTIES
        LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../bin$<0:>  # for *.so
        ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../bin$<0:>  # for *.a
        RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../bin$<0:>  # for *.dll on windows
        PDB_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../bin$<0:>
        COMPILE_PDB_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../bin$<0:>
)

set_target_properties(moor-ai
    PROPERTIES
        LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../bin$<0:>  # for *.so
        ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../bin$<0:>  # for *.a
        RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../bin$<0:>  # for *.dll on windows
        PDB_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../bin$<0:>
        COMPILE_PDB_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../bin$<0:>
)

set_target_properties(moor-ai PROPERTIES FOLDER "moor-ai")
set_target_properties(yaml-cpp PROPERTIES FOLDER "yaml-cpp")
set_target_properties(yaml-cpp-parse PROPERTIES FOLDER "yaml-cpp")
set_target_properties(yaml-cpp-read PROPERTIES FOLDER "yaml-cpp")
set_target_properties(yaml-cpp-sandbox PROPERTIES FOLDER "yaml-cpp")

file(COPY ${CMAKE_BINARY_DIR}/../bin/libmoor-ai.dylib
     DESTINATION ../python/moor_ai)