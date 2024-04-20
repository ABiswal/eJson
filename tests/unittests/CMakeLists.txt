
find_package(GTest REQUIRED)

enable_testing()
#-------------------------------------------
add_executable(
  main_test
  main_test.cc
)
target_link_libraries(
  main_test
  gtest::gtest

)

#include(GoogleTest)
#
add_test(main main_test)
#-------------------------------------------