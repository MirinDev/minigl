cmake_minimum_required(VERSION 3.6.0)
project(miniconsole LANGUAGES C)

file(GLOB source 
    "main.c"
    "src/*.c"
    "src/math/*.c"
)

set(include_dirs 
    "include/"
)

add_executable(${PROJECT_NAME} ${source})
include_directories(${include_dirs})