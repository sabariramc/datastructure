add_library(bst bst.cpp)

target_include_directories(bst INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})

list(APPEND EXTRA_LIBS binarytree)

target_link_libraries(bst PRIVATE ${EXTRA_LIBS})