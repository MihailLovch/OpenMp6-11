cmake_minimum_required(VERSION 3.26)
project(untitled1)

set(CMAKE_CXX_STANDARD 17)

find_package(OpenMP REQUIRED)

add_executable(Task2 task6.cpp
        task7.cpp
        task8.cpp
        task9.cpp
        task10.cpp
        task11.cpp
)

target_compile_options(Task2 PRIVATE -Wall ${OpenMP_CXX_FLAGS})
target_link_libraries(Task2 PRIVATE ${OpenMP_CXX_FLAGS})