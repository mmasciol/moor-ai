cmake_minimum_required(VERSION 3.0.0)
project(moor-ai VERSION 0.1.0)

include(CheckCXXCompilerFlag)

add_subdirectory("./pkg/bstring")
add_subdirectory("./pkg/yaml")
add_subdirectory("./src")
add_subdirectory("./test/entry")

set_target_properties(moor-ai
    PROPERTIES
        LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../bin$<0:>  # for *.so
        ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../bin$<0:>  # for *.a
        RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../bin$<0:>  # for *.dll on windows
        PDB_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../bin$<0:>
        COMPILE_PDB_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../bin$<0:>
)

set_target_properties(bstring
    PROPERTIES
        LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../bin$<0:>  # for *.so
        ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../bin$<0:>  # for *.a
        RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../bin$<0:>  # for *.dll on windows
        PDB_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../bin$<0:>
        COMPILE_PDB_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../bin$<0:>
)

set_target_properties(yaml
    PROPERTIES
        LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../bin$<0:>  # for *.so
        ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../bin$<0:>  # for *.a
        RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../bin$<0:>  # for *.dll on windows
        PDB_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../bin$<0:>
        COMPILE_PDB_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../bin$<0:>
)

set_target_properties(test-entry
    PROPERTIES
        LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../bin/test$<0:>  # for *.so
        ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../bin/test$<0:>  # for *.a
        RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../bin/test$<0:>  # for *.dll on windows
        PDB_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../bin/test$<0:>
        COMPILE_PDB_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../bin/test$<0:>
)

set_target_properties(bstring PROPERTIES FOLDER "bstring")
set_target_properties(moor-ai PROPERTIES FOLDER "moor-ai")
set_target_properties(test-entry PROPERTIES FOLDER "test")
set_target_properties(yaml PROPERTIES FOLDER "yaml")

target_include_directories(moor-ai
    PRIVATE  "${CMAKE_BINARY_DIR}/../pkg/bstring")

target_include_directories(test-entry
    PRIVATE  "${CMAKE_BINARY_DIR}/../src")

# target_include_directories(c-yaml
#     PRIVATE  "${CMAKE_BINARY_DIR}/../pkg/yaml/include")

install(TARGETS moor-ai
        LIBRARY DESTINATION ${CMAKE_BINARY_DIR}/../python/moor_ai)

install(TARGETS bstring
        LIBRARY DESTINATION ${CMAKE_BINARY_DIR}/../python/moor_ai)
