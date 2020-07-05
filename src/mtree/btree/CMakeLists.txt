add_library(btree btree.cpp)

list(APPEND EXTRA_LIBS stack)
list(APPEND EXTRA_LIBS redblack)

target_link_libraries(btree PRIVATE ${EXTRA_LIBS})

target_include_directories(btree INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
