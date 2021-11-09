## CMake configuration file of parser project

cmake_minimum_required(VERSION 3.0)

# set language std
set(CMAKE_CXX_STANDARD 17)
# set language std and Disable fallback to a previous version
set(CMAKE_CXX_STANDARD_REQUIRED ON)
# Disable CXX Syntax EXTENSIONS
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

project(parser VERSION 1.0)

option(PARSER_BUILD_TESTS "Build Parser's unit tests" ON)

file(COPY "conf" DESTINATION "./")

# This project is using gflags.
add_subdirectory("third_party/gflags")
# This project is using glog.
add_subdirectory("third_party/glog")
# This project is using yaml-cpp.
add_subdirectory("third_party/yaml-cpp")

# The project needs to install boost library.
# The install commands in different platforms are below:
# MacOs:    brew install boost
# Ubuntu:   sudo apt-get install libboost-all-dev
find_package(Boost COMPONENTS REQUIRED)
message("Boost_INCLUDE_DIR" ${Boost_INCLUDE_DIR})
include_directories(${Boost_INCLUDE_DIR})
link_libraries(${Boost_LIBRARIES})

include_directories("src")

set(BASIC_CXXFLAGS -g -pipe -fPIC -Wall -Wextra -Werror -pedantic-errors -pthread)
set(EXTRA_WARNINGS -Wnon-virtual-dtor -Wold-style-cast -Woverloaded-virtual -Wsign-promo -Wswitch-default -Wfloat-equal -Wshadow -Wcast-qual -Wextra-semi)
set(DEFAULT_CXXFLAGS ${BASIC_CXXFLAGS} ${EXTRA_WARNINGS})
# add_compile_options(${DEFAULT_CXXFLAGS})

set(CXXFLAGS_PROD ${DEFAULT_CXXFLAGS} -O3)
set(CXXFLAGS_TEST ${DEFAULT_CXXFLAGS} -O0 -fsanitize=address -fsanitize=undefined -fno-access-control -fno-omit-frame-pointer)
set(LDFLAGS_TEST -fsanitize=address -fsanitize=undefined)

file(GLOB MAIN_SRC src/main.cc)
file(GLOB BUILTIN_SRC src/data_define/builtin/*.cc)
file(GLOB CUSTOM_DATA_SRC src/data_define/custom_data/*.cc)
file(GLOB PARSER_SRC src/parser/*.cc)
file(GLOB REGISTER_SRC src/register/*.cc)
file(GLOB DICT_FORMAT_SRC src/dict_format/*.cc)
file(GLOB UTILS_SRC src/utils/*.cc)

set(GLOB_SOURCES ${BUILTIN_SRC} ${CUSTOM_DATA_SRC} ${PARSER_SRC} ${REGISTER_SRC} ${DICT_FORMAT_SRC} ${UTILS_SRC})
set(APP_SOURCES ${MAIN_SRC} ${GLOB_SOURCES})
set(BIN_NAME ${PROJECT_NAME})

add_executable(${BIN_NAME} ${APP_SOURCES})
target_compile_options(${BIN_NAME}
    PRIVATE ${CXXFLAGS_PROD})
target_link_libraries(${BIN_NAME} gflags glog yaml-cpp)
set_target_properties(${BIN_NAME}
    PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
    PDB_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")

if(PARSER_BUILD_TESTS)
    enable_testing()
    # This project is tested using GoogleTest.
    add_subdirectory("third_party/googletest")

    file(GLOB TEST_SRC test/*_test.cc)
    set(TEST_SOURCES ${TEST_SRC} ${GLOB_SOURCES})
    set(TEST_NAME ${PROJECT_NAME}_test)
    add_executable(${TEST_NAME} ${TEST_SOURCES})
    target_compile_options(${TEST_NAME}
        PRIVATE ${CXXFLAGS_TEST})
    target_link_libraries(${TEST_NAME} gtest gflags glog yaml-cpp)
    target_link_options(${TEST_NAME}
        PRIVATE ${LDFLAGS_TEST})
    set_target_properties(${TEST_NAME}
        PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/test"
        LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
        ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
        PDB_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")
    # add_test(NAME ${TEST_NAME} COMMAND ${TEST_NAME})
endif(PARSER_BUILD_TESTS)
