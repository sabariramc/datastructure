cmake_minimum_required(VERSION 3.10)

project(Datastructure VERSION 1.0)

add_subdirectory(linkedlist)
list(APPEND EXTRA_LIBS linkedlist)

add_subdirectory(stack)
list(APPEND EXTRA_LIBS stack)
add_dependencies(stack linkedlist)



add_executable(Datastructure main.cpp)

target_include_directories(Datastructure PUBLIC ${EXTRA_LIBS})