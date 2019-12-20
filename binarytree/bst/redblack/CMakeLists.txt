add_library(redblack redblack.cpp)

target_include_directories(redblack INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})

list(APPEND EXTRA_LIBS bst)

target_link_libraries(redblack PRIVATE ${EXTRA_LIBS})