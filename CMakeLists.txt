cmake_minimum_required(VERSION 3.10)
project(anitomy_c)

set(CMAKE_CXX_STANDARD 14)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wpedantic -Werror")

add_library(anitomy_c
    anitomy_c.cpp
    anitomy_c.h
    anitomy/anitomy/anitomy.cpp
    anitomy/anitomy/anitomy.h
    anitomy/anitomy/element.cpp
    anitomy/anitomy/element.h
    anitomy/anitomy/keyword.cpp
    anitomy/anitomy/keyword.h
    anitomy/anitomy/options.h
    anitomy/anitomy/parser.cpp
    anitomy/anitomy/parser.h
    anitomy/anitomy/parser_helper.cpp
    anitomy/anitomy/parser_number.cpp
    anitomy/anitomy/string.cpp
    anitomy/anitomy/string.h
    anitomy/anitomy/token.cpp
    anitomy/anitomy/token.h
    anitomy/anitomy/tokenizer.cpp
    anitomy/anitomy/tokenizer.h)

add_executable(anitomy_c_test
    testprog.c)
target_link_libraries(anitomy_c_test anitomy_c)