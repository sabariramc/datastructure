add_library(avl avl.cpp)

target_include_directories(avl INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})

list(APPEND EXTRA_LIBS bst)

target_link_libraries(avl PRIVATE ${EXTRA_LIBS})