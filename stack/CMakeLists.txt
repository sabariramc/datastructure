add_library(stack stack.cpp)
target_include_directories(
    stack
    INTERFACE  ${CMAKE_CURRENT_SOURCE_DIR}
    PRIVATE ${CMAKE_SOURCE_DIR}/linkedlist
)