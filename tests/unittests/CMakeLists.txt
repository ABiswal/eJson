
find_package(GTest REQUIRED)

enable_testing()
#-------------------------------------------
add_executable(
  main_test
  main_test.cc
  ${CMAKE_SOURCE_DIR}/../../thirdparty/jsont/jsont.cc
)
target_link_libraries(
  main_test
  gtest::gtest
)

target_include_directories(main_test PUBLIC
${CMAKE_SOURCE_DIR}/../../include
${CMAKE_SOURCE_DIR}/../../thirdparty/jsont
)   

#include(GoogleTest)
#
#add_test(main main_test)
add_test(main_test main_test)
#-------------------------------------------