cmake_minimum_required(VERSION 3.0.0)
project(moor-ai VERSION 0.1.0)

include(CheckCXXCompilerFlag)

enable_testing()

add_subdirectory("./pkg/bstring")
add_subdirectory("./pkg/yaml-cpp")
add_subdirectory("./src")
add_subdirectory("./test/entry")

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

set_target_properties(bstring
    PROPERTIES
        LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../bin$<0:>  # for *.so
        ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../bin$<0:>  # for *.a
        RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../bin$<0:>  # for *.dll on windows
        PDB_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../bin$<0:>
        COMPILE_PDB_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../bin$<0:>
)

set_target_properties(bstring PROPERTIES FOLDER "bstring")
set_target_properties(moor-ai PROPERTIES FOLDER "moor-ai")
set_target_properties(yaml-cpp PROPERTIES FOLDER "yaml-cpp")
set_target_properties(yaml-cpp-parse PROPERTIES FOLDER "yaml-cpp")
set_target_properties(yaml-cpp-read PROPERTIES FOLDER "yaml-cpp")
set_target_properties(yaml-cpp-sandbox PROPERTIES FOLDER "yaml-cpp")



add_test (NAME test-entry  COMMAND test-entry)
#     --build-and-test "${CMAKE_SOURCE_DIR}/test/entry"
#                      "${CMAKE_BINARY_DIR}/test/entry"
#    --build-generator ${CMAKE_GENERATOR}
#    --build-makeprogram ${CMAKE_MAKE_PROGRAM}
#    --build-project Simple
#    --test-command simple)
#
# set (passRegex "^Test passed" "^All ok")
# set (failRegex "Error" "Fail")
# set_property (TEST test-entry
#               PROPERTY PASS_REGULAR_EXPRESSION "${passRegex}")
# set_property (TEST test-entry
#               PROPERTY FAIL_REGULAR_EXPRESSION "${failRegex}")
#


target_include_directories(moor-ai
    PRIVATE  "${CMAKE_BINARY_DIR}/../pkg/bstring")

install(TARGETS moor-ai
        LIBRARY DESTINATION ${CMAKE_BINARY_DIR}/../python/moor_ai)

install(TARGETS bstring
        LIBRARY DESTINATION ${CMAKE_BINARY_DIR}/../python/bstring)
