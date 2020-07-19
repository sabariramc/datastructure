add_library(test stack.cpp queue.cpp binarytree.cpp btree.cpp bplustree.cpp heap.cpp binaryindexedtree.cpp)
target_include_directories(
    test
    INTERFACE  ${CMAKE_CURRENT_SOURCE_DIR}
)

list(APPEND EXTRA_LIBS stack)
list(APPEND EXTRA_LIBS linkedlist)
list(APPEND EXTRA_LIBS queue)
list(APPEND EXTRA_LIBS binarytree)
list(APPEND EXTRA_LIBS redblack)
list(APPEND EXTRA_LIBS bst)
list(APPEND EXTRA_LIBS btree)
list(APPEND EXTRA_LIBS bplustree)
list(APPEND EXTRA_LIBS heap)
list(APPEND EXTRA_LIBS binaryindexedtree)

target_link_libraries(test PUBLIC ${EXTRA_LIBS})