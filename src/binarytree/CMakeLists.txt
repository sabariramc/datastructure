add_library(binarytree binarytree.cpp)

list(APPEND EXTRA_LIBS stack)

target_link_libraries(binarytree PRIVATE ${EXTRA_LIBS})

target_include_directories(binarytree INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})

add_subdirectory(bst)