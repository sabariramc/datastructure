add_library(heap heap.cpp)


target_include_directories(heap
          INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}
          )