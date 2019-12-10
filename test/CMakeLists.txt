add_library(test stacktest.cpp queuetest.cpp)
target_include_directories(
    test
    INTERFACE  ${CMAKE_CURRENT_SOURCE_DIR}
)

list(APPEND EXTRA_LIBS stack)
list(APPEND EXTRA_LIBS linkedlist)

target_link_libraries(test PUBLIC ${EXTRA_LIBS})