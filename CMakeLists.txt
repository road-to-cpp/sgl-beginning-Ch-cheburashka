cmake_minimum_required(VERSION 3.0)

project(GSLib VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

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

add_executable(GSLibTest tests/vector_tests.cpp)

target_link_libraries(GSLibTest GSLib Catch2::Catch2WithMain)

add_executable(main main.cpp)