cmake_minimum_required(VERSION 3.6.0)
project(miniconsole LANGUAGES C)

file(GLOB source 
    "main.c"
    "src/*.c"
    "src/math/*.c"
)

file(COPY 
    ${CMAKE_CURRENT_SOURCE_DIR}/assets

    DESTINATION
    ${CMAKE_CURRENT_BINARY_DIR}
)

set(include_dirs 
    "include/"
)

add_executable(${PROJECT_NAME} ${source})
include_directories(${include_dirs})
target_link_libraries(${PROJECT_NAME} m)