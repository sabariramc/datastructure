add_library(binarytree binarytree.cpp)

target_include_directories(binarytree INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})

list(APPEND EXTRA_LIBS stack)

target_link_libraries(binarytree PRIVATE ${EXTRA_LIBS})