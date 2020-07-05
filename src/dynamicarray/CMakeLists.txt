
add_library(
    dynamicarray SHARED dynamicarray.cpp
)



target_include_directories(
    dynamicarray
    INTERFACE
    ${CMAKE_CURRENT_SOURCE_DIR}
)