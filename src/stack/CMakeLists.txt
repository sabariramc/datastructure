add_library(stack stack.cpp)
list(APPEND EXTRA_LIBS linkedlist)

target_link_libraries(stack PUBLIC ${EXTRA_LIBS})
target_include_directories(
    stack
    INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}
)
