#include(CompileOptions)
#include(Conan)

find_package(fmt REQUIRED)

add_library(eJson STATIC 
            ${CMAKE_SOURCE_DIR}/thirdparty/jsont/jsont.cc
            )

add_executable(main "main.cpp")
target_include_directories(main PUBLIC 
                            ${CMAKE_SOURCE_DIR}/include
                            ${CMAKE_SOURCE_DIR}/thirdparty/jsont
                            )
target_link_libraries(main PRIVATE fmt::fmt eJson)
target_compile_features(main PRIVATE cxx_std_11)
target_compile_options(main PRIVATE ${warnings} ${wae})
