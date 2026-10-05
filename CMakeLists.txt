cmake_minimum_required(VERSION 3.16)

project(mysh
    VERSION 1.0
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(mysh
    src/main.cpp
    src/shell.cpp
    src/parser.cpp
    src/executor.cpp
    src/builtins.cpp
    src/signals.cpp
    src/jobs.cpp
)

target_include_directories(mysh
    PRIVATE
        ${PROJECT_SOURCE_DIR}/include
)

target_compile_options(mysh
    PRIVATE
        -Wall
        -Wextra
        -Wpedantic
)