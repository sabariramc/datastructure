add_library(bplustree bplustree.cpp)

list(APPEND EXTRA_LIBS stack)
list(APPEND EXTRA_LIBS redblack)

target_link_libraries(bplustree PRIVATE ${EXTRA_LIBS})

target_include_directories(bplustree INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})