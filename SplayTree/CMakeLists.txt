cmake_minimum_required(VERSION 3.20..3.25)
project(SplayTree)
set(CMAKE_CXX_STANDARD 20)

# ${HEADERS}
set(HEADERS
    include/Node.hpp
    include/SplayTree.hpp)

#  ${SOURCES}
set(SOURCES
    src/SplayTree.cpp
    src/Node.cpp)

# Flags to compiler
set(FLAGS -Wall -Wextra -Werror -Wpedantic -Wunused)

add_executable(${PROJECT_NAME} ${SOURCES} src/main.cpp )

target_compile_options(${PROJECT_NAME} PUBLIC ${FLAGS})
add_library(${MODULE_NAME} STATIC ${SOURCES} ${HEADERS}) 

