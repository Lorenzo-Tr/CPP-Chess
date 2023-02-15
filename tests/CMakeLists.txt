project(Chess_Tests LANGUAGES CXX)

enable_testing()

# ---- Tests ----

set(TESTS_SRC 
  src/Chess_test.cc
  src/pieces.cc
)

add_executable(Chess_test ${TESTS_SRC})
install(TARGETS Chess_test DESTINATION ${CMAKE_SOURCE_DIR}/bin)
target_link_libraries(Chess_test PRIVATE GTest::gtest_main)
target_compile_features(Chess_test PRIVATE cxx_std_17)

# add_test(NAME Cmake-lib_test COMMAND Cmake-lib_test)

include(GoogleTest)
gtest_discover_tests(Chess_test)
