cmake_minimum_required(VERSION 3.10)

project(datastructures VERSION 1.0)

# set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_subdirectory(src)

add_subdirectory(test)
list(APPEND EXTRA_LIBS test)

add_executable(datastructures main.cpp)

target_link_libraries(datastructures PUBLIC ${EXTRA_LIBS})