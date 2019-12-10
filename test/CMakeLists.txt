add_library(test stack.cpp queue.cpp binarytree.cpp)
target_include_directories(
    test
    INTERFACE  ${CMAKE_CURRENT_SOURCE_DIR}
)

list(APPEND EXTRA_LIBS stack)
list(APPEND EXTRA_LIBS queue)
list(APPEND EXTRA_LIBS binarytree)

target_link_libraries(test PUBLIC ${EXTRA_LIBS})