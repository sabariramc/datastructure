cmake_minimum_required(VERSION 3.10)

project(datastructures VERSION 1.0)

add_subdirectory(linkedlist)
list(APPEND EXTRA_LIBS linkedlist)

add_subdirectory(stack)
list(APPEND EXTRA_LIBS stack)

add_subdirectory(queue)
list(APPEND EXTRA_LIBS queue)

add_subdirectory(binarytree)
list(APPEND EXTRA_LIBS binarytree)
list(APPEND EXTRA_LIBS bst)
list(APPEND EXTRA_LIBS avl)
list(APPEND EXTRA_LIBS redblack)

add_subdirectory(test)
list(APPEND EXTRA_LIBS test)

add_executable(datastructures main.cpp)

target_link_libraries(datastructures PUBLIC ${EXTRA_LIBS})