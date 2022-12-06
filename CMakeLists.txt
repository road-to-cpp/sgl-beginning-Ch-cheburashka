cmake_minimum_required(VERSION 3.0)

project(GSLib VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_FLAGS         "")
set(CMAKE_CXX_FLAGS_DEBUG   "")
set(CMAKE_CXX_FLAGS_RELEASE "")

string(APPEND CMAKE_CXX_FLAGS " -Wall -Wextra -pedantic")
string(APPEND CMAKE_CXX_FLAGS " -Wconversion -Wunreachable-code -Wuninitialized -Wold-style-cast")
string(APPEND CMAKE_CXX_FLAGS " -Wctor-dtor-privacy -Wnon-virtual-dtor -Wconversion -Wsign-conversion -Winit-self")
string(APPEND CMAKE_CXX_FLAGS " -Wunreachable-code -Wfloat-equal")

string(APPEND CMAKE_CXX_FLAGS " -fPIC")

string(APPEND CMAKE_CXX_FLAGS_DEBUG " -g -Og")
string(APPEND CMAKE_CXX_FLAGS_RELEASE " -O3 -Werror")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_CXX_EXTENSIONS OFF)

Include(FetchContent)

FetchContent_Declare(
        Catch2
        GIT_REPOSITORY https://github.com/catchorg/Catch2.git
        GIT_TAG        v3.0.1 # or a later release
)

FetchContent_MakeAvailable(Catch2)

add_library(GSLib INTERFACE)

target_include_directories(GSLib INTERFACE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)

add_executable(GSLibTest_array tests/array_tests.cpp)

add_executable(GSLibTest_vector tests/vector_tests.cpp)

add_executable(GSLibTest_linked_list tests/linked_list_tests.cpp)

target_link_libraries(GSLibTest_array GSLib Catch2::Catch2WithMain)

target_link_libraries(GSLibTest_vector GSLib Catch2::Catch2WithMain)

target_link_libraries(GSLibTest_linked_list GSLib Catch2::Catch2WithMain)

add_executable(main cli/main.cpp)

target_link_libraries(main GSLib)