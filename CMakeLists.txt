cmake_minimum_required(VERSION 3.0.0)
project(Chess VERSION 1.0.0 LANGUAGES CXX)

set(EXE Chess)
set(SRC ${CMAKE_SOURCE_DIR}/src)

add_subdirectory(${SRC})