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

add_subdirectory(mtree)
list(APPEND EXTRA_LIBS btree)
