add_library(linkedlist linkedlist.cpp)


target_include_directories(linkedlist
          INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}
          )