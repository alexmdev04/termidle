cmake_minimum_required(VERSION 3.28)
project(termidle C)
set(CMAKE_C_STANDARD 23)

set(SOURCES
        main.c
        source/terminalManager.c)
set(HEADERS
        include/terminalManager.h
        include/common.h)

add_executable(termidle ${SOURCES} ${HEADERS})
target_include_directories(termidle PUBLIC ${CMAKE_SOURCE_DIR}/include)