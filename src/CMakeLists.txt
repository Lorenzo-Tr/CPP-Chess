file(GLOB src_CPP . *.cpp)

include_directories(${CMAKE_SOURCE_DIR}/include)

add_executable(${EXE} ${src_CPP})
install(TARGETS ${EXE} DESTINATION ${CMAKE_SOURCE_DIR}/bin)