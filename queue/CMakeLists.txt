add_library(queue queue.cpp)
target_include_directories(
    queue
    INTERFACE  ${CMAKE_CURRENT_SOURCE_DIR}
)

list(APPEND EXTRA_LIBS linkedlist)

target_link_libraries(queue PUBLIC ${EXTRA_LIBS})