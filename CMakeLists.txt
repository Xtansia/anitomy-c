cmake_minimum_required(VERSION 3.9)
project(anitomy_c)

set(CMAKE_C_STANDARD 99)
set(CMAKE_CXX_STANDARD 14)

if ("${CMAKE_CXX_COMPILER_ID}" MATCHES "Clang" OR "${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
  set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra -Wpedantic -Werror")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wpedantic -Werror")
elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
  set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} /W4 /WX /MP")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4 /WX /MP /EHsc")
endif()

if(CMAKE_CXX_COMPILER_ID MATCHES "AppleClang")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -stdlib=libc++")
  set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} -stdlib=libc++")
endif()

add_library(anitomy_c STATIC
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

install(TARGETS anitomy_c
    ARCHIVE DESTINATION lib)