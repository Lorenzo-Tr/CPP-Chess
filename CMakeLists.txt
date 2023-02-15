cmake_minimum_required(VERSION 3.0.0)
project(Chess VERSION 1.0.0 LANGUAGES CXX)

include(CTest)
include_directories("${CMAKE_CURRENT_SOURCE_DIR}/include")

set(EXE Chess)
set(SRC ${CMAKE_SOURCE_DIR}/src)
set(TEST ${CMAKE_SOURCE_DIR}/tests)

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

add_subdirectory(${SRC})
add_subdirectory(${TEST})