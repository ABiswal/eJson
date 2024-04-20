cmake_minimum_required(VERSION 3.12)
project("eJsonProject"
        VERSION 1.0.0
        LANGUAGES CXX)

add_subdirectory(include)
add_subdirectory(src)
#add_subdirectory(tests/unittests)

#add_executable(${PROJECT_NAME} src/main.cpp)
