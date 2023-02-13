file(GLOB include_H . *.h)

install(FILES ${include_H} DESTINATION ${CMAKE_SOURCE_DIR}/include)